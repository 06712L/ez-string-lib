<div align="center">
<br />
<h1>Ez String Lib</h1>
<h3>ESL</h3>

一個處理文字的函數庫
</div>

[繁體中文] [[简体中文]](README-zh_hans.md) [[English]](README.md)

# 介紹

Ez String Lib 是一個為了練習及提供一些方便而誕生的函數庫

# 特色

- 處理和文字相關的事
- 處理NULL保證不會瞬間崩潰但可能會慢性崩潰
- 函數庫使用C99撰寫
- 采用MIT协议

# 依賴

這是目前測試過的最低版本

- (build) Xmake 2.9.9+
- 支援C99的編譯器
- (可選) 支援C++20的編譯器
- (可選) (test) Google Test 1.16.0+

# 環境變數

目前尚未支援針對語言環境變數的優化 :)

# 文檔

- [API文檔](https://06712l.github.io/ez-string-lib)

# 編譯

- `xmake` 編譯默認目標 *(共享庫/靜態庫)*
- `xmake build [目標]` 編譯特定目標
- `xmake build --all` 編譯所有目標
- `xmake build` 同 `xmake`
- `xmake run [目標]` 編譯並執行特定目標 *(僅是用於執行檔，如測試)*
- `xmake run --all` 編譯並執行所有目標 *(僅是用於執行檔，如測試)*
- `xmake config [options]` 配置編譯設定
- `xmake clean` 清除編譯產物
- `xmake clean --all` 清除所有，如編譯設定及編譯產物等等
- [更多Xmake使用方法](https://xmake.io/guide/quick-start.html)
