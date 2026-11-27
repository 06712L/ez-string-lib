<div align="center">
<br />
<h1>Ez String Lib</h1>
<h3>ESL</h3>

一个处理文本的函数库
</div>

[[繁體中文]](README-zh_hant.md) [简体中文] [[English]](README.md)

# 介绍

Ez String Lib 是一个为了练习及提供一些方便而诞生的函数库

# 特色

- 处理和文本相关的事
- 处理NULL保证不会瞬间崩溃但可能会慢性崩溃
- 函数库使用C99撰写
- 采用MIT协议

# 依赖

这是目前测试过的最低版本

- (build) Xmake 2.9.9+
- 支持C99的编译器
- (可选) 支持C++20的编译器
- (可选) (test) Google Test 1.16.0+

# 环境变量

目前尚未支持针对语言环境变量的优化 :)

# 文档

- [API文档](https://06712l.github.io/ez-string-lib)

# 编译

- `xmake` 编译默认目标 *(共享库/静态库)*
- `xmake build [目标]` 编译特定目标
- `xmake build --all` 编译所有目标
- `xmake build` 同 `xmake`
- `xmake run [目标]` 编译并执行特定目标 *(仅适用于可执行文件，如测试)*
- `xmake run --all` 编译并执行所有目标 *(仅适用于可执行文件，如测试)*
- `xmake config [options]` 配置编译设置
- `xmake clean` 清除编译产物
- `xmake clean --all` 清除所有，如编译设置及编译产物等等
- [更多Xmake使用方法](https://xmake.io/guide/quick-start.html)