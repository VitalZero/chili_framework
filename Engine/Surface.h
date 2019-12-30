#pragma once
#include "Colors.h"
#include <string>
#include "Rect.h"

class Surface
{
public:
	Surface(const std::string& fileName);
	Surface(int width, int height);
	Surface(const Surface& rhs);
	// move ctor
	Surface(Surface&& donor) noexcept;
	~Surface();
	// move assignement
	Surface& operator=(Surface&& donor) noexcept;
	Surface& operator=(const Surface& rhs);
	Surface() = default;
	void PutPixel(int x, int y, Color c);
	Color GetPixel(int x, int y) const;
	int GetWidth() const;
	int GetHeight() const;
	RectI GetRect() const;
private:
	Color* pPixels = nullptr;
	int width = 0;
	int height = 0;
};