#include "main.h"
#include "speed.h"
#include "plane.h"
#include "checkpoints.h"

extern Plane plane1;
extern int camera_state;

Speed::Speed(float x, float y, float z) {
	this->set_position(x, y, z);
	this->destroyed = false;
	float vert = 0.1f;
    this->rotation = 0.0f;
	int p,q,n=20;
	this->radius = 0.15f;
	GLfloat vertex_buffer_data[9*n];
	for(int i=0;i<9*n;i+=9) {
		p = (i+1)/9;
		q = p+1;
		vertex_buffer_data[i] = 0.0f;
		vertex_buffer_data[i+1] = 0.0f;
		vertex_buffer_data[i+2] = 0.0f;
		
		vertex_buffer_data[i+3] = this->radius*(sin((p*M_PI*2)/n));
		vertex_buffer_data[i+4] = this->radius*(cos((p*M_PI*2)/n));
		vertex_buffer_data[i+5] = 0.0f;
		vertex_buffer_data[i+6] = this->radius*(sin((q*M_PI*2)/n));
		vertex_buffer_data[i+7] = this->radius*(cos((q*M_PI*2)/n));
		vertex_buffer_data[i+8] = 0.0f;
	}
	GLfloat vertex_buffer_data1[] = {
		-0.1f,0.0f,0.0f,
		0.0f,0.0f,0.0f,
		-0.1f,0.01f,0.0f,
		0.0f,0.0f,0.0f,
		-0.1f,0.01f,0.0f,
		0.0f,0.01f,0.0f
	};
	this->objectSpeed = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data, COLOR_BACKGROUND, GL_FILL);
	this->objectSpeedMarker = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data1, COLOR_DARKRED, GL_FILL);
}

void Speed::draw(glm::mat4 VP2D) {
// 	if(camera_state == 0) this->rotation = 90.0f;
// 	else this->rotation = 0.0f;
	this->rotation = -(180.0*plane1.speed*25);
	if(this->rotation<-180) this->rotation = -180.0f;
	Matrices2D.model = glm::mat4(1.0f);
	glm::mat4 translate = glm::translate (this->position);    // glTranslatef
	glm::mat4 rotate    = glm::rotate(glm::radians(this->rotation), glm::vec3(0,0,1));
	Matrices2D.model *= (translate * rotate);
	glm::mat4 MVP2D = Matrices2D.model;
	glUniformMatrix4fv(Matrices2D.MatrixID, 1, GL_FALSE, &MVP2D[0][0]);
	draw3DObject(this->objectSpeed);
	draw3DObject(this->objectSpeedMarker);

}

void Speed::set_position(float x, float y,float z) {
	this->position = glm::vec3(x, y, z);
}

void Speed::tick() {
	if(plane1.fuel==0) plane1.speed = 0;
}
