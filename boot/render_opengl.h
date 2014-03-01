#ifndef RENDER_OPENGL_H
#define RENDER_OPENGL_H

#include <iostream>
#include <string>
#include <SDL.h>
#include <glew.h>
#include <SDL_opengl.h>

extern SDL_Window* gWindow;
extern SDL_GLContext gContext;
extern bool gRenderQuad;

//Graphics program
extern GLuint gProgramID;
extern GLint gVertexPos2DLocation;
extern GLuint gVBO;
extern GLuint gIBO;

void printProgramLog( GLuint program );
void printShaderLog( GLuint shader );

#endif