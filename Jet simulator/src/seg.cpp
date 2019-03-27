#include "main.h"
#include "plane.h"
#include "seg.h"

using namespace std;

Seg::Seg(float x, float y, float z, color_t color) {
    this-> position = glm::vec3(x,y,z);
    this->rotation = 0.0f;
    this->hor1 = getObj(0.1,0.01,0,0,0,0,COLOR_DARKRED);
    this->hor2 = getObj(0.1,0.01,0,0,0.1,0,COLOR_DARKRED);
    this->hor3 = getObj(0.1,0.01,0,0,-0.1,0,COLOR_DARKRED);
    this->vert1 = getObj(0.01,0.5*0.1,0,-0.1,-0.5*0.1,0,COLOR_DARKRED);
    this->vert2 = getObj(0.01,0.5*0.1,0,0.1,-0.5*0.1,0,COLOR_DARKRED);
    this->vert3 = getObj(0.01,0.5*0.1,0,-0.1,0.5*0.1,0,COLOR_DARKRED);
    this->vert4 = getObj(0.01,0.5*0.1,0,0.1,0.5*0.1,0,COLOR_DARKRED);
};


void Seg::draw(glm::mat4 VP,int digit){
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position); 
    glm::mat4 rotate    = glm::rotate(glm::radians(this->rotation), glm::vec3(0, 0, 1));
	Matrices.model *= (translate*rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    if(digit==2 || digit==3 || digit==4 || digit==5 || digit==6 || digit==8 ||digit==9 ) draw3DObject(this->hor1);
    if(digit == 0 || digit == 2 || digit == 3 || digit == 5 || digit == 6 || digit == 7 || digit == 8 || digit  == 9 ) draw3DObject(this->hor2);
    if(digit ==0 || digit == 2 || digit == 3 || digit == 5 || digit == 6 || digit == 8 ) draw3DObject(this->hor3);
    if(digit == 0 || digit == 2 || digit == 6 || digit == 8) draw3DObject(this->vert1);
    if(digit == 0 || digit == 1 || digit == 3 || digit == 4 || digit == 5 || digit == 6 || digit == 7|| digit == 8 || digit == 9) draw3DObject(this->vert2);
    if(digit == 0 || digit == 1 || digit == 2 || digit == 3 || digit == 4 || digit == 7 || digit == 8 || digit == 9) draw3DObject(this->vert4);
    if(digit == 0 || digit == 4 || digit == 5 || digit == 6 || digit == 8 || digit == 9) draw3DObject(this->vert3);
};
