#include "obstacles.h"
#include "main.h"
#include "player.h"

extern const float gravity;
extern Player player1;
extern int64_t get_time_ms();
extern float max_height;
extern float leftmost;
extern float rightmost;
extern float min_height;
FireEnemies::FireEnemies(float x,float y,int enemy_type,float angle) {
	//generate random x and y properly with no overlaps and stuff
	this->position_cyl1 = glm::vec3(x, y, 0);
	this->enemy_type = enemy_type;
	this->line_destroyed = false;
	// angle = get_random_angle();
	// angle = 45;
	int n= 20;
	if(enemy_type == 1) {
		angle = 0;
		moveable = true;
	}
	this->direction = 1;
	this->rotation = this->angle=angle;
	float l =3,m=0.02f;
	this->radius = 0.07f;
	this->position_cyl2 = glm::vec3(x+l*cos(angle/180*M_PI),y+l*sin(angle/180*M_PI),0.0f);
	GLfloat vertex_buffer_data[18*n+18];
	float p, q;
	int i,j;
	for(i=0;i<9*n;i+=9) {
		p = (i+1)/9;
		q = p+1;
		vertex_buffer_data[i] = 0.0f;
		vertex_buffer_data[i+1] = 0.0f;
		vertex_buffer_data[i+2] = 0.0f;
		vertex_buffer_data[i+3] = this->radius*(cos((p*M_PI*2)/n));
		vertex_buffer_data[i+4] = this->radius*(sin((p*M_PI*2)/n));
		vertex_buffer_data[i+5] = 0.0f;
		vertex_buffer_data[i+6] = this->radius*(cos((q*M_PI*2)/n));
		vertex_buffer_data[i+7] = this->radius*(sin((q*M_PI*2)/n));
		vertex_buffer_data[i+8] = 0.0f;
	}
	j=i;
	for(i=0;i<9*n;i+=9,j+=9) {
		p = (i+1)/9;
		q = p+1;
		vertex_buffer_data[j] = l+0.0f;
		vertex_buffer_data[j+1] = 0.0f;
		vertex_buffer_data[j+2] = 0.0f;
		vertex_buffer_data[j+3] = l+this->radius*(cos((p*M_PI*2)/n));
		vertex_buffer_data[j+4] =this->radius*(sin((p*M_PI*2)/n));
		vertex_buffer_data[j+5] = 0.0f;
		vertex_buffer_data[j+6] = l+this->radius*(cos((q*M_PI*2)/n));
		vertex_buffer_data[j+7] = this->radius*(sin((q*M_PI*2)/n));
		vertex_buffer_data[j+8] = 0.0f;
	}
	this->object1 = create3DObject(GL_TRIANGLES,6*n, vertex_buffer_data, COLOR_ORANGE, GL_FILL);
	GLfloat buffer_data [] = {
		0.0f, 0.0f, 0.0f,
		0.0f,m,0.0f,
		l,0.0f,0.0f,
		0.0f,m,0.0f,
		l,0.0f,0.0f,
		l,m,0.0f
	};
	this->object2 = create3DObject(GL_TRIANGLES,6, buffer_data, COLOR_DARKRED, GL_FILL);
}

Boomerang::Boomerang(float x,float y,color_t color, int enemy_type) {
	this->position = glm::vec3(x, y, 0);
	this->enemy_type = enemy_type;
	this->rotation = 90.0f;
	this->initiated_time = get_time_ms();
	this->previous_time = this->initiated_time;
	this->vel_x = 0.004f;
	this->vel_y = 0.001f;
	this->initial_posx = x;
	this->max_horizontallength = 3.0f;
	this->moveable = true;
	this->radius = 0.20f;
	int n = 20;
	GLfloat vertex_buffer_data[9*n];
	int p,q;
	for(int i=0;i<9*n;i+=9) {
		p = (i+1)/9;
		q = p+1;
		vertex_buffer_data[i] = 0.0f;
		vertex_buffer_data[i+1] = 0.0f;
		vertex_buffer_data[i+2] = 0.0f;
		vertex_buffer_data[i+3] = this->radius*(cos((p*M_PI*2)/n));
		vertex_buffer_data[i+4] = this->radius*(sin((p*M_PI*2)/n));
		vertex_buffer_data[i+5] = 0.0f;
		vertex_buffer_data[i+6] = this->radius*(cos((q*M_PI*2)/n));
		vertex_buffer_data[i+7] = this->radius*(sin((q*M_PI*2)/n));
		vertex_buffer_data[i+8] = 0.0f;
	}
	this->object = create3DObject(GL_TRIANGLES,n*3, vertex_buffer_data, color, GL_FILL);
}


void FireEnemies::draw(glm::mat4 VP) {
	Matrices.model = glm::mat4(1.0f);
	glm::mat4 translate = glm::translate (this->position_cyl1);    // glTranslatef
	glm::mat4 rotate    = glm::rotate(glm::radians(this->rotation), glm::vec3(0, 0, 1));
	// No need as coords centered at 0, 0, 0 of cube around which we want to rotate
	// rotate          = rotate * glm::translate(this->position_cyl1);
	Matrices.model *= (translate * rotate);
	glm::mat4 MVP = VP * Matrices.model;
	glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
	if(!this->line_destroyed) draw3DObject(this->object2);
	draw3DObject(this->object1);
}

