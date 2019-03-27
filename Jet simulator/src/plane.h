#include "main.h"

#ifndef BALL_H
#define BALL_H


class Plane {
public:
    Plane() {}
    Plane(float x, float y, float z,color_t color);
    glm::vec3 position;
    short colorNum;
    bool blinkmode;
    glm::vec3 roll_vec;
    glm::vec3 yaw_vec;
    glm::vec3 pitch_vec;
    float rotation;
    float barrel;
    float loop;
    float pitch;
    float yaw;
    float roll;
    float width1;
    float height1;
    float depth1;
    int counter;
    float width2;
    float height2;
    float depth2;
    float fuel;
    float health;
    float score;
    bool barrel_mode;
    bool loop_mode;
    int64_t init_time;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick();
    void blink();
    double speed;
private:
    std::vector<VAO*>objects;
};

VAO* getPyr(color_t color);
VAO*  getObj(float width, float height, float depth,float shiftx,float shifty,float shiftz, color_t color);

#endif // BALL_H
