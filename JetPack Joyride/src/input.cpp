#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include "player.h"
#include "powerups.h"
extern Player player1;
extern float screen_zoom;
bool   cannon_keyboard_input = true;
bool   drag_pan = false, old_cki;
double drag_oldx = -1, drag_oldy = -1;
extern void reset_screen();
std::vector<SpecialObj> water_droplets;

using namespace std;

/* Executed when a regular key is pressed/released/held-down */
/* Prefered for Keyboard events */
void keyboard(GLFWwindow *window, int key, int scancode, int action, int mods) {
	// Function is called first on GLFW_PRESS.
	if (action == GLFW_RELEASE) {

	} else if (action == GLFW_PRESS) {
		switch (key) {
			case GLFW_KEY_S: {
						 water_droplets.push_back(SpecialObj(player1.position.x+0.75,player1.position.y+0.375,COLOR_BLUE,3));
					 }
		}
	}
}

/* Executed for character input (like in text boxes) */
void keyboardChar(GLFWwindow *window, unsigned int key) {
	switch (key) {
		case 'Q':
		case 'q':
			quit(window);
			break;
		default:
			break;
	}
}

/* Executed when a mouse button is pressed/released */
void mouseButton(GLFWwindow *window, int button, int action, int mods) {
	switch (button) {
		case GLFW_MOUSE_BUTTON_LEFT:
			if (action == GLFW_PRESS) {
				// Do something
				return;
			} else if (action == GLFW_RELEASE) {
				// Do something
			}
			break;
			// case GLFW_MOUSE_BUTTON_RIGHT:
			// if (action == GLFW_RELEASE) {
			// rectangle_rot_dir *= -1;
			// }
			// break;
		default:
			break;
	}
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
	screen_zoom+=yoffset*0.01;
	reset_screen();
}
