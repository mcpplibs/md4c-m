# md4c

> MD4C, the fast CommonMark / GFM Markdown parser for C, through C++23 modules.

**English** · [简体中文](README.zh.md) · [Upstream](https://github.com/mity/md4c) · [Releases](https://github.com/mcpplibs/md4c-m/releases) · [mcpp](https://github.com/mcpp-community/mcpp) · [Index](https://github.com/mcpplibs/mcpp-index)

[![C++23](https://img.shields.io/badge/C%2B%2B-23-blue.svg)](https://en.cppreference.com/w/cpp/23)
[![License](https://img.shields.io/badge/license-Apache--2.0-blue.svg)](LICENSE)
[![mcpp-community](https://img.shields.io/badge/mcpp--community-mwrap-blue)](https://github.com/mcpp-community)
[![CI](https://github.com/mcpplibs/md4c-m/actions/workflows/ci.yml/badge.svg?branch=main)](https://github.com/mcpplibs/md4c-m/actions/workflows/ci.yml)

The upstream C API is unchanged: `md_parse`, `MD_PARSER`, `MD_BLOCK_*`, `md_html`
are the upstream globals. The parser is `compat.md4c` 0.5.3; this package adds
upstream's second library, the md4c-html renderer, and maps the `MD_FLAG_*`
macros to constants. Upstream's own test suites (CommonMark 0.31.2 spec, GFM
extensions, regressions: 808 examples) pass through the module on every CI run.

## Modules

- `import mcpplibs.mwrap.md4c;`: the parser API (`md_parse`, callbacks, details), re-exporting the two below
- `import mcpplibs.mwrap.md4c.html;`: `md_html`, Markdown straight to HTML
- `import mcpplibs.mwrap.md4c.macros;`: `MD_FLAG_*`, `MD_DIALECT_*`, `MD_HTML_FLAG_*` in `mcpplibs::mwrap::md4c::macros`

> More Modules API -> [Usage and API](docs/usage.md)

## Getting started

```sh
mcpp new notes --template mcpplibs.mwrap.md4c@0.5.3
cd notes
mcpp run
```

The default template renders a document with GitHub's extensions to HTML and
prints the outline of its headings from the `md_parse` callbacks.

```toml
[dependencies]
"mcpplibs.mwrap.md4c" = "0.5.3"
```

```cpp
import std;
import mcpplibs.mwrap.md4c;
namespace macros = mcpplibs::mwrap::md4c::macros;

int main() {
    std::string_view md = "# Hello\n\n- [x] *modules*\n";
    std::string html;
    md_html(md.data(), static_cast<MD_SIZE>(md.size()),
            [](const MD_CHAR* s, MD_SIZE n, void* out) { static_cast<std::string*>(out)->append(s, n); },
            &html, macros::MD_DIALECT_GITHUB, 0);
    std::print("{}", html);
}
```

## Macros

A named module cannot export a macro; the object-like ones are
`inline constexpr unsigned` under their original names:
`macros::MD_FLAG_TABLES`, `macros::MD_DIALECT_GITHUB`, `macros::MD_HTML_FLAG_XHTML`.
A translation unit that also includes `<md4c.h>` has the macros active, and they
expand even inside `macros::MD_FLAG_TABLES`; use the plain macro there (see
[tests/header_mix_test.cpp](tests/header_mix_test.cpp)).

## Examples

- [examples/md2html](examples/md2html): upstream's `md2html` options over stdin or a file; the program
  [tools/run_conformance.py](tools/run_conformance.py) drives through upstream's `test/run-testsuite.py`.

## Build and testing

Linux, macOS and Windows CI build the modules, run the tests, the export audit
([tools/check_exports.py](tools/check_exports.py): every public name of both
headers is exported) and the upstream conformance suites; a separate job
scaffolds the default template as an installed package and runs it.

## License

[Apache-2.0](LICENSE) for the wrapper, by mcpp-community; MD4C remains MIT.
[Original upstream README and license](upstream/md4c/), the vendored md4c-html
sources and their checksums ([upstream/documents.json](upstream/documents.json)).
