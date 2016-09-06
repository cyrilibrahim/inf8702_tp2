//
// Coherent noise function over 1, 2 or 3 dimensions
// (copyright Ken Perlin)
//

#include "noise.h"


#define MAXB 0x100
#define N 0x1000
#define NP 12   // 2^N
#define NM 0xfff

#define cc(i, j) (i) + ((j)*width)
#define s_curve(t) ( t * t * (3. - 2. * t) )
#define lerp(t, a, b) ( a + t * (b - a) )
#define setup(i, b0, b1, r0, r1)\
        t = vec[i] + N;\
        b0 = ((int)t) & BM;\
        b1 = (b0+1) & BM;\
        r0 = t - (int)t;\
        r1 = r0 - 1.;
#define at2(rx, ry) ( rx * q[0] + ry * q[1] )
#define at3(rx, ry, rz) ( rx * q[0] + ry * q[1] + rz * q[2] )

static void initNoise();

static int p[MAXB + MAXB + 2];
static double g3[MAXB + MAXB + 2][3];
static double g2[MAXB + MAXB + 2][2];
static double g1[MAXB + MAXB + 2];

int start;
int B;
int BM;


void SetNoiseFrequency(int frequency)
{
	start = 1;
	B = frequency;
	BM = B-1;
}

double noise1(double arg)
{
	int bx0, bx1;
	double rx0, rx1, sx, t, u, v, vec[1];

	vec[0] = arg;
	if (start)
	{
		start = 0;
		initNoise();
	}

	setup(0, bx0, bx1, rx0, rx1);

	sx = s_curve(rx0);
	u = rx0 * g1[p[bx0]];
	v = rx1 * g1[p[bx1]];

	return(lerp(sx, u, v));
}

double noise2(double vec[2])
{
	int bx0, bx1, by0, by1, b00, b10, b01, b11;
	double rx0, rx1, ry0, ry1, *q, sx, sy, a, b, t, u, v;
	int i, j;

	if (start)
	{
		start = 0;
		initNoise();
	}

	setup(0, bx0, bx1, rx0, rx1);
	setup(1, by0, by1, ry0, ry1);

	i = p[bx0];
	j = p[bx1];

	b00 = p[i + by0];
	b10 = p[j + by0];
	b01 = p[i + by1];
	b11 = p[j + by1];

	sx = s_curve(rx0);
	sy = s_curve(ry0);

	q = g2[b00]; u = at2(rx0, ry0);
	q = g2[b10]; v = at2(rx1, ry0);
	a = lerp(sx, u, v);

	q = g2[b01]; u = at2(rx0, ry1);
	q = g2[b11]; v = at2(rx1, ry1);
	b = lerp(sx, u, v);

	return lerp(sy, a, b);
}

double noise3(double vec[3])
{
	int bx0, bx1, by0, by1, bz0, bz1, b00, b10, b01, b11;
	double rx0, rx1, ry0, ry1, rz0, rz1, *q, sy, sz, a, b, c, d, t, u, v;
	int i, j;

	if (start)
	{
		start = 0;
		initNoise();
	}

	setup(0, bx0, bx1, rx0, rx1);
	setup(1, by0, by1, ry0, ry1);
	setup(2, bz0, bz1, rz0, rz1);

	i = p[bx0];
	j = p[bx1];

	b00 = p[i + by0];
	b10 = p[j + by0];
	b01 = p[i + by1];
	b11 = p[j + by1];

	t  = s_curve(rx0);
	sy = s_curve(ry0);
	sz = s_curve(rz0);

	q = g3[b00 + bz0]; u = at3(rx0, ry0, rz0);
	q = g3[b10 + bz0]; v = at3(rx1, ry0, rz0);
	a = lerp(t, u, v);

	q = g3[b01 + bz0]; u = at3(rx0, ry1, rz0);
	q = g3[b11 + bz0]; v = at3(rx1, ry1, rz0);
	b = lerp(t, u, v);

	c = lerp(sy, a, b);

	q = g3[b00 + bz1]; u = at3(rx0, ry0, rz1);
	q = g3[b10 + bz1]; v = at3(rx1, ry0, rz1);
	a = lerp(t, u, v);

	q = g3[b01 + bz1]; u = at3(rx0, ry1, rz1);
	q = g3[b11 + bz1]; v = at3(rx1, ry1, rz1);
	b = lerp(t, u, v);

	d = lerp(sy, a, b);

	return lerp(sz, c, d);
}

