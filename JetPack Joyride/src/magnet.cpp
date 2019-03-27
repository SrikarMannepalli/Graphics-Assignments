#include "main.h"
#include "magnet.h"

extern float leftmost;
extern float rightmost;
Magnet::Magnet(float x, float y) {
	this->position = glm::vec3(x, y, 0);
	this->rotation = 0;
	float size = 0.5f;
	int p,q;
	int n = 20;
	// Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
	// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
	GLfloat vertex_buffer_data[6*n-30];
	for(int i=0;i<6*n-30;i+=9) {
		p = (i+1)/9;
		q = p+1;
		vertex_buffer_data[i] = 0.0f;
		vertex_buffer_data[i+1] = 0.0f;
		vertex_buffer_data[i+2] = 0.0f;
		vertex_buffer_data[i+3] = size*(cos((p*M_PI*2)/n));
		vertex_buffer_data[i+4] = size*(sin((p*M_PI*2)/n));
		vertex_buffer_data[i+5] = 0.0f;
		vertex_buffer_data[i+6] = size*(cos((q*M_PI*2)/n));
		vertex_buffer_data[i+7] = size*(sin((q*M_PI*2)/n));
		vertex_buffer_data[i+8] = 0.0f;
	}

	this->object1 = create3DObject(GL_TRIANGLES, 2*n - 10, vertex_buffer_data, COLOR_RED, GL_FILL);

	float size2 = 0.3f;
	for(int i=0;i<6*n-30;i+=9) {
		p = (i+1)/9;
		q = p+1;
		vertex_buffer_data[i] = 0.0f;
		vertex_buffer_data[i+1] = 0.0f;
		vertex_buffer_data[i+2] = 0.0f;
		vertex_buffer_data[i+3] = size2*(cos((p*M_PI*2)/n));
		vertex_buffer_data[i+4] = size2*(sin((p*M_PI*2)/n));
		vertex_buffer_data[i+5] = 0.0f;
		vertex_buffer_data[i+6] = size2*(cos((q*M_PI*2)/n));
		vertex_buffer_data[i+7] = size2*(sin((q*M_PI*2)/n));
		vertex_buffer_data[i+8] = 0.0f;
	}
	this->object2 = create3DObject(GL_TRIANGLES, 2*n -10, vertex_buffer_data, COLOR_BACKGROUND, GL_FILL);
	GLfloat buffer_data [] = {
		size2 ,0.0f ,0.0f,
		size, 0.0f, 0.0f,
		size, -0.2f, 0.0f,
		size2 ,0.0f ,0.0f,
		size2, -0.2f, 0.0f,
		size, -0.2f, 0.0f,
		-size2 ,0.0f ,0.0f,
		-size, 0.0f, 0.0f,
		-size, -0.2f, 0.0f,
		-size2 ,0.0f ,0.0f,
		-size2, -0.2f, 0.0f,
		-size, -0.2f, 0.0f
	};
	this->object3 = create3DObject(GL_TRIANGLES, 12, buffer_data, COLOR_RED, GL_FILL);

}

void Magnet::draw(glm::mat4 VP) {
	Matrices.model = glm::mat4(1.0f);
	glm::mat4 translate = glm::translate (this->position);    // glTranslatef
	glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
	// No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
	// rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
	Matrices.model *= (translate * rotate);
	glm::mat4 MVP = VP * Matrices.model;
	glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
	draw3DObject(this->object1);
	draw3DObject(this->object2);
	draw3DObject(this->object3);
}

void Magnet::set_position(float x, float y) {
	this->position = glm::vec3(x, y, 0);
}

bool Magnet::on_screen() {
	if(this->position.x> leftmost && this->position.x<rightmost) {
		return true;
	}
	return false;
}
