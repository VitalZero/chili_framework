#pragma once
#include "Colors.h"
#include <string>
#include "Rect.h"
#include <memory>

class Surface
{
public:
	Surface(const std::string& fileName);
	Surface(int width, int height);
	Surface(const Surface& rhs);
	// move ctor
	Surface(Surface&& donor) noexcept = default;
	// move assignement
	Surface& operator=(Surface&& donor) noexcept = default;
	Surface& operator=(const Surface& rhs);
	Surface() = default;
	void PutPixel(int x, int y, Color c);
	Color GetPixel(int x, int y) const;
	int GetWidth() const;
	int GetHeight() const;
	RectI GetRect() const;
private:
	std::unique_ptr<Color[]> pPixels;
	int width = 0;
	int height = 0;
};