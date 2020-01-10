/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4 -*- */
/* libwpg
 * Version: MPL 2.0 / LGPLv2.1+
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Major Contributor(s):
 * Copyright (C) 2006 Ariya Hidayat (ariya@kde.org)
 * Copyright (C) 2004 Marc Oude Kotte (marc@solcon.nl)
 * Copyright (C) 2005 Fridrich Strba (fridrich.strba@bluewin.ch)
 *
 * For minor contributions see the git repository.
 *
 * Alternatively, the contents of this file may be used under the terms
 * of the GNU Lesser General Public License Version 2.1 or later
 * (LGPLv2.1+), in which case the provisions of the LGPLv2.1+ are
 * applicable instead of those above.
 *
 * For further information visit http://libwpg.sourceforge.net
 */

/* "This product is not manufactured, approved, or supported by
 * Corel Corporation or Corel Corporation Limited."
 */

#ifndef __WPGXPARSER_H__
#define __WPGXPARSER_H__

#include <libwpg/libwpg.h>
#include <librevenge-stream/librevenge-stream.h>
#include <librevenge/librevenge.h>
#include "WPGColor.h"

#include <map>

class WPGXParser
{
public:
	WPGXParser(librevenge::RVNGInputStream *input, librevenge::RVNGDrawingInterface *painter);
	WPGXParser(const WPGXParser &parser);
	virtual ~WPGXParser() {}
	virtual bool parse() = 0;

	unsigned char readU8();
	unsigned short readU16();
	unsigned int readU32();
	short readS16();
	int readS32();
	unsigned int readVariableLengthInteger();
	WPGXParser &operator=(const WPGXParser &parser);

protected:
	librevenge::RVNGInputStream *m_input;
	librevenge::RVNGDrawingInterface *m_painter;
	std::map<int,libwpg::WPGColor> m_colorPalette;
};

class WPGTextDataHandler : public ::librevenge::RVNGTextInterface
{
public:
	WPGTextDataHandler(librevenge::RVNGDrawingInterface *painter) :
		m_painter(painter),
		m_fontName("Times New Roman"),
		m_paragraphStyle(),
		m_textStyle() {}

	~WPGTextDataHandler() {}
	void setDocumentMetaData(const librevenge::RVNGPropertyList & /* propList */) {}

	void startDocument(const librevenge::RVNGPropertyList & /* propList */) {}
	void endDocument() {}

	void defineEmbeddedFont(const librevenge::RVNGPropertyList & /* propList */) {}

	void definePageStyle(const librevenge::RVNGPropertyList & /* propList */) {}
	void openPageSpan(const librevenge::RVNGPropertyList & /* propList */) {}
	void closePageSpan() {}
	void openHeader(const librevenge::RVNGPropertyList & /* propList */) {}
	void closeHeader() {}
	void openFooter(const librevenge::RVNGPropertyList & /* propList */) {}
	void closeFooter() {}

	void defineParagraphStyle(const librevenge::RVNGPropertyList & /* propList */) {}
	void openParagraph(const librevenge::RVNGPropertyList &propList);
	void closeParagraph();

	void defineCharacterStyle(const librevenge::RVNGPropertyList & /* propList */) {}
	void openSpan(const librevenge::RVNGPropertyList &propList);
	void closeSpan();

	void openLink(const librevenge::RVNGPropertyList & /* propList */) {}
	void closeLink() {}

	void defineSectionStyle(const librevenge::RVNGPropertyList & /* propList */) {}
	void openSection(const librevenge::RVNGPropertyList & /* propList */) {}
	void closeSection() {}

	void insertTab();
	void insertSpace();
	void insertText(const librevenge::RVNGString &text);
	void insertLineBreak();
	void insertField(const librevenge::RVNGPropertyList & /* propList */) {}

	void openOrderedListLevel(const librevenge::RVNGPropertyList & /* propList */) {}
	void openUnorderedListLevel(const librevenge::RVNGPropertyList & /* propList */) {}
	void closeOrderedListLevel() {}
	void closeUnorderedListLevel() {}
	void openListElement(const librevenge::RVNGPropertyList &propList);
	void closeListElement();

	void openFootnote(const librevenge::RVNGPropertyList & /* propList */) {}
	void closeFootnote() {}
	void openEndnote(const librevenge::RVNGPropertyList & /* propList */) {}
	void closeEndnote() {}
	void openComment(const librevenge::RVNGPropertyList & /* propList */) {}
	void closeComment() {}
	void openTextBox(const librevenge::RVNGPropertyList & /* propList */) {}
	void closeTextBox() {}

	void openTable(const librevenge::RVNGPropertyList & /* propList */) {}
	void openTableRow(const librevenge::RVNGPropertyList & /* propList */) {}
	void closeTableRow() {}
	void openTableCell(const librevenge::RVNGPropertyList & /* propList */) {}
	void closeTableCell() {}
	void insertCoveredTableCell(const librevenge::RVNGPropertyList & /* propList */) {}
	void closeTable() {}

	void openFrame(const librevenge::RVNGPropertyList & /* propList */) {}
	void closeFrame() {}

	void openGroup(const librevenge::RVNGPropertyList & /* propList */) {}
	void closeGroup() {}

	void defineGraphicStyle(const librevenge::RVNGPropertyList & /* propList */) {}
	void drawRectangle(const librevenge::RVNGPropertyList & /* propList */) {}
	void drawEllipse(const librevenge::RVNGPropertyList & /* propList */) {}
	void drawPolygon(const librevenge::RVNGPropertyList & /* propList */) {}
	void drawPolyline(const librevenge::RVNGPropertyList & /* propList */) {}
	void drawPath(const librevenge::RVNGPropertyList & /* propList */) {}
	void drawConnector(const librevenge::RVNGPropertyList & /* propList */) {}

	void insertBinaryObject(const librevenge::RVNGPropertyList & /* propList */) {}
	void insertEquation(const librevenge::RVNGPropertyList & /* propList */) {}

private:
	librevenge::RVNGDrawingInterface *m_painter;
	::librevenge::RVNGString m_fontName;
	::librevenge::RVNGPropertyList m_paragraphStyle, m_textStyle;
	// Unimplemented to prevent compiler from creating crasher ones
	WPGTextDataHandler(const WPGTextDataHandler &);
	WPGTextDataHandler &operator=(const WPGTextDataHandler &);
};


#endif // __WPGXPARSER_H__
/* vim:set shiftwidth=4 softtabstop=4 noexpandtab: */
