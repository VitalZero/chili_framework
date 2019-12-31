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
	Surface(const Surface&) = default;
	// move assignement
	Surface& operator=(Surface&& rhs) noexcept;
	Surface& operator=(const Surface& ) = default;
	Surface() = default;
	void PutPixel(int x, int y, Color c);
	Color GetPixel(int x, int y) const;
	int GetWidth() const;
	int GetHeight() const;
	RectI GetRect() const;
	void SetFill(Color c);
	const Color* Data() const;
private:
	std::vector<Color> pixels;
	int width = 0;
	int height = 0;
};