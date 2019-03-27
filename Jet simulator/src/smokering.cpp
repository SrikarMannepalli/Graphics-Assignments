#include "smokering.h"
#include "main.h"

Smokering::Smokering(float x, float y, float z,color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 90.0f;
    this->rotate = 0.0f;
    this->speed = 0.01f;
    int n = 20;
    this->checked = 0;
    float rBig =this->rBig =  1.8f;
    float rSmall = this->rSmall = 0.05f; 
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    int theth = 360;
    GLfloat vertex_buffer_data[4*theth*9*n];
	int p, q;
	this->radius = this->size*0.1;
    int k = 0;
    for(float j=0;j<theth;j+=0.25f) {
        for(int i=0;i<9*n;i+=9) { 
            p = (i+1)/9;
            q = p+1;
            vertex_buffer_data[9*n*k+i] = rBig*cos(glm::radians(float(j)));
            vertex_buffer_data[9*n*k+i+1] = 0.0f;
            vertex_buffer_data[9*n*k+i+2] = -rBig*sin(glm::radians(float(j)));
            vertex_buffer_data[9*n*k+i+3] = rBig*cos(glm::radians(float(j)))+rSmall*(cos((p*M_PI*2)/n));
            vertex_buffer_data[9*n*k+i+4] = rSmall*(sin((p*M_PI*2)/n));
            vertex_buffer_data[9*n*k+i+5] = -rBig*sin(glm::radians(float(j)));
            vertex_buffer_data[9*n*k+i+6] = rBig*cos(glm::radians(float(j)))+rSmall*(cos((q*M_PI*2)/n));
            vertex_buffer_data[9*n*k+i+7] = rSmall*(sin((q*M_PI*2)/n));
            vertex_buffer_data[9*n*k+i+8] = -rBig*sin(glm::radians(float(j)));
        }
        k+=1;
    }
	this->object = create3DObject(GL_TRIANGLES,4*3*theth*n, vertex_buffer_data, color, GL_FILL);
}

void Smokering::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);   // glTranslatef
    glm::mat4 rotate    = glm::rotate(glm::radians(this->rotation), glm::vec3(1,0,0));
    rotate    *= glm::rotate(glm::radians(this->rotate), glm::vec3(0,0,-1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Smokering::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void Smokering::tick() {
    this->rotate += 1.0f;
}
