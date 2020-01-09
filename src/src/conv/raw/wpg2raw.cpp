/* libwpg
 * Copyright (C) 2006 Ariya Hidayat (ariya@kde.org)
 * Copyright (C) 2005 Fridrich Strba (fridrich.strba@bluewin.ch)
 * Copyright (C) 2004 Marc Oude Kotte (marc@solcon.nl)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA  02111-1301 USA
 *
 * For further information visit http://libwpg.sourceforge.net
 */

/* "This product is not manufactured, approved, or supported by
 * Corel Corporation or Corel Corporation Limited."
 */

#include <stdio.h>

#include "libwpg.h"
#include "WPGStreamImplementation.h"

class RawPainter : public libwpg::WPGPaintInterface {
public:
	RawPainter();

	void startGraphics(double imageWidth, double imageHeight);
	void endGraphics();
	void startLayer(unsigned int id);
	void endLayer(unsigned int id);

	void setPen(const libwpg::WPGPen& pen);
	void setBrush(const libwpg::WPGBrush& brush);
	void setFillRule(FillRule rule);

	void drawRectangle(const libwpg::WPGRect& rect, double rx, double ry);
	void drawEllipse(const libwpg::WPGPoint& center, double rx, double ry);
	void drawPolygon(const libwpg::WPGPointArray& vertices);
	void drawPath(const libwpg::WPGPath& path);
	void drawBitmap(const libwpg::WPGBitmap& bitmap);
	void drawImageObject(const libwpg::WPGBinaryData& binaryData);
};

RawPainter::RawPainter(): libwpg::WPGPaintInterface()
{
}

void RawPainter::startGraphics(double width, double height)
{
	printf("RawPainter::startGraphics(width: %.4fin, height: %.4fin)\n", width, height);
}

void RawPainter::endGraphics()
{
	printf("RawPainter::endGraphics\n");
}

void RawPainter::startLayer(unsigned int id)
{
	printf("RawPainter::startLayer %d\n", id);
}

void RawPainter::endLayer(unsigned int id)
{
	printf("RawPainter::endLayer %d\n", id);
}

void RawPainter::setPen(const libwpg::WPGPen& /*pen*/)
{
	printf("RawPainter::setPen\n");
}

void RawPainter::setBrush(const libwpg::WPGBrush& brush)
{
	printf("RawPainter::setBrush\n");

	printf("  Brush style: ");
	switch(brush.style)
	{
		case libwpg::WPGBrush::NoBrush:  printf("none"); break;
		case libwpg::WPGBrush::Solid:    printf("solid"); break;
		case libwpg::WPGBrush::Pattern:  printf("pattern"); break;
		case libwpg::WPGBrush::Gradient: printf("gradient"); break;
		default: printf("unknown"); break;
	}
	printf("\n");

	printf("  Foreground color: RGB %d %d %d\n", brush.foreColor.red,
		brush.foreColor.green, brush.foreColor.blue);
	printf("  Background color: RGB %d %d %d\n", brush.backColor.red,
		brush.backColor.green, brush.backColor.blue);

	if(brush.style == libwpg::WPGBrush::Gradient)
	for(unsigned c = 0; c < brush.gradient.count(); c++)
		printf("  Gradient stop %d: %f   RGB %d %d %d\n", c+1,
			brush.gradient.stopOffset(c), brush.gradient.stopColor(c).red,
			brush.gradient.stopColor(c).green, brush.gradient.stopColor(c).blue);
}

void RawPainter::setFillRule(FillRule /*rule*/)
{
	printf("RawPainter::setFillRule\n");
}

void RawPainter::drawRectangle(const libwpg::WPGRect& rect, double rx, double ry)
{
	printf("RawPainter::drawRoundedRectangle ");
	printf(" (%g %g)-(%g,%g)", rect.x1, rect.y1, rect.x2, rect.y2);
	printf("  Roundndess: %g %g\n", rx, ry);
}

void RawPainter::drawEllipse(const libwpg::WPGPoint& /*center*/s, double rx, double ry)
{
	printf("RawPainter::drawEllipse ");
	printf("  Radius: %g %g\n", rx, ry);
}

void RawPainter::drawPolygon(const libwpg::WPGPointArray& vertices)
{
	printf("RawPainter::drawPolyline %d points\n", vertices.count());
	for(unsigned i = 0; i < vertices.count(); i++)
		printf(" (%g %g)\n", vertices[i].x, vertices[i].y);
}

void RawPainter::drawPath(const libwpg::WPGPath& path)
{
	printf("RawPainter::drawPath %d elements\n", path.count());
}

void RawPainter::drawBitmap(const libwpg::WPGBitmap& /*bitmap*/)
{
	printf("RawPainter::drawBitmap\n");
}

void RawPainter::drawImageObject(const libwpg::WPGBinaryData& /*binaryData*/)
{
	printf("RawPainter::drawBinaryData\n");
}

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("usage: wpg2raw <WordPerfect Graphic>\n");
		return -1;
	}

	const char* filename = argv[1];
	libwpg::WPGFileStream input(filename);

	if (!libwpg::WPGraphics::isSupported(&input))
	{
		fprintf(stderr, "ERROR: Unsupported file format (unsupported version) or file is encrypted!\n");
		return 1;
	}

	RawPainter painter;
	libwpg::WPGraphics::parse(&input, &painter);

	return 0;
}

