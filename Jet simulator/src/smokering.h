#include "main.h"

#ifndef SMOKERING_H
#define SMOKERING_H


class Smokering {
public:
    Smokering() {}
    Smokering(float x, float y, float z,color_t color);
    glm::vec3 position;
    float rotation;
    float rotate;
    float radius;
    float size;
    int checked;
    float rBig;
    float rSmall;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick();
    double speed;
private:
    VAO* object;
};

#endif // SMOKERING_H
