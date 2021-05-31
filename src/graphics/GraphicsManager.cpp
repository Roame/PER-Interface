#include "GraphicsManager.h"

#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <string>

#include "FileReader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

GLuint VAO, VBO, IBO, texture;

// const char* vertexShaderSource = "#version 330 core\n"
//     "layout (location = 0) in vec3 aPos;\n"
//     "layout (location = 1) in vec3 aColor;\n"
//     "layout (location = 2) in vec2 aTexCoord;\n"
//     "out vec3 ourColor;\n"
//     "out vec2 texCoord;\n"
//     "void main()\n"
//     "{\n"
//     "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//     "   ourColor = aColor;\n"
//     "   texCoord = aTexCoord;\n"
//     "}\0";

// const char* fragmentShaderSource = "#version 330 core\n"
//     "out vec4 FragColor;\n"
//     "in vec3 ourColor;\n"
//     "in vec2 texCoord;\n"
//     "uniform sampler2D ourTexture;\n"
//     "void main() {\n"
//     "   FragColor= texture(ourTexture, texCoord);"
//     "}\0";
    

void genTexture(){
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void loadTextureData(){
    unsigned char data[1920*1080*4];
    for(int i = 0; i < 1920; i++){
        for(int j = 0; j < 1080; j++){
            int index = 4*(j+i*1080);
            data[index] = (int) (i/1920.0*255.0);
            data[index+1] = 0;
            data[index+2] = 0;
            data[index+3] = 255;
        }
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1920, 1080, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
}

static void renderSceneCB(){
    glClear(GL_COLOR_BUFFER_BIT);

    glBindTexture(GL_TEXTURE_2D, texture);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);


    // glBindTexture(GL_TEXTURE_2D, texture);
    // loadTextureData();
    // glEnable(GL_TEXTURE_2D);

    glutSwapBuffers();
}

static void initializeGlutCallBacks(){
    glutDisplayFunc(renderSceneCB);
    glutIdleFunc(renderSceneCB);
}

static void generateBuffers(){
    float vertices[] = {-1, -1, 0,  1.0, 0.0, 0.0,  0.0, 0.0,
                        -1,  1, 0,  0.0, 1.0, 0.0,  1.0, 0.0,
                         1,  1, 0,  0.0, 0.0, 1.0,  1.0, 1.0,
                         1, -1, 0,  1.0, 1.0, 0.0,  0.0, 1.0};
    int indices[] = { 0, 1, 2,
                      2, 3, 0};
    
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*) (6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

static void compileShaders(){
    // Getting source
    std::string vertexShaderSource;
    std::string fragmentShaderSource;
    try {
        vertexShaderSource = readFile("shaders/vShader.txt");
    } catch(const char* err){
        std::cout << "Error loading vertex shader: " << err << std::endl;
        exit(1);
    }
    try {
        fragmentShaderSource = readFile("shaders/fShader.txt");
    } catch(const char* err){
        std::cout << "Error loading fragment shader: " << err << std::endl;
        exit(1);
    }
    const GLchar* vShaderPtr = vertexShaderSource.c_str();
    const GLchar* fShaderPtr = fragmentShaderSource.c_str();

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vShaderPtr, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fShaderPtr, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::FRAGMENT::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    glUseProgram(shaderProgram);

    // Cleaning up
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

GraphicsManager::GraphicsManager(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Placeholder");

    initializeGlutCallBacks();

    GLenum res = glewInit();
    if(res != GLEW_OK) {
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
        exit(1);
    }

    compileShaders();

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    genTexture();
    loadTextureData();
    generateBuffers();

    glutMainLoop();
}

GraphicsManager::~GraphicsManager(){}