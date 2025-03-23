#include "graphics.h"

void render_loop(GLFWwindow *window)
{
	// render loop
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		// render
		glClear(GL_COLOR_BUFFER_BIT);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse
		// moved etc.)
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

int main()
{
	Scene scene;
	init_scene(scene);

	GLFWwindow *window = init_glfw();
	if (window == NULL)
		return (1);

	if (!init_glad())
		return (1);

	render_loop(window);

	// glfw: terminate, clearing all previously allocated GLFWresources.
	glfwTerminate();
	return (0);
}
