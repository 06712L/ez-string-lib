<div align="center">
<br />
<h1>Ez String Lib</h1>
<h3>ESL</h3>

A library for working with text
</div>

[[繁體中文]](README-zh_hant.md) [[简体中文]](README-zh_hans.md) [English]

# Introduction

Ez String Lib is a library created for practice and convenience.

# Features

- Handles text-related tasks
- NULL handling won't crash immediately, but may cause problems over time
- Written in C99
- MIT licensed

# Dependencies

These are the minimum tested versions:

- (build) Xmake 2.9.9+
- A C99-compatible compiler
- (optional) A C++20-compatible compiler
- (optional) (test) Google Test 1.16.0+

# Environment Variables

Locale environment variable optimization is not supported yet :)

# Documentation

- [API Documentation](https://06712l.github.io/ez-string-lib)

# Build

- `xmake` builds the default target *(shared/static library)*
- `xmake build [target]` builds a specific target
- `xmake build --all` builds all targets
- `xmake build` is equivalent to `xmake`
- `xmake run [target]` builds and runs a specific target *(executables only, such as tests)*
- `xmake run --all` builds and runs all targets *(executables only, such as tests)*
- `xmake config [options]` configures build settings
- `xmake clean` removes build artifacts
- `xmake clean --all` removes everything, including build settings and artifacts
- [More Xmake usage](https://xmake.io/guide/quick-start.html)