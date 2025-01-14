// -------------------------------------------------- //
// This file is autogenerated by pioasm; do not edit! //
// -------------------------------------------------- //

#pragma once

#if !PICO_NO_HARDWARE
#include "hardware/pio.h"
#endif

// ------ //
// pio_tx //
// ------ //

#define pio_tx_wrap_target 0
#define pio_tx_wrap 3

#define pio_tx_TX_DATA_BITS 12

static const uint16_t pio_tx_program_instructions[] = {
            //     .wrap_target
    0x9fa0, //  0: pull   block           side 1 [7] 
    0xf72c, //  1: set    x, 12           side 0 [7] 
    0x6001, //  2: out    pins, 1                    
    0x0642, //  3: jmp    x--, 2                 [6] 
            //     .wrap
};

#if !PICO_NO_HARDWARE
static const struct pio_program pio_tx_program = {
    .instructions = pio_tx_program_instructions,
    .length = 4,
    .origin = -1,
};

static inline pio_sm_config pio_tx_program_get_default_config(uint offset) {
    pio_sm_config c = pio_get_default_sm_config();
    sm_config_set_wrap(&c, offset + pio_tx_wrap_target, offset + pio_tx_wrap);
    sm_config_set_sideset(&c, 2, true, false);
    return c;
}

// pioasm.exe or https://wokwi.com/tools/pioasm to convert it.
#include "hardware/clocks.h"
#define OUT_PIN 4
#define OUT_BITS pio_tx_TX_DATA_BITS
static inline void pio_tx_program_init(PIO pio, uint sm, uint offset, uint out_pin, float tx_baud) {
	// ステートマシンのデフォルト設定を取得
	pio_sm_config c = pio_tx_program_get_default_config(offset);
	// OUT命令用GPIOピンを設定
	sm_config_set_out_pins(&c, out_pin, 1);
	// SIDESET命令用GPIOピンを設定
	sm_config_set_sideset_pins(&c, out_pin);
	// GPIOをPIOに割り当てる(out_pin)
	pio_gpio_init(pio, out_pin);
	// PIOに設定したGPIOの向きを設定（true=out, false=in）
	pio_sm_set_consecutive_pindirs(pio, sm, out_pin, 1, true);
	// ステートマシンのビットシフト関連の設定
	sm_config_set_out_shift(
		&c,
		true,		// LSB first
		true,		  // 
		OUT_BITS+1	// パリティ入りビット数
	);
	// FIFOを送信専用に設定
	sm_config_set_fifo_join(&c, PIO_FIFO_JOIN_TX);
	// ステートマシンの１クロックの設定
	float div =  (float)clock_get_hz(clk_sys) / (8 * tx_baud);
	sm_config_set_clkdiv(&c, div);
	// ステートマシンを所定の設定で初期化
	pio_sm_init(pio, sm, offset, &c);
	// ステートマシンを稼働
	pio_sm_set_enabled(pio, sm, true);
}
static void pio_tx(PIO pio, uint sm, uint c, bool even_parity) {
	uint32_t tx = c;
	uint32_t b = 1;
	uint32_t parity = (even_parity ? 0 : 1);
	for (int i = 0; i < OUT_BITS; i++) {
		parity ^= (tx & b);
		b <<= 1;
		parity <<= 1;
	}
	tx |= parity;
	LOG_I("Send=%04X\n", tx);
	pio_sm_put_blocking(pio, sm, tx);
}

#endif
