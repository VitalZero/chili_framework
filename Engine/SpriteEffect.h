#pragma once
#include "Colors.h"
#include "Graphics.h"

namespace SpriteEffect
{
	class Negative
	{
	public:
		Negative(Color c)
			:
			chroma(c)
		{}
		void operator()(Color cSrc, int xDest, int yDest, Graphics& gfx) const
		{
			if (cSrc != chroma)
			{
				gfx.PutPixel(xDest, yDest, { 255u - cSrc.GetR(), 255u - cSrc.GetG(), 255u - cSrc.GetB()} );
			}
		}
	private:
		Color chroma;
	};
	class Chroma
	{
	public:
		Chroma(Color c)
			:
			chroma(c)
		{}
		void operator()(Color cSrc, int xDest, int yDest, Graphics& gfx) const
		{
			if (cSrc != chroma)
			{
				gfx.PutPixel(xDest, yDest, cSrc);
			}
		}
	private:
		Color chroma;
	};
	class Substitution
	{
	public:
		Substitution(Color c, Color s)
			:
			chroma(c),
			sub(s)
		{}
		void operator()(Color cSrc, int xDest, int yDest, Graphics& gfx) const
		{
			if (cSrc != chroma)
			{
				gfx.PutPixel(xDest, yDest, sub);
			}
		}
	private:
		Color chroma = Colors::Magenta;
		Color sub;
	};
	class Copy
	{
		void operator()(Color cSrc, int xDest, int yDest, Graphics& gfx) const
		{
			gfx.PutPixel(xDest, yDest, cSrc);
		}
	};
	class Ghost
	{
	public:
		Ghost(Color c)
			:
			chroma(c)
		{}
		void operator()(Color cSrc, int xDest, int yDest, Graphics& gfx) const
		{
			if (cSrc != chroma)
			{
				const Color backPixel = gfx.GetPixel(xDest, yDest);
				const Color blendedPixel = {
					unsigned char((cSrc.GetR() + backPixel.GetR()) / 2),
					unsigned char((cSrc.GetG() + backPixel.GetG()) / 2),
					unsigned char((cSrc.GetB() + backPixel.GetB()) / 2)
				};

				gfx.PutPixel(xDest, yDest, blendedPixel);
			}
		}
	private:
		Color chroma = Colors::Magenta;
	};
}