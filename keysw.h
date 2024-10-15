// ◇ キー状態をキーイベントに変換する処理
// Copyright 2024 GORRY.
// =====================================================================

// キースイッチ状態を溜めておくバッファ
unsigned char KB_BAK[KB_ADR_MAX];
unsigned char KB_NOW[KB_ADR_MAX];

typedef void KEYSW(bool b);
extern const KEYSW* KEYSWTBL[KB_ADR_MAX*KB_DATA_SIZE];

#define KBBIT(a,b) ((KB_NOW[a] & (1<<b)) ? false : true)
#define KBBIT_KANA() KBBIT(0x08,5)

bool CAPS_TOGGLE;

extern void send88kb_push(int adr, int kbbit, bool b);

// =====================================================================

// 初期化
void keysw_init(void) {
	// キーボード入力を溜めておくバッファ
	memset(&KB_BAK, 0xff, KB_ADR_MAX);
	memset(&KB_NOW, 0xff, KB_ADR_MAX);

	CAPS_TOGGLE = false;

}

// =====================================================================

// キースイッチのセット
void keysw_set(int adr, int sw) {
	KB_NOW[adr] = sw;
}

// =====================================================================

// 変化のあったキースイッチの処理を行う
bool keysw(void) {
	bool diff = false;
	for (int adr=0; adr<KB_ADR_SIZE; adr++) {
		int d = KB_BAK[adr] ^ KB_NOW[adr];
		if (d) {
			for (int x=0; x<KB_DATA_SIZE; x++) {
				if (d & (1<<x)) {
					KEYSW* sw = KEYSWTBL[adr*KB_DATA_SIZE+x];
					bool b = ((KB_NOW[adr] & (1<<x)) ? false : true); // 負論理につき
					sw(b);
				}
				KB_BAK[adr] = KB_NOW[adr];
				diff = true;
			}
		}
	}
	return diff;
}

// =====================================================================

void keysw_00(bool b) {
	if (KBBIT_KANA()) {
		send88kb_push(0x0d, 2, b); // PC
	} else {
		send88kb_push(0x00, 0, b); // NUM 0
	}
}

void keysw_01(bool b) {
	if (KBBIT_KANA()) {
		send88kb_push(0x0a, 2, b); // LEFT
	} else {
		send88kb_push(0x00, 1, b); // NUM 1
	}
}

void keysw_02(bool b) {
	if (KBBIT_KANA()) {
		send88kb_push(0x0a, 1, b); // DOWN
	} else {
		send88kb_push(0x00, 2, b); // NUM 2
	}
}

void keysw_03(bool b) {
	if (KBBIT_KANA()) {
		send88kb_push(0x08, 2, b); // RIGHT
	} else {
		send88kb_push(0x00, 3, b); // NUM 3
	}
}

void keysw_04(bool b) {
	if (KBBIT_KANA()) {
		send88kb_push(0x0a, 2, b); // LEFT
	} else {
		send88kb_push(0x00, 4, b); // NUM 4
	}
}

void keysw_05(bool b) {
	if (KBBIT_KANA()) {
		send88kb_push(0x00, 5, b); // NUM 5
	} else {
		send88kb_push(0x00, 5, b); // NUM 5
	}
}

void keysw_06(bool b) {
	if (KBBIT_KANA()) {
		send88kb_push(0x08, 2, b); // RIGHT
	} else {
		send88kb_push(0x00, 6, b); // NUM 6
	}
}

void keysw_07(bool b) {
	if (KBBIT_KANA()) {
		send88kb_push(0x0a, 2, b); // LEFT
	} else {
		send88kb_push(0x00, 7, b); // NUM 7
	}
}

// --------

void keysw_10(bool b) {
	if (KBBIT_KANA()) {
		send88kb_push(0x08, 1, b); // UP
	} else {
		send88kb_push(0x01, 0, b); // NUM 8
	}
}

void keysw_11(bool b) {
	if (KBBIT_KANA()) {
		send88kb_push(0x08, 2, b); // RIGHT
	} else {
		send88kb_push(0x01, 1, b); // NUM 9
	}
}

void keysw_12(bool b) {
	if (KBBIT_KANA()) {
		send88kb_push(0x0b, 0, b); // ROLLUP
	} else {
		send88kb_push(0x01, 2, b); // NUM *
	}
}

void keysw_13(bool b) {
	if (KBBIT_KANA()) {
		send88kb_push(0x0b, 1, b); // ROLLDOWN
	} else {
		send88kb_push(0x01, 3, b); // NUM +
	}
}

