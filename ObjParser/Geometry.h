#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include "Vecteur3.h"
#include <assert.h> 

using namespace Math3D;

struct Vertex
{
    float Texture[ 2 ];
    CVecteur3 Normal;
    CVecteur3 Position;
    

    Vertex( void )
        : Normal( CVecteur3:: ZERO )
        , Position( CVecteur3::ZERO )
    {
        Texture[ 0 ] = 0.0f;
        Texture[ 1 ] = 0.0f;
    }

    Vertex( const CVecteur3& P, const CVecteur3& N = CVecteur3::ZERO )
        : Normal( N )
        , Position( P )
    {
        Texture[ 0 ] = 0.0f;
        Texture[ 1 ] = 0.0f;
    }
};

struct Triangle
{
    unsigned int Vertex[ 3 ];

    Triangle( void )
    {
        memset( Vertex, 0, 3 * sizeof( unsigned int ) );
    }

    Triangle( const int V0, const int V1, const int V2 )
    {
        Vertex[ 0 ] = V0;
        Vertex[ 1 ] = V1;
        Vertex[ 2 ] = V2;
    }
};

struct Quad
{
    unsigned int Vertex[ 4 ];

    Quad( void )
    {
        memset( Vertex, 0, 4 * sizeof( unsigned int ) );
    }

    Quad( const int V0, const int V1, const int V2, const int V3 )
    {
        Vertex[ 0 ] = V0;
        Vertex[ 1 ] = V1;
        Vertex[ 2 ] = V2;
        Vertex[ 3 ] = V3;
    }
};

static void getFloatsFromVertex(Vertex v, float* float_array)
{
	//assert(float_array.size() == 8);

	float_array[0] = v.Texture[0];
	float_array[1] = v.Texture[1];
	float_array[2] = v.Normal.x;
	float_array[3] = v.Normal.y;
	float_array[4] = v.Normal.z;
	float_array[5] = v.Position.x;
	float_array[6] = v.Position.y;
	float_array[7] = v.Position.z;
};

static vector<float> getFloatsFromVertices(vector<Vertex> vertices)
{
	//iterate over vertices and create a big float vector
	unsigned int size = vertices.size();
	//unsigned int floats_size = size*sizeof(float);
	vector<float> values;
	float v_vals[8];
	for (unsigned i = 0; i < size; i++) {
		getFloatsFromVertex(vertices[i], v_vals);
		for (int j = 0; j < 8; j++){
			values.push_back(v_vals[j]);
		}
	}
	return values;
};

#endif