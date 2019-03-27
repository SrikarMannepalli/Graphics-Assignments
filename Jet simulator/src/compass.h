#include "main.h"
 
#ifndef COMPASS_H
#define COMPASS_H

class Compass {
public:
    Compass() {}
    Compass(float x, float y,float z);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void tick();
    float radius;
    void set_position(float x, float y,float z);
    bool on_screen();
private:
    VAO *compass;
    VAO *marker1;
    VAO *marker2;
};

#endif // COMPASS_H