void keysw_14(bool b) {
	if (KBBIT_KANA()) {
		send88kb_push(0x0b, 0, b); // ROLLUP
	} else {
		send88kb_push(0x01, 4, b); // NUM =
	}
}

void keysw_15(bool b) {
	send88kb_push(0x01, 5, b); // NUM ,
}

void keysw_16(bool b) {
	if (KBBIT_KANA()) {
		send88kb_push(0x0a, 4, b); // COPY
	} else {
		send88kb_push(0x01, 6, b); // NUM .
	}
}

void keysw_17(bool b) {
	send88kb_push(0x01, 7, b); // RETURN
}

// --------

void keysw_20(bool b) {
	send88kb_push(0x02, 0, b); // @
}

void keysw_21(bool b) {
	send88kb_push(0x02, 1, b); // A
}

void keysw_22(bool b) {
	send88kb_push(0x02, 2, b); // B
}

void keysw_23(bool b) {
	send88kb_push(0x02, 3, b); // C
}

void keysw_24(bool b) {
	send88kb_push(0x02, 4, b); // D
}

void keysw_25(bool b) {
	send88kb_push(0x02, 5, b); // E
}

void keysw_26(bool b) {
	send88kb_push(0x02, 6, b); // F
}

void keysw_27(bool b) {
	send88kb_push(0x02, 7, b); // G
}

// --------

void keysw_30(bool b) {
	send88kb_push(0x03, 0, b); // H
}

void keysw_31(bool b) {
	send88kb_push(0x03, 1, b); // I
}

void keysw_32(bool b) {
	send88kb_push(0x03, 2, b); // J
}

void keysw_33(bool b) {
	send88kb_push(0x03, 3, b); // K
}

void keysw_34(bool b) {
	send88kb_push(0x03, 4, b); // L
}

void keysw_35(bool b) {
	send88kb_push(0x03, 5, b); // M
}

void keysw_36(bool b) {
	send88kb_push(0x03, 6, b); // N
}

void keysw_37(bool b) {
	send88kb_push(0x03, 7, b); // O
}

// --------

void keysw_40(bool b) {
	send88kb_push(0x04, 0, b); // P
}

void keysw_41(bool b) {
	send88kb_push(0x04, 1, b); // Q
}

void keysw_42(bool b) {
	send88kb_push(0x04, 2, b); // R
}

void keysw_43(bool b) {
	send88kb_push(0x04, 3, b); // S
}

void keysw_44(bool b) {
	send88kb_push(0x04, 4, b); // T
}

void keysw_45(bool b) {
	send88kb_push(0x04, 5, b); // U
}

void keysw_46(bool b) {
	send88kb_push(0x04, 6, b); // V
}

void keysw_47(bool b) {
	send88kb_push(0x04, 7, b); // W
}

// --------

void keysw_50(bool b) {
	send88kb_push(0x05, 0, b); // X
}

void keysw_51(bool b) {
	send88kb_push(0x05, 1, b); // Y
}

void keysw_52(bool b) {
	send88kb_push(0x05, 2, b); // Z
}

void keysw_53(bool b) {
	send88kb_push(0x05, 3, b); // [
}

void keysw_54(bool b) {
	send88kb_push(0x05, 4, b); // "\\" 
}

void keysw_55(bool b) {
	send88kb_push(0x05, 5, b); // ]
}

void keysw_56(bool b) {
	send88kb_push(0x05, 6, b); // ^
}

void keysw_57(bool b) {
	send88kb_push(0x05, 7, b); // -
}

// --------

void keysw_60(bool b) {
	send88kb_push(0x06, 0, b); // 0
}

void keysw_61(bool b) {
	send88kb_push(0x06, 1, b); // 1
}

void keysw_62(bool b) {
	send88kb_push(0x06, 2, b); // 2
}

void keysw_63(bool b) {
	send88kb_push(0x06, 3, b); // 3
}

void keysw_64(bool b) {
	send88kb_push(0x06, 4, b); // 4
}

void keysw_65(bool b) {
	send88kb_push(0x06, 5, b); // 5
}

void keysw_66(bool b) {
	send88kb_push(0x06, 6, b); // 6
}

void keysw_67(bool b) {
	send88kb_push(0x06, 7, b); // 7
}

// --------

void keysw_70(bool b) {
	send88kb_push(0x07, 0, b); // 8
}

