// md_parse through the module: the callbacks, the detail structs and the
// attribute substrings arrive exactly as <md4c.h> documents them.
#include <gtest/gtest.h>

import std;
import mcpplibs.mwrap.md4c;

namespace macros = mcpplibs::mwrap::md4c::macros;

namespace {

struct Recorder {
    std::vector<std::string> events;
    std::string              text;
    unsigned                 heading_level = 0;
    unsigned                 list_start = 0;
    char                     list_delimiter = 0;
    int                      task = 0;
    char                     task_mark = 0;
    MD_OFFSET                task_offset = 0;
    std::string              code_lang;
    char                     fence = 0;
    unsigned                 table_columns = 0;
    std::vector<MD_ALIGN>    aligns;
    std::string              href, title;
    std::string              img_src;
};

std::string attribute(const MD_ATTRIBUTE& a) {
    return a.text ? std::string(a.text, a.size) : std::string();
}

int enter_block(MD_BLOCKTYPE type, void* detail, void* user) {
    auto& r = *static_cast<Recorder*>(user);
    r.events.push_back(std::format("+b{}", static_cast<int>(type)));
    switch (type) {
        case MD_BLOCK_H: r.heading_level = static_cast<MD_BLOCK_H_DETAIL*>(detail)->level; break;
        case MD_BLOCK_OL: {
            auto* d = static_cast<MD_BLOCK_OL_DETAIL*>(detail);
            r.list_start = d->start;
            r.list_delimiter = d->mark_delimiter;
            break;
        }
        case MD_BLOCK_LI: {
            auto* d = static_cast<MD_BLOCK_LI_DETAIL*>(detail);
            if (d->is_task) {
                r.task = 1;
                r.task_mark = d->task_mark;
                r.task_offset = d->task_mark_offset;
            }
            break;
        }
        case MD_BLOCK_CODE: {
            auto* d = static_cast<MD_BLOCK_CODE_DETAIL*>(detail);
            r.code_lang = attribute(d->lang);
            r.fence = d->fence_char;
            break;
        }
        case MD_BLOCK_TABLE: r.table_columns = static_cast<MD_BLOCK_TABLE_DETAIL*>(detail)->col_count; break;
        case MD_BLOCK_TH:
        case MD_BLOCK_TD: r.aligns.push_back(static_cast<MD_BLOCK_TD_DETAIL*>(detail)->align); break;
        default: break;
    }
    return 0;
}
int leave_block(MD_BLOCKTYPE type, void*, void* user) {
    static_cast<Recorder*>(user)->events.push_back(std::format("-b{}", static_cast<int>(type)));
    return 0;
}
int enter_span(MD_SPANTYPE type, void* detail, void* user) {
    auto& r = *static_cast<Recorder*>(user);
    r.events.push_back(std::format("+s{}", static_cast<int>(type)));
    if (type == MD_SPAN_A) {
        auto* d = static_cast<MD_SPAN_A_DETAIL*>(detail);
        r.href = attribute(d->href);
        r.title = attribute(d->title);
    } else if (type == MD_SPAN_IMG) {
        r.img_src = attribute(static_cast<MD_SPAN_IMG_DETAIL*>(detail)->src);
    }
    return 0;
}
int leave_span(MD_SPANTYPE type, void*, void* user) {
    static_cast<Recorder*>(user)->events.push_back(std::format("-s{}", static_cast<int>(type)));
    return 0;
}
int text(MD_TEXTTYPE type, const MD_CHAR* s, MD_SIZE n, void* user) {
    auto& r = *static_cast<Recorder*>(user);
    if (type == MD_TEXT_SOFTBR) r.text += '\n';
    else r.text.append(s, n);
    return 0;
}

Recorder parse(std::string_view source, unsigned flags) {
    Recorder r;
    MD_PARSER p{};
    p.abi_version = 0;
    p.flags = flags;
    p.enter_block = enter_block;
    p.leave_block = leave_block;
    p.enter_span = enter_span;
    p.leave_span = leave_span;
    p.text = text;
    const int rc = md_parse(source.data(), static_cast<MD_SIZE>(source.size()), &p, &r);
    EXPECT_EQ(rc, 0);
    return r;
}

}  // namespace

TEST(Parse, BlocksAndSpansNest) {
    const Recorder r = parse("# Title *em*\n\npara **b**\n", macros::MD_DIALECT_COMMONMARK);
    const std::vector<std::string> expected{"+b0", "+b6", "+s0", "-s0", "-b6", "+b9", "+s1", "-s1", "-b9", "-b0"};
    EXPECT_EQ(r.events, expected);
    EXPECT_EQ(r.heading_level, 1u);
    EXPECT_EQ(r.text, "Title empara b");
}

TEST(Parse, OrderedListDetail) {
    const Recorder r = parse("7) seven\n8) eight\n", 0);
    EXPECT_EQ(r.list_start, 7u);
    EXPECT_EQ(r.list_delimiter, ')');
}

TEST(Parse, TaskListsGiveTheMarkAndItsOffset) {
    const std::string source = "- [x] done\n";
    const Recorder r = parse(source, macros::MD_FLAG_TASKLISTS);
    ASSERT_EQ(r.task, 1);
    EXPECT_EQ(r.task_mark, 'x');
    EXPECT_EQ(source[r.task_offset], 'x');
    EXPECT_EQ(parse(source, 0).task, 0);  // the extension is off by default
}

TEST(Parse, FencedCodeLanguage) {
    const Recorder r = parse("~~~cpp title\nint x;\n~~~\n", 0);
    EXPECT_EQ(r.code_lang, "cpp");
    EXPECT_EQ(r.fence, '~');
    EXPECT_EQ(r.text, "int x;\n");
}

TEST(Parse, TablesAndAlignment) {
    const Recorder r = parse("| a | b | c |\n|:--|:-:|--:|\n| 1 | 2 | 3 |\n", macros::MD_FLAG_TABLES);
    EXPECT_EQ(r.table_columns, 3u);
    ASSERT_EQ(r.aligns.size(), 6u);
    EXPECT_EQ(r.aligns[0], MD_ALIGN_LEFT);
    EXPECT_EQ(r.aligns[1], MD_ALIGN_CENTER);
    EXPECT_EQ(r.aligns[2], MD_ALIGN_RIGHT);
}

TEST(Parse, LinkAndImageAttributes) {
    const Recorder r = parse("[x](/u \"t\") ![i](/p.png)\n", 0);
    EXPECT_EQ(r.href, "/u");
    EXPECT_EQ(r.title, "t");
    EXPECT_EQ(r.img_src, "/p.png");
}

TEST(Parse, GithubDialectAutolinksAndStrikethrough) {
    const Recorder r = parse("see www.example.com and ~~old~~\n", macros::MD_DIALECT_GITHUB);
    EXPECT_EQ(r.href, "http://www.example.com");
    EXPECT_NE(std::ranges::find(r.events, std::format("+s{}", static_cast<int>(MD_SPAN_DEL))), r.events.end());
}

TEST(Parse, AbortsWhenACallbackFails) {
    MD_PARSER p{};
    p.enter_block = [](MD_BLOCKTYPE, void*, void*) { return 7; };
    p.leave_block = [](MD_BLOCKTYPE, void*, void*) { return 0; };
    p.enter_span = [](MD_SPANTYPE, void*, void*) { return 0; };
    p.leave_span = [](MD_SPANTYPE, void*, void*) { return 0; };
    p.text = [](MD_TEXTTYPE, const MD_CHAR*, MD_SIZE, void*) { return 0; };
    EXPECT_EQ(md_parse("x", 1, &p, nullptr), 7);
}
