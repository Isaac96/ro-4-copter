#include "sensor.h"

#include <math.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>

#include "config.h"
#include "pindef.h"
#include "macros.h"

#include "calc.h"

static volatile uint16_t adc_res_t[8];
static volatile uint16_t adc_res[8];
static volatile uint16_t adc_offset[8];
static volatile uint8_t adc_chan;
static volatile uint8_t adc_new_cycle;

#ifdef use_ordered_sensors
static uint8_t adc_chan_order[6];
#endif

ISR(ADC_vect)
{
	adc_res_t[adc_chan] = ADC; // read
	adc_chan++; // next channel
	adc_chan %= 6; // overflow channel count
	
	#ifdef use_ordered_sensors
	ADMUX = (ADMUX & 0b11100000) | adc_chan_order[adc_chan]; // set channel
	#else
	ADMUX = (ADMUX & 0b11100000) | adc_chan; // set channel
	#endif
	
	ADCSRA = _BV(ADEN) | _BV(ADSC) | _BV(ADIE) | _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0); // start read
	if(adc_chan == 0)
	{
		// copy to second array while interrupts are disabled
		memcpy(adc_res, adc_res_t, sizeof(uint16_t) * 8);
		adc_new_cycle++;
	}
}

// start ADC module on channel c, f is for other flags (such as ADIE)
void adc_start(uint8_t c, uint8_t f)
{
	ADMUX = (ADMUX & 0b11100000) | c;
	ADCSRA = _BV(ADEN) | _BV(ADSC) | _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0) | f;
}

// stop the ADC module from taking samples
void adc_wait_stop()
{
	cbi(ADCSRA, ADIE);
	while (bit_is_set(ADCSRA, ADSC));
}

// initialize the sensor module and start the ADC
void sens_init()
{
	#ifdef use_ordered_sensors
	// set channel read order
	adc_chan_order[0] = roll_accel_chan;
	adc_chan_order[1] = roll_gyro_chan;
	adc_chan_order[2] = pitch_accel_chan;
	adc_chan_order[3] = pitch_gyro_chan;
	adc_chan_order[4] = vert_accel_chan;
	adc_chan_order[5] = yaw_gyro_chan;
	#endif
	
	// reset all values
	for(uint8_t i = 0; i < 8; i++)
	{
		adc_offset[i] = 0;
	}

	adc_chan = 0;
	adc_new_cycle = 0;

	adc_start(0, _BV(ADIE));
}

// read the 10 bit ADC reading of a channel
volatile inline uint16_t sens_read(uint8_t i)
{
	return adc_res[i];
}

// read the calibration results of a channel
volatile inline uint16_t sens_offset(uint8_t i)
{
	return adc_offset[i];
}

// find the center values of all channels using t number of samples
void sens_calibrate(uint8_t t)
{
	uint32_t sum[8] = {0,0,0,0,0,0,0,0};

	adc_wait_stop();
	for(uint8_t i = 0; i < t; i++)
	{
		for(uint8_t j = 0; j < 8; j++)
		{
			adc_start(j, 0);
			while (bit_is_set(ADCSRA, ADSC));
			sum[j] += ADC;
		}
	}
	for(uint8_t j = 0; j < 8; j++)
	{
		adc_offset[j] = calc_multi(sum[j], 1, t);
	}
	
	adc_start(0, _BV(ADIE));
}

// returns the number of ADC samples that have been collected, clear the counter by setting c to 0, or else use 0xFF for c
volatile inline uint8_t adc_rounds_cnt(uint8_t c)
{
	adc_new_cycle &= c;
	return adc_new_cycle;
}