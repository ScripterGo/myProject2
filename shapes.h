#pragma once
#include"util.h"
#include"game_math.h"
using namespace utility;


class d3shape {
protected:
	matrix3<float> orientation;
	std::vector<vertex> vertex_list; //Buffer for 2d vertices
	std::vector<vector3<float>> corner_list; //Buffer for the corners
	std::vector<vector3<float>> corner_pos_list;
	float x, y, z;
	int cnt;

public:
	d3shape(float x, float y, float z, int cnt);

	virtual void generate_vertex_list() = 0;
	virtual void generate_corner_list() = 0;

	void rotate_y(float u);
	void rotate_x(float u);
	void rotate_z(float u);

	int get_vertex_list_count() const;
	const vertex* get_vertex_list_data() const;
	int get_corner_list_count() const;
	const vector3<float>* get_corner_list_data() const;

	void before_render();
};

class cube : public d3shape{
	float length;
	const vector3<float> corners[8] = {
			{1,1,1},
			{1,1,-1},
			{1,-1,1},
			{-1,1,1},
			{-1,-1,1},
			{1,-1,-1},
			{-1,1,-1},
			{-1,-1,-1}
	};
	const int connection[8][3] = { //Describes the lines
		{1,2,3},
		{0,5,6},
		{0,4,5},
		{0,4,6},
		{2,3,7},
		{1,2,7},
		{1,3,7},
		{4,5,6}
	};



public:
	cube(float x, float y, float z, float length);
	void generate_vertex_list_wire_frame();
	void generate_vertex_list();
	void generate_corner_list();
};

class tri : public d3shape {

public:
	tri(const float corners[3][3]);
	void generate_vertex_list();
	void generate_corner_list();
	static float get_mid_val(float x0, float x1, float x2);
};


