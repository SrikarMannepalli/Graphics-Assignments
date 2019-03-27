#include "plane.h"
#include "main.h"

extern int64_t get_time_ms();
extern Plane plane1;

Plane::Plane(float x, float y, float z,color_t color) {
    this->pitch_vec =glm::vec3 (1,0,0);
    this->yaw_vec =     glm::vec3 (0,1,0);
    this->roll_vec =    glm::vec3 (0,0,-1);
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->blinkmode = false;
    this->barrel_mode = false;
    this->loop_mode = false;
    this->barrel = 0.0f;
    this->counter = 0;
    this->loop = 0.0f;
    this->pitch = 0;
    this->fuel = 10000.0f;
    this->health = 100.0f;
    this->yaw = 0;
    this->roll = 0;
    this->speed = 0.01f;
    this->colorNum = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    this->width1 = 0.6f;
    this->height1 = 0.6f;
    this->depth1 = 2.0f;
    this->width2 = 2.6f;
    this->height2 = 0.3f;
    this->depth2 = 0.5f;
    
   
    this->objects.push_back(getObj(0.30, 0.30, 1.0,0,0,0,COLOR_BLACK));   //body
    this->objects.push_back(getObj(0.6,0.15,0.25,0.7,0,0,COLOR_GREY));  //wingleft
    this->objects.push_back(getObj(0.6,0.15,0.25,-0.7,0,0,COLOR_GREY)); //wingright
    // this->objects.push_back(getPyr(COLOR_GREY));

}

VAO* getPyr(color_t color) {
     GLfloat vertex_buffer1 [] = {
        -0.5*plane1.width1, -0.5*plane1.height1 , 0.5*plane1.depth1,
        -0.5*plane1.width1, 0.5*plane1.height1, 0.5*plane1.depth1,
        0.0, 0.0,+0.5*plane1.depth1+0.3,
        0.5*plane1.width1, -0.5*plane1.height1 , 0.5*plane1.depth1,
        0.5*plane1.width1, 0.5*plane1.height1, 0.5*plane1.depth1,
        0.0, 0.0,0.5*plane1.depth1+0.3,
        -0.5*plane1.width1, -0.5*plane1.height1 , 0.5*plane1.depth1,
        0.5*plane1.width1, -0.5*plane1.height1, 0.5*plane1.depth1,
        0.0, 0.0,0.5*plane1.depth1+0.3,
        -0.5*plane1.width1, 0.5*plane1.height1 , 0.5*plane1.depth1,
        0.5*plane1.width1, 0.5*plane1.height1, 0.5*plane1.depth1,
        0.0, 0.0,0.5*plane1.depth1+0.3,
        0.5*plane1.width1, 0.25*plane1.height1,0.5*plane1.depth1,
        0.5*plane1.width1+0.3, 0.25*plane1.height1,0.5*plane1.depth1+0.001,
        0.5*plane1.width1, 0.25*plane1.height1,0.5*plane1.depth1-0.3,
        -0.5*plane1.width1, 0.25*plane1.height1,0.5*plane1.depth1,
        -0.5*plane1.width1-0.3, 0.25*plane1.height1,0.5*plane1.depth1+0.01,
        -0.5*plane1.width1, 0.25*plane1.height1,0.5*plane1.depth1-0.3,
        0,0.5*plane1.height1,0.5*plane1.depth1-0.3,
        0,0.5*plane1.height1,0.5*plane1.depth1,
        0,0.5*plane1.height1+0.2,0.5*plane1.depth1

    };
    return create3DObject(GL_TRIANGLES, 7*3, vertex_buffer1, color, GL_FILL);
}

