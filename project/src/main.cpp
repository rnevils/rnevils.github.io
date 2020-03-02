/*
CPE/CSC 471 Lab base code Wood/Dunn/Eckhardt
*/

#include <iostream>
#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "GLSL.h"
#include "Program.h"
#include "MatrixStack.h"

#include "WindowManager.h"
#include "Shape.h"
// value_ptr for glm
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace std;
using namespace glm;
shared_ptr<Shape> shape;


double get_last_elapsed_time()
{
    static double lasttime = glfwGetTime();
    double actualtime =glfwGetTime();
    double difference = actualtime- lasttime;
    lasttime = actualtime;
    return difference;
}
class camera
{
public:
    glm::vec3 pos, rot;
    int w, a, s, d, up, down, high, low;
    camera()
    {
        w = a = s = d = 0;
        rot = glm::vec3(0.4, 0, 0);
        pos = glm::vec3(0, -3, -8);
    }
    glm::mat4 process(double ftime)
    {
        float speed = 0;
        if (w == 1)
        {
            speed = 5*ftime;
        }
        else if (s == 1)
        {
            speed = -5*ftime;
        }
        float yangle=0;
        float xangle=0;
        float elevation=0;
        if (a == 1)
            yangle = -2*ftime;
        else if(d==1)
            yangle = 2*ftime;
        
        if (up == 1)
        {
            xangle = -2*ftime;
        }
            
        else if(down==1)
        {
            xangle = 2*ftime;
        }
        
        rot.y += yangle;
        rot.x += xangle;
        glm::mat4 Ry = glm::rotate(glm::mat4(1), rot.y, glm::vec3(0, 1, 0));
        glm::mat4 Rx = glm::rotate(glm::mat4(1), rot.x, glm::vec3(1, 0, 0));
        glm::mat4 TransZ = glm::translate(glm::mat4(1.0f), glm::vec3(elevation, 0.0f, 0.0f));
        glm::vec4 dir = glm::vec4(0, 0, speed,1);
        dir = dir*Rx*Ry * TransZ;
        pos += glm::vec3(dir.x, dir.y, dir.z);
        glm::mat4 T = glm::translate(glm::mat4(1), pos);
        return Rx*Ry*T;
        
    }
};

camera mycam;

class Application : public EventCallbacks
{

public:

    WindowManager * windowManager = nullptr;

    // Our shader program
    std::shared_ptr<Program> prog, prog2;

    // Contains vertex information for OpenGL
    GLuint VertexArrayID, VertexArrayID2, WikiVBO;

    // Data necessary to give our box to OpenGL
    GLuint VertexBufferID, VertexBufferID2, VertexNormDBox, VertexTexBox, InstanceBuffer, VertexColorIDBox, IndexBufferIDBox, IndexBufferIDBox2;
    GLuint MeshPosID, MeshTexID;

    //texture data
    GLuint Texture;
    GLuint Texture2;
    GLuint Texture3;
    GLuint Texture4;
    GLuint Texture5;
    GLuint Texture6;
    
    GLuint solution = 0;
    GLuint spd = 1;
    //GLuint solution = 0;
    

    void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
    {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
        
        if (key == GLFW_KEY_W && action == GLFW_PRESS)
        {
            mycam.w = 1;
        }
        if (key == GLFW_KEY_W && action == GLFW_RELEASE)
        {
            mycam.w = 0;
        }
        if (key == GLFW_KEY_S && action == GLFW_PRESS)
        {
            mycam.s = 1;
        }
        if (key == GLFW_KEY_S && action == GLFW_RELEASE)
        {
            mycam.s = 0;
        }
        if (key == GLFW_KEY_A && action == GLFW_PRESS)
        {
            mycam.a = 1;
        }
        if (key == GLFW_KEY_A && action == GLFW_RELEASE)
        {
            mycam.a = 0;
        }
        if (key == GLFW_KEY_D && action == GLFW_PRESS)
        {
            mycam.d = 1;
        }
        if (key == GLFW_KEY_D && action == GLFW_RELEASE)
        {
            mycam.d = 0;
        }
        if (key == GLFW_KEY_UP && action == GLFW_PRESS)
        {
            mycam.up = 1;
        }
        if (key == GLFW_KEY_UP && action == GLFW_RELEASE)
        {
            mycam.up = 0;
        }
        if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
        {
            mycam.down = 1;
        }
        if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE)
        {
            mycam.down = 0;
        }
        if (key == GLFW_KEY_Q && action == GLFW_PRESS)
        {
            mycam.high = 1;
        }
        if (key == GLFW_KEY_Q && action == GLFW_RELEASE)
        {
            mycam.high = 0;
        }
        if (key == GLFW_KEY_E && action == GLFW_PRESS)
        {
            mycam.low = 1;
        }
        if (key == GLFW_KEY_E && action == GLFW_RELEASE)
        {
            mycam.low = 0;
        }
        