void keysw_71(bool b) {
	send88kb_push(0x07, 1, b); // 9
}

void keysw_72(bool b) {
	send88kb_push(0x07, 2, b); // :
}

void keysw_73(bool b) {
	send88kb_push(0x07, 3, b); // ;
}

void keysw_74(bool b) {
	send88kb_push(0x07, 4, b); // ,
}

void keysw_75(bool b) {
	send88kb_push(0x07, 5, b); // .
}

void keysw_76(bool b) {
	send88kb_push(0x07, 6, b); // /
}

void keysw_77(bool b) {
	send88kb_push(0x07, 7, b); // _
}

// --------

void keysw_80(bool b) {
	if (KBBIT_KANA()) {
		send88kb_push(0x0d, 2, b); // PC
	} else {
		send88kb_push(0x08, 0, b); // HOME
	}
}

void keysw_81(bool b) {
	if (KBBIT_KANA()) {
		send88kb_push(0x0a, 3, b); // HELP
	} else {
		send88kb_push(0x08, 1, b); // UP
	}
}

void keysw_82(bool b) {
	if (KBBIT_KANA()) {
		if (b) { // ON/OFFで順序が変わる
			send88kb_push(0x0c, 6, b); // INS
			send88kb_push(0x08, 6, b); // SHIFT
			send88kb_push(0x08, 3, b); // INS/DEL
		} else {
			send88kb_push(0x0c, 6, b); // INS
			send88kb_push(0x08, 3, b); // INS/DEL
			send88kb_push(0x08, 6, b); // SHIFT
		}
	} else {
		send88kb_push(0x08, 2, b); // RIGHT
	}
}

void keysw_83(bool b) {
	if (KBBIT_KANA()) {
		if (b) { // ON/OFFで順序が変わる
			send88kb_push(0x0c, 7, b); // DEL
			send88kb_push(0x08, 3, b); // INS/DEL
		} else {
			send88kb_push(0x0c, 7, b); // DEL
			send88kb_push(0x08, 3, b); // INS/DEL
		}
	} else {
		send88kb_push(0x08, 3, b); // INS/DEL
	}
}

void keysw_84(bool b) {
	send88kb_push(0x08, 4, b); // GRPH
}

void keysw_85(bool b) {
	send88kb_push(0x08, 5, b); // KANA
}

void keysw_86(bool b) {
	send88kb_push(0x08, 6, b); // SHIFT
}

void keysw_87(bool b) {
	send88kb_push(0x08, 7, b); // CTRL
}

// --------

void keysw_90(bool b) {
	send88kb_push(0x09, 0, b); // STOP
}

void keysw_91(bool b) {
	if (KBBIT_KANA()) {
		if (b) { // ON/OFFで順序が変わる
			send88kb_push(0x0c, 0, b); // F6
			send88kb_push(0x08, 6, b); // SHIFT
			send88kb_push(0x09, 1, b); // F1
		} else {
			send88kb_push(0x0c, 0, b); // F6
			send88kb_push(0x09, 1, b); // F1
			send88kb_push(0x08, 6, b); // SHIFT
		}
	} else {
		send88kb_push(0x09, 1, b); // F1
	}
}

void keysw_92(bool b) {
	if (KBBIT_KANA()) {
		if (b) { // ON/OFFで順序が変わる
			send88kb_push(0x0c, 1, b); // F7
			send88kb_push(0x08, 6, b); // SHIFT
			send88kb_push(0x09, 2, b); // F2
		} else {
			send88kb_push(0x0c, 1, b); // F7
			send88kb_push(0x09, 2, b); // F2
			send88kb_push(0x08, 6, b); // SHIFT
		}
	} else {
		send88kb_push(0x09, 2, b); // F2
	}
}

void keysw_93(bool b) {
	if (KBBIT_KANA()) {
		if (b) { // ON/OFFで順序が変わる
			send88kb_push(0x0c, 2, b); // F8
			send88kb_push(0x08, 6, b); // SHIFT
			send88kb_push(0x09, 3, b); // F3
		} else {
			send88kb_push(0x0c, 2, b); // F8
			send88kb_push(0x09, 3, b); // F3
			send88kb_push(0x08, 6, b); // SHIFT
		}
	} else {
		send88kb_push(0x09, 3, b); // F3
	}
}

