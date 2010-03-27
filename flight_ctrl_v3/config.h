#ifndef config_h
#define config_h

#include <stdint.h>

#define MATH_MULTIPLIER 1000
#define MATH_MULTI MATH_MULTIPLIER

#define use_atan
//#define use_asin
#define use_comp_filter
//#define use_kalman_filter
#define use_ordered_sensors

#define ticks_500us ((F_CPU * 5) / 10000)
#define ticks_10ms (ticks_500us * 20)

#define gyro_to_rad_per_sec 1
#define accel_gyro_w_ratio 0.2
#define frame_delta_time 0.01

#define ppm_highest_chan_default 6

#define sens_hist_len_max 8
#define sens_hist_len_default 8

#endif