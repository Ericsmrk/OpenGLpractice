#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
using namespace std;

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

	if (GLEW_OK != glewInit())
		cout << "Error!" << endl;

    /*unsigned int a;
    glGenBuffers(1, &a);*/

    cout << glGetString(GL_VERSION) << endl;

    // make an array for the data for the buffer
    float positions[6] = {
        -0.5f, -0.f,  //x, y
         0.0f,  0.5f,
         0.5f, -0.5f
    };
    
    // define a vertex buffer
	unsigned int buffer;
	glGenBuffers(1, &buffer);                           //generate a buffer
    glBindBuffer(GL_ARRAY_BUFFER, buffer);              // bind the buffer we just generated with an array
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);   // add data (positions) to the buffer 

    // tell opengl what the layout of our buffer is
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0); //

    glBindBuffer(GL_ARRAY_BUFFER, 0); // bind no buffer

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        // make a basic triangle by specifying three vertices
        /*glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f( 0.0f,  0.5f);
        glVertex2f( 0.5f, -0.5f);
        glEnd();*/ 

        // issue draw call
        glDrawArrays(GL_TRIANGLES, 0, 3); // draw what is bound

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}