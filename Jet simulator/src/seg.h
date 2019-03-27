#include "main.h"

#ifndef SEG_H
#define SEG_H

class Seg
{
  public:
    Seg() {}
    Seg(float x, float y,float z, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP,int dig);
    void tick();
  private:
    VAO* hor1;
    VAO* hor2;
    VAO* hor3;
    VAO* vert1;
    VAO* vert2;
    VAO* vert3;
    VAO* vert4;
};

#endif //SEG_H