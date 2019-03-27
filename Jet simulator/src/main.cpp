#include "main.h"
#include "timer.h"
#include "plane.h"
#include "sea.h"
#include "arrow.h"
#include "bomb.h"
#include "missile.h"
#include "checkpoints.h"
#include "speed.h"
#include "altitude.h"
#include "fuel.h"
#include "enemies.h"
#include "enemybarrel.h"
#include "smokering.h"
#include "powerups.h"
#include "para.h"
#include "collisions.h"
#include "compass.h"
#include "seg.h"

using namespace std;

GLMatrices Matrices;
GLMatrices Matrices2D;
GLuint     programID;
GLFWwindow *window;

char title[100];
Plane plane1;
Sea sea;
vector<Para> paras;
vector<Smokering> smokerings;
vector<Enemybarrel> enemybarrel;
Speed speedometer;
Altitude altimeter;
Fuel fuelometer;
Compass compass;
vector<Enemies> enemies;
vector<Bomb> bombs;
vector<Missile> missiles;
vector<Missile> enemybullets;
vector<Checkpoint> checkpoints;
vector<Checkpoint> volcanoes;
vector<Powerups> powerups;
vector<Arrow>arrows;
Seg units;
Seg tens;
Seg hundreds;
Seg thous;
Seg tenthous;
Seg health_units;
Seg health_tens;
Seg health_hundreds;

int score=0;
extern glm::vec3 eye;
extern glm::vec3 target;
extern glm::vec3 up;

glm::vec3 eye2D (0, 0, 5);
glm::vec3 target2D (0, 0, -10);
glm::vec3 up2D (0,1,0);

double mousex,mousey;
float helirotx=0.0f;
float heliroty=0.0f;
int camFlag = 1;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
int camera_state = 0;
float helirad = 5.0f/screen_zoom;

Timer t60(1.0 / 60);

