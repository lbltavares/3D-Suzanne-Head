#ifndef MAIN_H
#define MAIN_H

#include "SDL2/SDL.h"

#define WIDTH 550
#define HEIGHT 500

#define FPS 120

#define MAX(x, y) x > y ? x : y
#define MIN(x, y) x < y ? x : y


double head[507][4];

void init();
void makePoint(double arr[4], double x, double y, double z, double w);

void matmul(double m1[4], double m2[4][4]);

void translate(const int numVertices, double mesh[numVertices][4], double x, double y, double z);
void scale(const int numVertices, double mesh[numVertices][4], double x, double y, double z);
void rotateX(const int numVertices, double mesh[numVertices][4], double angle);
void rotateY(const int numVertices, double mesh[numVertices][4], double angle);
void rotateZ(const int numVertices, double mesh[numVertices][4], double angle);

void drawmesh(const int numVertices, double mesh[numVertices][4], SDL_Renderer *renderer, int x, int y);

void render(SDL_Renderer *renderer);
void parse_events(SDL_Event *event);

#endif