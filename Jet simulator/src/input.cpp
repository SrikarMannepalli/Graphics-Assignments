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

#include "main.h"
#include "bomb.h"
#include "plane.h"
#include "missile.h"
using namespace std;

extern vector<Bomb> bombs;
extern vector<Missile> missiles;
extern Plane plane1;

bool   cannon_keyboard_input = true;
bool   drag_pan = false, old_cki;
double drag_oldx = -1, drag_oldy = -1;
extern float screen_zoom;

glm::vec3 eye;
glm::vec3 target;
glm::vec3 up;

/* Executed when a regular key is pressed/released/held-down */
/* Prefered for Keyboard events */
void keyboard(GLFWwindow *window, int key, int scancode, int action, int mods) {
    // Function is called first on GLFW_PRESS.

    if (action == GLFW_RELEASE) {
        switch (key) {
        }
    } else if (action == GLFW_PRESS) {
        switch (key) {
        
        case GLFW_KEY_ESCAPE:
            quit(window);
            break;
        default:
            break;
        }
    }
}

/* Executed for character input (like in text boxes) */
void keyboardChar(GLFWwindow *window, unsigned int key) {
    switch (key) {
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
            missiles.push_back(Missile(plane1.position.x-sin(glm::radians(plane1.yaw)),plane1.position.y,plane1.position.z-cos(glm::radians(plane1.yaw)),0));
            system("aplay ../src/missile.wav &");
            break;
            // Do something
        }
        break;
    case GLFW_MOUSE_BUTTON_RIGHT:
        if (action == GLFW_RELEASE) {
            bombs.push_back(Bomb(plane1.position.x,plane1.position.y,plane1.position.z));
            break;
        }
    break;
    default:
        break;
    }
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    screen_zoom += yoffset*0.01;
}