void draw() {
    // clear the color and depth in the frame buffer

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    if(camFlag == 1) {
        camera_state = 0;
        eye = plane1.position;
        eye.z-=cos(glm::radians(plane1.yaw))*cos(glm::radians(plane1.pitch));
        eye.x-=sin(glm::radians(plane1.yaw))*cos(glm::radians(plane1.pitch));
        eye.y-=sin(glm::radians(plane1.pitch));
        target = plane1.position;
        target.z -= 3.0*cos(glm::radians(plane1.yaw));
        target.x -= 3.0*sin(glm::radians(plane1.yaw));
        target.y -= plane1.position.y;
        up =glm::vec3 (-sin(glm::radians(plane1.roll))*cos(glm::radians(plane1.yaw)),cos(glm::radians(plane1.roll)),-sin(glm::radians(plane1.roll))*sin(glm::radians(plane1.yaw)));
    }
    else if(camFlag == 0) {
        camera_state = 1;

        eye = plane1.position + glm::vec3(0,5,0);
        target = plane1.position;
        up = glm::vec3(0,0,-1);
    }
    else if(camFlag == 2) {
        camera_state = 1;

        eye = glm::vec3(0,4,10);
        // target = glm::vec3(0,0,-20);
        target = plane1.position;
        up = glm::vec3(0,1,0);
    }
    else if(camFlag == 3) {
        camera_state = 1;

        eye = plane1.position + glm::vec3(5*sin(glm::radians(plane1.yaw)), 2, 5*cos(glm::radians(plane1.yaw)));
        target = plane1.position;
        up = glm::vec3(0,1,0);
    }
    else if(camFlag == 4) {
        glfwGetCursorPos(window,&mousex,&mousey);
        if(mousex>900) heliroty +=1.0f;
        else if(mousex<100) heliroty-=1.0f;

        if(mousey>700) helirotx-=1.0f;
        else if(mousey<100) helirotx+=1.0f;

        helirad = 5.0f/screen_zoom;
        eye.x = plane1.position.x +helirad*sin(glm::radians(heliroty))*cos(glm::radians(helirotx));
        eye.y = plane1.position.y +helirad*sin(glm::radians(heliroty))*sin(glm::radians(helirotx));
        eye.z = plane1.position.z -helirad*cos(glm::radians(heliroty))*cos(glm::radians(helirotx));
        target = plane1.position;
        up = glm::vec3(0,1,0);
    }

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    glm::mat4 VP = Matrices.projection * Matrices.view;
    glm::mat4 MVP;  // MVP = Projection * View * Model
    
    Matrices2D.view = glm::lookAt( eye2D, target2D, up2D ); // Rotating Camera for 3D
    glm::mat4 VP2D = Matrices2D.projection * Matrices2D.view;
    glm::mat4 MVP2D;  // MVP = Projection * View * Model

    // Scene render
    plane1.draw(VP);
    sea.draw(VP);
    for(int i=0;i<bombs.size();i++) {
        if(!bombs[i].destroyed) bombs[i].draw(VP);
    }
    for(int i=0;i<checkpoints.size();i++) checkpoints[i].draw(VP);
    for(int i=0;i<missiles.size();i++) {
        if(!missiles[i].destroyed) missiles[i].draw(VP);
    }
    for(int i=0;i<arrows.size();i++) {
        if(!arrows[i].destroyed) arrows[i].draw(VP);
    }
    for(int i=0;i<smokerings.size();i++) smokerings[i].draw(VP);
    speedometer.draw(VP2D);
    
    for(int i=0;i<enemies.size();i++) {
        if(!enemies[i].destroyed) {
            enemies[i].draw(VP);
            enemybarrel[i].draw(VP);
        }
    }
    for(int i=0;i<powerups.size();i++) {
        if(!powerups[i].destroyed) powerups[i].draw(VP);
    }
    for(int i=0;i<paras.size();i++) {
        if(!paras[i].destroyed) paras[i].draw(VP);
    }
    for(int i=0;i<enemybullets.size();i++) {
        if(!enemybullets[i].destroyed) enemybullets[i].draw(VP);
    }
    for(int i=0;i<volcanoes.size();i++) volcanoes[i].draw(VP);
    fuelometer.draw(VP2D);
    altimeter.draw(VP2D);
    compass.draw(VP2D);
    int temp = score;
    units.draw(VP2D,temp%10);
    temp/=10;
    tens.draw(VP2D,temp%10);
    temp/=10;
    hundreds.draw(VP2D,temp%10);
    temp/=10;
    thous.draw(VP2D,temp%10);
    temp/=10;
    tenthous.draw(VP2D,temp%10);
    temp = plane1.health;
    health_units.draw(VP2D,temp%10);
    temp/=10;
    health_tens.draw(VP2D,temp%10);
    temp/=10;
    health_hundreds.draw(VP2D,temp%10);
}

