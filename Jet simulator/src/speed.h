#include "main.h"
 
#ifndef SPEED_H
#define SPEED_H

class Speed {
public:
    Speed() {}
    Speed(float x, float y,float z);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void tick();
    float radius;
    void set_position(float x, float y,float z);
    bool on_screen();
    bool destroyed;
private:
    VAO *objectSpeed;
    VAO *objectSpeedMarker;
};

#endif // SPEED_H
