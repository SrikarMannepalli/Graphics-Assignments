#include "enemies.h"
#include "enemybarrel.h"
#include "arrow.h"
#include "missile.h"
#include "main.h"
#include "plane.h"

extern Plane plane1;
extern std::vector<Enemybarrel> enemybarrel;
extern std::vector<Missile> enemybullets;
extern std::vector<Arrow> arrows;
extern int64_t get_time_ms();

Enemies::Enemies(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->radius = 0.05f;
    this->destroyed = false;
    speed = 1;
    this->counter = 0;
    this->init_time = get_time_ms();
    float width = this->width = 0.4f;
    float height = this->height = 0.1f;
    float depth = this->depth = 0.5f;
    float cyl_length = 0.5f;
    enemybarrel.push_back(Enemybarrel(x,y,z));
    arrows.push_back(Arrow(x,y+2,z));
    
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

    this->object1 = getObj(width,height,depth,0,0,0,COLOR_BLACK);
}

void Enemies::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    // this->rotation = 90.0f;
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate(glm::radians(this->rotation), glm::vec3(0, 0, 1));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
}

void Enemies::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void Enemies::tick() {
    this->counter++;
    if(this->counter == 300) {
        this->counter = 0;
        enemybullets.push_back(Missile(this->position.x, this->position.y+0.1,this->position.z,1));
        system("aplay ../src/cannon.wav &");
    }
}