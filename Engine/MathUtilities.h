#pragma once

namespace MathUtilities {
	int LerpInt (const int a, const int b, const float t) {
		return int(a * (1 - t) + b * (t));
	}
}