        //for changing the type of wave
        if (key == GLFW_KEY_0 && action == GLFW_PRESS)
        {
            solution = 0;
        }
        if (key == GLFW_KEY_1 && action == GLFW_PRESS)
        {
            solution = 1;
        }
        if (key == GLFW_KEY_2 && action == GLFW_PRESS)
        {
            solution = 2;
        }
        if (key == GLFW_KEY_3 && action == GLFW_PRESS)
        {
            solution = 3;
        }
        if (key == GLFW_KEY_4 && action == GLFW_PRESS)
        {
            solution = 4;
        }
        if (key == GLFW_KEY_5 && action == GLFW_PRESS)
        {
            solution = 5;
        }
        if (key == GLFW_KEY_6 && action == GLFW_PRESS)
        {
            solution = 6;
        }
        if (key == GLFW_KEY_7 && action == GLFW_PRESS)
        {
            solution = 7;
        }
        if (key == GLFW_KEY_8 && action == GLFW_PRESS)
        {
            solution = 8;
        }
        if (key == GLFW_KEY_9 && action == GLFW_PRESS)
        {
            solution = 9;
        }
        if (key == GLFW_KEY_L && action == GLFW_PRESS)
        {
            spd += 0.5;
        }
        if (key == GLFW_KEY_K && action == GLFW_PRESS)
        {
            spd -= 0.5;
        }

        
        // like rocket league free cam, want to be able to go vertically directly up
    }

    // callback for the mouse when clicked move the triangle when helper functions
    // written
    void mouseCallback(GLFWwindow *window, int button, int action, int mods)
    {
        double posX, posY;
        float newPt[2];
        if (action == GLFW_PRESS)
        {
            glfwGetCursorPos(window, &posX, &posY);
            std::cout << "Pos X " << posX <<  " Pos Y " << posY << std::endl;

            //change this to be the points converted to WORLD
            //THIS IS BROKEN< YOU GET TO FIX IT - yay!
            newPt[0] = 0;
            newPt[1] = 0;

            std::cout << "converted:" << newPt[0] << " " << newPt[1] << std::endl;
            glBindBuffer(GL_ARRAY_BUFFER, VertexBufferID);
            //update the vertex array with the updated points
            glBufferSubData(GL_ARRAY_BUFFER, sizeof(float)*6, sizeof(float)*2, newPt);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
    }

    //if the window is resized, capture the new size and reset the viewport
    void resizeCallback(GLFWwindow *window, int in_width, int in_height)
    {
        //get the window size - may be different then pixels for retina
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
    }
    
#define MESHSIZE 200
    void init_mesh()
    {
        //generate the VAO
        glGenVertexArrays(1, &VertexArrayID);
        glBindVertexArray(VertexArrayID);

        //generate vertex buffer to hand off to OGL
        glGenBuffers(1, &MeshPosID);
        glBindBuffer(GL_ARRAY_BUFFER, MeshPosID);
        vec3 vertices[MESHSIZE * MESHSIZE * 4];
        for(int x=0;x<MESHSIZE;x++)
            for (int z = 0; z < MESHSIZE; z++)
                {
                vertices[x * 4 + z*MESHSIZE * 4 + 0] = vec3(0.0, 0.0, 0.0) + vec3(x, 0, z);
                vertices[x * 4 + z*MESHSIZE * 4 + 1] = vec3(1.0, 0.0, 0.0) + vec3(x, 0, z);
                vertices[x * 4 + z*MESHSIZE * 4 + 2] = vec3(1.0, 0.0, 1.0) + vec3(x, 0, z);
                vertices[x * 4 + z*MESHSIZE * 4 + 3] = vec3(0.0, 0.0, 1.0) + vec3(x, 0, z);
                }
        

        // shifting
        for(int x=0;x<MESHSIZE;x++)
        {
            for (int z = 0; z < MESHSIZE; z++)
                {
                    vertices[x * 4 + z*MESHSIZE * 4 + 0] += vec3(-100.0, 0.0, -100.0);
                    vertices[x * 4 + z*MESHSIZE * 4 + 1] += vec3(-100.0, 0.0, -100.0);
                    vertices[x * 4 + z*MESHSIZE * 4 + 2] += vec3(-100.0, 0.0, -100.0);
                    vertices[x * 4 + z*MESHSIZE * 4 + 3] += vec3(-100.0, 0.0, -100.0);
                    
                }
        }
        
        // scaling down
        for(int x=0;x<MESHSIZE;x++)
        {
            for (int z = 0; z < MESHSIZE; z++)
                {
                    vertices[x * 4 + z*MESHSIZE * 4 + 0] *= vec3(0.1, 0.1, 0.1);
                    vertices[x * 4 + z*MESHSIZE * 4 + 1] *= vec3(0.1, 0.1, 0.1);
                    vertices[x * 4 + z*MESHSIZE * 4 + 2] *= vec3(0.1, 0.1, 0.1);
                    vertices[x * 4 + z*MESHSIZE * 4 + 3] *= vec3(0.1, 0.1, 0.1);
                }
        }
        
        glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * MESHSIZE * MESHSIZE * 4, vertices, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        //tex coords
        float t = 1. / 100;
        vec2 tex[MESHSIZE * MESHSIZE * 4];
        for (int x = 0; x<MESHSIZE; x++)
            for (int y = 0; y < MESHSIZE; y++)
            {
                tex[x * 4 + y*MESHSIZE * 4 + 0] = vec2(0.0, 0.0)+ vec2(x, y)*t;
                tex[x * 4 + y*MESHSIZE * 4 + 1] = vec2(t, 0.0)+ vec2(x, y)*t;
                tex[x * 4 + y*MESHSIZE * 4 + 2] = vec2(t, t)+ vec2(x, y)*t;
                tex[x * 4 + y*MESHSIZE * 4 + 3] = vec2(0.0, t)+ vec2(x, y)*t;
            }
        glGenBuffers(1, &MeshTexID);
        //set the current state to focus on our vertex buffer
        glBindBuffer(GL_ARRAY_BUFFER, MeshTexID);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vec2) * MESHSIZE * MESHSIZE * 4, tex, GL_STATIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

        glGenBuffers(1, &IndexBufferIDBox);
        //set the current state to focus on our vertex buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferIDBox);
        GLuint elements[MESHSIZE * MESHSIZE * 6];
        int ind = 0;
        for (int i = 0; i<MESHSIZE * MESHSIZE * 6; i+=6, ind+=4)
            {
            elements[i + 0] = ind + 0;
            elements[i + 1] = ind + 1;
            elements[i + 2] = ind + 2;
            elements[i + 3] = ind + 0;
            elements[i + 4] = ind + 2;
            elements[i + 5] = ind + 3;
            }
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*MESHSIZE * MESHSIZE * 6, elements, GL_STATIC_DRAW);
        glBindVertexArray(0);
    }

    /*Note that any gl calls must always happen after a GL state is initialized */
    void initGeom()
    {
        
        //initialize the net mesh
        init_mesh();
        


    
        
        glGenVertexArrays(1, &VertexArrayID2);
        glBindVertexArray(VertexArrayID2);

        //generate vertex buffer to hand off to OGL
        glGenBuffers(1, &VertexBufferID2);
        //set the current state to focus on our vertex buffer
        glBindBuffer(GL_ARRAY_BUFFER, VertexBufferID2);

        GLfloat cube_vertices[] = {
            // front
            -1.0, 0.8,  0.0,//LD
            0.2, 0.8,  0.0,//RD
            0.2,  1.0,  0.0,//RU
            -1.0, 1.0,  0.0,//LU
        };
        //make it a bit smaller
//        for (int i = 0; i < 12; i++)
//            cube_vertices[i] *= 0.5;
        
        //actually memcopy the data - only do this once
        glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_DYNAMIC_DRAW);
        
        

        //we need to set up the vertex array
        glEnableVertexAttribArray(0);
        
        assert(glGetError() == GL_NO_ERROR);
        //key function to get up how many elements to pull out at a time (3)
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);




        //color
        GLfloat cube_norm[] = {
            // front colors
            0.0, 0.0, 1.0,
            0.0, 0.0, 1.0,
            0.0, 0.0, 1.0,
            0.0, 0.0, 1.0,

        };
        glGenBuffers(1, &VertexNormDBox);
        //set the current state to focus on our vertex buffer
        glBindBuffer(GL_ARRAY_BUFFER, VertexNormDBox);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cube_norm), cube_norm, GL_STATIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

        //color
        glm::vec2 cube_tex[] = {
            // front colors
            glm::vec2(0.0, 1.0),
            glm::vec2(1.0, 1.0),
            glm::vec2(1.0, 0.0),
            glm::vec2(0.0, 0.0),

        };
        glGenBuffers(1, &VertexTexBox);
        //set the current state to focus on our vertex buffer
        glBindBuffer(GL_ARRAY_BUFFER, VertexTexBox);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cube_tex), cube_tex, GL_STATIC_DRAW);
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

        glGenBuffers(1, &IndexBufferIDBox2);
        //set the current state to focus on our vertex buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferIDBox2);
        GLushort cube_elements[] = {

            // front
            0, 1, 2,
            2, 3, 0,
        };
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_elements), cube_elements, GL_STATIC_DRAW);
        
        
        glBindVertexArray(0);
        
        
    
        string resourceDirectory = "../../resources" ;
        // Initialize mesh.
        shape = make_shared<Shape>();
        //shape->loadMesh(resourceDirectory + "/t800.obj");
        shape->loadMesh(resourceDirectory + "/sphere.obj");
        shape->resize();
        shape->init();

        int width, height, channels;
        char filepath[1000];

        //texture 1
        string str = resourceDirectory + "/eqn0.png";
        strcpy(filepath, str.c_str());
        unsigned char* data = stbi_load(filepath, &width, &height, &channels, 4);
        glGenTextures(1, &Texture);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, Texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        //texture 2
        str = resourceDirectory + "/eqn1.png";
        strcpy(filepath, str.c_str());
        data = stbi_load(filepath, &width, &height, &channels, 4);
        glGenTextures(1, &Texture2);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, Texture2);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        
        //texture 3
        str = resourceDirectory + "/eqn2.png";
        strcpy(filepath, str.c_str());
        data = stbi_load(filepath, &width, &height, &channels, 4);
        glGenTextures(1, &Texture3);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, Texture3);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        
        //texture 4
        str = resourceDirectory + "/eqn3.png";
        strcpy(filepath, str.c_str());
        data = stbi_load(filepath, &width, &height, &channels, 4);
        glGenTextures(1, &Texture4);
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, Texture4);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        
        
        //texture 4
        str = resourceDirectory + "/eqn4.png";
        strcpy(filepath, str.c_str());
        data = stbi_load(filepath, &width, &height, &channels, 4);
        glGenTextures(1, &Texture5);
        glActiveTexture(GL_TEXTURE4);
        glBindTexture(GL_TEXTURE_2D, Texture5);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        
        //texture 6
        str = resourceDirectory + "/eqn5.png";
        strcpy(filepath, str.c_str());
        data = stbi_load(filepath, &width, &height, &channels, 4);
        glGenTextures(1, &Texture6);
        glActiveTexture(GL_TEXTURE5);
        glBindTexture(GL_TEXTURE_2D, Texture6);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        //[TWOTEXTURES]
        //set the 2 textures to the correct samplers in the fragment shader:
        GLuint Tex1Location = glGetUniformLocation(prog->pid, "tex");//tex, tex2... sampler in the fragment shader
        GLuint Tex2Location = glGetUniformLocation(prog->pid, "tex2");
        GLuint Tex3Location = glGetUniformLocation(prog->pid, "tex3");
        //GLuint Tex4Location = glGetUniformLocation(prog->pid, "tex4");
        // Then bind the uniform samplers to texture units:
        glUseProgram(prog->pid);
        glUniform1i(Tex1Location, 0);
        glUniform1i(Tex2Location, 1);
        glUniform1i(Tex3Location, 2);
        //glUniform1i(Tex4Location, 3);
        
        
        // uhhh copying this again to hopefully work for prog2
        GLuint Tex1Location2 = glGetUniformLocation(prog2->pid, "tex");//tex, tex2... sampler in the fragment shader
        GLuint Tex2Location2 = glGetUniformLocation(prog2->pid, "tex2");
        GLuint Tex3Location2 = glGetUniformLocation(prog2->pid, "tex3");
        GLuint Tex4Location2 = glGetUniformLocation(prog2->pid, "tex4");
        GLuint Tex5Location2 = glGetUniformLocation(prog2->pid, "tex5");
        GLuint Tex6Location2 = glGetUniformLocation(prog2->pid, "tex6");
        // Then bind the uniform samplers to texture units:
        glUseProgram(prog2->pid);
        glUniform1i(Tex1Location2, 0);
        glUniform1i(Tex2Location2, 1);
        glUniform1i(Tex3Location2, 2);
        glUniform1i(Tex4Location2, 3);
        glUniform1i(Tex5Location2, 4);
        glUniform1i(Tex6Location2, 5);

    }

    //General OGL initialization - set OGL state here
    void init(const std::string& resourceDirectory)
    {
        GLSL::checkVersion();

        // Set background color.
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        // Enable z-buffer test.
        glEnable(GL_DEPTH_TEST);
        //glDisable(GL_DEPTH_TEST);
        
        // Enable blending/transparency
        //glEnable(GL_BLEND);
        //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Initialize the GLSL program.
        prog = std::make_shared<Program>();
        prog->setVerbose(true);
        prog->setShaderNames(resourceDirectory + "/shader_vertex.glsl", resourceDirectory + "/shader_fragment.glsl");
        if (!prog->init())
        {
            std::cerr << "One or more shaders failed to compile... exiting!" << std::endl;
            exit(1);
        }
        prog->addUniform("P");
        prog->addUniform("V");
        prog->addUniform("M");
        prog->addUniform("t");
        prog->addUniform("soln");
        prog->addUniform("spd");
        prog->addUniform("campos");
        
        prog->addAttribute("vertPos");
        prog->addAttribute("vertNor");
        prog->addAttribute("vertTex");
        
        
        // add second shader for equation box
        
        prog2 = std::make_shared<Program>();
        prog2->setVerbose(true);
        prog2->setShaderNames(resourceDirectory + "/shader_vertex_eqn.glsl", resourceDirectory + "/shader_fragment_eqn.glsl");
        if (!prog2->init())
        {
            std::cerr << "One or more shaders failed to compile... exiting!" << std::endl;
            exit(1);
        }
        prog2->addUniform("M");
        prog2->addUniform("soln");
        prog2->addUniform("campos");
        
        prog2->addAttribute("vertPos");
        prog2->addAttribute("vertNor");
        prog2->addAttribute("vertTex");
    }


    /****DRAW
    This is the most important function in your program - this is where you
    will actually issue the commands to draw any geometry you have set up to
    draw
    ********/
    void render()
    {
        //glEnable(GL_BLEND);
        //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        double frametime = get_last_elapsed_time();
        

        // Get current frame buffer size.
        int width, height;
        glfwGetFramebufferSize(windowManager->getHandle(), &width, &height);
        
        glViewport(0, 0, width, height);

        // Clear framebuffer.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Create the matrix stacks - please leave these alone for now
        glm::mat4 V, M, P; //View, Model and Perspective matrix
        V = mycam.process(frametime);
        M = glm::mat4(1);
        P = glm::perspective((float)(3.14159 / 4.), (float)((float)width/ (float)height), 0.1f, 1000.0f); //so much type casting... GLM metods are quite funny ones


        //animation with the model matrix:
        static float w = 0.0;
        static float ww = 0.0;
        
        
        w += 1.0 * frametime;//rotation angle
        

        glm::mat4 TransUP = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 S = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));

        M =  TransUP * S;

        //Drawing programs that use prog shader
        prog->bind();
