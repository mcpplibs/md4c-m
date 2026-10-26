#!/usr/bin/env python3
"""Run upstream md4c's own test suites (CommonMark spec, GFM extensions,
regressions, coverage) against this wrapper's md2html example.

The upstream release tarball is downloaded once into target/upstream and
verified against the SHA256 recorded in upstream/documents.json; its test/
directory is used unchanged. Every suite must pass with no failures.
"""
import argparse
import hashlib
import json
import os
from pathlib import Path
import subprocess
import sys
import tarfile
import urllib.request


def fetch(root: Path) -> Path:
    provenance = json.loads((root / 'upstream/documents.json').read_text(encoding='utf-8'))
    cache = root / 'target/upstream'
    cache.mkdir(parents=True, exist_ok=True)
    archive = cache / 'md4c-release.tar.gz'
    if not archive.exists() or hashlib.sha256(archive.read_bytes()).hexdigest() != provenance['upstream_sha256']:
        print('+ fetch', provenance['upstream'], flush=True)
        with urllib.request.urlopen(provenance['upstream'], timeout=120) as response:
            archive.write_bytes(response.read())
    digest = hashlib.sha256(archive.read_bytes()).hexdigest()
    if digest != provenance['upstream_sha256']:
        sys.exit(f'upstream archive checksum {digest} != {provenance["upstream_sha256"]}')
    with tarfile.open(archive) as tar:
        top = tar.getmembers()[0].name.split('/')[0]
        if not (cache / top).exists():
            tar.extractall(cache, filter='data')
    return cache / top / 'test'


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--program', type=Path, help='the md2html binary (default: build examples/md2html)')
    parser.add_argument('--mcpp', default='mcpp')
    args = parser.parse_args()
    root = Path(__file__).resolve().parents[1]
    program = args.program
    if program is None:
        example = root / 'examples/md2html'
        subprocess.run([args.mcpp, 'build'], cwd=example, check=True)
        name = 'md2html.exe' if os.name == 'nt' else 'md2html'
        found = sorted((example / 'target').rglob(name), key=lambda p: p.stat().st_mtime)
        found = [p for p in found if p.parent.name == 'bin']
        if not found:
            sys.exit('md2html was not built')
        program = found[-1]
    tests = fetch(root)
    suites = sorted(tests.glob('*.txt'))
    failed = []
    for suite in suites:
        print(f'== {suite.name}', flush=True)
        result = subprocess.run([sys.executable, 'run-testsuite.py', '-s', suite.name, '-p', str(program.resolve())],
                                cwd=tests, capture_output=True, text=True, encoding='utf-8')
        lines = result.stdout.strip().splitlines()
        print(lines[-1] if lines else result.stderr, flush=True)
        if result.returncode != 0:
            print(result.stdout[-4000:])
            failed.append(suite.name)
    if failed:
        sys.exit('failing suites: ' + ', '.join(failed))
    print(f'conformance: {len(suites)} upstream suites pass')


if __name__ == '__main__':
    main()
