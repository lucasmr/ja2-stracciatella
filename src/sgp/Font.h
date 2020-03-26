#ifndef FONT_H
#define FONT_H

#include "SGPStrings.h"
#include "Types.h"


#define DEFAULT_SHADOW		2
#define MILITARY_SHADOW	67
#define NO_SHADOW		0

// these are bogus! No palette is set yet!
// font foreground color symbols
#define FONT_FCOLOR_WHITE	208
#define FONT_FCOLOR_RED	162
#define FONT_FCOLOR_NICERED	164
#define FONT_FCOLOR_BLUE	203
#define FONT_FCOLOR_GREEN	184
#define FONT_FCOLOR_YELLOW	144
#define FONT_FCOLOR_BROWN	184
#define FONT_FCOLOR_ORANGE	76
#define FONT_FCOLOR_PURPLE	160


extern SGPFont FontDefault;


void SetFontColors(UINT16 usColors);
void SetFontForeground(UINT8 ubForeground);
void SetFontBackground(UINT8 ubBackground);
void SetFontShadow(UINT8 ubBackground);

/* Print to the currently selected destination buffer, at the X/Y coordinates
 * specified, using the currently selected font. */

void GPrint(INT32 x, INT32 y, const ST::utf32_buffer& codepoints);
void GPrint(INT32 x, INT32 y, const ST::string& str);
template <typename ... T>
inline void gprintf(INT32 x, INT32 y, const ST::string& fmt_printf, T&& ... args)
{
	GPrint(x, y, st_format_printf(ST::substitute_invalid, fmt_printf, std::forward<T>(args) ...));
}

/* Prints to the currently selected destination buffer, at the X/Y coordinates
 * specified, using the currently selected font. Uses monochrome font color settings */

UINT32 MPrintChar(INT32 x, INT32 y, char32_t c);
void MPrintBuffer(UINT16* pDestBuf, UINT32 uiDestPitchBYTES, INT32 x, INT32 y, const ST::utf32_buffer& codepoints);
void MPrintBuffer(UINT16* pDestBuf, UINT32 uiDestPitchBYTES, INT32 x, INT32 y, const ST::string& str);
template <typename ... T>
inline void mprintf_buffer(UINT16* pDestBuf, UINT32 uiDestPitchBYTES, INT32 x, INT32 y, const ST::string& fmt_printf, T&& ... args)
{
	MPrintBuffer(pDestBuf, uiDestPitchBYTES, x, y, st_format_printf(ST::substitute_invalid, fmt_printf, std::forward<T>(args) ...));
}
void MPrint(INT32 x, INT32 y, const ST::utf32_buffer& codepoints);
void MPrint(INT32 x, INT32 y, const ST::string& str);
template <typename ... T>
inline void mprintf(INT32 x, INT32 y, const ST::string& fmt_printf, T&& ... args)
{
	MPrint(x, y, st_format_printf(ST::substitute_invalid, fmt_printf, std::forward<T>(args) ...));
}

/* Sets the destination buffer for printing to and the clipping rectangle. */
void SetFontDestBuffer(SGPVSurface* dst, INT32 x1, INT32 y1, INT32 x2, INT32 y2);

/* Set the destination buffer for printing while using the whole surface. */
void SetFontDestBuffer(SGPVSurface* dst);

/** Replace backbuffer if it is used by the font system. */
void ReplaceFontBackBuffer(SGPVSurface* oldBackbuffer, SGPVSurface* newBackbuffer);

void SetFont(SGPFont);

void SetFontAttributes(SGPFont, UINT8 foreground, UINT8 shadow = DEFAULT_SHADOW, UINT8 background = 0);

SGPFont LoadFontFile(const char* filename);
UINT16  GetFontHeight(SGPFont);
void    InitializeFontManager(void);
void    UnloadFont(SGPFont);

UINT32 GetCharWidth(HVOBJECT SGPFont, char32_t c);

INT16 StringPixLength(const ST::utf32_buffer& codepoints, SGPFont font);
INT16 StringPixLength(const ST::string& str, SGPFont font);
extern void SaveFontSettings(void);
extern void RestoreFontSettings(void);

void FindFontRightCoordinates(INT16 sLeft, INT16 sTop, INT16 sWidth, INT16 sHeight, const ST::utf32_buffer& codepoints, SGPFont font, INT16* psNewX, INT16* psNewY);
void FindFontRightCoordinates(INT16 sLeft, INT16 sTop, INT16 sWidth, INT16 sHeight, const ST::string& str, SGPFont font, INT16* psNewX, INT16* psNewY);
void FindFontCenterCoordinates(INT16 sLeft, INT16 sTop, INT16 sWidth, INT16 sHeight, const ST::utf32_buffer& codepoints, SGPFont font, INT16* psNewX, INT16* psNewY);
void FindFontCenterCoordinates(INT16 sLeft, INT16 sTop, INT16 sWidth, INT16 sHeight, const ST::string& str, SGPFont font, INT16* psNewX, INT16* psNewY);

bool IsPrintableChar(char32_t c);

#endif
