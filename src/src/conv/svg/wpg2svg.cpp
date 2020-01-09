/* libwpg
 * Copyright (C) 2006 Ariya Hidayat (ariya@kde.org)
 * Copyright (C) 2005 Fridrich Strba (fridrich.strba@bluewin.ch)
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
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 *
 * For further information visit http://libwpg.sourceforge.net
 */

/* "This product is not manufactured, approved, or supported by
 * Corel Corporation or Corel Corporation Limited."
 */

#include <iostream>
#include <sstream>
#include "libwpg.h"
#include "WPGStreamImplementation.h"


int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		std::cout << "usage: wpg2svg <WordPerfect Graphic>" << std::endl;
		return -1;
	}

	const char* filename = argv[1];
	libwpg::WPGFileStream input(filename);

	if (!libwpg::WPGraphics::isSupported(&input))
	{
		std::cerr << "ERROR: Unsupported file format (unsupported version) or file is encrypted!" << std::endl;
		return 1;
	}

	libwpg::WPGString output;
	if (!libwpg::WPGraphics::generateSVG(&input, output))
	{
		std::cerr << "ERROR: SVG Generation failed!" << std::endl;
		return 1;
	}		

	std::cout << output.cstr() << std::endl;
	return 0;
}
