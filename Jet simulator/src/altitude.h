#include "main.h"
 
#ifndef ALTITUDE_H
#define ALTITUDE_H

class Altitude {
public:
    Altitude() {}
    Altitude(float x, float y,float z);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void tick();
    float radius;
    void set_position(float x, float y,float z);
    bool on_screen();
    bool destroyed;
private:
    VAO *objectAlt;
    VAO *objectAltMarker;
};

#endif // ALTITUDE_H
