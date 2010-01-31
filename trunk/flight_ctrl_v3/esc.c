#include <avr/io.h>
#include <avr/interrupt.h>

#include "esc.h"

#include "config.h"
#include "pindef.h"
#include "macros.h"

#include "timer.h"

static volatile unsigned short esc_chan_width[8];
static volatile unsigned char esc_chan;
static volatile signed long esc_elapsed;
static volatile unsigned char esc_done;
static volatile unsigned char esc_safety;
static volatile unsigned char esc_extra_servo;

ISR(TIMER1_COMPA_vect)
{
	sbi(TCCR1C, FOC1A);

	OCR1A += esc_chan_width[esc_chan]; // calculate next alarm considering overflow
	esc_elapsed += esc_chan_width[esc_chan];

	esc_chan++;

	if(esc_chan == 4 + esc_extra_servo)
	{
		if(esc_elapsed > ticks_10ms)
		{
			esc_done = 1;
		}
		else
		{
			esc_chan--;
		}
	}
}

void esc_init()
{
	// set default
	for(unsigned char i = 0; i < 8; i++)
	{
		esc_chan_width[i] = ticks_500us;
	}

	// be safe
	esc_safety = 1;

	// initialize port
	cbi(esc_port, esc_rst_pin);
	cbi(esc_port, esc_clk_pin);
	cbi(esc_port, esc_dat_pin);
	sbi(esc_ddr, esc_rst_pin);
	sbi(esc_ddr, esc_clk_pin);
	sbi(esc_ddr, esc_dat_pin);

	// prepare shift register
	esc_start_next();

	timer1_init();

	// start timer output module
	sbi(TCCR1A, COM1A0);
	sbi(TIMSK1, OCIE1A);
}

void esc_shift_rst()
{
	// reset the shift register
	cbi(esc_port, esc_rst_pin);
	nop(); nop(); nop(); nop(); // small delay
	nop(); nop(); nop(); nop();
	nop(); nop(); nop(); nop();
	nop(); nop(); nop(); nop();

	// if armed, then unlock shift register
	if(esc_safety == 0)
	{
		sbi(esc_port, esc_rst_pin);
	}

	// place a bit into the first bit location to prepare
	
	cbi(esc_port, esc_clk_pin);

	sbi(esc_port, esc_dat_pin);

	sbi(TCCR1C, FOC1A);
	nop(); nop(); nop(); nop();
	nop(); nop(); nop(); nop();
	nop(); nop(); nop(); nop();
	nop(); nop(); nop(); nop();
	sbi(TCCR1C, FOC1A);

	cbi(esc_port, esc_dat_pin);
}

void esc_start_next()
{
	OCR1A = TCNT1 + 128;

	esc_chan = 0;
	esc_done = 0;
	esc_elapsed = 0;

	esc_shift_rst();
}

inline unsigned char esc_is_done()
{
	return esc_done;
}

inline void esc_is_done_clear()
{
	esc_done = 0;
}

inline void esc_safe(unsigned char c)
{
	esc_safety = c;
}

void esc_set_width(unsigned char c, unsigned short w)
{
	if(w < ticks_500us * 2)
	{
		w = ticks_500us * 2;
	}
	else if(w > ticks_500us * 4)
	{
		w = ticks_500us * 4;
	}
	
	esc_chan_width[c] = w;
}

unsigned long esc_get_total()
{
	unsigned long sum = 0;
	for(unsigned char i = 0; i < 4 + esc_extra_servo; i++)
	{
		sum += esc_chan_width[i];
	}
	return sum;
}

inline void esc_set_extra_chan(unsigned char n)
{
	esc_extra_servo = n;
}