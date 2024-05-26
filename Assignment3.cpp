#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#include "P6/MyVector.h"
#include <string>
#include <iostream>

#include <chrono>

using namespace std::chrono_literals;

constexpr std::chrono::nanoseconds timestep(16ms);

float translate_x_mod = 0.f;
float translate_y_mod = 0.f;
float rotate_x_mod = 0.f;
float rotate_y_mod = 1.f;
float scale_mod = 0.f;
//float zoom_mod = -1.5f;

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    float window_width = 800.0f;
    float window_height = 800.0f;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(window_width, window_height, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    gladLoadGL();

    /*glViewport(0, //min x
        0, //min y
        640, //x
        480); //y */

        //load vert shader
    std::fstream vertSrc("Shaders/sample.vert");
    std::stringstream vertBuff;
    vertBuff << vertSrc.rdbuf();

    std::string vertS = vertBuff.str();
    const char* v = vertS.c_str();

    //load frag shader
    std::fstream fragSrc("Shaders/sample.frag");
    std::stringstream fragBuff;
    fragBuff << fragSrc.rdbuf();

    std::string fragS = fragBuff.str();
    const char* f = fragS.c_str();

    //add vertex shader
    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertShader, 1, &v, NULL);
    glCompileShader(vertShader);

    GLint isCompiled = 0;

    glGetShaderiv(vertShader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(vertShader, maxLength, &maxLength, &errorLog[0]);
        std::cout << &errorLog[0];
        // Provide the infolog in whatever manor you deem best.
        // Exit with failure.
        //glDeleteShader(fragShader); // Don't leak the shader.
    }

    //add frag shader
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &f, NULL);
    glCompileShader(fragShader);

    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(fragShader, maxLength, &maxLength, &errorLog[0]);
        std::cout << &errorLog[0];
        // Provide the infolog in whatever manor you deem best.
        // Exit with failure.
        glDeleteShader(fragShader); // Don't leak the shader.
    }

    //create shader program and attach compiled shaders
    GLuint shaderProg = glCreateProgram();
    glAttachShader(shaderProg, vertShader);
    glAttachShader(shaderProg, fragShader);

    //finalize the compilation process
    glLinkProgram(shaderProg);

    std::string path = "3D/sphere.obj";
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> material;  
    std::string warning, error;

    tinyobj::attrib_t attributes;

    bool success = tinyobj::LoadObj(
        &attributes,
        &shapes,
        &material,
        &warning,
        &error,
        path.c_str()
    );

    //get EBO indices array
    std::vector<GLuint> mesh_indices;
    for (int i = 0; i < shapes[0].mesh.indices.size(); i++) {
        mesh_indices.push_back(
            shapes[0].mesh.indices[i].vertex_index
        );
    }

    GLfloat vertices[]{
        //x   y     z
        0.f, 0.5f, 0.f, //0
        -0.5f, -0.5f, 0.f, //1
        0.5f, -0.5f, 0.f //2
    };

    GLuint indices[]{
        0, 1, 2
    };

    GLuint VAO, VBO, EBO;
    //Initialize VAO and VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    //tell opengl to use shader for VAOs below
    glUseProgram(shaderProg);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //VBO
    glBufferData(GL_ARRAY_BUFFER,
        sizeof(GL_FLOAT) * attributes.vertices.size(), //bytes
        &attributes.vertices[0],         // == attributes.vertices.data()
        GL_STATIC_DRAW);

    glVertexAttribPointer(
        0, //0 pos, 1 tex, 2 norms
        3, //xyz
        GL_FLOAT,
        GL_FALSE,
        3 * sizeof(GL_FLOAT),
        (void*)0
    );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        sizeof(GLuint) * mesh_indices.size(),
        &mesh_indices[0],
        GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    float x, y, z;
    x = y = z = 0.0f;
    z = -5.0f;
    glm::mat3 identity_matrix3 = glm::mat3(1.0f);
    glm::mat4 identity_matrix4 = glm::mat4(1.0f);

    float scale_x, scale_y, scale_z = 1.f;
    scale_x = scale_y = scale_z = 1.f;

    float axis_x, axis_y, axis_z, theta = 0.f;
    axis_x = axis_y = axis_z = theta = 0.f;
    axis_y = 1.f;

    glm::mat4 projectionMatrix = glm::ortho(
        -1.f, //left
        1.f, //right
        -1.f, //bottom
        1.f, //top
        -1.f, //znear
        400.f //zfar
    );

    /*glm::mat4 projectionMatrix = glm::ortho(
        -400.f, //left
        400.f, //right
        -400.f, //bottom
        400.f, //top
        -400.f, //znear
        400.f //zfar
    );*/


    /*glm::mat4 projectionMatrix = glm::perspective(
        glm::radians(60.f), //fov
        window_height / window_width, //aspect ratio
        0.1f, //znear > 0
        100.0f //zfar
    );*/

    P6::MyVector sample(0, 0, 0);
    sample.x = 100;

    //initialize clock
    using clock = std::chrono::high_resolution_clock;
    auto curr_time = clock::now();
    auto prev_time = curr_time;
    std::chrono::nanoseconds curr_ns(0);

    float initiXvel;
    float initiYvel;
    float initiZvel;
    float originH = 0;

    //initialize launch of cannon
    bool bLaunch = true;
    bool bHasLanded = true;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        //CODEBLOCK FOR ADDING INITIAL VELOCITY, MAKE SURE BALL IS ALREADY LANDED FROM ITS ORIGINAL POINT AND THE PROJECTILE WAS NOT LAUNCHED ALREADY
        if (bLaunch == true && bHasLanded == true) {

            std::cout << "Input the initial velocity: " << std::endl;
            std::cout << "X: " << std::endl;
            std::cin >> initiXvel;
            std::cout << "Y: " << std::endl;
            std::cin >> initiYvel;
            std::cout << "Z: " << std::endl;
            std::cin >> initiZvel;

            originH = sample.y;

            P6::MyVector initial(initiXvel, initiYvel, initiZvel);
            
            sample.Add(initial);
            bLaunch = false;
            bHasLanded = false;


        }

        //get current time
        curr_time = clock::now();
        //check duration
        auto dur = std::chrono::duration_cast<std::chrono::nanoseconds>(curr_time - prev_time);
        //set prev to current
        prev_time = curr_time;
        //add duration
        curr_ns += dur;

        if (curr_ns >= timestep) {
            //convert ns to ms
            curr_ns -= timestep;
            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(curr_ns);
            std::cout << "MS: " << (float)ms.count() << "\n";
            //reset
            curr_ns -= curr_ns;
            //call updates
           std::cout << "P6 Update" << "\n";

           //Code snippet for gravitational falling effect:

           if (bHasLanded != true) {

               P6::MyVector acceleration(0, -50, 0);
               sample.Subtract(acceleration);
               std::cout << "Current vector is now falling at exactly: " << sample.y << "\n";

           }

           //Code snipper for the cannonball stopping after its reached its original point in time.
           if (sample.y <= originH) {

               bHasLanded = true;
               bLaunch = true;
               std::cout << "It took: " << (float)ms.count() << " seconds to land." << "\n";
           }

        }
        //std::cout << "Normal Update" << "\n";

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        //x = translate_x_mod;
        //y = translate_y_mod;
        //z = zoom_mod;
        //theta = rotate_x_mod;
        //axis_y = rotate_y_mod;

        glm::mat4 transformation_matrix = glm::translate(
            identity_matrix4,
            glm::vec3(x, y, z)
        );

        transformation_matrix = glm::scale(
            transformation_matrix,
            glm::vec3(scale_x, scale_y, scale_z)
        );

        transformation_matrix = glm::rotate(
            transformation_matrix,
            glm::radians(theta),
            glm::normalize(glm::vec3(axis_x, axis_y, axis_z))
        );

        transformation_matrix = glm::rotate(
            transformation_matrix,
            glm::radians(axis_y),
            glm::normalize(glm::vec3(1.0f, 0.0f, axis_z))
        );

        unsigned int projectionLoc = glGetUniformLocation(shaderProg, "projection");

        glUniformMatrix4fv(projectionLoc, //address of transform variable
            1, //how many matrices to assign
            GL_FALSE, //transpose
            glm::value_ptr(projectionMatrix) //pointer to matrix
        );

        //get location of transform variable in shader
        unsigned int transformLoc = glGetUniformLocation(shaderProg, "transform");

        //assign matrix
        glUniformMatrix4fv(transformLoc, //address of transform variable
            1, //how many matrices to assign
            GL_FALSE, //transpose
            glm::value_ptr(transformation_matrix) //pointer to matrix
        );

        glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES,
            mesh_indices.size(),
            GL_UNSIGNED_INT,
            0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;
}