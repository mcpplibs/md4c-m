#!/usr/bin/env python3
"""Audit the module surface against the public headers.

Every typedef, enum, enumerator, struct and function of <md4c.h> must be
exported by src/md4c.cppm, md_html by src/html.cppm, and every object-like
MD_FLAG_* / MD_DIALECT_* / MD_HTML_FLAG_* macro mapped in src/macros.cppm.
<md4c.h> is read from the upstream release tarball (fetched and verified by
run_conformance.fetch, the same bytes compat.md4c builds), <md4c-html.h> from
upstream/md4c/src.
"""
from pathlib import Path
import re
import sys


def strip_comments(text: str) -> str:
    return re.sub(r'/\*.*?\*/', '', text, flags=re.S)


def find_md4c_h(root: Path) -> Path:
    sys.path.insert(0, str(Path(__file__).resolve().parent))
    from run_conformance import fetch
    return fetch(root).parent / 'src/md4c.h'


def names_of(header: str):
    text = strip_comments(header)
    names = set()
    names |= set(re.findall(r'typedef\s+(?:unsigned|char|WCHAR)\s+(MD_\w+)\s*;', text))
    names |= set(re.findall(r'typedef\s+(?:enum|struct)\s+(MD_\w+)\s*\{', text))
    names |= set(re.findall(r'\}\s*(MD_\w+)\s*;', text))
    names |= set(re.findall(r'typedef\s+MD_\w+\s+(MD_\w+)\s*;', text))
    for body in re.findall(r'typedef\s+enum\s+\w+\s*\{(.*?)\}', text, flags=re.S):
        names |= set(re.findall(r'\b(MD_[A-Z_0-9]+)\b\s*(?:=\s*\d+\s*)?,?', body))
    names |= set(re.findall(r'^int\s+(md_\w+)\s*\(', text, flags=re.M))
    macros = set(re.findall(r'#define\s+((?:MD_FLAG|MD_DIALECT|MD_HTML_FLAG)_\w+)\s', text))
    return names, macros


def exported(path: Path):
    return set(re.findall(r'export using ::(\w+);', path.read_text(encoding='utf-8')))


def main():
    root = Path(__file__).resolve().parents[1]
    core_names, core_macros = names_of(find_md4c_h(root).read_text(encoding='utf-8'))
    html_names, html_macros = names_of((root / 'upstream/md4c/src/md4c-html.h').read_text(encoding='utf-8'))
    problems = []
    missing = core_names - exported(root / 'src/md4c.cppm')
    if missing:
        problems.append('src/md4c.cppm lacks: ' + ', '.join(sorted(missing)))
    missing = html_names - exported(root / 'src/html.cppm')
    if missing:
        problems.append('src/html.cppm lacks: ' + ', '.join(sorted(missing)))
    mapped = set(re.findall(r'inline constexpr unsigned (MD_\w+) =', (root / 'src/macros.cppm').read_text(encoding='utf-8')))
    missing = (core_macros | html_macros) - mapped
    if missing:
        problems.append('src/macros.cppm lacks: ' + ', '.join(sorted(missing)))
    if problems:
        sys.exit('\n'.join(problems))
    print(f'exports: {len(core_names)} md4c.h names, {len(html_names)} md4c-html.h names, {len(mapped)} macros')


if __name__ == '__main__':
    main()
