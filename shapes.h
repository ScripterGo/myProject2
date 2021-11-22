#pragma once
#include"util.h"
#include"game_math.h"
using namespace utility;


class cube{
	float length;
	matrix3<float> orientation;
	std::vector<vertex> vertices;
	float x, y, z;
	const int cnt = 8;
public:
	cube(float x, float y, float z, float length);

	void rotate_y(float u);
	void rotate_x(float u);
	void rotate_z(float u);

	void generate_vertices();
	const vertex* get_vertex_data() const;
	int get_vertex_count() const;
};
