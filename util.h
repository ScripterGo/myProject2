#pragma once

namespace utility {
	struct vertex {
		float x, y;
	};
	vertex to_screen_space(float x, float y, float z);
}
