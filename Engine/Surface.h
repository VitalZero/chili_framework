#pragma once
#include "Colors.h"
#include <string>
#include "Rect.h"
#include <memory>
#include <vector>

class Surface
{
public:
	Surface(const std::string& fileName);
	Surface(int width, int height);
	// move ctor
	Surface(Surface&& donor) noexcept;
	// move assignement
	Surface& operator=(Surface&& rhs) noexcept;
	Surface& operator=(const Surface& rhs) = default;
	Surface() = default;
	void PutPixel(int x, int y, Color c);
	Color GetPixel(int x, int y) const;
	int GetWidth() const;
	int GetHeight() const;
	RectI GetRect() const;
	const Color* Surface::GetData() const;
private:
	std::vector<Color> pixels;
	int width = 0;
	int height = 0;
};