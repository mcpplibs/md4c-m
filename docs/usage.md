# Usage and API

## Modules

| Module | Exports (upstream globals) |
|---|---|
| `mcpplibs.mwrap.md4c` | `MD_CHAR`, `MD_SIZE`, `MD_OFFSET`; `MD_BLOCKTYPE`, `MD_SPANTYPE`, `MD_TEXTTYPE`, `MD_ALIGN` and all their enumerators; `MD_ATTRIBUTE` and every `*_DETAIL` struct; `MD_PARSER`, `MD_RENDERER`; `md_parse`. Re-exports the two modules below. |
| `mcpplibs.mwrap.md4c.html` | `md_html` |
| `mcpplibs.mwrap.md4c.macros` | `mcpplibs::mwrap::md4c::macros::` `MD_FLAG_*`, `MD_DIALECT_COMMONMARK`, `MD_DIALECT_GITHUB`, `MD_HTML_FLAG_*` |

`tools/check_exports.py` parses `<md4c.h>` and `<md4c-html.h>` and fails when a
public name or an object-like flag macro is missing from the modules.

## Parsing with callbacks

`md_parse` reports the document as nested enter / leave calls for blocks and
spans and text callbacks between them; `detail` points to the `*_DETAIL` of the
block or span (`MD_BLOCK_H_DETAIL::level`, `MD_BLOCK_LI_DETAIL::task_mark_offset`,
`MD_SPAN_A_DETAIL::href` …). A non-zero return from a callback aborts the parse
and becomes `md_parse`'s result. Attributes (`MD_ATTRIBUTE`) are split into
substrings by type: entities stay undecoded there (`MD_TEXT_ENTITY`).

In a tight list, paragraphs inside list items are not reported as
`MD_BLOCK_P`: their text arrives directly inside `MD_BLOCK_LI`.

## Dialects

`MD_DIALECT_COMMONMARK` (0) is CommonMark 0.31; `MD_DIALECT_GITHUB` adds tables,
strikethrough, task lists and permissive URL / www / e-mail autolinks. Other
extensions: `MD_FLAG_LATEXMATHSPANS`, `MD_FLAG_WIKILINKS`, `MD_FLAG_UNDERLINE`,
`MD_FLAG_HARD_SOFT_BREAKS`; `MD_FLAG_NOHTML` disables raw HTML.

## Rendering HTML

`md_html(input, size, output, userdata, parser_flags, renderer_flags)` calls
`output` with consecutive pieces of the HTML. Renderer flags: `MD_HTML_FLAG_XHTML`
(`<br />`, `<hr />`), `MD_HTML_FLAG_VERBATIM_ENTITIES` (keep `&copy;`),
`MD_HTML_FLAG_SKIP_UTF8_BOM`, `MD_HTML_FLAG_DEBUG`.

## Conformance

`python3 tools/run_conformance.py` builds `examples/md2html`, fetches the
upstream release tarball (checksum from `upstream/documents.json`) and runs every
`test/*.txt` suite of upstream through `test/run-testsuite.py`.