void Boomerang::draw(glm::mat4 VP) {
	Matrices.model = glm::mat4(1.0f);
	glm::mat4 translate = glm::translate (this->position);    // glTranslatef
	glm::mat4 rotate    = glm::rotate(glm::radians(this->rotation), glm::vec3(0, 0, 1));
	// No need as coords centered at 0, 0, 0 of cube around which we want to rotate
	// rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
	Matrices.model *= (translate * rotate);
	glm::mat4 MVP = VP * Matrices.model;
	glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
	draw3DObject(this->object);
}

void Boomerang::move(int direction) {
	int64_t current_time;
	current_time = get_time_ms();
	this->position.y -= direction*vel_y*(current_time - previous_time);   
	this->position.x = this->initial_posx-(vel_x*(current_time - this->initiated_time) - 0.05*gravity*(current_time - this->initiated_time)*(current_time - this->initiated_time));
	this->previous_time = current_time;
	this->previous_posx = this->position.x;
	if(this->position.y-this->radius<=min_height) this->destroyed = true;
}

void FireEnemies::move() {
	if(this->position_cyl1.y+this->radius == max_height-0.5f) {
		this->direction = -1;
	}
	else if(this->position_cyl1.y - this->radius == min_height) {
		this->direction = 1;
	}
	this->position_cyl1.y += this->direction*0.05f;
	this->position_cyl2.y += this->direction*0.05f;
	if(this->direction == 1) {
		if(this->position_cyl1.y+this->radius>max_height-0.5f) {
			this->position_cyl1.y = max_height-0.5f -this->radius;
			this->position_cyl2.y = max_height-0.5f -this->radius;
		}
	}
	else if(this->direction == -1)
	{
		if(this->position_cyl1.y-this->radius<min_height) {
			this->position_cyl1.y = min_height+this->radius; 
			this->position_cyl2.y = min_height+this->radius; 
		}
	}
}

Viserion::Viserion(float x,float y) {
	this->position = glm::vec3(x, y, 0);
	this->rotation = 0.0f;
	this->destroyed = false;
	this->vel_y = 0.00f;
    this->width=this->height = 0.5f;
	static const GLfloat vertex_buffer_data[] = {
		0.0f, 0.0f, 0.0f,
		this->width, 0.0f, 0.0f,
		0.0f, this->height, 0.0f, 
		this->width, 0.0f, 0.0f,
		0.0f, this->height, 0.0f,
		this->width, this->height, 0.0f,
        0.0f,this->height - 0.15f, 0.0f,
        -0.2f,this->height - 0.15f, 0.0f,
        0.0f, this->height - 0.15f - 0.2f,0.0f,
        -0.2f,this->height - 0.15f, 0.0f,
        -0.2f, this->height - 0.15f - 0.2f,0.0f,
        0.0f, this->height - 0.15f - 0.2f,0.0f,
        0.05f, 0.0f,0.0f,
        0.05f, -0.15f,0.0f,
        0.2f, -0.15f, 0.0f,
        0.2f, 0.0f,0.0f,
        0.05f, 0.0f,0.0f,
        0.2, -0.15f, 0.0f,
        this->width-0.05f, 0.0f,0.0f,
        this->width-0.05f, -0.15f,0.0f,
        this->width-0.2f, -0.15f, 0.0f,
        this->width-0.2f, 0.0f,0.0f,
        this->width-0.05f, 0.0f,0.0f,
        this->width-0.2f, -0.15f, 0.0f
	};
	this->object = create3DObject(GL_TRIANGLES,8*3, vertex_buffer_data, COLOR_PURPLE, GL_FILL);
}

void Viserion::draw(glm::mat4 VP) {
	Matrices.model = glm::mat4(1.0f);
	glm::mat4 translate = glm::translate (this->position);    // glTranslatef
	glm::mat4 rotate    = glm::rotate(glm::radians(this->rotation), glm::vec3(0, 0, 1));
	// No need as coords centered at 0, 0, 0 of cube around which we want to rotate
	// rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
	Matrices.model *= (translate * rotate);
	glm::mat4 MVP = VP * Matrices.model;
	glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
	draw3DObject(this->object);
}

void Viserion::move() {
    this->position.y = player1.position.y+0.15f;
	if (player1.position.x>= this->position.x) this->destroyed = true;
}

bool Viserion::on_screen() {
	if(this->position.x> leftmost && this->position.x<rightmost) {
		return true;
	}
	return false;
}

//safety coord boomerang diag
// -vert, 0.0f, 0.0f,
// 0.0f, -vert, 0.0f,
// 0.0f,  vert, 0.0f,
// 0.0f, -vert, 0.0f,
// 0.0f,  vert, 0.0f,
// vert, 0.0f, 0.0f

//safety coord boomerang diag
// 0.0f, 0.0f, 0.0f,
// vert,-0.125 , 0.0f,
// 0.0f, vert-0.15f, 0.0f,
// 0.0f, vert-0.15f, 0.0f,
// -vert,  -0.125, 0.0f,
// 0.0, 0.0f, 0.0f
