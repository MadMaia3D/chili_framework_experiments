#pragma once
#include "Graphics.h"

namespace SpriteEffects{
	class Copy {
	public:
		void operator()(Graphics& gfx, int x, int y, const Color& pixelColor) const
		{
			gfx.PutPixel(x, y, pixelColor);
		}
	};

	class Chroma {
	public:
		Chroma(const Color& chroma)
			:
			chroma(chroma)
		{ }
		void operator()(Graphics& gfx, int x, int y, const Color& pixelColor) const
		{
			if (pixelColor != chroma) {
				gfx.PutPixel(x, y, pixelColor);
			}
		}
	private:
		Color chroma;
	};

	class Substitution {
	public:
		Substitution(const Color& fillColor, const Color& chroma)
			:
			fillColor(fillColor),
			chroma(chroma)
		{ }
		void operator()(Graphics& gfx, int x, int y, const Color& pixelColor) const
		{
			if (pixelColor != chroma) {
				gfx.PutPixel(x, y, fillColor);
			}
		}
	private:
		Color chroma;
		Color fillColor;
	};

	class Transparency {
	public:
		Transparency(float alpha, const Color& chroma)
			:
			alpha(alpha),
			chroma(chroma)
		{ }
		void operator()(Graphics& gfx, int x, int y, const Color& pixelColor) const
		{
			if (pixelColor != chroma) {
				gfx.PutPixel(x, y, pixelColor, alpha);
			}
		}
	private:
		float alpha;
		Color chroma;
	};
}