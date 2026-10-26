// mcpplibs.mwrap.md4c — MD4C, the CommonMark / GFM parser for C, as a C++
// module. Every exported name is the upstream global from <md4c.h>, unchanged;
// the root also re-exports the md4c-html renderer and the macro mappings.
module;
#include <md4c.h>

export module mcpplibs.mwrap.md4c;

export import mcpplibs.mwrap.md4c.html;
export import mcpplibs.mwrap.md4c.macros;

// typedefs
export using ::MD_CHAR;
export using ::MD_SIZE;
export using ::MD_OFFSET;

// enums
export using ::MD_BLOCKTYPE;
export using ::MD_SPANTYPE;
export using ::MD_TEXTTYPE;
export using ::MD_ALIGN;

// enumerators: MD_BLOCKTYPE
export using ::MD_BLOCK_DOC;
export using ::MD_BLOCK_QUOTE;
export using ::MD_BLOCK_UL;
export using ::MD_BLOCK_OL;
export using ::MD_BLOCK_LI;
export using ::MD_BLOCK_HR;
export using ::MD_BLOCK_H;
export using ::MD_BLOCK_CODE;
export using ::MD_BLOCK_HTML;
export using ::MD_BLOCK_P;
export using ::MD_BLOCK_TABLE;
export using ::MD_BLOCK_THEAD;
export using ::MD_BLOCK_TBODY;
export using ::MD_BLOCK_TR;
export using ::MD_BLOCK_TH;
export using ::MD_BLOCK_TD;

// enumerators: MD_SPANTYPE
export using ::MD_SPAN_EM;
export using ::MD_SPAN_STRONG;
export using ::MD_SPAN_A;
export using ::MD_SPAN_IMG;
export using ::MD_SPAN_CODE;
export using ::MD_SPAN_DEL;
export using ::MD_SPAN_LATEXMATH;
export using ::MD_SPAN_LATEXMATH_DISPLAY;
export using ::MD_SPAN_WIKILINK;
export using ::MD_SPAN_U;

// enumerators: MD_TEXTTYPE
export using ::MD_TEXT_NORMAL;
export using ::MD_TEXT_NULLCHAR;
export using ::MD_TEXT_BR;
export using ::MD_TEXT_SOFTBR;
export using ::MD_TEXT_ENTITY;
export using ::MD_TEXT_CODE;
export using ::MD_TEXT_HTML;
export using ::MD_TEXT_LATEXMATH;

// enumerators: MD_ALIGN
export using ::MD_ALIGN_DEFAULT;
export using ::MD_ALIGN_LEFT;
export using ::MD_ALIGN_CENTER;
export using ::MD_ALIGN_RIGHT;

// structs
export using ::MD_ATTRIBUTE;
export using ::MD_BLOCK_UL_DETAIL;
export using ::MD_BLOCK_OL_DETAIL;
export using ::MD_BLOCK_LI_DETAIL;
export using ::MD_BLOCK_H_DETAIL;
export using ::MD_BLOCK_CODE_DETAIL;
export using ::MD_BLOCK_TABLE_DETAIL;
export using ::MD_BLOCK_TD_DETAIL;
export using ::MD_SPAN_A_DETAIL;
export using ::MD_SPAN_IMG_DETAIL;
export using ::MD_SPAN_WIKILINK;
export using ::MD_SPAN_WIKILINK_DETAIL;
export using ::MD_PARSER;
export using ::MD_RENDERER;

// functions
export using ::md_parse;
