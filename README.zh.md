# md4c

> 通过 C++23 模块使用 MD4C：一个快速的 CommonMark / GFM Markdown C 解析器。

[English](README.md) · **简体中文** · [Upstream](https://github.com/mity/md4c) · [Releases](https://github.com/mcpplibs/md4c-m/releases) · [mcpp](https://github.com/mcpp-community/mcpp) · [Index](https://github.com/mcpplibs/mcpp-index)

[![C++23](https://img.shields.io/badge/C%2B%2B-23-blue.svg)](https://en.cppreference.com/w/cpp/23)
[![License](https://img.shields.io/badge/license-Apache--2.0-blue.svg)](LICENSE)
[![mcpp-community](https://img.shields.io/badge/mcpp--community-mwrap-blue)](https://github.com/mcpp-community)
[![CI](https://github.com/mcpplibs/md4c-m/actions/workflows/ci.yml/badge.svg?branch=main)](https://github.com/mcpplibs/md4c-m/actions/workflows/ci.yml)

上游 C API 保持不变：`md_parse`、`MD_PARSER`、`MD_BLOCK_*`、`md_html` 都是上游的全局名字。
解析器来自 `compat.md4c` 0.5.3；本包加上上游的第二个库 md4c-html（HTML 渲染器），并把
`MD_FLAG_*` 宏映射成常量。每次 CI 都通过模块运行上游自己的测试集（CommonMark 0.31.2 规范、
GFM 扩展、回归用例，共 808 个例子）。

## 模块

- `import mcpplibs.mwrap.md4c;`：解析 API（`md_parse`、回调、各种 detail），并重新导出下面两个模块
- `import mcpplibs.mwrap.md4c.html;`：`md_html`，Markdown 直接转 HTML
- `import mcpplibs.mwrap.md4c.macros;`：`MD_FLAG_*`、`MD_DIALECT_*`、`MD_HTML_FLAG_*`，位于 `mcpplibs::mwrap::md4c::macros`

> 更多模块 API -> [用法与 API](docs/usage.md)

## 快速开始

```sh
mcpp new notes --template mcpplibs.mwrap.md4c@0.5.3
cd notes
mcpp run
```

默认模板用 GitHub 扩展把一篇文档渲染成 HTML，并通过 `md_parse` 的回调打印标题大纲。

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

## 宏

具名模块不能导出宏；对象式的宏以原名映射为 `inline constexpr unsigned`：
`macros::MD_FLAG_TABLES`、`macros::MD_DIALECT_GITHUB`、`macros::MD_HTML_FLAG_XHTML`。
同一个翻译单元如果还包含了 `<md4c.h>`，宏是生效的，连 `macros::MD_FLAG_TABLES` 里的名字也会被展开；
这时直接用宏本身（见 [tests/header_mix_test.cpp](tests/header_mix_test.cpp)）。

## 示例

- [examples/md2html](examples/md2html)：支持上游 `md2html` 的选项，读标准输入或文件；
  [tools/run_conformance.py](tools/run_conformance.py) 用它驱动上游的 `test/run-testsuite.py`。

## 构建和测试

Linux、macOS、Windows 的 CI 构建模块、运行测试、导出审计（[tools/check_exports.py](tools/check_exports.py)：
两个头文件的每个公开名字都已导出）和上游一致性测试集；另一个作业把默认模板当作已安装的包来创建并运行。

## 许可

封装部分为 [Apache-2.0](LICENSE)，归属 mcpp-community；MD4C 本身仍是 MIT。
[上游原始 README 和许可证](upstream/md4c/)、vendored 的 md4c-html 源码及其校验和见
[upstream/documents.json](upstream/documents.json)。
