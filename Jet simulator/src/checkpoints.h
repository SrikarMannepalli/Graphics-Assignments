#include "main.h"

#ifndef CHECKPOINT_H
#define CHECKPOINT_H


class Checkpoint {
public:
    Checkpoint() {}
    Checkpoint(float x, float y, float z,color_t color,int type);
    glm::vec3 position;
    float rotation;
    float height;
    float width;
    float depth;
    float radius1;
    float radius2;
    int type;
    bool blinkmode;
    float height_check;
    float width_check;
    float depth_check;
    bool noVolcanoZone;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick();
    double speed;
private:
    VAO *object;
    VAO *object1;
    VAO *object2;
};

#endif // CHECKPOINT_H