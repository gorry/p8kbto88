// ◇ PC-8801キーボードデータ線へ送信する処理
// Copyright 2024 GORRY.
// =====================================================================

// pio-txで使う値
#define PIO_TX_PIO pio0
#define PIO_TX_STATE_MACHINE 0
#define PIO_TX_OUT_PIN 4
#define PIO_TX_BAUD 20800

// =====================================================================

// キーボード入力イベントを溜めておくバッファ
#define KB_EVT_BUF_MAX 256
typedef struct {
	int adr;
	int kbbit;
	bool b;
} KB_EVT;
KB_EVT KB_EVT_BUF[KB_EVT_BUF_MAX];
int KB_EVT_BUF_HEAD;
int KB_EVT_BUF_TAIL;

unsigned char KB_OUT[KB_ADR_MAX];

// =====================================================================

// 初期化
void send88kb_init(void) {
	// pio-tx初期化
	pio_tx_program_init(
		PIO_TX_PIO,
		PIO_TX_STATE_MACHINE,
		pio_add_program(pio0, &pio_tx_program),
		PIO_TX_OUT_PIN,
		PIO_TX_BAUD
	);

	// キーボード入力イベントバッファ初期化
	KB_EVT_BUF_HEAD = 0;
	KB_EVT_BUF_TAIL = 0;
	memset(&KB_OUT, 0xff, KB_ADR_MAX);
	KB_OUT[0x0e] &= 0x7f; // 常に0
}

// =====================================================================

// 貯め込んだキー入力イベントをPC-8801キーボードデータ線へ送信する
void send88kb(void) {
	while (KB_EVT_BUF_TAIL != KB_EVT_BUF_HEAD) {
		KB_EVT* k = &(KB_EVT_BUF[KB_EVT_BUF_TAIL]);
		int adr = k->adr;
		int kbbit = k->kbbit;
		bool b = k->b;
		int keyno = adr*KB_DATA_SIZE+kbbit;
		LOG_I("%02X, %d: [%s] %s\n", adr, kbbit, keyname(keyno), (b ? "make" : "break"));

		if (b) { // 負論理につき
			KB_OUT[adr] &= ~(1<<kbbit);
		} else {
			KB_OUT[adr] |= (1<<kbbit);
		}

		// pio-tx送信
		int c = (KB_OUT[adr]<<4) | (adr<<0);
		pio_tx(PIO_TX_PIO, PIO_TX_STATE_MACHINE, c, true);

		KB_EVT_BUF_TAIL = (KB_EVT_BUF_TAIL+1) & (KB_EVT_BUF_MAX-1);
	}
}

// =====================================================================

// キー入力イベントを貯め込む
void send88kb_push(int adr, int kbbit, bool b) {
	int keyno = adr*KB_DATA_SIZE+kbbit;
	LOG_I("%02X, %d: [%s] %s\n", adr, kbbit, keyname(keyno), (b ? "on" : "off"));

	KB_EVT_BUF[KB_EVT_BUF_HEAD] = {adr, kbbit, b};
	KB_EVT_BUF_HEAD = (KB_EVT_BUF_HEAD+1) & (KB_EVT_BUF_MAX-1);
}

// =====================================================================
// [EOF]
