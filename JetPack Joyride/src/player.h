#include "main.h"
 
#ifndef PLAYER_H
#define PLAYER_H


class Player {
public:
    Player() {}
    Player(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    float velocity;
    float width;
    float height;
    int health;
    int  level;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    float move_sidewards(int direction);
    void movesemi(int direction);
    void move_up();
    int lives;
    int score;
private:
    VAO *object;
};

#endif // PLAYER_H
