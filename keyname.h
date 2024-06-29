// ◇ キー名定義
// Copyright 2024 GORRY.
// =====================================================================

const char* KEY_NAME[KB_ADR_MAX*KB_DATA_SIZE] = {
	// 00
	"NUM 0",
	"NUM 1",
	"NUM 2",
	"NUM 3",
	"NUM 4",
	"NUM 5",
	"NUM 6",
	"NUM 7",

	// 01
	"NUM 8",
	"NUM 9",
	"NUM *",
	"NUM +",
	"NUM =",
	"NUM ,",
	"NUM .",
	"NUM RET",

	// 02
	"@",
	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"G",

	// 03
	"H",
	"I",
	"J",
	"K",
	"L",
	"M",
	"N",
	"O",

	// 04
	"P",
	"Q",
	"R",
	"S",
	"T",
	"U",
	"V",
	"W",

	// 05
	"X",
	"Y",
	"Z",
	"[",
	"\\",
	"]",
	"^",
	"-",

	// 06
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",

	// 07
	"8",
	"9",
	":",
	";",
	",",
	".",
	"/",
	"_",

	// 08
	"HOME/CLR",
	"UP",
	"RIGHT",
	"INS/DEL",
	"GRPH",
	"KANA",
	"SHIFT",
	"CTRL",

	// 09
	"STOP",
	"F1",
	"F2",
	"F3",
	"F4",
	"F5",
	"SPACE",
	"ESC",

	// 0A
	"TAB",
	"DOWN",
	"LEFT",
	"HELP",
	"COPY",
	"NUM -",
	"NUM /",
	"CAPS",

	// 0B
	"ROLLUP",
	"ROLLDOWN",
	"(B2)",
	"(B3)",
	"(B4)",
	"(B5)",
	"(B6)",
	"(B7)",

	// 0C
	"F6",
	"F7",
	"F8",
	"F9",
	"F10",
	"BS",
	"INS",
	"DEL",

	// 0D
	"変換",
	"決定",
	"PC",
	"全角",
	"(D4)",
	"(D5)",
	"(D6)",
	"(D7)",

	// 0E
	"RETURN",
	"NUM RET",
	"LSHIFT",
	"RSHIFT",
	"(E4)",
	"(E5)",
	"(E6)",
	"(E7)",

	// 0F
	"(F0)",
	"(F1)",
	"(F2)",
	"(F3)",
	"(F4)",
	"(F5)",
	"(F6)",
	"(F7)",

};

const char* keyname(int no) {
	return KEY_NAME[no];
}

// =====================================================================
// [EOF]
