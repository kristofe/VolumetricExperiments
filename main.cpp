//
//  main.cpp
//  Texture3DExperiments
//
//  Created by Kristofer Schlachter on 7/8/13.
//  Copyright (c) 2013 Kristofer Schlachter. All rights reserved.
//
#define GLFW_INCLUDE_GLCOREARB
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

GLuint gVAO = 0;
GLuint gVBO = 0;
GLint  shaderProgram1 = 0;
GLint  vertSlot = 0;
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
  //glMatrixMode(GL_PROJECTION);
  glm::mat4 ortho = glm::ortho(-ratio,ratio, -1.0f, 1.0f, 1.0f, -1.0f);
  //glLoadMatrixf(&ortho[0][0]);

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


void loadTriangle()
{
   // make and bind the VAO
   glGenVertexArrays(1, &gVAO);
   glBindVertexArray(gVAO);

   // make and bind the VBO
   glGenBuffers(1, &gVBO);
   glBindBuffer(GL_ARRAY_BUFFER, gVBO);

   // Put the three triangle verticies into the VBO
   GLfloat vertexData[] = {
      //  X     Y     Z
      0.0f, 0.8f, 0.0f,
      -0.8f,-0.8f, 0.0f,
      0.8f,-0.8f, 0.0f,
   };
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

   // connect the xyz to the "vert" attribute of the vertex shader
   GLint vertSlot = glGetAttribLocation(shaderProgram1,"vert");
   glEnableVertexAttribArray(vertSlot);
   glVertexAttribPointer(vertSlot, 3, GL_FLOAT, GL_FALSE, 0, NULL);

   // unbind the VBO and VAO
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glBindVertexArray(0);

   GLUtil::checkGLErrors();
}

void drawTriangle()
{
   // bind the program (the shaders)
    glUseProgram(shaderProgram1);

    // bind the VAO (the triangle)
    glBindVertexArray(gVAO);

    // draw the VAO
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // unbind the VAO
    glBindVertexArray(0);

    // unbind the program
    glUseProgram(0);
}

int main(void)
{
  test();
  GLFWwindow* window;
  glfwSetErrorCallback(error_callback);
  if (!glfwInit())
    exit(EXIT_FAILURE);
  
  hintOpenGL32CoreProfile();
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
  loadTriangle();

  glm::mat4 identityMatrix = glm::mat4(1.0);//Identity matrix

  while (!glfwWindowShouldClose(window))
  {
    sizeViewport(window);
    //glMatrixMode(GL_MODELVIEW);
    glm::mat4 rotMat = glm::rotate(identityMatrix,(float) glfwGetTime() * 50.f,
                                   glm::vec3(0.f,0.f,1.f));
    //glLoadMatrixf(&rotMat[0][0]);

    drawTriangle();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwDestroyWindow(window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}
