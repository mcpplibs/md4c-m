// mcpplibs.mwrap.md4c.macros — the object-like macros of <md4c.h> and
// <md4c-html.h> as `inline constexpr unsigned` under their original names in
// mcpplibs::mwrap::md4c::macros (a named module cannot export a macro). md4c
// has no function-like or control-flow macros, so no side header is needed.
module;
#include <md4c-html.h>

namespace mwrap_md4c_capture {
inline constexpr unsigned value_MD_FLAG_COLLAPSEWHITESPACE = MD_FLAG_COLLAPSEWHITESPACE;
inline constexpr unsigned value_MD_FLAG_PERMISSIVEATXHEADERS = MD_FLAG_PERMISSIVEATXHEADERS;
inline constexpr unsigned value_MD_FLAG_PERMISSIVEURLAUTOLINKS = MD_FLAG_PERMISSIVEURLAUTOLINKS;
inline constexpr unsigned value_MD_FLAG_PERMISSIVEEMAILAUTOLINKS = MD_FLAG_PERMISSIVEEMAILAUTOLINKS;
inline constexpr unsigned value_MD_FLAG_NOINDENTEDCODEBLOCKS = MD_FLAG_NOINDENTEDCODEBLOCKS;
inline constexpr unsigned value_MD_FLAG_NOHTMLBLOCKS = MD_FLAG_NOHTMLBLOCKS;
inline constexpr unsigned value_MD_FLAG_NOHTMLSPANS = MD_FLAG_NOHTMLSPANS;
inline constexpr unsigned value_MD_FLAG_TABLES = MD_FLAG_TABLES;
inline constexpr unsigned value_MD_FLAG_STRIKETHROUGH = MD_FLAG_STRIKETHROUGH;
inline constexpr unsigned value_MD_FLAG_PERMISSIVEWWWAUTOLINKS = MD_FLAG_PERMISSIVEWWWAUTOLINKS;
inline constexpr unsigned value_MD_FLAG_TASKLISTS = MD_FLAG_TASKLISTS;
inline constexpr unsigned value_MD_FLAG_LATEXMATHSPANS = MD_FLAG_LATEXMATHSPANS;
inline constexpr unsigned value_MD_FLAG_WIKILINKS = MD_FLAG_WIKILINKS;
inline constexpr unsigned value_MD_FLAG_UNDERLINE = MD_FLAG_UNDERLINE;
inline constexpr unsigned value_MD_FLAG_HARD_SOFT_BREAKS = MD_FLAG_HARD_SOFT_BREAKS;
inline constexpr unsigned value_MD_FLAG_PERMISSIVEAUTOLINKS = MD_FLAG_PERMISSIVEAUTOLINKS;
inline constexpr unsigned value_MD_FLAG_NOHTML = MD_FLAG_NOHTML;
inline constexpr unsigned value_MD_DIALECT_COMMONMARK = MD_DIALECT_COMMONMARK;
inline constexpr unsigned value_MD_DIALECT_GITHUB = MD_DIALECT_GITHUB;
inline constexpr unsigned value_MD_HTML_FLAG_DEBUG = MD_HTML_FLAG_DEBUG;
inline constexpr unsigned value_MD_HTML_FLAG_VERBATIM_ENTITIES = MD_HTML_FLAG_VERBATIM_ENTITIES;
inline constexpr unsigned value_MD_HTML_FLAG_SKIP_UTF8_BOM = MD_HTML_FLAG_SKIP_UTF8_BOM;
inline constexpr unsigned value_MD_HTML_FLAG_XHTML = MD_HTML_FLAG_XHTML;
}  // namespace mwrap_md4c_capture

#undef MD_FLAG_COLLAPSEWHITESPACE
#undef MD_FLAG_PERMISSIVEATXHEADERS
#undef MD_FLAG_PERMISSIVEURLAUTOLINKS
#undef MD_FLAG_PERMISSIVEEMAILAUTOLINKS
#undef MD_FLAG_NOINDENTEDCODEBLOCKS
#undef MD_FLAG_NOHTMLBLOCKS
#undef MD_FLAG_NOHTMLSPANS
#undef MD_FLAG_TABLES
#undef MD_FLAG_STRIKETHROUGH
#undef MD_FLAG_PERMISSIVEWWWAUTOLINKS
#undef MD_FLAG_TASKLISTS
#undef MD_FLAG_LATEXMATHSPANS
#undef MD_FLAG_WIKILINKS
#undef MD_FLAG_UNDERLINE
#undef MD_FLAG_HARD_SOFT_BREAKS
#undef MD_FLAG_PERMISSIVEAUTOLINKS
#undef MD_FLAG_NOHTML
#undef MD_DIALECT_COMMONMARK
#undef MD_DIALECT_GITHUB
#undef MD_HTML_FLAG_DEBUG
#undef MD_HTML_FLAG_VERBATIM_ENTITIES
#undef MD_HTML_FLAG_SKIP_UTF8_BOM
#undef MD_HTML_FLAG_XHTML

