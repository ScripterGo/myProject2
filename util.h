#pragma once

namespace utility {
	struct vertex {
		float x, y;
		float r, g, b;
	};
	vertex to_screen_space(float x, float y, float z);
	void tri_make_wind_order(vertex vertices[3]);
}
