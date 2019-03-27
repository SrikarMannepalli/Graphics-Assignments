#include "main.h"
#include "bomb.h"
#include "plane.h"


Bomb::Bomb(float x, float y, float z) {
	this->set_position(x, y, z);
	this->rotation = 0;
	int p,q;
	int n = 20;
	float vert = 0.1f;
	this->destroyed = false;
	this->width = this->height = this->depth = vert;
	this->object = getObj(vert,vert,vert,0,0,0,COLOR_DARKBLUE);
}

void Bomb::draw(glm::mat4 VP) {
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

void Bomb::set_position(float x, float y,float z) {
	this->position = glm::vec3(x, y, z);
}

void Bomb::tick() {
    this->position.y -=0.01f;
	if(this->position.y<=-2.8f) this->destroyed = true;
}