//        glEnable(GL_CULL_FACE);
//        glFrontFace(GL_CCW);

        //send the matrices to the shaders
        glUniformMatrix4fv(prog->getUniform("P"), 1, GL_FALSE, &P[0][0]);
        glUniformMatrix4fv(prog->getUniform("V"), 1, GL_FALSE, &V[0][0]);
        glUniformMatrix4fv(prog->getUniform("M"), 1, GL_FALSE, &M[0][0]);
        //glUniform1f(prog->getUniform("t"), (float)t);
        glUniform1f(prog->getUniform("t"), ww);
        glUniform1i(prog->getUniform("soln"), solution);
        glUniform1i(prog->getUniform("spd"), spd);
        glUniform3fv(prog->getUniform("campos"), 1, &mycam.pos[0]);
        
        if (solution < 1)
        {
            ww = 0;
        }
        ww += 0.01;
        // draw circle
        if (solution == 1 || solution == 2 || solution == 5 || solution == 0)
        {
            shape->draw(prog,0);
        }
        

        // draw 2D points
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        //glm::mat4 TransY = glm::translate(glm::mat4(1.0f), glm::vec3(-50.0f, -3.0f, -50));
        S = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
        //M = TransY;
        M = glm::mat4(1) * S;
        glUniformMatrix4fv(prog->getUniform("M"), 1, GL_FALSE, &M[0][0]);
        glUniformMatrix4fv(prog->getUniform("P"), 1, GL_FALSE, &P[0][0]);
        glUniformMatrix4fv(prog->getUniform("V"), 1, GL_FALSE, &V[0][0]);


        glUniform3fv(prog->getUniform("campos"), 1, &mycam.pos[0]);
        glBindVertexArray(VertexArrayID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferIDBox);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, Texture2);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, Texture);
        glDrawElements(GL_TRIANGLES, MESHSIZE*MESHSIZE*6, GL_UNSIGNED_INT, (void*)0);
        
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

