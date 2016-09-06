
#ifndef NOISE_H
#define NOISE_H

#include <stdlib.h>
#include <cmath>
#include <GL/glew.h>
#include "Cst.h"

void SetNoiseFrequency(int frequency);
double noise1(double arg);
double noise2(double vec[2]);
double noise3(double vec[3]);
void normalize2(double v[2]);
void normalize3(double v[3]);
double PerlinNoise1D(double x,double alpha,double beta,int n);
double PerlinNoise2D(double x, double y, double alpha, double beta, int n);
double PerlinNoise3D(double x, double y, double z, double alpha, double beta, int n);
void make1DNoiseTexture(GLubyte* Noise1DTexPtr, int width, int startFreq = 4, int numOctaves = 4, double amp = 0.5);
GLubyte * make2DNoiseTexture(int width, int height, int startFreq = 4, int numOctaves = 4, double amp = 0.5);
GLubyte * make3DNoiseTexture(int width, int height, int depth, int startFreq = 4, int numOctaves = 4, double amp = 0.5);
float* make2DNoiseArray(int width, int height, int freq = 4, float amp = 1.0);
vect3D * compute2DNormalTexture(float * texNoise2D, int width, int height);

#endif