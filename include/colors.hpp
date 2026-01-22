#pragma once

struct Color{
	Uint8 r, g, b, a;

	Color (Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha)
	: r(red), g(green), b(blue), a(alpha) {}
};

constexpr Color WHITE {255, 255, 255, 255};
constexpr Color BLACK {0, 0, 0, 255};
constexpr Color DARKGRAY {80, 80, 80, 255};


