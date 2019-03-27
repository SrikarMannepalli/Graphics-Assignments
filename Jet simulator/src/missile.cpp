#include "main.h"
#include "missile.h"
#include "plane.h"

extern int64_t get_time_ms();
extern Plane plane1;
float gravity = 0.00005f;

Missile::Missile(float x, float y, float z, int type) {
	this->set_position(x, y, z);
	this->rotation = 0;
	int p,q;
    this->initial_y = this->position.y;
    this->vel_hor = 0.2f;
	this->vel = 0.005f;
	int n = 20;
	this->type = type;
	float vert = 0.08f;
	this->width = vert;
	this->height = vert;
	this->depth = vert;
	this->destroyed = false;
	this->dx = this->dy = this->dz = 0.0f;
    this->initial_time = get_time_ms();
	if(type == 1) {
		this->dx = -(plane1.position.x - x);
		this->dy = -(plane1.position.y - y);
		this->dz = -(plane1.position.z - z);
		this->norm = sqrt(this->dx*this->dx+this->dy*this->dy+this->dz*this->dz);
	}
	this->object = getObj(vert,vert,vert,0,0,0,COLOR_DARKBLUE);
}

void Missile::draw(glm::mat4 VP) {
	Matrices.model = glm::mat4(1.0f);
	glm::mat4 translate = glm::translate (this->position);    // glTranslatef
	glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
	// No need as coords centered at 0, 0, 0 of cube around which we want to rotate
	// rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
	Matrices.model *= (translate * rotate);
	glm::mat4 MVP = VP * Matrices.model;
	glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
	draw3DObject(this->object);

}

void Missile::set_position(float x, float y,float z) {
	this->position = glm::vec3(x, y, z);
}

void Missile::tick() {
	if(type == 0) {
		int64_t current_time = get_time_ms();
		this->position.z -= this->vel_hor*cos(glm::radians(plane1.yaw));
		this->position.x -= this->vel_hor*sin(glm::radians(plane1.yaw));
		this->position.y = this->initial_y - (0.5*gravity*(current_time-this->initial_time)*(current_time-this->initial_time));
	}
	else if(type == 1) {	
		this->position.x -= this->vel*this->dx;
		this->position.y -= this->vel*this->dy;
		this->position.z -= this->vel*this->dz;
	}
	if(this->position.y<=-2.8f) this->destroyed = true;
}
