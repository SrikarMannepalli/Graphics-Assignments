#include "main.h"
 
#ifndef SEMI_H
#define SEMI_H

class Semi {
public:
    Semi() {}
    Semi(float x, float y);
    glm::vec3 position;
    float rotation;
    float radius;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    bool on_screen();
private:
    VAO *object1;
    VAO *object2;
};



#endif // SEMI_H
