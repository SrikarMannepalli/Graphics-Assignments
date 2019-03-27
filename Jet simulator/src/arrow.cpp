#include "main.h"
#include "arrow.h"
#include "plane.h"
#include "checkpoints.h"

extern std::vector<Checkpoint> checkpoints;
extern Plane plane1;

Arrow::Arrow(float x, float y, float z) {
	this->set_position(x, y, z);
	this->rotation = 0.0f;
	this->yaw = this->pitch = this->roll = 0;
    this->pitch_vec =glm::vec3 (1,0,0);
    this->yaw_vec =     glm::vec3 (0,1,0);
    this->roll_vec =    glm::vec3 (0,0,-1);
	this->destroyed = true;
	float vert1 = 0.5f;
	float vert2 = 0.1f;
	// Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
	// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
	static const GLfloat vertex_buffer_data1[] = {
		-0.1,-0.3,0,
		0,-0.4,0,
		0.1,-0.3,0
    };

	this->object1 = getObj(0.1,0.3,0,0,0,0,COLOR_DARKRED);
    this->object2 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data1, COLOR_DARKRED, GL_FILL);
    // this->object2 = create3DObject(GL_TRIANGLES, 1*3, vertex_buffer_data2, COLOR_DARKRED, GL_FILL);
}

void Arrow::draw(glm::mat4 VP) {
	float scalex = (abs(this->position.x - plane1.position.x))/4;
	float scaley = (abs(this->position.y - plane1.position.y - 2))/4;
	float scalez = (abs(this->position.z - plane1.position.z))/4;
	if(scalex<1) scalex = 1;
	if(scaley<1) scaley = 1;
	if(scalez<1) scalez = 1;
	float scalef = fmax(fmax(scalex,scaley),scalez);
	Matrices.model = glm::mat4(1.0f);
	glm::mat4 translate = glm::translate (this->position);    // glTranslatef
	// glm::mat4 rotate    = glm::rotate(glm::radians(this->roll), this->roll_vec);
    glm::mat4 rotate    = glm::rotate(this->rotation, glm::vec3(0,1,0));
	glm::mat4 scale     = glm::scale(glm::vec3(scalef,scalef,scalef));
    // rotate    *= glm::rotate(glm::radians(this->pitch), this->pitch_vec);
	// No need as coords centered at 0, 0, 0 of cube around which we want to rotate
	// rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
	Matrices.model *= (translate * rotate*scale);
	glm::mat4 MVP = VP * Matrices.model;
	glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
	draw3DObject(this->object1);
	draw3DObject(this->object2);

}

void Arrow::set_position(float x, float y,float z) {
	this->position = glm::vec3(x, y, z);
}

void Arrow::tick() {
	this->rotation +=90.0f;
}
