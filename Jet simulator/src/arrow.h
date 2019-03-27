#include "main.h"
 
#ifndef ARROW_H
#define ARROW_H

class Arrow {
public:
    Arrow() {}
    Arrow(float x, float y,float z);
    glm::vec3 position;
    glm::vec3 roll_vec;
    glm::vec3 yaw_vec;
    glm::vec3 pitch_vec;
    float rotation;
    float pitch;
    float yaw;
    float roll;
    void draw(glm::mat4 VP);
    void tick();
    void set_position(float x, float y,float z);
    bool on_screen();
    bool destroyed;
private:
    VAO *object1;
    VAO *object2;
};



#endif // ARROW_H
