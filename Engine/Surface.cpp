#include "Surface.h"
#include "ChiliWin.h"
#include <cassert>
#include <fstream>

Surface::Surface(const std::string & fileName)
{
	std::ifstream file(fileName, std::ios::binary);
	assert(file);

	BITMAPFILEHEADER bmpFileHeader;
	file.read(reinterpret_cast<char*>(&bmpFileHeader), sizeof(bmpFileHeader));

	BITMAPINFOHEADER bmpInfoHeader;
	file.read(reinterpret_cast<char*>(&bmpInfoHeader), sizeof(bmpInfoHeader));

	assert(bmpInfoHeader.biBitCount == 24 || bmpInfoHeader.biBitCount == 32);
	assert(bmpInfoHeader.biCompression == BI_RGB);

	width = bmpInfoHeader.biWidth;
	
	const bool is32Bit = bmpInfoHeader.biBitCount == 32;

	int yStart;
	int yEnd;
	int dy;

	if (bmpInfoHeader.biHeight < 0)
	{
		height = -bmpInfoHeader.biHeight;
		yStart = 0;
		yEnd = height;
		dy = 1;
	}
	else
	{
		height = bmpInfoHeader.biHeight;
		yStart = height - 1;
		yEnd = -1;
		dy = - 1;
	}

	pixels.resize(width * height);
	
	file.seekg(bmpFileHeader.bfOffBits, std::ios::beg);

	const unsigned int nPadding = (width % 4) % 4;
	//const unsigned int nPadding = (4 - (width * 3) % 4) % 4;

	for (int y = yStart; y != yEnd; y += dy)
	{
		for (int x = 0; x < width; ++x)
		{

			const unsigned char b = file.get();
			const unsigned char g = file.get();
			const unsigned char r = file.get();
			
			PutPixel(x, y, { r, g, b });

			if (is32Bit)
			{
				file.seekg(1, std::ios::cur);
			}			
		}
		if (!is32Bit)
		{
			file.seekg(nPadding, std::ios::cur);
		}
	}
}

Surface::Surface(int width, int height)
	:
	width(width),
	height(height),
	pixels(width*height)
{
}

Surface::Surface(Surface && donor) noexcept
{
	*this = std::move(donor);
}

Surface & Surface::operator=(Surface&& rhs) noexcept
{
	width = rhs.width;
	height = rhs.height;
	
	pixels = std::move(rhs.pixels);
	rhs.width = 0;
	rhs.height = 0;

	return *this;
}

void Surface::PutPixel(int x, int y, Color c)
{
	assert(x >= 0);
	assert(x < width);
	assert(y >= 0);
	assert(y < height);

	pixels[y * width + x] = c;
}

Color Surface::GetPixel(int x, int y) const
{
	assert(x >= 0);
	assert(x < width);
	assert(y >= 0);
	assert(y < height);

	return pixels[y * width + x];
}

int Surface::GetWidth() const
{
	return width;
}

int Surface::GetHeight() const
{
	return height;
}

RectI Surface::GetRect() const
{
	return { 0, width, 0, height };
}

const Color* Surface::GetData() const
{
	return pixels.data();
}