void normalize2(double v[2])
{
	double s;

	s = sqrt(v[0] * v[0] + v[1] * v[1]);
	v[0] = v[0] / s;
	v[1] = v[1] / s;
}

void normalize3(double v[3])
{
	double s;

	s = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	v[0] = v[0] / s;
	v[1] = v[1] / s;
	v[2] = v[2] / s;
}

void initNoise()
{
	int i, j, k;

	srand(30757);
	for (i = 0; i < B; i++)
	{
		p[i] = i;
		g1[i] = (double)((rand() % (B + B)) - B) / B;

		for (j = 0; j < 2; j++)
			g2[i][j] = (double)((rand() % (B + B)) - B) / B;
		normalize2(g2[i]);

		for (j = 0; j < 3; j++)
			g3[i][j] = (double)((rand() % (B + B)) - B) / B;
		normalize3(g3[i]);
	}

	while (--i)
	{
		k = p[i];
		p[i] = p[j = rand() % B];
		p[j] = k;
	}

	for (i = 0; i < B + 2; i++)
	{
		p[B + i] = p[i];
		g1[B + i] = g1[i];
		for (j = 0; j < 2; j++)
			g2[B + i][j] = g2[i][j];
		for (j = 0; j < 3; j++)
			g3[B + i][j] = g3[i][j];
	}
}

// My harmonic summing functions - PDB

//
// In what follows "alpha" is the weight when the sum is formed.
// Typically it is 2, As this approaches 1 the function is noisier.
// "beta" is the harmonic scaling/spacing, typically 2.
//

double PerlinNoise1D(double x,double alpha,double beta,int n)
{
	int i;
	double val,sum = 0;
	double p,scale = 1;

	p = x;
	for (i = 0; i < n; i++)
	{
		val = noise1(p);
		sum += val / scale;
		scale *= alpha;
		p *= beta;
	}
	return(sum);
}

double PerlinNoise2D(double x, double y, double alpha, double beta, int n)
{
	int i;
	double val, sum = 0;
	double p[2], scale = 1;

	p[0] = x;
	p[1] = y;
	for (i = 0; i < n; i++)
	{
		val = noise2(p);
		sum += val / scale;
		scale *= alpha;
		p[0] *= beta;
		p[1] *= beta;
	}
	return(sum);
	}

double PerlinNoise3D(double x, double y, double z, double alpha, double beta, int n)
{
	int i;
	double val,sum = 0;
	double p[3],scale = 1;

	p[0] = x;
	p[1] = y;
	p[2] = z;
	for (i = 0; i < n; i++)
	{
		val = noise3(p);
		sum += val / scale;
		scale *= alpha;
		p[0] *= beta;
		p[1] *= beta;
		p[2] *= beta;
	}
	return(sum);
}
GLubyte * make2DNoiseTexture(int width, int height, int startFreq, int numOctaves, double amp)
{
 	int f, i, j, inc;
	int startFrequency = startFreq;
	double ni[2];
	double inci, incj;
	int frequency = startFrequency;
	GLubyte* ptr;

	GLubyte * Noise2DTexPtr = (GLubyte*) malloc(width * height * 4);
	for (f = 0, inc = 0; f < numOctaves; ++f, frequency *= 2, ++inc, amp *= 0.5)
	{
		SetNoiseFrequency(frequency);
		ptr = Noise2DTexPtr;
		ni[0] = ni[1] = 0;

		inci = 1.0 / ((double)width / (double)frequency);
		for (i = 0; i < width; ++i, ni[0] += inci)
		{
			incj = 1.0 / ((double)height / (double)frequency);
			for (j = 0; j < height; ++j, ni[1] += incj, ptr += 4)
			{
				*(ptr + inc) = (GLubyte) (((noise2(ni) + 1.0) * amp) * 128.0);
			}
		}
	}
   return (Noise2DTexPtr);
}

