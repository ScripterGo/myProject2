
#include"shapes.h"
#include"game_math.h"
#include<algorithm>

using namespace utility;
using namespace std;

d3shape::d3shape(float x, float y, float z, int cnt) : x(x), y(y), z(z), cnt(cnt) {}
void d3shape::rotate_y(float u) {
	matrix3<float> rot_matrix; rot_matrix.to_y_rotation(u);
	this->orientation* rot_matrix;
	this->generate_corner_list();
}
void d3shape::rotate_x(float u) {
	matrix3<float> rot_matrix; rot_matrix.to_x_rotation(u);
	this->orientation* rot_matrix;
	this->generate_corner_list();
};
void d3shape::rotate_z(float u) {
	matrix3<float> rot_matrix; rot_matrix.to_z_rotation(u);
	this->orientation* rot_matrix;
	this->generate_corner_list();
};

int d3shape::get_corner_list_count() const { return (int) this->corner_list.size(); }
int d3shape::get_vertex_list_count() const { return (int) this->vertex_list.size(); };
const vertex* d3shape::get_vertex_list_data() const {
	return this->vertex_list.data();
}
const vector3<float>* d3shape::get_corner_list_data() const {
	return this->corner_list.data();
}

void d3shape::before_render() {
	if (this->get_corner_list_count() == 0) this->generate_corner_list();
	this->generate_vertex_list();
}


cube::cube(float x, float y, float z, float length) : d3shape(x, y, z, 8), length(length) {}
void cube::generate_corner_list() {
	this->corner_list.clear(); this->corner_list.shrink_to_fit();

	float length = this->length;
	float part = length / 2.0f;
	float midX = this->x;
	float midY = this->y;
	float midZ = this->z;

	for (int i = 0; i < 8; i++) {
		float new_pos_x = this->corners[i].getX() * part + midX;
		float new_pos_y = this->corners[i].getY() * part + midY;
		float new_pos_z = this->corners[i].getZ() * part + midZ;
		vector3<float> curr = { new_pos_x - midX, new_pos_y - midY, new_pos_z - midZ };
		curr.transform(this->orientation);
		vector3<float> curr_2 = { curr.getX() + midX, curr.getY() + midY, curr.getZ() + midZ };
		this->corner_list.push_back(curr_2);
	}
}

void cube::generate_vertex_list_wire_frame(){
	this->vertex_list.clear(); this->vertex_list.shrink_to_fit();
	for (int i = 0; i < 8; i++) {
		vector3<float> curr_corner = this->corner_list[i];
		vertex v = to_screen_space(curr_corner.getX(), curr_corner.getY(), curr_corner.getZ());

		for (int j = 0; j < 3; j++) {
			if (this->connection[i][j] <= i) continue;
			int ot = this->connection[i][j];
			vector3<float> ot_corner = this->corner_list[ot];
			vertex v_t = to_screen_space(ot_corner.getX(), ot_corner.getY(), ot_corner.getZ());
			v_t.r = 1; v_t.g = 0; v_t.b = 0;

			this->vertex_list.push_back(v);
			this->vertex_list.push_back(v_t);
		}
	}
}

void cube::generate_vertex_list() {
	this->vertex_list.clear(); this->vertex_list.shrink_to_fit();
	
	vector<int> v_list = {
		1,0,2, 1,2,5,
		7,5,2, 7,2,4,
		3,7,4, 3,6,7,
		3,0,1, 3,1,6,
		4,2,0, 4,0,3,
		6,1,5, 6,5,7
	};
	

	vector3<float> colors[6] = {
		{1.0f,1.0f,1.0f},
		{0.23f, 0.6f, 0.1f},
		{0.22f, 0.8f, 0.0f},
		{0.0f, 1.0f, 0.5f},
		{0.31f, 0.5f, 0.8f},
		{1.0f, 0.0f, 1.0f}
	};


	for (int i = 0; i < v_list.size(); i++) {
		vector3<float> corner = this->corner_list[v_list[i]];
		vertex new_vert = to_screen_space(corner.getX(), corner.getY(), corner.getZ());
		new_vert.r = colors[i%6].getX(); new_vert.g = colors[i%6].getY(); new_vert.b = colors[i%6].getZ();

		this->vertex_list.push_back(new_vert);
	}
}


tri::tri(const float corners[3][3]) : d3shape(get_mid_val(corners[0][0], corners[1][0], corners[2][0]), get_mid_val(corners[0][1], corners[1][1], corners[2][1]), get_mid_val(corners[0][2], corners[1][2], corners[2][2]), 3) {
	this->corner_pos_list.push_back(vector3<float>(corners[0][0], corners[0][1], corners[0][2]));
	this->corner_pos_list.push_back(vector3<float>(corners[1][0], corners[1][1], corners[1][2]));
	this->corner_pos_list.push_back(vector3<float>(corners[2][0], corners[2][1], corners[2][2]));
}

float tri::get_mid_val(float x0, float x1, float x2) {
	return (max(x0, max(x1, x2)) - min(x0, min(x1, x2))) / 2;
}

void tri::generate_corner_list() {
	this->corner_list.clear(); this->corner_list.shrink_to_fit();
	
	for (int i = 0; i < 3; i++) {
		vector3<float> c = this->corner_pos_list[i];
		c.transform(this->orientation);
		this->corner_list.push_back(c);
	}
}

void tri::generate_vertex_list() {
	this->vertex_list.clear(); this->vertex_list.resize(0);

	for (int i = 0; i < 3; i++) {
		vector3<float> c = this->corner_list[i];
		vertex u = to_screen_space(c.getX(), c.getY(), c.getZ());
		u.r = 1.0f; u.b = 1.0f; u.g = 0;

		this->vertex_list.push_back(u);
	}
}

