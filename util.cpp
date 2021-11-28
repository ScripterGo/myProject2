
#include"util.h"
#include<algorithm>

using namespace std;
	

utility::vertex utility::to_screen_space(float x, float y, float z) {
	float res_x = 0;
	float res_y = 0;

	const float space_width = 640.0f;
	const float space_height = 640.0f;

	float z_translated = z / (space_width/2);

	res_x = x / (space_width / 2.0f) / z_translated;
	res_y = y / (space_height / 2.0f) / z_translated;
	return { res_x, res_y };
}

void utility::tri_make_wind_order(vertex vertices[3]) {
	sort(vertices, vertices + 3, [](const vertex& a, const vertex& b) {
		if (a.x != b.x) return a.x < b.x;
		return false;
	});
}