GLubyte * make3DNoiseTexture(int width, int height, int depth, int startFreq, int numOctaves, double amp)
{
	int f, i, j, k, inc;
	int startFrequency = startFreq;
	double ni[3];
	double inci, incj, inck;
	int frequency = startFrequency;
	GLubyte* ptr;

	GLubyte * Noise3DTexPtr = (GLubyte*) malloc(width * height * depth * 4);
	for (f = 0, inc = 0; f < numOctaves; ++f, frequency *= 2, ++inc, amp *= 0.5)
	{
		SetNoiseFrequency(frequency);
		ptr = Noise3DTexPtr;
		ni[0] = ni[1] = ni[2] = 0.0;

		inci = 1.0 / ((double)width / (double)frequency);
		for (i = 0; i < width; ++i, ni[0] += inci)
		{
			incj = 1.0 / ((double)height / (double)frequency);
			for (j = 0; j < height; ++j, ni[1] += incj)
			{
				inck = 1.0 / ((double)depth / (double)frequency);
				for (k = 0; k < depth; ++k, ni[2] += inck, ptr += 4)
					*(ptr + inc) = (GLubyte) (((noise3(ni) + 1.0) * amp) * 128.0);
			}
		}
	}
   return (Noise3DTexPtr);
}


float * make2DNoiseArray(int width, int height, int freq, float amp)
{
 	int i, j, inc;
	double ni[2];
	double inci, incj;
	float* noise2DArray;

   // allocation de l'espace m�moire
   noise2DArray = (float*) malloc(width * height * sizeof(float));

   inc = 0;
   ni[0] = ni[1] = 0.0;
   
	SetNoiseFrequency(freq);

	incj = 1.0 / ((double)height / (double)freq);
   for (j = 0; j < height; ++j, ni[1] += incj)
	{
      inci = 1.0 / ((double)width / (double)freq);
		for (i = 0; i < width; ++i, ni[0] += inci)
		{
         noise2DArray[cc(i,j)] = (float)((noise2(ni) + 0.5) * double(amp));  
		}
	}
   return (noise2DArray);
}



vect3D * compute2DNormalTexture(float * texNoise2D, int width, int height) 
{
   int i,j;
   vect3D * texNormal2D;
   vect3D tangentX, tangentY, normale;
   vect3D v;
   float norm;

   // allocation de m�moire
   texNormal2D = (vect3D*) malloc(width * height * sizeof(vect3D));

   v.x = 0.0;
   v.y = 0.0;
   v.z = 1.0;

   // fixer la normale � (0,0,1) pour toute la p�riph�rie de la texture
   j = 0;
   for (i=0; i<width; i++)
      texNormal2D[cc(i,j)] = v;

   j = height-1;
   for (i=0; i<width; i++)
      texNormal2D[cc(i,j)] = v;

   i = 0;
   for (j=0; j<height; j++)
      texNormal2D[cc(i,j)] = v;

   i = width - 1;
   for (j=0; j<height; j++)
      texNormal2D[cc(i,j)] = v;

   // calculer la normale sur toute la surface restante de la texture
   for (i=1; i<width-1; i++) {
      for (j=1; j<height-1; j++) {
         // calculer la d�riv�e (diff�rence finie) en x
         tangentX.x = 0.6;
         tangentX.y = 0.0;
         tangentX.z = texNoise2D[cc((i+1),j)] - texNoise2D[cc((i-1),j)];

         // calculer la d�riv�e (diff�rence finie) en y
         tangentY.x = 0.0;
         tangentY.y = 0.6;
         tangentY.z = texNoise2D[cc(i,(j+1))] - texNoise2D[cc(i,(j-1))];
         
         // calculer l'approximation de la normale au point(i,j)
         normale.x = (tangentX.y*tangentY.z) - (tangentX.z*tangentY.y);
         normale.y = (tangentX.z*tangentY.x) - (tangentX.x*tangentY.z);
         normale.z = (tangentX.x*tangentY.y) - (tangentX.y*tangentY.x);

         // calculer la norme du vecteur
         norm = sqrt((normale.x*normale.x) + (normale.y*normale.y) + (normale.z*normale.z));

         v.x = normale.x / norm;
         v.y = normale.y / norm;
         v.z = normale.z / norm;

         // normaliser
         texNormal2D[cc(i,j)] = v;
      }
   }
   return texNormal2D;
}

