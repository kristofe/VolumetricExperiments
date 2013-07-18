//
//  main.cpp
//  Texture3DExperiments
//
//  Created by Kristofer Schlachter on 7/8/13.
//  Copyright (c) 2013 Kristofer Schlachter. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "GLFW/glfw3.h" // - lib is in /usr/local/lib/libglfw3.a
#include "test.h"
#include "glutil.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

using namespace kdslib;

//TODO: Move this kind of stuff into a renderer
typedef struct {
   GLfloat x, y, z, r, g, b;
} Triangle;

Triangle triangle[3] = {
   {-0.6f, -0.4f, 0.f, 1.f, 0.f, 0.f},
   {0.6f, -0.4f, 0.f,0.f, 1.f, 0.f},
   {0.f, 0.6f, 0.f,0.f, 0.f, 1.f}
};

GLubyte indices[3] = {
    0, 1, 2
};

GLuint vboVerts;
GLuint vboIndices;
GLint  shaderProgram1;
/////

void hintOpenGL32CoreProfile(){
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void sizeViewport(GLFWwindow* window){
  float ratio;
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  ratio = width / (float) height;
  glViewport(0, 0, width, height);
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glm::mat4 ortho = glm::ortho(-ratio,ratio, -1.0f, 1.0f, 1.0f, -1.0f);
  glLoadMatrixf(&ortho[0][0]);

  //glLoadIdentity();
  //glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
}

static void error_callback(int error, const char* description)
{
  fputs(description, stderr);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}

void loadAndLinkShaders(){
      shaderProgram1 = GLUtil::loadShaders("../vertShader.glsl","../fragShader.glsl","");
}

void setupVBO()
{
   glGenBuffers(1,&vboVerts);
   glBindBuffer(GL_ARRAY_BUFFER, vboVerts);
   glBufferData(GL_ARRAY_BUFFER, sizeof(triangle),&triangle[0].x,GL_STATIC_DRAW);


   glGenBuffers(1, &vboIndices);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndices);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices[0], GL_STATIC_DRAW);

   GLUtil::checkGLErrors();
}

void drawVBO() {
    //glEnableVertexAttribArray(positionSlot);
    //glEnableVertexAttribArray(uvSlot);


    glBindBuffer(GL_ARRAY_BUFFER, vboVerts);

    //glUniformMatrix4fv(projectionUniformSlot, 1, 0, projectionMatrix);
    //glUniformMatrix4fv(modelViewUniformSlot, 1, 0, modelviewMatrix);
    //glVertexAttribPointer(positionSlot, 2, GL_FLOAT, GL_FALSE, sizeof(V2fT2f),  BUFFER_OFFSET(0));
    //glVertexAttribPointer(uvSlot, 2, GL_FLOAT, GL_FALSE, sizeof(V2fT2f),  BUFFER_OFFSET(sizeof(float)*2));



    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndices);
    glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_BYTE, 0);

    //glDisableVertexAttribArray(positionSlot);
    //glDisableVertexAttribArray(uvSlot);
    GLUtil::checkGLErrors();

}
int main(void)
{
  test();
  GLFWwindow* window;
  glfwSetErrorCallback(error_callback);
  if (!glfwInit())
    exit(EXIT_FAILURE);
  
  //hintOpenGL32CoreProfile();
  window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
  if (!window)
  {
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  glfwMakeContextCurrent(window);
  glfwSetKeyCallback(window, key_callback);

  std::cout << GLUtil::getOpenGLInfo() << std::endl;std::cout.flush();
  loadAndLinkShaders();
  setupVBO();
  glm::mat4 identityMatrix = glm::mat4(1.0);//Identity matrix

  while (!glfwWindowShouldClose(window))
  {
    sizeViewport(window);
    glMatrixMode(GL_MODELVIEW);
    //TODO: MAKE THIS OPENGL 3.2 Compatible
    glm::mat4 rotMat = glm::rotate(identityMatrix,(float) glfwGetTime() * 50.f,
                                   glm::vec3(0.f,0.f,1.f));
    glLoadMatrixf(&rotMat[0][0]);

    //TODO: DO full opengl 3.2 with shaders
    //drawVBO();

    glBegin(GL_TRIANGLES);
    glColor3f(1.f, 0.f, 0.f);
    glVertex3f(-0.6f, -0.4f, 0.f);
    glColor3f(0.f, 1.f, 0.f);
    glVertex3f(0.6f, -0.4f, 0.f);
    glColor3f(0.f, 0.f, 1.f);
    glVertex3f(0.f, 0.6f, 0.f);
    glEnd();


    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwDestroyWindow(window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}