void keysw_94(bool b) {
	if (KBBIT_KANA()) {
		if (b) { // ON/OFFで順序が変わる
			send88kb_push(0x0c, 3, b); // F9
			send88kb_push(0x08, 6, b); // SHIFT
			send88kb_push(0x09, 4, b); // F4
		} else {
			send88kb_push(0x0c, 3, b); // F9
			send88kb_push(0x09, 4, b); // F4
			send88kb_push(0x08, 6, b); // SHIFT
		}
	} else {
		send88kb_push(0x09, 4, b); // F4
	}
}

void keysw_95(bool b) {
	if (KBBIT_KANA()) {
		if (b) { // ON/OFFで順序が変わる
			send88kb_push(0x0c, 4, b); // F10
			send88kb_push(0x08, 6, b); // SHIFT
			send88kb_push(0x09, 5, b); // F5
		} else {
			send88kb_push(0x0c, 4, b); // F10
			send88kb_push(0x09, 5, b); // F5
			send88kb_push(0x08, 6, b); // SHIFT
		}
	} else {
		send88kb_push(0x09, 5, b); // F5
	}
}

void keysw_96(bool b) {
	send88kb_push(0x09, 6, b); // SPACE
}

void keysw_97(bool b) {
	if (KBBIT_KANA()) {
		CAPS_TOGGLE = !CAPS_TOGGLE;
		send88kb_push(0x0a, 7, CAPS_TOGGLE); // CAPS
	} else {
		send88kb_push(0x09, 7, b); // ESC
	}
}

// --------

void keysw_A0(bool b) {
	send88kb_push(0x0a, 0, b); // TAB
}

void keysw_A1(bool b) {
	send88kb_push(0x0a, 1, b); // DOWN
}

void keysw_A2(bool b) {
	send88kb_push(0x0a, 2, b); // LEFT
}

void keysw_A3(bool b) {
	send88kb_push(0x0a, 3, b); // HELP
}

void keysw_A4(bool b) {
	send88kb_push(0x0a, 4, b); // COPY
}

void keysw_A5(bool b) {
	send88kb_push(0x0a, 5, b); // NUM -
}

void keysw_A6(bool b) {
	send88kb_push(0x0a, 6, b); // NUM /
}

void keysw_A7(bool b) {
	send88kb_push(0x0a, 7, b); // CAPS
}

// --------

void keysw_B0(bool b) {
	send88kb_push(0x0b, 0, b); // ROLLUP
}

void keysw_B1(bool b) {
	send88kb_push(0x0b, 1, b); // ROLLDOWN
}

void keysw_B2(bool b) {
	send88kb_push(0x0b, 2, b); // (B2)
}

void keysw_B3(bool b) {
	send88kb_push(0x0b, 3, b); // (B3)
}

void keysw_B4(bool b) {
	send88kb_push(0x0b, 4, b); // (B4)
}

void keysw_B5(bool b) {
	send88kb_push(0x0b, 5, b); // (B5)
}

void keysw_B6(bool b) {
	send88kb_push(0x0b, 6, b); // (B6)
}

void keysw_B7(bool b) {
	send88kb_push(0x0b, 7, b); // (B7)
}

// --------

void keysw_C0(bool b) {
	send88kb_push(0x0c, 0, b); // F6
}

void keysw_C1(bool b) {
	send88kb_push(0x0c, 1, b); // F7
}

void keysw_C2(bool b) {
	send88kb_push(0x0c, 2, b); // F8
}

void keysw_C3(bool b) {
	send88kb_push(0x0c, 3, b); // F9
}

void keysw_C4(bool b) {
	send88kb_push(0x0c, 4, b); // F10
}

void keysw_C5(bool b) {
	send88kb_push(0x0c, 5, b); // BS
}

void keysw_C6(bool b) {
	send88kb_push(0x0c, 6, b); // INS
}

void keysw_C7(bool b) {
	send88kb_push(0x0c, 7, b); // DEL
}

// --------

void keysw_D0(bool b) {
	send88kb_push(0x0d, 0, b); // 変換
}

void keysw_D1(bool b) {
	send88kb_push(0x0d, 1, b); // 決定
}

void keysw_D2(bool b) {
	send88kb_push(0x0d, 2, b); // PC
}

void keysw_D3(bool b) {
	send88kb_push(0x0d, 3, b); // 全角
}

void keysw_D4(bool b) {
	send88kb_push(0x0d, 4, b); // (D4)
}

void keysw_D5(bool b) {
	send88kb_push(0x0d, 5, b); // (D5)
}

