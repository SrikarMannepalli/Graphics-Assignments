#include "main.h"
#include "timer.h"
#include "player.h"
#include "ground.h"
#include "powerups.h"
#include "obstacles.h"
#include "collisions.h"
#include "magnet.h"
#include "semi.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

Player player1;
Ground ground;
Semi semi;
bool inSemi = false;
float ang;
int cntboom1 = 0;
int cntboom2 = 0;
int cntspc1 = 0;
int lvlcnt = 0;

vector<Coins>coins;
vector<SpecialObj>special_objs;
vector<Magnet>magnets;
Viserion viserion;
extern vector <SpecialObj> water_droplets;
vector<SpecialObj> ice_balls;

vector<Boomerang> booms;
vector<FireEnemies> fire_lasers;
vector<FireEnemies> fire_angles;
int64_t release_time;
int64_t previous_time;
int exist = 0;

char title[100];
float screen_zoom =1.0f;
float maxi = (float)(8.0/screen_zoom);
float max_height = 8.0f;
float rightmost = (float)(8.0/screen_zoom);
float leftmost = (float)(0.0/screen_zoom);
float min_height = 1.5f;
float camera_rotation_angle = 90;
const float gravity = 0.000015f;

Timer t60(1.0 / 60);

// Eye - Location of camera. Don't change unless you are sure!!
glm::vec3 eye (5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
// Target - Where is the camera looking at.  Don't change unless you are sure!!
glm::vec3 target (0, 0, 0);
// Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
glm::vec3 up (0, 1, 0);

glm::mat4 VP;
/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
	// clear the color and depth in the frame buffer
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// use the loaded shader program
	// Don't change unless you know what you are doing
	glUseProgram (programID);

	// Compute Camera matrix (view)
	Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
	// Don't change unless you are sure!!
	// Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

	// Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
	// Don't change unless you are sure!!
	VP = Matrices.projection * Matrices.view;

	// Send our transformation to the currently bound shader, in the "MVP" uniform
	// For each model you render, since the MVP will be different (at least the M part)
	// Don't change unless you are sure!!
	glm::mat4 MVP;  // MVP = Projection * View * Model

    if(player1.lives == -1) {
		system("aplay ../src/mb_die.wav &");
		exit(1);
	}
	// Scene render
	ground.draw(VP);
    for(int i=0;i<coins.size();i++) {
	    if(!coins[i].destroyed) coins[i].draw(VP);
    }
    for(int i=0;i<special_objs.size();i++) {
	    if(!special_objs[i].destroyed) special_objs[i].draw(VP);
    }
    for(int i=0;i<water_droplets.size();i++) {
	    if(!water_droplets[i].destroyed) water_droplets[i].draw(VP);
    }
    for(int i=0;i<booms.size();i++) {
	    if(!booms[i].destroyed) booms[i].draw(VP);
    }
    for(int i=0;i<fire_lasers.size();i++) {
	    fire_lasers[i].draw(VP);
    }
    for(int i=0;i<fire_angles.size();i++) {
	    fire_angles[i].draw(VP);
    }
    for(int i=0;i<magnets.size();i++) {
	    if(!magnets[i].destroyed) magnets[i].draw(VP);
    }
    if(viserion.on_screen() && !viserion.destroyed) viserion.draw(VP);
    for(int i=0;i<ice_balls.size();i++) {
        if(!ice_balls[i].destroyed)ice_balls[i].draw(VP);
    }
	semi.draw(VP);
	player1.draw(VP);
}

bool compareIntervalCoins(Coins c1, Coins c2)  { 
    return (c1.position.x < c2.position.x); 
} 

bool compareIntervalSpec(SpecialObj c1, SpecialObj c2) { 
    return (c1.position.x < c2.position.x); 
} 

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
	/* Objects should be created before any other gl function and shaders */
	// Create the models
	create_map();
	
    // sort(coins.begin(),coins.end(),compareIntervalCoins);
    // sort(special_objs.begin(),special_objs.end(),compareIntervalSpec);
	// Create and compile our GLSL program from the shaders
	programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
	// Get a handle for our "MVP" uniform
	Matrices.MatrixID = glGetUniformLocation(programID, "MVP");

	reshapeWindow (window, width, height);

	// Background color of the scene
	glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
	glClearDepth (1.0f);

	glEnable (GL_DEPTH_TEST);
	glDepthFunc (GL_LEQUAL);

	cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
	cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
	cout << "VERSION: " << glGetString(GL_VERSION) << endl;
	cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}

