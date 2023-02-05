#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
using namespace std;

// Compile a shader 
static unsigned int CompileShader(unsigned int type, const string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    // Error handling
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {                                       // shader didn't compile successfully
        int length;                                                 // error message length
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));       // cheat to allocate mem on the stack
        glGetShaderInfoLog(id, length, &length, message);
        cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << endl; // check type for output
        cout << message << endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

// Create a shader 
static unsigned int CreateShader(const string& vertexShader, const string& fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader); // shader object
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader); // shader object

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}


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

    // make an array for the data for the buffer (positions)
    float positions[6] = {
        -0.5f, -0.5f,  //x, y
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
    //glBindBuffer(GL_ARRAY_BUFFER, 0); // bind no buffer

    string vertexShader =
        "#version 330 core\n"
        "\n"
        "layout(location = 0) in vec4 position;\n"
        "\n"
        "void main()\n"
        "{\n"
        "   gl_Position = position;\n"
        "}\n";

	string fragmentShader =
		"#version 330 core\n"
		"\n"
		"layout(location = 0) out vec4 color;\n"
		"\n"
		"void main()\n"
		"{\n"
		"   color = vec4(1.0, 0.0, 0.0, 1.0);\n"  //r g b a
		"}\n";

    unsigned int shader = CreateShader(vertexShader, fragmentShader);
    glUseProgram(shader); //bind the new red shader

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

    glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}