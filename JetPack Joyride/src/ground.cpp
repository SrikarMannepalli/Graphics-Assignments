#include "ground.h"
#include "main.h"

extern float max_height;
Ground::Ground(float x, float y, color_t color) {
	this->position = glm::vec3(x, y, 0);
	this->rotation = 0;
	speed = 0;
	// Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
	// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
	static const GLfloat vertex_buffer_data[] = {
		0.0f, 0.0f, 0.0f,
		0.0f, 1.5f, 0.0f,
		100.0f, 0.0f, 0.0f, 
		100.0f, 0.0f, 0.0f,
		0.0f, 1.5f, 0.0f,
		100.0f, 1.5f, 0.0f,
		0.0f, max_height, 0.0f,
		100.0f, max_height, 0.0f,
		0.0f, max_height - 0.5, 0.0f, 
		100.0f, max_height, 0.0f,
		0.0f, max_height - 0.5, 0.0f,
		100.0f, max_height - 0.5, 0.0f
	};

	this->object = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data, color, GL_FILL);
}

void Ground::draw(glm::mat4 VP) {
	Matrices.model = glm::mat4(1.0f);
	glm::mat4 translate = glm::translate (this->position);    // glTranslatef
	glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
	// No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
	// rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
	Matrices.model *= (translate * rotate);
	glm::mat4 MVP = VP * Matrices.model;
	glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
	draw3DObject(this->object);
}

void Ground::set_position(float x, float y) {
	this->position = glm::vec3(x, y, 0);
}