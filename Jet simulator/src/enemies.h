#include "main.h"

#ifndef ENEMIES_H
#define ENEMIES_H


class Enemies {
public:
    Enemies() {}
    Enemies(float x, float y, float z);
    glm::vec3 position;
    float rotation;
    float radius;
    bool destroyed;
    float width;
    float depth;
    int counter;
    int64_t init_time;
    float height;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick();
    double speed;
private:
    VAO *object1;
    VAO *object2;
    VAO *object3;
};

#endif // ENEMIES_H