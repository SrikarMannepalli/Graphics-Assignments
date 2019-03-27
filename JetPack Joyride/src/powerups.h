#include "main.h"

#ifndef POWERUPS_H
#define POWERUPS_H

extern int64_t get_time_ms();
extern const float gravity;

class Powerups {
public:
    Powerups() {}
    Powerups(float x, float y, color_t color, int special_obj,float size);
    glm::vec3 position;
    float radius;
    float rotation;
    bool destroyed;
    int in;
    bool moveable;
    float size;
    int score;
    int more_coins;
    int speedup;
    int water_drop;
    int ice_ball;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
private:
    VAO *object;
};

class Coins : public Powerups {
public:
    Coins() {}
    Coins(float x,float y, color_t color,int special_obj) : Powerups(x,y,color,special_obj,2) {
        moveable = false;
        size = 2;
        if(color.r == 255 && color.g == 242 && color.b == 0) { //yellow coins add 1 to score
            score = 10;
        }
        else if(color.r == 0 && color.g == 164 && color.b == 229) { //blue coins add 2 to score
            score = 20;
        }
        else if(color.r == 152 && color.g == 0 && color.b == 220) { //purple coins add 3 to score
            score = 30;
        }
    }
private:
    VAO * object;
};

class SpecialObj : public Powerups {
public:
    float vel_x;
    float vel_y;
    float initial_posy;
    float angle;
    float previous_posy;
    int64_t initiated_time;
    int64_t previous_time;
    SpecialObj() {}
    SpecialObj(float x,float y, color_t color, int special_obj) : Powerups(x, y,color,special_obj,2) {
        if(special_obj != 3) {
        vel_x = 0.002f;
        vel_y = 0.002f;
        } else {
            vel_x = 0.002f;
            vel_y = 0.0f;
        }
        initial_posy = y;
        previous_posy = y;
        moveable = true;
        initiated_time = get_time_ms();
        previous_time = initiated_time;
        if(special_obj == 1) {
            more_coins = 1;
            speedup = 0;
            water_drop = 0;
            ice_ball = 0;
        }
        else if(special_obj == 2) {
            more_coins = 0;
            speedup = 1;
            water_drop = 0;
            ice_ball = 0;
        }
        else if(special_obj == 3) {
            more_coins = 0;
            speedup = 0;
            water_drop = 1;
            ice_ball = 0;
        }
        else if(special_obj == 4) {
            vel_y = 0.0f;
            vel_x = 0.05f;
            more_coins = 0;
            speedup = 0;
            water_drop = 0;
            ice_ball = 1;
        }
    }
    void move_special_obj(int direction);
private:
    VAO * object;
};

#endif //POWERUPS_H