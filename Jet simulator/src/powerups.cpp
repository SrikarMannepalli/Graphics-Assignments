#include "powerups.h"
#include "main.h"
#include "plane.h"

extern Plane plane1;

Powerups::Powerups(float x, float y, float z, int type) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->type = type;
    this->destroyed = false;
    this->direction = 1;
    this->speed = 0.1f;
    speed = 1;
    float width = this->width = 0.1f;
    float height = this->height = 0.1f;
    float depth = this->depth = 0.1f;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

    this->object1 = getObj(width,height,depth,0,0,0,COLOR_DARKRED);
    GLfloat vertex_buffer_data1 [] = {
        0.08-width,0.033-height,0.0+depth,
        0.08-width,height-0.033,0.0+depth,
        width - 0.08,0.033-height,0.0+depth,
        0.08-width,height-0.033,0.0+depth,
        width - 0.08,0.033-height,0.0+depth,
        width - 0.08,height - 0.033,0.0+depth,
        0.033-width,0.08-height, 0.0+depth,
        0.033-width,height-0.08, 0.0+depth,
        width - 0.033, 0.08-height,0.0+depth,
        width - 0.033, 0.08-height,0.0+depth,
        0.033-width,height-0.08, 0.0+depth,
        width - 0.033,height - 0.08,0.0+depth
    };
    GLfloat vertex_buffer_data2 [] = {
        0.033-width, 0.033 - height,0.0+depth,
        0.033-width, height - 0.033,0.0+depth,
        width-0.033,0.033-height,0.0+depth,
        0.033-width, height - 0.033,0.0+depth,
        width-0.033,0.033-height,0.0+depth,
        width-0.033,height-0.033,0.0+depth
    };
    GLfloat vertex_buffer_data3 [] = {
        width-0.033,height-0.033,0.0+depth,
        width-0.09,height-0.033,0.0+depth,
        width-0.033,height-0.09,0.0+depth
    };
    this->object2 = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data1, COLOR_BACKGROUND, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data2, COLOR_YELLOW, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, 1*3, vertex_buffer_data3, COLOR_DARKRED, GL_FILL);

}

void Powerups::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    // this->rotation = 90.0f;
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate(glm::radians(this->rotation), glm::vec3(0, 0, 1));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    if(this->type == 0) draw3DObject(this->object2);
    else {
        draw3DObject(this->object3);
        draw3DObject(this->object4);
    }
}

void Powerups::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void Powerups::tick() {
    // if(this->direction == 1 && this->position.y-this->speed<=-1) this->direction = -1;
    // else if(this->direction == -1 && this->position.y+this->speed>=5) this->direction = 1;
    // this->position.y -= this->direction*this->speed;
}