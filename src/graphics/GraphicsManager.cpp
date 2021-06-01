#include "GraphicsManager.h"

#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <string>

#include "../utility/FileReader.h"
#define STB_IMAGE_IMPLEMENTATION

GLuint VAO, VBO, IBO, texture;    

void genTexture(){
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

static void renderSceneCB(){
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glutSwapBuffers();
}

static void initializeGlutCallBacks(){
    glutDisplayFunc(renderSceneCB);
    glutIdleFunc(renderSceneCB);
}

static void generateBuffers(){
    float vertices[] = {-1, -1, 0,  0.0, 0.0,
                        -1,  1, 0,  0.0, 1.0,
                         1,  1, 0,  1.0, 1.0,
                         1, -1, 0,  1.0, 0.0};
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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glBindVertexArray(0);
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

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    genTexture();
    loadTexture(Texture());
    generateBuffers();

    // glutMainLoop(); // Avoiding inf. loop
}

GraphicsManager::~GraphicsManager(){}

void GraphicsManager::update(){
    glutMainLoopEvent();
}

void GraphicsManager::loadTexture(Texture texture) {
    // Note: data should be organized left-to-right, then bottom-to-top
    this->tex = texture;

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex.width, tex.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex.data);
    glGenerateMipmap(GL_TEXTURE_2D);
}