//        glDisable(GL_CULL_FACE);


        prog->unbind();




        // drawing the equation
        prog2->bind();
        
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        //send the matrices to the shaders
        glUniformMatrix4fv(prog2->getUniform("M"), 1, GL_FALSE, &M[0][0]);
        glUniform3fv(prog2->getUniform("campos"), 1, &mycam.pos[0]);
        glUniform1i(prog2->getUniform("soln"), solution);

        glBindVertexArray(VertexArrayID2);
        //actually draw from vertex 0, 3 vertices
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferIDBox2);
        //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, (void*)0);
        mat4 Vi = glm::transpose(V);
        Vi[0][3] = 0;
        Vi[1][3] = 0;
        Vi[2][3] = 0;
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, Texture);
        
        
        //so what is the point of binding both these textures??? do they both count for 'tex1'?
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, Texture2);
        
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, Texture3);
        
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, Texture4);
        
        glActiveTexture(GL_TEXTURE4);
        glBindTexture(GL_TEXTURE_2D, Texture5);
        
        glActiveTexture(GL_TEXTURE5);
         glBindTexture(GL_TEXTURE_2D, Texture6);

        glm::mat4 TransZ = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 3.0f));

        M =  TransZ * Vi;
        
        


        glUniformMatrix4fv(prog2->getUniform("M"), 1, GL_FALSE, &M[0][0]);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, (void*)0);


        glBindVertexArray(0);
        
        
        glDisable(GL_BLEND);

        prog2->unbind();
    }

};
//******************************************************************************************
int main(int argc, char **argv)
{
    std::string resourceDir = "../../resources"; // Where the resources are loaded from
    if (argc >= 2)
    {
        resourceDir = argv[1];
    }

    Application *application = new Application();

    /* your main will always include a similar set up to establish your window
        and GL context, etc. */
    WindowManager * windowManager = new WindowManager();
    windowManager->init(1920, 1080);
    windowManager->setEventCallbacks(application);
    application->windowManager = windowManager;

    /* This is the code that will likely change program to program as you
        may need to initialize or set up different data and state */
    // Initialize scene.
    application->init(resourceDir);
    application->initGeom();

    // Loop until the user closes the window.
    while(! glfwWindowShouldClose(windowManager->getHandle()))
    {
        // Render scene.
        application->render();

        // Swap front and back buffers.
        glfwSwapBuffers(windowManager->getHandle());
        // Poll for and process events.
        glfwPollEvents();
    }

    // Quit program.
    windowManager->shutdown();
    return 0;
}
