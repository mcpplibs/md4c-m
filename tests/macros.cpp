import mcpplibs.mwrap.md4c.macros;
namespace macros = mcpplibs::mwrap::md4c::macros;
static_assert(macros::MD_DIALECT_COMMONMARK == 0);
static_assert(macros::MD_FLAG_PERMISSIVEAUTOLINKS ==
              (macros::MD_FLAG_PERMISSIVEEMAILAUTOLINKS | macros::MD_FLAG_PERMISSIVEURLAUTOLINKS | macros::MD_FLAG_PERMISSIVEWWWAUTOLINKS));
static_assert(macros::MD_DIALECT_GITHUB ==
              (macros::MD_FLAG_PERMISSIVEAUTOLINKS | macros::MD_FLAG_TABLES | macros::MD_FLAG_STRIKETHROUGH | macros::MD_FLAG_TASKLISTS));
static_assert(macros::MD_FLAG_NOHTML == (macros::MD_FLAG_NOHTMLBLOCKS | macros::MD_FLAG_NOHTMLSPANS));
int main() { return macros::MD_FLAG_TABLES == 0x0100 && macros::MD_HTML_FLAG_XHTML == 0x0008 ? 0 : 1; }
