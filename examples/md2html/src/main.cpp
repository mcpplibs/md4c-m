// md2html — Markdown to HTML with md_html, accepting upstream md2html's
// dialect options, so md4c's own test/run-testsuite.py can drive this build:
//
//     md2html [--commonmark | --github] [--f<extension> ...] [--xhtml] [FILE]
import std;
import mcpplibs.mwrap.md4c;

namespace macros = mcpplibs::mwrap::md4c::macros;

namespace {

struct Option {
    std::string_view name;
    unsigned         parser = 0, renderer = 0;
};

constexpr std::array options{
    Option{"--commonmark", macros::MD_DIALECT_COMMONMARK},
    Option{"--github", macros::MD_DIALECT_GITHUB},
    Option{"--fcollapse-whitespace", macros::MD_FLAG_COLLAPSEWHITESPACE},
    Option{"--fhard-soft-breaks", macros::MD_FLAG_HARD_SOFT_BREAKS},
    Option{"--flatex-math", macros::MD_FLAG_LATEXMATHSPANS},
    Option{"--fpermissive-atx-headers", macros::MD_FLAG_PERMISSIVEATXHEADERS},
    Option{"--fpermissive-autolinks", macros::MD_FLAG_PERMISSIVEAUTOLINKS},
    Option{"--fpermissive-email-autolinks", macros::MD_FLAG_PERMISSIVEEMAILAUTOLINKS},
    Option{"--fpermissive-url-autolinks", macros::MD_FLAG_PERMISSIVEURLAUTOLINKS},
    Option{"--fpermissive-www-autolinks", macros::MD_FLAG_PERMISSIVEWWWAUTOLINKS},
    Option{"--fno-indented-code", macros::MD_FLAG_NOINDENTEDCODEBLOCKS},
    Option{"--fno-html-blocks", macros::MD_FLAG_NOHTMLBLOCKS},
    Option{"--fno-html-spans", macros::MD_FLAG_NOHTMLSPANS},
    Option{"--fno-html", macros::MD_FLAG_NOHTML},
    Option{"--fstrikethrough", macros::MD_FLAG_STRIKETHROUGH},
    Option{"--ftables", macros::MD_FLAG_TABLES},
    Option{"--ftasklists", macros::MD_FLAG_TASKLISTS},
    Option{"--funderline", macros::MD_FLAG_UNDERLINE},
    Option{"--fwiki-links", macros::MD_FLAG_WIKILINKS},
    Option{"--xhtml", 0, macros::MD_HTML_FLAG_XHTML},
    Option{"--fverbatim-entities", 0, macros::MD_HTML_FLAG_VERBATIM_ENTITIES},
};

}  // namespace

int main(int argc, char** argv) {
    unsigned parser = 0, renderer = macros::MD_HTML_FLAG_SKIP_UTF8_BOM;
    std::optional<std::string> file;
    for (int i = 1; i < argc; ++i) {
        const std::string_view a = argv[i];
        const auto o = std::ranges::find(options, a, &Option::name);
        if (o != options.end()) {
            parser |= o->parser;
            renderer |= o->renderer;
        } else if (!a.starts_with("--") && !file) {
            file = std::string(a);
        } else {
            std::println(std::cerr, "md2html: unknown option {}", a);
            return 2;
        }
    }
    std::string input;
    if (file) {
        std::ifstream in(*file, std::ios::binary);
        if (!in) {
            std::println(std::cerr, "md2html: cannot read {}", *file);
            return 1;
        }
        input.assign(std::istreambuf_iterator<char>(in), {});
    } else {
        std::ios::sync_with_stdio(false);
        std::cin >> std::noskipws;
        input.assign(std::istreambuf_iterator<char>(std::cin), {});
    }
    std::string out;
    const int rc = md_html(
        input.data(), static_cast<MD_SIZE>(input.size()),
        [](const MD_CHAR* s, MD_SIZE n, void* user) { static_cast<std::string*>(user)->append(s, n); }, &out, parser, renderer);
    std::cout.write(out.data(), static_cast<std::streamsize>(out.size()));
    std::cout.flush();
    return rc == 0 ? 0 : 1;
}
