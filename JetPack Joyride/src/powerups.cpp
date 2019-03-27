#include "powerups.h"
#include "main.h"
#include "player.h"

extern int64_t get_time_ms();
extern const float gravity;
extern Player player1;
extern float min_height;
extern float leftmost;
extern float rightmost;

Powerups::Powerups(float x, float y, color_t color,int special_obj,float size) {
	this->destroyed = false;
	this->position = glm::vec3(x, y, 0);
	this->rotation = 0;
	int n = 20;
	this->in = 0;
	this->size = size;
	GLfloat vertex_buffer_data[9*n];
	int p, q;
	if(special_obj == 3 || special_obj == 4) {
		this->size = 0.625f;
	}
	if(special_obj == 0) {
		n = 6;
	}
	this->radius = this->size*0.1;
	for(int i=0;i<9*n;i+=9) {
		p = (i+1)/9;
		q = p+1;
		vertex_buffer_data[i] = 0.0f;
		vertex_buffer_data[i+1] = 0.0f;
		vertex_buffer_data[i+2] = 0.0f;
		vertex_buffer_data[i+3] = this->size*0.1*(cos((p*M_PI*2)/n));
		vertex_buffer_data[i+4] = this->size*0.1*(sin((p*M_PI*2)/n));
		vertex_buffer_data[i+5] = 0.0f;
		vertex_buffer_data[i+6] = this->size*0.1*(cos((q*M_PI*2)/n));
		vertex_buffer_data[i+7] = this->size*0.1*(sin((q*M_PI*2)/n));
		vertex_buffer_data[i+8] = 0.0f;
	}
	this->object = create3DObject(GL_TRIANGLES,3*n, vertex_buffer_data, color, GL_FILL);
}

void Powerups::draw(glm::mat4 VP) {
	// if(!this->moveable) this->rotation+=5.0f;
	Matrices.model = glm::mat4(1.0f);
	glm::mat4 translate = glm::translate (this->position);    // glTranslatef
	glm::mat4 rotate    = glm::rotate(glm::radians(this->rotation), glm::vec3(0, 1, 0));
	// No need as coords centered at 0, 0, 0 of cube around which we want to rotate
	// rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
	Matrices.model *= (translate * rotate);
	glm::mat4 MVP = VP * Matrices.model;
	glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
	draw3DObject(this->object);
}

void Powerups::set_position(float x, float y) {
	this->position = glm::vec3(x, y, 0);
}

void SpecialObj::move_special_obj(int direction) {
	int64_t current_time;
	current_time = get_time_ms();
	// this->position.y += (this->initial_posy+this->vel_y*(current_time - this->initiated_time) - 0.05*gravity*(current_time - this->initiated_time)*(current_time - this->initiated_time)-this->previous_posy);
	if(!this->ice_ball) {
	this->position.x += direction*this->vel_x*(current_time - previous_time);   
		this->position.y = this->initial_posy+(this->vel_y*(current_time - this->initiated_time) - 0.05*gravity*(current_time - this->initiated_time)*(current_time - this->initiated_time));    
		// else this->position.y;
		this->previous_time = current_time;
		this->previous_posy = this->position.y;
		if(this->position.y -this->radius<= min_height) {
			if(this->water_drop) this->destroyed = true;
			this->position.y = min_height + this->radius;
			this->initiated_time = get_time_ms();
			this->previous_time = this->initiated_time;
			this->previous_posy = this->initial_posy = this->position.y;
		}
		if(this->position.x>rightmost) this->destroyed = true;
	} 
	else {
		this->position.x += direction*this->vel_x;
		// if(this->position.x<=leftmost) this->destroyed = true;
	}
}
