// ◇ PC-8001のキーボードを読み取る処理
// Copyright 2024 GORRY.
// =====================================================================

// 初期化
void read80kb_init() {
	// アドレスピン（OUT）の準備
	for (int y=0; y<KB_ADR_SIZE; y++) {
		pinMode(GPIO_ADR[y], OUTPUT);
		digitalWrite(GPIO_ADR[y], 1);
	}

	// A10ピンの初期化
	pinMode(14, OUTPUT);
	digitalWrite(14, 0);

	// A11ピンの初期化も念のため
	pinMode(15, OUTPUT);
	digitalWrite(15, 0);

	// データピン（IN）の準備。プルアップで
	for (int x=0; x<KB_DATA_SIZE; x++) {
		pinMode(GPIO_DATA[x], INPUT_PULLUP);
	}

}

// =====================================================================

// PC-8001のキースイッチを読み込む
void read80kb() {
	int adr;
	// アドレスピンを１本ずつONにしながらキースイッチを読み込む
	// アドレスピンは負論理（ON=0, OFF=1）
	for (adr=0; adr<KB_ADR_SIZE; adr++) {
		// 前のアドレスをOFFにしながら、今のアドレスをONにする
		if (adr != 0) {
			digitalWrite(GPIO_ADR[adr-1], 1);
		}
		digitalWrite(GPIO_ADR[adr], 0);

		// 少し待ったほうがいい気がする
		// delay(1);
		delayMicroseconds(100);

		// データピンを読む
		// データピンは負論理（ON=0, OFF=1）
		unsigned char d = 0;
		for (int x=0; x<KB_DATA_SIZE; x++) {
			int p = digitalRead(GPIO_DATA[x]);
			d = (d<<1)|p;
		}
		keysw_set(adr, d);
	}
	// 最後のアドレスピンをOFFにする
	digitalWrite(GPIO_ADR[adr-1], 1);
}

// =====================================================================
// [EOF]
