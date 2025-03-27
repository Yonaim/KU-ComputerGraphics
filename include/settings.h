#ifndef SETTINGS_H
#define SETTINGS_H

#include "gl_core.h"

// option
#define PRINT_MSG_PROCESSING_LINE_NUMBER true

// the image resolution is 512 × 512
#define SCR_WIDTH  512
#define SCR_HEIGHT 512

void errorCallback(int error, const char *description);
void keyCallback(GLFWwindow *window, int key, int scancode, int action,
				 int mods);
void resizeCallback(GLFWwindow *window, int width, int height);

#endif