void tick_input(GLFWwindow *window) {
    int w_butt = glfwGetKey(window, GLFW_KEY_W);
    int t_butt = glfwGetKey(window, GLFW_KEY_T);
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int a_butt = glfwGetKey(window, GLFW_KEY_A);
    int s_butt = glfwGetKey(window, GLFW_KEY_S);
    int d_butt = glfwGetKey(window, GLFW_KEY_D);
    int q_butt = glfwGetKey(window, GLFW_KEY_Q);
    int e_butt = glfwGetKey(window, GLFW_KEY_E);
    int f_butt = glfwGetKey(window, GLFW_KEY_F);
    int h_butt = glfwGetKey(window, GLFW_KEY_H);
    int b_butt = glfwGetKey(window, GLFW_KEY_B);
    int l_butt = glfwGetKey(window, GLFW_KEY_L);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    if (a_butt && plane1.fuel>0) {
        if(plane1.roll>-45) plane1.roll-=0.5;
    }
    else if(d_butt && plane1.fuel>0) {
        if(plane1.roll<45) plane1.roll+=0.5;    
    }
    else if(q_butt && plane1.fuel>0) {
        // if(plane1.yaw<180) 
            plane1.yaw+=0.5;
        if(plane1.roll>-2.5) plane1.roll-=0.5;
    }
    else if(e_butt && plane1.fuel>0) {
        // if(plane1.yaw>-180) 
            plane1.yaw-=0.5;
        if(plane1.roll<2.5) plane1.roll+=0.5;   
    }
    else if(w_butt && plane1.fuel>0) {
        if(plane1.speed<0.04) plane1.speed +=0.003;
    }
    else if(s_butt) {
        if(plane1.speed-0.003>=0) plane1.speed -= 0.0003;
        else plane1.speed = 0;
    }
    else if(space) {
        plane1.position.y +=0.05f;
        plane1.pitch = 45.0f;
    }
    else if(down) {
        if(plane1.position.y>=-2.65f) plane1.position.y -=0.05f;
        plane1.pitch = -45.0f;
    }
    else if(left) { //top view
        camFlag = 0;
    }
    else if(right) { //first person view
        camFlag = 1;
    }
    else if(t_butt) { //tower view
        camFlag = 2;
    }
    else if(f_butt) { //follow cam view
        camFlag = 3;
    }
    else if(h_butt) { //helicopter view
        camFlag = 4;
    }
    else if(b_butt) {
        plane1.barrel_mode = true;
    }
    else if(l_butt) {
        plane1.loop_mode = true;
    }
}



int check =0;
int check1 =0;
void tick_elements() {
    score+=1;
    check = 0;
    for(int i=0;i<volcanoes.size();i++) {
        if(volcanoes[i].blinkmode) {
            check = 1;
            break;
        }
    }
    if(check == 1) {
        plane1.blinkmode = true;
    }
    else {
        plane1.blinkmode = false;
    }
    plane1.tick();
    for(int i=0;i<smokerings.size();i++) {
        if(!smokerings[i].checked) detect_coll_plane_smokering(&plane1,&smokerings[i]);
    }
    for(int i=0;i<powerups.size();i++) {
        if(!powerups[i].destroyed) powerups[i].tick();
    }
    for(int i=0;i<enemies.size();i++) {
        if(!enemies[i].destroyed) {
            arrows[i].destroyed = false;
            break;
        }
    }
    for(int i=0;i<enemies.size();i++) {
        if(!enemies[i].destroyed) {
            enemies[i].tick();
        }
    }
    for(int i=0;i<arrows.size();i++) {
        if(!arrows[i].destroyed) arrows[i].tick();
    }
    for(int i=0;i<powerups.size();i++) {
        if(!powerups[i].destroyed) detect_coll_powerups_plane(&plane1, &powerups[i]);
    }
    for(int i=0;i<missiles.size();i++) {
        if(!missiles[i].destroyed) {
            missiles[i].tick();
            for(int j=0;j<enemies.size();j++) { 
                if(!enemies[j].destroyed) detect_coll_enemy_missile(&enemies[j], &missiles[i],&arrows[j]);
            }
            for(int j=0;j<paras.size();j++) {
                if(!paras[j].destroyed) detect_coll_paras_missile(&paras[j],&missiles[i]);
            }
        }
    }
    for(int i=0;i<bombs.size();i++) {
        if(!bombs[i].destroyed) {
            bombs[i].tick();
            for(int j=0;j<enemies.size();j++) { 
                if(!enemies[j].destroyed) detect_coll_enemy_bomb(&enemies[j], &bombs[i],&arrows[j]);
            }
            for(int j=0;j<paras.size();j++) {
                if(!paras[j].destroyed) detect_coll_paras_bomb(&paras[j],&bombs[i]);
            }
        }
    }
    for(int i=0;i<enemybullets.size();i++) {
        if(!enemybullets[i].destroyed) {
            enemybullets[i].tick();
            detect_coll_enebull_plane(&plane1,&enemybullets[i]);
        }
    }
    for(int i=0;i<paras.size();i++) {
        if(!paras[i].destroyed) {
            paras[i].tick();
            detect_coll_para_plane(&plane1,&paras[i]);
        }
    }
    for(int i=0;i<volcanoes.size();i++) detect_coll_plane_vol(&plane1,&volcanoes[i]);
    fuelometer.tick();
    speedometer.tick();
    check1 = 0;
    for(int i=0;i<enemies.size();i++) {
        if(!enemies[i].destroyed) check1 = 1;
    }
    if(check1 == 0) {
        sprintf(title,"You won!!!");
        system("aplay ../src/winning.wav");
        exit(-1);
    }
    
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    eye = glm::vec3(0,-3,5);
    target = glm::vec3(0,-3,5.5);
    up = glm::vec3(0,1,0);
    map1();
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


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 1000;
    int height = 800;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();

            // Swap Frame Buffer in double buffering

            tick_elements();
            tick_input(window);
			sprintf(title,"JET FIGHTER");
            if(plane1.health <= 0) {
                sprintf(title,"No Health");
                system("aplay ../src/die.wav");
                exit(-1);
            }
            else if(plane1.position.y<=-1.0f) {
                system("aplay ../src/die.wav");
                sprintf(title,"Low altitude");
                exit(-1);
            }
            glfwSetWindowTitle(window, title);
            glfwSwapBuffers(window);

        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left  = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
	Matrices2D.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}


