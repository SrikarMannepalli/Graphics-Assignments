#include "main.h"
 
#ifndef FUEL_H
#define FUEL_H

class Fuel {
public:
    Fuel() {}
    Fuel(float x, float y,float z);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void tick();
    float radius;
    float speed;
    int direction;
    void set_position(float x, float y,float z);
    bool on_screen();
    bool destroyed;
private:
    VAO *objectFuel;
    VAO *objectFuelMarker;
};

#endif // FUEL_H
