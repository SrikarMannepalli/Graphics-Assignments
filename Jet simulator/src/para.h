#include "main.h"

#ifndef PARA_H
#define PARA_H


class Para {
public:
    Para() {}
    Para(float x, float y, float z);
    glm::vec3 position;
    float rotation;
    short direction;
    float height;
    float radius1;
    float radius2;
    bool destroyed;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick();
    double speed;
private:
    std::vector<VAO*>objects;
};

#endif // PARA_H