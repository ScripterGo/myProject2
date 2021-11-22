#pragma once


#include<vector>
using namespace std;

template<typename T>
class matrix3 {
	vector<vector<T>> data;

public:
	matrix3() {
		this->data.assign(3, vector<T>(3));
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				this->data[i][j] = (i == j);
			}
		}
	}

	void operator*(const matrix3<T>& ot) {
		for (int i = 0; i < 3; i++) {
			T buffer[3];
			for (int j = 0; j < 3; j++) {
				T ans = (T)0;
				for (int k = 0; k < 3; k++) {
					ans += this->data[i][k] * ot.data[k][j];
				}
				buffer[j] = ans;
			}
			for (int j = 0; j < 3; j++) {
				this->data[i][j] = buffer[j];
			}
		}
	}

	void to_y_rotation(float u) {
		T cos_u = cos(u);
		T sin_u = sin(u);
		this->data = {
			{cos_u, (T)0, -sin_u},
			{(T)0,(T)1,(T)0},
			{sin_u, T(0), cos_u}
		};
	}

	void to_x_rotation(float u) {
		T cos_u = cos(u);
		T sin_u = sin(u);
		this->data = {
			{(T)1, 0, 0},
			{(T)0, cos_u, sin_u},
			{(T)0, -sin_u, cos_u}
		};
	}

	T get(int i, int j) const {
		return this->data[i][j];
	}
};

template<typename T>
class vector3 {
	float x, y, z;
public:
	vector3(T x, T y, T z) : x(x), y(y), z(z) {}
	vector3() : x((T)0), y((T)0), z((T)0) {};

	void operator=(vector3<T>& ot) {
		this->x = ot.x;
		this->y = ot.y;
		this->z = ot.z;
	}

	void transform(const matrix3<T>& mat) {
		T curr_x = this->x;
		T curr_y = this->y;
		T curr_z = this->z;

		this->x = curr_x * mat.get(0, 0) + curr_y * mat.get(0, 1) + curr_z * mat.get(0, 2);
		this->y = curr_x * mat.get(1, 0) + curr_y * mat.get(1, 1) + curr_z * mat.get(1, 2);
		this->z = curr_x * mat.get(2, 0) + curr_y * mat.get(2, 1) + curr_z * mat.get(2, 2);
	}

	T getX()const { return this->x; }
	T getY() const { return this->y; }
	T getZ() const { return this->z; }
};
