#include "enemybarrel.h"
#include "main.h"
#include "plane.h"

extern Plane plane1;
Enemybarrel::Enemybarrel(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->radius = 0.1f;
    this->destroyed = false;
    speed = 1;
    float width = 0.4f;
    float height = 0.1f;
    float depth = 0.5f;
    float cyl_length = 0.5f;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

    int n = 20,p,q;
    float l;
    GLfloat vertex_buffer_data[2*9*n];
    for(int k=0;k<2;k++) {
        if(k == 0) l = 0.0f;
        else l = cyl_length;
        for(int i=0;i<9*n;i+=9) {
                p = (i+1)/9;
                q = p+1;
                vertex_buffer_data[9*n*k+i] = l;
                vertex_buffer_data[9*n*k+i+1] = 0.0f;
                vertex_buffer_data[9*n*k+i+2] = 0.0f;
                vertex_buffer_data[9*n*k+i+3] = l;
                vertex_buffer_data[9*n*k+i+4] = this->radius*(sin((p*M_PI*2)/n));
                vertex_buffer_data[9*n*k+i+5] = this->radius*(cos((p*M_PI*2)/n));
                vertex_buffer_data[9*n*k+i+6] = l;
                vertex_buffer_data[9*n*k+i+7] = this->radius*(sin((q*M_PI*2)/n));
                vertex_buffer_data[9*n*k+i+8] = this->radius*(cos((q*M_PI*2)/n));
            }
    }
    GLfloat vertex_data[18*360];
    for(int i=0;i<360*18;i+=18) {
        vertex_data[i] = 0.0f;
        vertex_data[i+1] = this->radius*cos(glm::radians(float(i/18)));
        vertex_data[i+2] = -this->radius*sin(glm::radians(float(i/18)));
        vertex_data[i+3] = cyl_length;
        vertex_data[i+4] = this->radius*cos(glm::radians(float(i/18)));
        vertex_data[i+5] = -this->radius*sin(glm::radians(float(i/18)));
        vertex_data[i+6] = 0.0f;
        vertex_data[i+7] = this->radius*cos(glm::radians(float(i/18+1)));
        vertex_data[i+8] = -this->radius*sin(glm::radians(float(i/18+1)));
        vertex_data[i+9] = vertex_data[i+6];
        vertex_data[i+10] = vertex_data[i+7];
        vertex_data[i+11] = vertex_data[i+8];
        vertex_data[i+12] = vertex_data[i+3];
        vertex_data[i+13] = vertex_data[i+4];
        vertex_data[i+14] = vertex_data[i+5];
        vertex_data[i+15] = cyl_length;
        vertex_data[i+16] = vertex_data[i+7];
        vertex_data[i+17] = vertex_data[i+8];
    }
    this->object1 = create3DObject(GL_TRIANGLES, 2*n*3, vertex_buffer_data, COLOR_GREY, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 6*360, vertex_data, COLOR_GREY, GL_FILL);
}

void Enemybarrel::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    this->rotation = 45.0f;
    float dz = -this->position.z + plane1.position.z;
    float dx = -this->position.x + plane1.position.x;
    float ang = atan2(dz,dx);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate(-ang, glm::vec3(0, 1, 0));
    rotate    *= glm::rotate(glm::radians(this->rotation), glm::vec3(0,0,1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
}

void Enemybarrel::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void Enemybarrel::tick() {
}