#ifndef SETTINGS_H
#define SETTINGS_H

// the image resolution is 512 × 512
#define SCR_WIDTH 512
#define SCR_HEIGHT 512

void errorCallback(int error, const char *description);
void keyCallback(GLFWwindow *window, int key, int scancode, int action,
				 int mods);

#endif
