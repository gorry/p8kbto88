// ◇ PC-8001のキーボードをPC-8801（ミニDIN5p型）へ接続する
// Copyright 2024 GORRY.
// =====================================================================

#include <stdarg.h>

#define PICOPROBE 0

// =====================================================================

#define LOG_E_ENABLE 1
#define LOG_W_ENABLE 1
#define LOG_I_ENABLE 1
#define LOG_D_ENABLE 1
#define LOG_T_ENABLE 1

#if PICOPROBE
#define LOG_E(...) if (LOG_E_ENABLE) {Serial1.printf(__VA_ARGS__);}
#define LOG_W(...) if (LOG_W_ENABLE) {Serial1.printf(__VA_ARGS__);}
#define LOG_I(...) if (LOG_I_ENABLE) {Serial1.printf(__VA_ARGS__);}
#define LOG_D(...) if (LOG_D_ENABLE) {Serial1.printf(__VA_ARGS__);}
#define LOG_T(...) if (LOG_T_ENABLE) {Serial1.printf(__VA_ARGS__);}
#else
#define LOG_E(...) if (LOG_E_ENABLE) {Serial.printf(__VA_ARGS__);}
#define LOG_W(...) if (LOG_W_ENABLE) {Serial.printf(__VA_ARGS__);}
#define LOG_I(...) if (LOG_I_ENABLE) {Serial.printf(__VA_ARGS__);}
#define LOG_D(...) if (LOG_D_ENABLE) {Serial.printf(__VA_ARGS__);}
#define LOG_T(...) if (LOG_T_ENABLE) {Serial.printf(__VA_ARGS__);}
#endif

// =====================================================================

#include "pio_tx.h"
#include "gpiodef.h"
#include "keyname.h"
#include "keysw.h"
#include "read80kb.h"
#include "send88kb.h"

// =====================================================================

int TEST_LED;

// =====================================================================

void setup() {
 // put your setup code here, to run once:
	if (PICOPROBE) {
		Serial1.setTX(0);
		Serial1.setRX(1);
		Serial1.begin(115200);
		LOG_I("Begin P8KB1 with Picoprobe\n");
	} else {
		Serial.begin(115200);
		LOG_I("Begin P8KB1\n");
	}

	// 初期化
	keysw_init();
	read80kb_init();
	send88kb_init();
	TEST_LED = 1;

	// キーに入力がある度に本体LEDを点滅させるための処理
	pinMode(25, OUTPUT);
	digitalWrite(25, TEST_LED); TEST_LED = 1-TEST_LED;
}

// =====================================================================

void loop() {
	read80kb();
	bool diff = keysw();
	send88kb();

	// キーの状態変化があったらLEDを点滅させる
	if (diff) {
		 digitalWrite(25, TEST_LED); TEST_LED = 1-TEST_LED;
	}

	delay(1);
}

// =====================================================================
// [EOF]
