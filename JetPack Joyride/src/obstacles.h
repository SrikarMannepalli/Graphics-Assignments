#include "main.h"

#ifndef OBSTACLES_H
#define OBSTACLES_H

class FireEnemies {
public:
    float rotation;
    bool moveable;
    int enemy_type;
    float angle;
    float radius;
    int direction;
    glm::vec3 position_cyl1;
    glm::vec3 position_cyl2;
    bool line_destroyed;
    FireEnemies() {}
    FireEnemies(float x,float y, int enemy_type,float angle); //if enemy type is 0, then fire  lines, 1-fire beams
    void draw(glm::mat4 VP);
    void move();
private:
    VAO * object1;
    VAO * object2;
};

class Boomerang {
public:
    float rotation;
    float max_horizontallength;
    bool moveable;
    float vel_x;
    float vel_y;
    float width;
    float radius;
    float height;
    int64_t initiated_time;
    int64_t previous_time;
    float initial_posx;
    float previous_posx;
    glm::vec3 position;
    bool destroyed;
    int enemy_type;
    Boomerang() {}
    Boomerang(float x,float y,color_t color, int enemy_type);
    void draw(glm::mat4 VP);
    void move(int direction);
private:
    VAO * object;
};

class Viserion {
public:
    float rotation;
    float vel_y;
    float width;
    float height;
    glm::vec3 position;
    bool destroyed;
    Viserion() {}
    Viserion(float x,float y);
    void draw(glm::mat4 VP);
    void move();
    bool on_screen();
private:
    VAO * object;
};

#endif //OBSTACLES_H