export module mcpplibs.mwrap.md4c.macros;

export namespace mcpplibs::mwrap::md4c::macros {
// Parser flags (MD_PARSER::flags).
inline constexpr unsigned MD_FLAG_COLLAPSEWHITESPACE = mwrap_md4c_capture::value_MD_FLAG_COLLAPSEWHITESPACE;
inline constexpr unsigned MD_FLAG_PERMISSIVEATXHEADERS = mwrap_md4c_capture::value_MD_FLAG_PERMISSIVEATXHEADERS;
inline constexpr unsigned MD_FLAG_PERMISSIVEURLAUTOLINKS = mwrap_md4c_capture::value_MD_FLAG_PERMISSIVEURLAUTOLINKS;
inline constexpr unsigned MD_FLAG_PERMISSIVEEMAILAUTOLINKS = mwrap_md4c_capture::value_MD_FLAG_PERMISSIVEEMAILAUTOLINKS;
inline constexpr unsigned MD_FLAG_NOINDENTEDCODEBLOCKS = mwrap_md4c_capture::value_MD_FLAG_NOINDENTEDCODEBLOCKS;
inline constexpr unsigned MD_FLAG_NOHTMLBLOCKS = mwrap_md4c_capture::value_MD_FLAG_NOHTMLBLOCKS;
inline constexpr unsigned MD_FLAG_NOHTMLSPANS = mwrap_md4c_capture::value_MD_FLAG_NOHTMLSPANS;
inline constexpr unsigned MD_FLAG_TABLES = mwrap_md4c_capture::value_MD_FLAG_TABLES;
inline constexpr unsigned MD_FLAG_STRIKETHROUGH = mwrap_md4c_capture::value_MD_FLAG_STRIKETHROUGH;
inline constexpr unsigned MD_FLAG_PERMISSIVEWWWAUTOLINKS = mwrap_md4c_capture::value_MD_FLAG_PERMISSIVEWWWAUTOLINKS;
inline constexpr unsigned MD_FLAG_TASKLISTS = mwrap_md4c_capture::value_MD_FLAG_TASKLISTS;
inline constexpr unsigned MD_FLAG_LATEXMATHSPANS = mwrap_md4c_capture::value_MD_FLAG_LATEXMATHSPANS;
inline constexpr unsigned MD_FLAG_WIKILINKS = mwrap_md4c_capture::value_MD_FLAG_WIKILINKS;
inline constexpr unsigned MD_FLAG_UNDERLINE = mwrap_md4c_capture::value_MD_FLAG_UNDERLINE;
inline constexpr unsigned MD_FLAG_HARD_SOFT_BREAKS = mwrap_md4c_capture::value_MD_FLAG_HARD_SOFT_BREAKS;
inline constexpr unsigned MD_FLAG_PERMISSIVEAUTOLINKS = mwrap_md4c_capture::value_MD_FLAG_PERMISSIVEAUTOLINKS;
inline constexpr unsigned MD_FLAG_NOHTML = mwrap_md4c_capture::value_MD_FLAG_NOHTML;
inline constexpr unsigned MD_DIALECT_COMMONMARK = mwrap_md4c_capture::value_MD_DIALECT_COMMONMARK;
inline constexpr unsigned MD_DIALECT_GITHUB = mwrap_md4c_capture::value_MD_DIALECT_GITHUB;
// Renderer flags (md_html's renderer_flags).
inline constexpr unsigned MD_HTML_FLAG_DEBUG = mwrap_md4c_capture::value_MD_HTML_FLAG_DEBUG;
inline constexpr unsigned MD_HTML_FLAG_VERBATIM_ENTITIES = mwrap_md4c_capture::value_MD_HTML_FLAG_VERBATIM_ENTITIES;
inline constexpr unsigned MD_HTML_FLAG_SKIP_UTF8_BOM = mwrap_md4c_capture::value_MD_HTML_FLAG_SKIP_UTF8_BOM;
inline constexpr unsigned MD_HTML_FLAG_XHTML = mwrap_md4c_capture::value_MD_HTML_FLAG_XHTML;
}  // namespace mcpplibs::mwrap::md4c::macros
