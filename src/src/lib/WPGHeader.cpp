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

#include "WPGHeader.h"
#include "libwpg_utils.h"

namespace
{
static inline unsigned short readU16(const void *p)
{
	const unsigned char *ptr = (const unsigned char *) p;
	return (unsigned short)(ptr[0]+(ptr[1]<<8));
}

static inline unsigned long readU32(const void *p)
{
	const unsigned char *ptr = (const unsigned char *) p;
	return (unsigned long)(unsigned)(ptr[0]+(ptr[1]<<8)+(ptr[2]<<16)+(ptr[3]<<24));
}
}

WPGHeader::WPGHeader() :
	m_identifier(),
	m_startOfDocument(0L),
	m_productType(0x01),
	m_fileType(0x16),
	m_majorVersion(0x02),
	m_minorVersion(0x00),
	m_encryptionKey(0x00),
	m_startOfPacketData(0)
{
	m_identifier[0] = 0xff;
	m_identifier[1] = 'W';
	m_identifier[2] = 'P';
	m_identifier[3] = 'C';
}

bool WPGHeader::load(librevenge::RVNGInputStream *input)
{
//	input->seek(0, librevenge::RVNG_SEEK_SET);

	unsigned long n = 0;
	unsigned char const *prefix = input->read(26, n);
	if (n < 26)
		return false;

	m_identifier[0] = prefix[0];
	m_identifier[1] = prefix[1];
	m_identifier[2] = prefix[2];
	m_identifier[3] = prefix[3];
	m_startOfDocument = readU32(prefix+4);
	m_productType = prefix[8];
	m_fileType = prefix[9];
	m_majorVersion = prefix[10];
	m_minorVersion = prefix[11];
	m_encryptionKey = readU16(prefix+12);
	m_startOfPacketData = readU16(prefix+14);

	WPG_DEBUG_MSG(("Header Identifier  = %c%c%c\n", m_identifier[1],
	               m_identifier[2], m_identifier[3]));
	WPG_DEBUG_MSG(("Product type       = 0x%x\n",  m_productType));
	WPG_DEBUG_MSG(("File type          = 0x%x\n",  m_fileType));
	WPG_DEBUG_MSG(("Major version      = 0x%x\n",  m_majorVersion));
	WPG_DEBUG_MSG(("Minor version      = 0x%x\n",  m_minorVersion));
	WPG_DEBUG_MSG(("Encryption key     = 0x%x\n",  m_encryptionKey));

	return true;
}

bool WPGHeader::isSupported() const
{
	return (
	           (m_identifier[0] == 0xFF) &&
	           (m_identifier[1] == 'W') &&
	           (m_identifier[2] == 'P') &&
	           (m_identifier[3] == 'C') &&
	           (m_productType == 0x01) &&
	           (m_fileType == 0x16) &&
	           (m_encryptionKey == 0x00) &&     // we don't support encryption
	           ((m_majorVersion == 0x02) || (m_majorVersion == 0x01)) &&
	           (m_minorVersion == 0x00)
	       );
}

unsigned long WPGHeader::startOfDocument() const
{
	return m_startOfDocument;
}

int WPGHeader::majorVersion() const
{
	return m_majorVersion;
}
/* vim:set shiftwidth=4 softtabstop=4 noexpandtab: */
