#include "player.h"
#include "main.h"
#include "semi.h"

extern float max_height;
extern Semi semi;
extern float ang;
extern bool inSemi;
extern int64_t release_time;
extern int64_t previous_time;

Player::Player(float x, float y, color_t color) {
	this->position = glm::vec3(x, y, 0);
	this->rotation = 0;
	this->velocity = 0.05f;
	this->lives = 3;
	this->score = 0;
	this->width = 0.75f;
	this->height = 0.75f;
	this->health = 100;
	// Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
	// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
	static const GLfloat vertex_buffer_data[] = {
		0.0f, 0.0f, 0.0f,
		this->width, 0.0f, 0.0f,
		0.0f, this->height, 0.0f, 
		this->width, 0.0f, 0.0f,
		0.0f, this->height, 0.0f,
		this->width, this->height, 0.0f
	};

	this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color, GL_FILL);
}

void Player::draw(glm::mat4 VP) {
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

void Player::set_position(float x, float y) {
	this->position = glm::vec3(x, y, 0);
}

float Player::move_sidewards(int direction) {
	float jump = this->velocity;
	this->position.x += direction * jump;
	return jump;
}

void Player::move_up() {
	this->position.y += 0.05f;
	system("aplay ../src/mb_jump.wav &");
	if(this->position.y+0.75>max_height-0.5f) this->position.y = max_height-0.5f - 0.75f;
}

void Player::movesemi(int direction) {
	if(ang>180 || ang< 0) {
		release_time = get_time_ms();
		previous_time = release_time;
		this->position.x = semi.position.x+semi.radius+0.001f;
		inSemi = false;
		return;
	}
	// if(this->position.x >= semi.position.x) {
	// 	this->position.x=semi.position.x-this->width-semi.radius+semi.radius*(1-cos(glm::radians(ang)));
	// }
	// else if(this->position.x < semi.position.x)
	// {
	// 	this->position.x=semi.position.x-semi.radius+semi.radius*(1-cos(glm::radians(ang)));
	// }
	this->position.x=semi.position.x-semi.radius+semi.radius*(1-cos(glm::radians(ang)));
	this->position.y=semi.position.y - semi.radius*sin(glm::radians(ang));
}
