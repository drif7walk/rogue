#ifndef INCLUDES_H
#define INCLUDES_H

#define false 0 
#define  true 1
#define bool unsigned char 
// OpenGL / glew Headers
#define GL3_PROTOTYPES 1
#include <GL/glew.h>

// SDL2 Headers
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

SDL_Renderer* renderer;
#include "assets.h"
#include "engine.h"

#endif