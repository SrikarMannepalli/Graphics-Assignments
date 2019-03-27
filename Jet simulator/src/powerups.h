#include "main.h"

#ifndef POWERUPS_H
#define POWERUPS_H


class Powerups {
public:
    Powerups() {}
    Powerups(float x, float y, float z, int type);
    glm::vec3 position;
    float rotation;
    float radius;
    float width;
    float height;
    float depth;
    int type;
    bool destroyed;
    float speed;
    int direction;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick();
    // double speed;
private:
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;
};

#endif // POWERUPS_H