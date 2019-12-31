#include "Surface.h"
#include "ChiliWin.h"
#include <cassert>
#include <fstream>

Surface::Surface(const std::string & fileName)
{
	OutputDebugStringA("Surface loaded from file.\n");

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

	pPixels = std::make_unique<Color[]>(width * height);

	const unsigned int iOffsetData = bmpFileHeader.bfOffBits;

	file.seekg(iOffsetData, std::ios::beg);
	const unsigned int nPadding = (width % 4) % 4;
	//const unsigned int nPadding = (4 - (width * 3) % 4) % 4;

	for (int y = yStart; y != yEnd; y += dy)
	{
		for (int x = 0; x < width; ++x)
		{

			const unsigned char b = file.get();
			const unsigned char g = file.get();
			const unsigned char r = file.get();

			if (is32Bit)
			{
				/*unsigned int dwPixels;

				file.read(reinterpret_cast<char*>(&dwPixels), sizeof(dwPixels));

				cPixel.dword = dwPixels;*/

				file.seekg(1, std::ios::cur);
			}

			PutPixel(x, y, { r, g, b });
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
	pPixels(std::make_unique<Color[]>(width * height) )
{
}

Surface::Surface(const Surface & rhs)
	:
	Surface(rhs.width, rhs.height)
{
	OutputDebugStringA("Surface copy ctor called.\n");

	const int nPixels = width * height;
	for (int i = 0; i < nPixels; ++i)
	{
		pPixels[i] = rhs.pPixels[i];
	}
}

Surface & Surface::operator=(const Surface & rhs)
{
	OutputDebugStringA("Surface copy ass called.\n");

	if (this != &rhs)
	{
		width = rhs.width;
		height = rhs.height;
	
		pPixels = std::make_unique<Color[]>(width * height);

		const int nPixels = width * height;
		for (int i = 0; i < nPixels; ++i)
		{
			pPixels[i] = rhs.pPixels[i];
		}
	}
	return *this;
}

void Surface::PutPixel(int x, int y, Color c)
{
	assert(x >= 0);
	assert(x < width);
	assert(y >= 0);
	assert(y < height);

	pPixels[y * width + x] = c;
}

Color Surface::GetPixel(int x, int y) const
{
	assert(x >= 0);
	assert(x < width);
	assert(y >= 0);
	assert(y < height);

	return pPixels[y * width + x];
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