VAO* getObj(float width, float height, float depth,float shiftx,float shifty,float shiftz, color_t color) {
    GLfloat vertex_buffer_data[] = {
        shiftx-width,shifty-height,shiftz-depth,
        shiftx-width,shifty+height,shiftz-depth,
        shiftx+width,shifty+height,shiftz-depth,
        shiftx-width,shifty-height,shiftz-depth,
        shiftx+width,shifty+height,shiftz-depth,
        shiftx+width,shifty-height,shiftz-depth,
        shiftx-width,shifty-height,shiftz+depth,
        shiftx-width,shifty+height,shiftz+depth,
        shiftx+width,shifty+height,shiftz+depth,
        shiftx-width,shifty-height,shiftz+depth,
        shiftx+width,shifty+height,shiftz+depth,
        shiftx+width,shifty-height,shiftz+depth,
        shiftx-width,shifty-height,shiftz-depth,
        shiftx-width,shifty-height,shiftz+depth,
        shiftx-width,shifty+height,shiftz+depth,
        shiftx-width,shifty+height,shiftz+depth,
        shiftx-width,shifty+height,shiftz-depth,
        shiftx-width,shifty-height,shiftz-depth,
        shiftx+width,shifty-height,shiftz-depth,
        shiftx+width,shifty-height,shiftz+depth,
        shiftx+width,shifty+height,shiftz+depth,
        shiftx+width,shifty+height,shiftz+depth,
        shiftx+width,shifty+height,shiftz-depth,
        shiftx+width,shifty-height,shiftz-depth,
        shiftx+width,shifty+height,shiftz+depth,
        shiftx+width,shifty+height,shiftz-depth,
        shiftx-width,shifty+height,shiftz-depth,
        shiftx-width,shifty+height,shiftz-depth,
        shiftx-width,shifty+height,shiftz+depth,
        shiftx+width,shifty+height,shiftz+depth,
        shiftx+width,shifty-height,shiftz+depth,
        shiftx+width,shifty-height,shiftz-depth,
        shiftx-width,shifty-height,shiftz-depth,
        shiftx-width,shifty-height,shiftz-depth,
        shiftx-width,shifty-height,shiftz+depth,
        shiftx+width,shifty-height,shiftz+depth
    };
    return create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);
}

void Plane::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);   // glTranslatef
    glm::mat4 rotate;
    if(loop_mode) {
        this->loop+=1.0f;
        rotate    = glm::translate(glm::vec3(0,-1,0));
        rotate    *= glm::rotate(glm::radians(this->loop), glm::vec3(1,0,0));
        rotate    *= glm::translate(glm::vec3(0,-1,0));
        if(loop == 360) this->loop_mode = false;
    }
    else if(barrel_mode) {
        this->barrel+=1.0f;
        rotate    = glm::translate(glm::vec3(-2,0,0));
        rotate    *= glm::rotate(glm::radians(this->barrel), glm::vec3(0,0,1));
        rotate    *= glm::translate(glm::vec3(2,0,0));
        if(barrel == 360) this->barrel_mode = false;
    }
    else {
        rotate    = glm::rotate(glm::radians(this->roll), this->roll_vec);
    }
    rotate    *= glm::rotate(glm::radians(this->yaw), this->yaw_vec);
    rotate    *= glm::rotate(glm::radians(this->pitch), this->pitch_vec);
    
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate

    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    for(int i=0;i<this->objects.size();i++) draw3DObject(this->objects[i]);
}

void Plane::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void Plane::tick() {
    this->pitch = 0.0f;
    if(this->speed>0.01) this->speed -= 0.0008f;
    this->position.z-=this->speed*cos(glm::radians(this->yaw));
    this->position.x-=this->speed*sin(glm::radians(this->yaw));
    if(this->fuel<20 || this->blinkmode) {
        this->counter++;
        if(this->counter==15) {
            this->blink();
            this->counter = 0;  
        } 
    }
    else{
        this->objects.clear();
        this->objects.push_back(getObj(0.30, 0.30, 1.0,0,0,0,COLOR_BLACK));   //body
        this->objects.push_back(getObj(0.6,0.15,0.25,0.7,0,0,COLOR_GREY));  //wingleft
        this->objects.push_back(getObj(0.6,0.15,0.25,-0.7,0,0,COLOR_GREY)); //wingright 
        this->objects.push_back(getPyr(COLOR_GREY));
    }
    if(this->position.y<=-0.5) this->health = 0;
}

void Plane::blink() {
    this->objects.clear();
    if(colorNum == 0) {
        this->objects.push_back(getObj(0.30, 0.30, 1.0, 0,0,0,COLOR_GREY));   //body
        this->objects.push_back(getObj(0.6,0.15,0.25,0.7, 0,0,COLOR_BLACK));  //wingleft
        this->objects.push_back(getObj(0.6,0.15,0.25,-0.7,0,0,COLOR_BLACK)); //wingright
        this->objects.push_back(getPyr(COLOR_BLACK));

        colorNum = 1;
    }
    else {
        this->objects.push_back(getObj(0.30, 0.30, 1.0,0,0,0,COLOR_BLACK));   //body
        this->objects.push_back(getObj(0.6,0.15,0.25,0.7,0,0,COLOR_GREY));  //wingleft
        this->objects.push_back(getObj(0.6,0.15,0.25,-0.7,0,0,COLOR_GREY)); //wingright
        this->objects.push_back(getPyr(COLOR_GREY));
        colorNum = 0;
    }
}
