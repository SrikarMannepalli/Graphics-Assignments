#include "main.h"
 
#ifndef BOMB_H
#define BOMB_H

class Bomb {
public:
    Bomb() {}
    Bomb(float x, float y,float z);
    glm::vec3 position;
    float rotation;
    float yaw;
    float roll;
    float width;
    float height;
    float depth;
    void draw(glm::mat4 VP);
    void tick();
    void set_position(float x, float y,float z);
    bool on_screen();
    bool destroyed;
private:
    VAO *object;
};



#endif // BOMB_H
