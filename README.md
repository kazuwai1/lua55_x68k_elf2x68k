# lua-5.5 for x68k(elf2x68k)
Lua 5.5.0 を elf2x68kを使ってx68k向けにビルドしてみました。  
XC lib版との大きな違いは以下になります。
* 整数型データが64bit intです
* X-BASIC互換関数は非対応です

## インストール
### とにかくインタプリタを使ってみたい人
* install/bin の中にある"lua.x" と "luac.x"を環境変数PATHに含まれるディレクトリにコピーして lua.x を起動してください

### lua-cjsonモジュールを使ってみたい人
* cjson.decode/cjson.encodeは標準で組み込まれているためrequire("cjson")しなくても使えます
* cjson.utilを使いたい場合は以下の手順を実施しておいて require("cjson.util") して使用します  
    * install/luamodフォルダの中身を環境変数 LUA_PATH に含まれるディレクトリにコピーする
    * ( LUA_PATHの設定例 : LUA_PATH=;;A:\\luamod\\?.lua;A:\\luamod\\?.luac )
* lua_cjsonのAPI関数については [このあたり](https://github.com/kazuwai1/lua_cjson_x68k/blob/main/README_orig.md)や[このあたり](https://github.com/kazuwai1/lua_cjson_x68k/blob/main/manual.adoc)を参照してください

### LuaのC言語プログラムへの組み込みも試してみたい人
* install/libの中の "lualib.a" をターゲットプログラムと一緒にリンクしてください
* 以下のヘッダファイルを適宜インクルードしてください。
    * lauxlib.h
    * lua.h
    * lua.hpp
    * luaconf.h
    * lualib.h

## 起動と起動オプション
* lua.xを実行すると対話環境が起動します
* luac.xはソースコードをバイトコードにコンパイルするために使用します。
* 対話環境を終了するには "os.exit()"と入力するか、ctrl-zを入力してください。
* 起動時に指摘できるオプションは無効なオプションを指定すると見ることができます("lua -z"等)

## r1 の主な実装内容
* elf2x68kでビルドできるようにしました
* lua_cjsonをスタティックリンクして使用可能にしています
* readlineとしてHISTORY.Xを使えるように _dos_gets() を使用しています。

## ビルド環境
elf2x68k環境でビルドできます。私はdebianにインストールした環境でビルドしています

## ビルドについて
* lua-5.5.0ディレクトリで make すればビルドが走るようにしています
* lua-5.5.0ディレクトリで make local すると install ディレクトリに以下のファイルがコピーされます
    * install/bin : lua.x および luac.x
    * install/include : 他のアプリに組み込む際に必要になるヘッダファイル
    * install/lib     : 他のアプリに組み込む際に必要になるライブラリファイル
* lua.x / luac.x はx68k環境へコピーして使用してください。ヘッダファイルとライブラリファイルは組み込み環境から適宜参照してください。

## ライセンス
* Luaは下記のようにMITライセンスで配布されています。Lua for x68k向けの独自改変部分についても同様の扱いとします。[Copyright © 1994–2023 Lua.org, PUC-Rio.](https://www.lua.org/license.html)
* lua-cjsonはMITのライセンスで配布されています。詳しくは[ここ](https://github.com/kazuwai1/lua_cjson_x68k/blob/main/LICENSE)を参照してください。
