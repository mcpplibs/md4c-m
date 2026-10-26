// md_html, upstream's renderer, through mcpplibs.mwrap.md4c.html.
#include <gtest/gtest.h>

import std;
import mcpplibs.mwrap.md4c;

namespace macros = mcpplibs::mwrap::md4c::macros;

namespace {

std::string html(std::string_view md, unsigned parser = 0, unsigned renderer = 0) {
    std::string out;
    const int rc = md_html(
        md.data(), static_cast<MD_SIZE>(md.size()),
        [](const MD_CHAR* s, MD_SIZE n, void* user) { static_cast<std::string*>(user)->append(s, n); }, &out, parser, renderer);
    EXPECT_EQ(rc, 0);
    return out;
}

}  // namespace

TEST(Html, CommonMark) {
    EXPECT_EQ(html("# Hi\n\n*a* & <b>\n"), "<h1>Hi</h1>\n<p><em>a</em> &amp; <b></p>\n");
    EXPECT_EQ(html("- a\n- b\n"), "<ul>\n<li>a</li>\n<li>b</li>\n</ul>\n");
    EXPECT_EQ(html("```py\nx = 1\n```\n"), "<pre><code class=\"language-py\">x = 1\n</code></pre>\n");
}

TEST(Html, EntitiesAreDecodedUnlessVerbatim) {
    EXPECT_EQ(html("&copy; &#x4E2D;\n"), "<p>© 中</p>\n");
    EXPECT_EQ(html("&copy;\n", 0, macros::MD_HTML_FLAG_VERBATIM_ENTITIES), "<p>&copy;</p>\n");
}

TEST(Html, XhtmlAndBom) {
    EXPECT_EQ(html("a  \nb\n\n---\n", 0, macros::MD_HTML_FLAG_XHTML), "<p>a<br />\nb</p>\n<hr />\n");
    EXPECT_EQ(html("\xEF\xBB\xBFx\n", 0, macros::MD_HTML_FLAG_SKIP_UTF8_BOM), "<p>x</p>\n");
}

TEST(Html, GithubExtensions) {
    EXPECT_EQ(html("- [ ] todo\n", macros::MD_DIALECT_GITHUB),
              "<ul>\n<li class=\"task-list-item\"><input type=\"checkbox\" class=\"task-list-item-checkbox\" disabled>todo</li>\n</ul>\n");
    EXPECT_EQ(html("|a|\n|-|\n|1|\n", macros::MD_FLAG_TABLES),
              "<table>\n<thead>\n<tr>\n<th>a</th>\n</tr>\n</thead>\n<tbody>\n<tr>\n<td>1</td>\n</tr>\n</tbody>\n</table>\n");
    EXPECT_EQ(html("<b>raw</b>\n", macros::MD_FLAG_NOHTML), "<p>&lt;b&gt;raw&lt;/b&gt;</p>\n");
}
