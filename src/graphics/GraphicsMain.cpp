#include "GraphicsMain.h"

#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

GLuint VBO;

static void RenderSceneCB(){
    glClear(GL_COLOR_BUFFER_BIT);


    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(0);

    glutSwapBuffers();
}

static void InitializeGlutCallBacks(){
    glutDisplayFunc(RenderSceneCB);
}

static void CreateVertexBuffer(){
    float vertices[] = {0, 0, 0,
                        1, 1, 0,
                        1, 0, 0};
    
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

GraphicsMain::GraphicsMain(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Placeholder");

    InitializeGlutCallBacks();

    GLenum res = glewInit();
    if(res != GLEW_OK) {
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
        exit(1);
    }

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    CreateVertexBuffer();

    glutMainLoop();
}

GraphicsMain::~GraphicsMain(){

}