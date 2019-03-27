#include "main.h"
 
#ifndef MISSILE_H
#define MISSILE_H

class Missile {
public:
    Missile() {}
    Missile(float x, float y,float z,int type);
    glm::vec3 position;
    int type;
    float rotation;
    float vel_hor;
    float vel;
    float dx;
    float dy;
    float dz;
    float norm;
    float width;
    float depth;
    float height;
    float initial_y;
    int64_t initial_time;
    void draw(glm::mat4 VP);
    void tick();
    void set_position(float x, float y,float z);
    bool on_screen();
    bool destroyed;
private:
    VAO *object;
};



#endif // MISSILE_H
