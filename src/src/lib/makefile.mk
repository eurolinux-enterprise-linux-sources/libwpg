EXTERNAL_WARNINGS_NOT_ERRORS := TRUE

PRJ=..$/..$/..$/..$/..$/..

PRJNAME=libwpg
TARGET=wpglib
ENABLE_EXCEPTIONS=TRUE
LIBTARGET=NO

.INCLUDE :  settings.mk

.IF "$(GUI)"=="WNT"
CFLAGS+=-GR
.ENDIF
.IF "$(COM)"=="GCC"
CFLAGSCXX+=-frtti
.ENDIF

.IF "$(SYSTEM_LIBWPD)" == "YES"
INCPRE+=$(LIBWPD_CFLAGS) -I..
.ELSE
INCPRE+=$(SOLARVER)$/$(UPD)$/$(INPATH)$/inc$/libwpd
.ENDIF

SLOFILES= \
        $(SLO)$/WPG1Parser.obj \
        $(SLO)$/WPG2Parser.obj \
        $(SLO)$/WPGBinaryData.obj \
        $(SLO)$/WPGBitmap.obj \
        $(SLO)$/WPGBrush.obj \
        $(SLO)$/WPGColor.obj \
        $(SLO)$/WPGGradient.obj \
        $(SLO)$/WPGHeader.obj \
        $(SLO)$/WPGInternalStream.obj \
        $(SLO)$/WPGPath.obj \
        $(SLO)$/WPGPen.obj \
        $(SLO)$/WPGPoint.obj \
        $(SLO)$/WPGraphics.obj \
        $(SLO)$/WPGRect.obj \
        $(SLO)$/WPGString.obj \
        $(SLO)$/WPGSVGGenerator.obj \
        $(SLO)$/WPGXParser.obj

LIB1ARCHIV=$(LB)$/libwpglib.a
LIB1TARGET=$(SLB)$/$(TARGET).lib
LIB1OBJFILES= $(SLOFILES)

.INCLUDE :  target.mk
