#include <avr/io.h>
#include <avr/pgmspace.h>
#include <math.h>

#include "calc.h"

#include "config.h"
#include "pindef.h"
#include "macros.h"

/*
// function which performs fixed point multiplication, has been replaced with a macro
volatile inline int32_t calc_multi(int32_t in, int32_t numer, int32_t denom)
{
        if(denom == 0)
        {
                if(in * numer > 0)
                {
                        return INT32_MAX;
                }
                else if(in * numer < 0)
                {
                        return INT32_MIN;
                }
                else
                {
                        return 0;
                }
        }
        
        int32_t r = (in * numer) + (denom / 2);
        return r / denom;
}
//*/

#include "trig_tbl.h"

#ifdef use_asin

volatile inline int32_t calc_asin(int32_t opp, int32_t hyp)
{
        // calculate arcsine angle using opposite length and hypotenus length
        // using look up table with the division of opp/hyp as the address
        int32_t addr = calc_multi(opp, asin_multiplier, hyp);
        int32_t r = pgm_read_dword(&(asin_tbl[calc_abs(addr)]));
        return addr < 0 ? -r : r;
}

#endif


#ifdef use_atan

inline int32_t calc_atan2(int32_t y, int32_t x)
{
        // calculate arctan angle using opposite length and adjacent length
        // using look up table with the division of opp/adj as the address
        
        int32_t z = 0;
        if(calc_abs(x) > calc_abs(y))
        {
                z = calc_multi(y, atan_multiplier, x);
        }
        else if(calc_abs(x) < calc_abs(y))
        {
                z = calc_multi(x, atan_multiplier, y);
        }
        else if(x == 0 && y == 0)
        {
                return 0;
        }
        else if(x == y)
        {
                z = atan_multiplier;
        }

        int32_t r_ = pgm_read_dword(&(atan_tbl[calc_abs(z)]));
        int32_t _r = r_;
        int32_t r;

        if(calc_abs(x) < calc_abs(y))
        {
                _r = (90 * MATH_MULTIPLIER) - r_;
        }

        if(x >= 0)
        {
                if(y < 0)
                {
                        _r *= -1;
                }
                r = _r;
        }
        else
        {
                r = y >= 0 ? (180 * MATH_MULTIPLIER) - _r : (-180 * MATH_MULTIPLIER) + _r;
        }

        return r;
        // note that angle is returned in degrees
}

#endif

inline int32_t PID_mv(PID_data * pid, int32_t kp, int32_t ki, int32_t kd, int32_t current, int32_t target)
{
        // proportional, integral, derivative
        // refer to external resources to learn more about this functioln
        
        int32_t err = target - current;

        pid->err_sum = calc_constrain(pid->err_sum + err, -1000000, 1000000);

        int32_t delta_err = err - pid->err_last;

        int32_t mv = err * kp + pid->err_sum * ki + delta_err * kd;

        pid->err_last = err;

        return calc_multi(mv, 1, MATH_MULTIPLIER);
}

inline PID_data PID_init()
{
        // create a PID persistent data structure and reset its values
        PID_data r;
        r.err_sum = 0;
        r.err_last = 0;
        return r;
}

#ifdef use_comp_filter

inline int32_t complementary_filter(int32_t * ang, int32_t accel_ang, int32_t gyro_r, int32_t w, int32_t dt)
{
        int32_t g = calc_multi(gyro_r, dt, MATH_MULTIPLIER);
        *ang = calc_multi
                        (
                                (MATH_MULTIPLIER - w),
                                (*ang + g),
                                MATH_MULTIPLIER
                        ) + calc_multi(w, accel_ang, MATH_MULTIPLIER);
        return *ang;
}

#endif

#ifdef use_kalman_filter

inline double kalman_filter(kalman_data * kd, double gyro_r, double ang, double dt)
{
        // using kalman filtering to calculate angle
        // all double precision calculation, very very slow
        
        kd->x[0] += dt * (gyro_r - kd->x[1]);
        kd->P[0] += (-dt * (kd->P[2] + kd->P[1])) + (dt * kd->Q[0]);
        kd->P[1] -= dt * kd->P[3];
        kd->P[2] -= dt * kd->P[3];
        kd->P[3] += dt * kd->Q[1];

        double y = ang - kd->x[0];
        double S = kd->P[0] + kd->R;
        double K[2] = {kd->P[0] / S, kd->P[2] / S};

        kd->x[0] += K[0] * y;
        kd->x[1] += K[1] * y;

        kd->P[0] -= K[0] * kd->P[0];
        kd->P[1] -= K[0] * kd->P[1];
        kd->P[2] -= K[1] * kd->P[0];
        kd->P[3] -= K[1] * kd->P[1];

        return kd->x[0];
}

void kalman_init(kalman_data * kd, double Q_accel, double Q_gyro, double R_accel)
{
        // initialize a kalman matrix
        
        kd->x[0] = 0;
        kd->x[1] = 0;

        kd->P[0] = 0;
        kd->P[1] = 0;
        kd->P[2] = 0;
        kd->P[3] = 0;

        kd->Q[0] = Q_accel;
        kd->Q[1] = Q_gyro;
        kd->R = R_accel;
}

#endif