#include "main.h"

#ifndef ENEMYBARREL_H
#define ENEMYBARREL_H


class Enemybarrel {
public:
    Enemybarrel() {}
    Enemybarrel(float x, float y, float z);
    glm::vec3 position;
    float rotation;
    float radius;
    bool destroyed;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick();
    double speed;
private:
    VAO *object1;
    VAO *object2;
};

#endif // ENEMYBARREL_H