void keysw_D6(bool b) {
	send88kb_push(0x0d, 6, b); // (D6)
}

void keysw_D7(bool b) {
	send88kb_push(0x0d, 7, b); // (D7)
}

// --------

void keysw_E0(bool b) {
	send88kb_push(0x0e, 0, b); // RETURN
}

void keysw_E1(bool b) {
	send88kb_push(0x0e, 1, b); // NUM RET
}

void keysw_E2(bool b) {
	send88kb_push(0x0e, 2, b); // LSHIFT
}

void keysw_E3(bool b) {
	send88kb_push(0x0e, 3, b); // RSHIFT
}

void keysw_E4(bool b) {
	send88kb_push(0x0e, 4, b); // (E4)
}

void keysw_E5(bool b) {
	send88kb_push(0x0e, 5, b); // (E5)
}

void keysw_E6(bool b) {
	send88kb_push(0x0e, 6, b); // (E6)
}

void keysw_E7(bool b) {
	send88kb_push(0x0e, 7, b); // (E7)
}

// --------

void keysw_F0(bool b) {
	send88kb_push(0x0f, 0, b); // (F0)
}

void keysw_F1(bool b) {
	send88kb_push(0x0f, 1, b); // (F1)
}

void keysw_F2(bool b) {
	send88kb_push(0x0f, 2, b); // (F2)
}

void keysw_F3(bool b) {
	send88kb_push(0x0f, 3, b); // (F3)
}

void keysw_F4(bool b) {
	send88kb_push(0x0f, 4, b); // (F4)
}

void keysw_F5(bool b) {
	send88kb_push(0x0f, 5, b); // (F5)
}

void keysw_F6(bool b) {
	send88kb_push(0x0f, 6, b); // (F6)
}

void keysw_F7(bool b) {
	send88kb_push(0x0f, 7, b); // (F7)
}

// =====================================================================

// キースイッチ
const KEYSW* KEYSWTBL[KB_ADR_MAX*KB_DATA_SIZE] = {
	&keysw_00, &keysw_01, &keysw_02, &keysw_03, &keysw_04, &keysw_05, &keysw_06, &keysw_07,
	&keysw_10, &keysw_11, &keysw_12, &keysw_13, &keysw_14, &keysw_15, &keysw_16, &keysw_17,
	&keysw_20, &keysw_21, &keysw_22, &keysw_23, &keysw_24, &keysw_25, &keysw_26, &keysw_27,
	&keysw_30, &keysw_31, &keysw_32, &keysw_33, &keysw_34, &keysw_35, &keysw_36, &keysw_37,
	&keysw_40, &keysw_41, &keysw_42, &keysw_43, &keysw_44, &keysw_45, &keysw_46, &keysw_47,
	&keysw_50, &keysw_51, &keysw_52, &keysw_53, &keysw_54, &keysw_55, &keysw_56, &keysw_57,
	&keysw_60, &keysw_61, &keysw_62, &keysw_63, &keysw_64, &keysw_65, &keysw_66, &keysw_67,
	&keysw_70, &keysw_71, &keysw_72, &keysw_73, &keysw_74, &keysw_75, &keysw_76, &keysw_77,
	&keysw_80, &keysw_81, &keysw_82, &keysw_83, &keysw_84, &keysw_85, &keysw_86, &keysw_87,
	&keysw_90, &keysw_91, &keysw_92, &keysw_93, &keysw_94, &keysw_95, &keysw_96, &keysw_97,
	&keysw_A0, &keysw_A1, &keysw_A2, &keysw_A3, &keysw_A4, &keysw_A5, &keysw_A6, &keysw_A7,
	&keysw_B0, &keysw_B1, &keysw_B2, &keysw_B3, &keysw_B4, &keysw_B5, &keysw_B6, &keysw_B7,
	&keysw_C0, &keysw_C1, &keysw_C2, &keysw_C3, &keysw_C4, &keysw_C5, &keysw_C6, &keysw_C7,
	&keysw_D0, &keysw_D1, &keysw_D2, &keysw_D3, &keysw_D4, &keysw_D5, &keysw_D6, &keysw_D7,
	&keysw_E0, &keysw_E1, &keysw_E2, &keysw_E3, &keysw_E4, &keysw_E5, &keysw_E6, &keysw_E7,
	&keysw_F0, &keysw_F1, &keysw_F2, &keysw_F3, &keysw_F4, &keysw_F5, &keysw_F6, &keysw_F7,
};

// =====================================================================
// [EOF]
