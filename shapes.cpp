
#include"shapes.h"
#include"game_math.h"
#include<algorithm>

using namespace utility;
using namespace std;

const float eps = 0.001;

cube::cube(float x, float y, float z, float length) : x(x), y(y), z(z), length(length) {}

void cube::rotate_y(float u) {
	matrix3<float> rot_matrix; rot_matrix.to_y_rotation(u);
	this->orientation* rot_matrix;
}

void cube::rotate_x(float u) {
	matrix3<float> rot_matrix; rot_matrix.to_x_rotation(u);
	this->orientation* rot_matrix;
};
void cube::rotate_z(float u) {};
int cube::get_vertex_count() const { return this->vertices.size(); };

void cube::generate_vertices(){
	this->vertices.clear(); this->vertices.resize(0);

	float length = this->length;
	float part = length / 2.0f;
	float midX = this->x;
	float midY = this->y;
	float midZ = this->z;

	vector3<float> corners[8] = {
		{1,1,1},
		{1,1,-1},
		{1,-1,1},
		{-1,1,1},
		{-1,-1,1},
		{1,-1,-1},
		{-1,1,-1},
		{-1,-1,-1}
	};

	int connection[8][3] = {
		{1,2,3},
		{0, 5,6},
		{0, 4, 5},
		{0, 4, 6},
		{2,3,7},
		{1, 2, 7},
		{1, 3, 7},
		{4,5,6}
	};

	for (int i = 0; i < 8; i++) {
		float new_pos_x = corners[i].getX() * part + midX;
		float new_pos_y = corners[i].getY() * part + midY;
		float new_pos_z = corners[i].getZ() * part + midZ;
		vector3<float> curr = { new_pos_x - midX, new_pos_y - midY, new_pos_z - midZ};
		curr.transform(this->orientation);
		vector3<float> curr_2 = { curr.getX() + midX, curr.getY()+midY, curr.getZ()+midZ};
		vertex v = to_screen_space(curr_2.getX(), curr_2.getY(), curr_2.getZ());

		for (int j = 0; j < 3; j++) {
			if (connection[i][j] <= i) continue;
			int ot = connection[i][j];
			new_pos_x = corners[ot].getX() * part + midX;
			new_pos_y = corners[ot].getY() * part + midY;
			new_pos_z = corners[ot].getZ() * part + midZ;

			vector3<float> curr_t = { new_pos_x-midX, new_pos_y-midY, new_pos_z-midZ };
			curr_t.transform(this->orientation);
			vector3<float> curr_t_2 = { curr_t.getX() + midX, curr_t.getY() + midY, curr_t.getZ() + midZ };
			vertex v_t = to_screen_space(curr_t_2.getX(), curr_t_2.getY(), curr_t_2.getZ());

			this->vertices.push_back(v);
			this->vertices.push_back(v_t);
		}
	}
}

const vertex* cube::get_vertex_data() const {
	return this->vertices.data();
}