int chk = 0;
int main(int argc, char **argv) {
	srand(time(0));
	int width  = 800;
	int height = 800;

	window = initGLFW(width, height);
	system("aplay ../src/mb_new.wav &");
	initGL (window, width, height);
	player1.level = 1;


	/* Draw in loop */
	while (!glfwWindowShouldClose(window)) {
		// std::cout<<leftmost<<std::endl;
		if(leftmost>13 && lvlcnt == 0) {
			lvlcnt = 1;
			system("aplay ../src/mb_new.wav &");
			player1.level = 2;
		}
		if(leftmost>17 && cntboom2 ==0) {
			cntboom2++;
			booms.push_back(Boomerang(26, 7.5, COLOR_BROWN, 2));
		}
		if(leftmost>15 && cntboom1 ==0) {
			cntboom1++;
			booms.push_back(Boomerang(24, 7.5, COLOR_BROWN, 2));
		} 
		if(leftmost>18 && cntspc1==0) {
			cntspc1++;
			magnets.push_back(Magnet(36,7));
			special_objs.push_back(SpecialObj(22, 5, COLOR_LIGHTRED, 1));
			special_objs.push_back(SpecialObj(22, 6, COLOR_RED, 2));
		}
		if(player1.position.x >=42) {
			sprintf(title,"GAME CONQUERED");
			system("aplay ../src/smb_world_clear.wav");
			exit(1);
		}
        int check =0;
		// Process timers
		if (t60.processTick()) {
			// 60 fps
			// OpenGL Draw commands
			draw();
			process_input(window);
            for(int i=0;i<magnets.size();i++) {
                if(!magnets[i].destroyed && magnets[i].on_screen()) {
                    check = 1;
                    attract_magnet(i);
                }
            }
            if(!check && !inSemi) check_down_movement(window);
            for(int i=0;i<special_objs.size();i++) {
			    if(!special_objs[i].destroyed) special_objs[i].move_special_obj(1);
            }
            for(int i=0;i<water_droplets.size();i++) {
			    if(!water_droplets[i].destroyed) water_droplets[i].move_special_obj(1);
            }
            for(int i=0;i<booms.size();i++) {
			    if(!booms[i].destroyed) booms[i].move(1);
            }
            for(int i=0;i<fire_lasers.size();i++) {
			    fire_lasers[i].move();
            }
            if(viserion.on_screen() && !viserion.destroyed) {
                viserion.move();
				if(rand()%10==2)ice_balls.push_back(SpecialObj(viserion.position.x,viserion.position.y,COLOR_GREY,4));
            }
            for(int i=0;i<ice_balls.size();i++) {
                if(!ice_balls[i].destroyed) ice_balls[i].move_special_obj(-1);
            }
            for(int i=0;i<coins.size();i++) {
			    if(!coins[i].destroyed) detect_coll_coins(&player1,&coins[i]);
            }
            for(int i=0;i<special_objs.size();i++) {
			    if(!special_objs[i].destroyed) detect_coll_specialObj(&player1,&special_objs[i]);
            }
            for(int i=0;i<fire_angles.size();i++) {
			    if(!fire_angles[i].line_destroyed)detect_coll_fireEnemies(&player1,&fire_angles[i]);
            }
            for(int i=0;i<fire_lasers.size();i++) {
			    if(!fire_lasers[i].line_destroyed)detect_coll_fireEnemies(&player1,&fire_lasers[i]);
            }
            for(int i=0;i<water_droplets.size();i++) {
                for(int j=0;j<fire_angles.size();j++) {
			        if(!water_droplets[i].destroyed && !fire_angles[j].line_destroyed)detect_coll_water_line(&water_droplets[i],&fire_angles[j]);
                }
            }
            for(int i=0;i<water_droplets.size();i++) {
                for(int j=0;j<fire_lasers.size();j++) {
			        if(!water_droplets[i].destroyed && !fire_lasers[j].line_destroyed)detect_coll_water_line(&water_droplets[i],&fire_lasers[j]);
                }
            }
            for(int i=0;i<booms.size();i++) {
                if(!booms[i].destroyed) detect_coll_boomerang(&player1, &booms[i]);
            }
            for(int i=0;i<ice_balls.size();i++) {
                if(!ice_balls[i].destroyed) detect_coll_specialObj(&player1,&ice_balls[i]);
            }
			if(player1.lives!=-1) sprintf(title,"JETPACK JOYRIDE LEVEL :%d,SCORE:%d  HEALTH:%d  LIVES: %d",player1.level,player1.score,player1.health,player1.lives);
            // if(magnet_onscreen()) attract_magnet();
            glfwSetWindowTitle(window, title);
			// Swap Frame Buffer in double buffering
			glfwSwapBuffers(window);
		}
		// Poll for Keyboard and mouse events
		glfwPollEvents();
	}
	quit(window);
}


void attract_magnet(int magnum) {
    // float m = (magnet.position.y-player1.position.y)/(magnet.position.x-player1.position.x);
    float vel = 0.8f;
    player1.position.x+=(magnets[magnum].position.x-player1.position.x)/35;
    player1.position.y+=(magnets[magnum].position.y-player1.position.y)/25;
    float dist = sqrt((magnets[magnum].position.x-0.5f-player1.position.x)*(magnets[magnum].position.x-player1.position.x)+(magnets[magnum].position.y-0.2-player1.position.y)*(magnets[magnum].position.y-player1.position.y));
    float rando = (float)(rand()%200)/100;
    if(!rando) rando=1.0f;
    if(dist <= rando) {
        release_time = get_time_ms();
		previous_time = release_time;
        magnets[magnum].destroyed = true;
    }
}

