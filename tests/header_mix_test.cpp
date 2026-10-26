// The raw headers and the import in one translation unit (headers first, the
// canonical order): the module's names are the very same entities. While a
// header's macro is defined it expands even inside a qualified name, so
// `macros::MD_FLAG_TABLES` is only reachable with the macro set aside.
#include <md4c-html.h>
#include <gtest/gtest.h>

import std;
import mcpplibs.mwrap.md4c;

namespace {
constexpr unsigned raw_tables = MD_FLAG_TABLES, raw_github = MD_DIALECT_GITHUB, raw_xhtml = MD_HTML_FLAG_XHTML;
}

#pragma push_macro("MD_FLAG_TABLES")
#pragma push_macro("MD_DIALECT_GITHUB")
#pragma push_macro("MD_HTML_FLAG_XHTML")
#undef MD_FLAG_TABLES
#undef MD_DIALECT_GITHUB
#undef MD_HTML_FLAG_XHTML
static_assert(mcpplibs::mwrap::md4c::macros::MD_FLAG_TABLES == raw_tables);
static_assert(mcpplibs::mwrap::md4c::macros::MD_DIALECT_GITHUB == raw_github);
static_assert(mcpplibs::mwrap::md4c::macros::MD_HTML_FLAG_XHTML == raw_xhtml);
#pragma pop_macro("MD_HTML_FLAG_XHTML")
#pragma pop_macro("MD_DIALECT_GITHUB")
#pragma pop_macro("MD_FLAG_TABLES")

TEST(HeaderMix, SameEntities) {
    static_assert(std::is_same_v<decltype(&::md_parse), int (*)(const MD_CHAR*, MD_SIZE, const MD_PARSER*, void*)>);
    static_assert(std::is_same_v<MD_RENDERER, MD_PARSER>);
    EXPECT_EQ(MD_FLAG_TABLES, 0x0100);  // the macro again
    EXPECT_EQ(MD_BLOCK_TD, 15);
}
