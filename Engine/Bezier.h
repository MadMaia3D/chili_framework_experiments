#pragma once
#include "Graphics.h"
#include "MathUtilities.h"

class QuadraticBezier {
public:
	QuadraticBezier(Vec2 p1, Vec2 p2, Vec2 p3)
		:
		p1(p1),
		p2(p2),
		p3(p3)
	{}
	void Draw(Graphics& gfx, Color c = Colors::White)
	{
		gfx.DrawLine(p1, p2, Colors::Gray);
		gfx.DrawLine(p2, p3, Colors::Gray);

		float step_delta = 1.0f / steps;

		Vec2 previous_position = p1;

		for (int i = 1; i <= steps; i++) {
			const float t = step_delta * i;
			Vec2 q1 = MathUtilities::LerpVector2<float>(p1, p2, t);
			Vec2 q2 = MathUtilities::LerpVector2<float>(p2, p3, t);
			Vec2 r1 = MathUtilities::LerpVector2<float>(q1, q2, t);

			gfx.DrawLine(previous_position, r1, c);
			previous_position = r1;
		}
	}
public:
	Vec2 p1;
	Vec2 p2;
	Vec2 p3;
	int steps = 10;
};

class CubicBezier {
public:
	CubicBezier(Vec2 p1, Vec2 p2, Vec2 p3, Vec2 p4)
		:
		p1(p1),
		p2(p2),
		p3(p3),
		p4(p4)
	{}
	void Draw(Graphics& gfx, Color c = Colors::White)
	{
		gfx.DrawLine(p1, p2, Colors::Gray);
		gfx.DrawLine(p2, p3, Colors::Gray);
		gfx.DrawLine(p3, p4, Colors::Gray);

		float step_delta = 1.0f / steps;

		Vec2 previous_position = p1;

		for (int i = 1; i <= steps; i++) {
			const float t = step_delta * i;
			Vec2 q1 = MathUtilities::LerpVector2<float>(p1, p2, t);
			Vec2 q2 = MathUtilities::LerpVector2<float>(p2, p3, t);
			Vec2 q3 = MathUtilities::LerpVector2<float>(p3, p4, t);

			Vec2 r1 = MathUtilities::LerpVector2<float>(q1, q2, t);
			Vec2 r2 = MathUtilities::LerpVector2<float>(q2, q3, t);

			Vec2 s1 = MathUtilities::LerpVector2<float>(r1, r2, t);

			gfx.DrawLine(previous_position, s1, c);
			previous_position = s1;
		}
	}
public:
	Vec2 p1;
	Vec2 p2;
	Vec2 p3;
	Vec2 p4;
	int steps = 10;
};