void process_input(GLFWwindow *window) {
	int left  = glfwGetKey(window, GLFW_KEY_LEFT);
	int right = glfwGetKey(window, GLFW_KEY_RIGHT);
	int escape = glfwGetKey(window, GLFW_KEY_ESCAPE);
	int up = glfwGetKey(window, GLFW_KEY_SPACE);
	int s_key = glfwGetKey(window,GLFW_KEY_S);
	float velocity;
	if (left) {
		if(!inSemi && player1.position.x >leftmost) velocity = player1.move_sidewards(-1);
		if(inSemi) {ang-=1;player1.movesemi(-1);}
	}
	else if(right) {
		if(!inSemi){
			velocity = player1.move_sidewards(1);
			if(player1.position.x>0.5*(rightmost+leftmost)) {
				move_camera(velocity,1);
			}
		}
		else {
			ang+=1;
			player1.movesemi(1);
			if(player1.position.x>0.5*(rightmost+leftmost)) {
			move_camera(velocity,1);
			}
		}
	}
	else if(up && !inSemi) {
		if(player1.position.y<=max_height-1.25) player1.move_up();
		release_time = get_time_ms();
		previous_time = release_time;
	}
	else if(escape) {
		quit(window);
	}
}

void move_camera(float jump, int direction) {
	eye.x += direction*jump;
	target.x += direction*jump;
	leftmost += direction*jump;
	rightmost += direction*jump;
}

void check_down_movement(GLFWwindow *window) {
	int64_t current_time = get_time_ms();
	if(player1.position.y > 1.5f){
		player1.position.y-=((0.5*gravity*(current_time-release_time)*(current_time-release_time))-(0.5*gravity*(previous_time-release_time)*(previous_time-release_time)));
		previous_time = current_time;
		if(player1.position.y < 1.5f) player1.position.y = 1.5f;
		if(player1.position.x>semi.position.x-semi.radius && player1.position.x<semi.position.x+semi.radius && player1.position.y<=semi.position.y &&player1.position.y>semi.position.y-semi.radius){
			inSemi = true;
			ang = 0;
			player1.position.x = semi.position.x - semi.radius+0.1f;
			player1.position.y = semi.position.y;
		}
	}
}

void reset_screen() {
	float top    =  8 / screen_zoom;
	float bottom = 0.0f;
	float left   = 0.0f;
	float right  =  8 / screen_zoom;
	Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}

int64_t get_time_ms() {
	int64_t nowms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	return nowms;
}

void create_map() {
	player1           = Player(0, 1.5f, COLOR_BLACK);
	ground            = Ground(0, 0, COLOR_GREY);
	for(int j=4;j<8;j++) {
    for(int i=4;i<8;i++) {
	    coins.push_back(Coins((float)j/2, (float)i/2, COLOR_BLUE,0));
    }
	}
	for(int j=4;j<8;j++) {
    for(int i=8;i<12;i++) {
	    coins.push_back(Coins((float)j/2, (float)i/2, COLOR_YELLOW,0));
    }
	}
	for(int j=4;j<8;j++) {
    for(int i=12;i<15;i++) {
	    coins.push_back(Coins((float)j/2, (float)i/2, COLOR_PURPLE,0));
    }
	}
	booms.push_back(Boomerang(5, 7.5, COLOR_BROWN, 2));
	fire_lasers.push_back(FireEnemies(6, 7 , 1,0.0));
	fire_lasers.push_back(FireEnemies(9, 4 , 1,0.0));
	for(int j=14;j<20;j++) {
    for(int i=6;i<10;i++) {
	    coins.push_back(Coins((float)j/2, (float)i/2, COLOR_YELLOW,0));
    }
	}
	fire_angles.push_back(FireEnemies(13, 4 , 0,45.0));
	for(int j=26;j<30;j++) {
    for(int i=10;i<14;i++) {
	    coins.push_back(Coins((float)j/2, (float)i/2, COLOR_PURPLE,0));
    }
	}
	special_objs.push_back(SpecialObj(2, 5, COLOR_RED, 2));


	fire_angles.push_back(FireEnemies(20.5, 4 , 0,-45.0));
	fire_lasers.push_back(FireEnemies(23, 4 , 1 ,0.0));
	fire_lasers.push_back(FireEnemies(26, 5 , 1 ,0.0));
	fire_angles.push_back(FireEnemies(29, 2 , 0,45.0));
	fire_angles.push_back(FireEnemies(33, 2 , 0,0.0));
	fire_angles.push_back(FireEnemies(33, 3 , 0,0.0));
	fire_angles.push_back(FireEnemies(36, 3 , 0,0.0));
	fire_angles.push_back(FireEnemies(36, 4 , 0,0.0));
	semi 			  = Semi(38, 6);
	magnets.push_back(Magnet(16,7));
    viserion          = Viserion(18,5);
}