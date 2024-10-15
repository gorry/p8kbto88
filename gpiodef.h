// ◇ GPIO定義
// Copyright 2024 GORRY.
// =====================================================================

#define KB_ADR_MAX 16

// キーボードアドレスピン（IN）の定義
#define KB_ADR_SIZE 10
const unsigned char GPIO_ADR[KB_ADR_SIZE] = {
	15, // GP13:Adr9
	14, // GP12:Adr8
	13, // GP11:Adr7
	12, // GP10:Adr6
	11, // GP 9:Adr5
	10, // GP 8:Adr4
	 9, // GP 7:Adr3
	 8, // GP 6:Adr2
	 7, // GP 3:Adr1
	 6, // GP 2:Adr0
};

// キーボードデータピン（OUT）の定義
#define KB_DATA_SIZE 8
const unsigned char GPIO_DATA[8] = {
	16, // GP16:Data0
	17, // GP17:Data1
	18, // GP18:Data2
	19, // GP19:Data3
	20, // GP20:Data4
	21, // GP21:Data5
	22, // GP22:Data6
	26, // GP26:Data7
};

// =====================================================================
// [EOF]
