// mcpplibs.mwrap.md4c.html — md4c-html, upstream's HTML renderer, as a C++
// module: md_html() parses with md_parse() and writes HTML through a callback.
// Its flags are mapped in mcpplibs.mwrap.md4c.macros.
module;
#include <md4c-html.h>

export module mcpplibs.mwrap.md4c.html;

export using ::md_html;
