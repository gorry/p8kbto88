
# ◇P8KB288
PC-8001 Keyboard to PC-8801(mini DIN 5p type)
PC-8001キーボードをPC-8801（ミニDIN5p型）へ接続する

## これはなに？
これは、「PC-8001用キーボードをPC-8801に接続する」ためのRaspberry Pi Pico（以下Pico）用モジュールのプロダクトです。こんな酔狂な使い方をする人はそうそういないと思うのですが、「キーマトリクスが直接バスに繋がっている方式のキーボードを読み取る」ことと「キー入力をシリアル（UART）で送出する」コードのサンプルとしては使い物になるかもしれません。

## 内容
本プロダクトには、kicadによる回路図データおよび画像と、それに搭載されたPicoで駆動するプログラムが含まれています。
PC-8001キーボードについては、当方による以下資料をご覧ください。
- https://github.com/gorry/P8MK2KB

PC-8801キーボードについては、youkan氏による以下の資料が便利です。
- http://www.maroon.dti.ne.jp/youkan/pc88/kbd.html

## 使い方
1. PC-8001のキーボードを本体から取り出し、ケーブルを抜いて分離します。
2. 分離したキーボードにPicoを接続します。キーボード側のコネクタは2.54mm間隔のピンで、デュポンコネクタが接続できます。PC-8001では10ピンが２本、PC-8001mkⅡ/SRでは10ピンと12ピンです。
3. PC-8801シリーズの「キーボードコネクタがミニDIN5p型の機種」のコネクタにPicoを接続します。「ミニDIN5p型の機種」は、FH/MH以降が該当します。
4. この状態でPC-8801の電源を投入すると、PicoおよびPC-8001のキーボードに電力が供給され、PC-8001のキーボードからの入力がPC-8801へ送信されます。

### 拡張されたキーマッピング
本システムでは、「かな」キーをロックした状態のキーで「PC-8001キーボードで不足しているキー」を入力することができます。
- NUM 0 → PC
- NUM 1 → 左矢印
- NUM 2 → 下矢印
- NUM 3 → 右矢印
- NUM 4 → 左矢印
- NUM 6 → 右矢印
- NUM 7 → 左矢印
- NUM 8 → 上矢印
- NUM 9 → 右矢印
- NUM * → ROLL UP
- NUM + → ROLL DOWN
- NUM = → ROLL UP
- NUM . → COPY
- HOME → PC
- 上矢印 → HELP
- 右矢印 → INS
- INS/DEL → DEL
- ESC → CAPS（トグル動作）

## 回路の解説
回路は、大きく３つに分かれています。

![20240628_p8kbto88](https://github.com/gorry/p8kbto88/assets/486696/cb9a44a0-ccce-4029-8868-2c472313688b)

### 1. PC-8001キーマトリクスへのアドレス出力
PC-8001キーマトリクスのA0-A9をすべてHI状態にした後、１本ずつ順にLOWにしていきます。
mkⅡ/SR以降のキーボードの場合、A10は常にHIにしておきます。A11は未接続です。

### 2. PC-8001キーマトリクスからのデータ入力
LOWにしたアドレス線に繋がるキースイッチに対して、D0-D7でON(LOW)/OFF(HI)情報を得ることができます。

### 3. PC-8801キーボードデータ線へのシリアル送信
入力されたキー情報をTxD線でPC-8801キーボードデータ線へ送信します。またこの線が含まれたコネクタから電源を得て、回路全体を駆動します。

## プログラムについて
プログラムはArduino環境で書かれているため、大きくsetup()とloop()の２つに分かれています。
またloop()は「PC-8001のキーボードを読み取る部分」「キー状態をキーイベントに変換する部分」「PC-8801キーボードデータ線へ送信する部分」の３つに分かれています。

### 1. setup
ほとんどはGPIOの初期設定です。
デバッグ環境の選択用にPICOPROBEマクロが定義されています。1にするとpicoprobeを使用（Serial1へログを出力）、0にすると非使用（Serial0へログを出力）となります。picoprobeに関しては、以下をご覧ください。
https://github.com/raspberrypi/debugprobe/releases

### 2. PC-8001のキーボードを読み取る部分
read80kb.h が担当しています。
PC-8001キーマトリクスのA0-A9をすべてHI状態にした後、１本ずつ順にLOWにしていきながら、D0-D7の状態を読み取ります。キーが押されているとLOW、押されていないとHIが読み取れます。
8bitx9本で合計72個分のキースイッチを読み取ります。

### 3. キー状態をキーイベントに変換する部分
キー状態の処理を keysw.h が、キーイベントとして貯め込む処理を send88kb.h が担当しています。
72個のキーに対して前回状態との差分を検知し、それぞれ個別のキーの処理へ割り振ります。
個別のキーの処理先で、「PC-8801で入力されるキー」をキー入力イベントとして send88kb.h へ送ります。

### 4. PC-8801キーボードデータ線へ送信する部分
send88kb.h が担当しています。
keysw.h から送られたキー入力イベントを貯め込み、順にPC-8801キーボードデータ線へ送信します。
実際の送信処理は pio/pio_tx.pio から生成された pio_tx.h が行います。rp2040独自のpioasmで「20800bps/スタート1bit/データ12bit/偶数パリティ/ストップ1bit」のUARTデータとして送出されます。

## 著作権表記

Copyright 2024 Hiroaki GOTO as GORRY

本プロダクトは、自由かつ無償で使用・コピー・配布・変更・流用を行うことができます。また許可なく再配布・出版・販売を行うことができます。
本プロダクトは、無保証です。使用した、あるいはしなかったことによる一切の責任は使用者にあるものとします。
本プロダクトは、以下URLを配布先とします。利便性などのためにこれ以外のURLで配布することがありますが、以下が最も正式なものであり、完全な最新のパッケージを得ることができます。

## 連絡先

https://github.com/gorry/p8kbto88

## [EOF]
