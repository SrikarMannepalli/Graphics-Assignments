#include "checkpoints.h"
#include "main.h"
#include "plane.h"
#include "enemies.h"

extern std::vector<Enemies> enemies;
Checkpoint::Checkpoint(float x, float y, float z,color_t color, int type) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->type = type;
    if(type==1) this->noVolcanoZone = true;
    else this->noVolcanoZone = false;
    speed = 1;
    this->blinkmode = false;
    float width = this->width = 1.0f;
    float height =this->height =  0.25f;
    float depth = this->depth = 1.0f;
    float size = 1.5f;
    this->radius1 = 1.0f; 
    this->radius2 = 0.2f;
    if(type == 0) {
        enemies.push_back(Enemies(x,y+height,z));
    }
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    int p,q;
    float rad;
    int n=20;
    float l;
    float cyl_length = 1.2f;
    this->height_check = 1.2f;
    this->width_check = this->radius1;
    this->depth_check = this->radius1;
    this->object = getObj(width,height,depth,0,0,0,color);
    GLfloat vertex_buffer_data[2*9*n];
    for(int k=0;k<2;k++) {
        if(k == 0) {l = 0.0f;rad = this->radius1;}
        else {l = cyl_length;rad = this->radius2;}
        for(int i=0;i<9*n;i+=9) {
                p = (i+1)/9;
                q = p+1;
                vertex_buffer_data[9*n*k+i] = 0.0f;
                vertex_buffer_data[9*n*k+i+1] = l;
                vertex_buffer_data[9*n*k+i+2] = 0.0f;
                vertex_buffer_data[9*n*k+i+3] = rad*(sin((p*M_PI*2)/n));
                vertex_buffer_data[9*n*k+i+4] = l;
                vertex_buffer_data[9*n*k+i+5] = rad*(cos((p*M_PI*2)/n));
                vertex_buffer_data[9*n*k+i+6] = rad*(sin((q*M_PI*2)/n));
                vertex_buffer_data[9*n*k+i+7] = l;
                vertex_buffer_data[9*n*k+i+8] = rad*(cos((q*M_PI*2)/n));
            }
    }
    GLfloat vertex_data[18*360];
    for(int i=0;i<360*18;i+=18) {
        vertex_data[i] = this->radius1*cos(glm::radians(float(i/18)));
        vertex_data[i+1] = 0.0f;
        vertex_data[i+2] = -this->radius1*sin(glm::radians(float(i/18)));
        vertex_data[i+3] = this->radius2*cos(glm::radians(float(i/18)));
        vertex_data[i+4] = cyl_length;
        vertex_data[i+5] = -this->radius2*sin(glm::radians(float(i/18)));
        vertex_data[i+6] = this->radius1*cos(glm::radians(float(i/18+1)));
        vertex_data[i+7] = 0.0f;
        vertex_data[i+8] = -this->radius1*sin(glm::radians(float(i/18+1)));
        vertex_data[i+9] = vertex_data[i+6];
        vertex_data[i+10] = vertex_data[i+7];
        vertex_data[i+11] = vertex_data[i+8];
        vertex_data[i+12] = vertex_data[i+3];
        vertex_data[i+13] = vertex_data[i+4];
        vertex_data[i+14] = vertex_data[i+5];
        vertex_data[i+15] = this->radius2*cos(glm::radians(float(i/18+1)));
        vertex_data[i+16] = cyl_length;
        vertex_data[i+17] = -this->radius2*sin(glm::radians(float(i/18+1)));
    }
	this->object1 = create3DObject(GL_TRIANGLES, 2*3*n, vertex_buffer_data, COLOR_BROWN,GL_FILL) ;
    this->object2 = create3DObject(GL_TRIANGLES, 6*360, vertex_data, COLOR_BROWN, GL_FILL);
}

void Checkpoint::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    if(this->type == 1) {draw3DObject(this->object1);draw3DObject(this->object2);}
}

void Checkpoint::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void Checkpoint::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}