int64_t get_time_ms() {
	int64_t nowms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	return nowms;
}


void map1() {
    plane1       = Plane(0, 0, 6,COLOR_RED);
    sea         = Sea(0,-3,0,COLOR_BLUE);
    checkpoints.push_back(Checkpoint(0,-3,0,COLOR_GREEN,0));
    checkpoints.push_back(Checkpoint(0,-3,-15,COLOR_GREEN,0));
    checkpoints.push_back(Checkpoint(-10,-3,-5,COLOR_GREEN,0));
    checkpoints.push_back(Checkpoint(8,-3,2,COLOR_GREEN,0));
    checkpoints.push_back(Checkpoint(3,-3,-24,COLOR_GREEN,0));
    volcanoes.push_back(Checkpoint(2,-3,-8,COLOR_GREEN,1));
    volcanoes.push_back(Checkpoint(-2,-3,8,COLOR_GREEN,1));
    // enemybullets.push_back(Missile(0,-3+checkpoints[0].height,0,1));
    paras.push_back(Para(0,2,-6));
    paras.push_back(Para(0,2,-8));
    paras.push_back(Para(2,2,-1));
    paras.push_back(Para(-2,2,-4));
    compass = Compass(2,2,0);
    smokerings.push_back(Smokering(0, 0 , -5,COLOR_RED));
    smokerings.push_back(Smokering(0, 0 , -7,COLOR_RED));
    smokerings.push_back(Smokering(0, 0 , -9,COLOR_RED));
    plane1.init_time = get_time_ms();
    
    powerups.push_back(Powerups(0,0,2,1));
    powerups.push_back(Powerups(0,0,-5,0));
    powerups.push_back(Powerups(0,0,-7,1));
    powerups.push_back(Powerups(0,0,-9,0));
    speedometer = Speed(-0.75,-0.75,0);
    fuelometer = Fuel(-0.00,-0.75,0);
    altimeter = Altitude(0.75,-0.75,0);
    units = Seg(-2,2,0,COLOR_DARKRED);
    tens = Seg(-2.3,2,0,COLOR_DARKRED);
    hundreds = Seg(-2.6,2,0,COLOR_DARKRED);
    thous = Seg(-2.9,2,0,COLOR_DARKRED);
    tenthous = Seg(-3.2,2,0,COLOR_DARKRED);
    health_units = Seg(-2,2-0.3,0,COLOR_DARKRED);
    health_tens = Seg(-2.3,2-0.3,0,COLOR_DARKRED);
    health_hundreds = Seg(-2.6,2-0.3,0,COLOR_DARKRED);
}