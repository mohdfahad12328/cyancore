/*
 * CYANCORE LICENSE
 * Copyrights (C) 2024, Cyancore Team
 *
 * File Name		: math.h
 * Description		: This file contains prototypes of math function
 *			  It is same as the one in toolchain but tailored
 *			  for cyancore
 * Primary Author	: Akash Kollipara [akashkollipara@gmail.com]
 * Organisation		: Cyancore Core-Team
 */

#pragma once
#include <status.h>

#define M_E		2.7182818284590452354
#define M_LOG2E		1.4426950408889634074	/* log_2 e */
#define M_LOG10E	0.43429448190325182765	/* log_10 e */
#define M_LN2		0.69314718055994530942	/* log_e 2 */
#define M_LN10		2.30258509299404568402	/* log_e 10 */
#define M_PI		3.14159265358979323846	/* pi */
#define M_PI_2		1.57079632679489661923	/* pi/2 */
#define M_PI_4		0.78539816339744830962	/* pi/4 */
#define M_1_PI		0.31830988618379067154	/* 1/pi */
#define M_2_PI		0.63661977236758134308	/* 2/pi */
#define M_2_SQRTPI	1.12837916709551257390	/* 2/sqrt(pi) */
#define M_SQRT2		1.41421356237309504880	/* sqrt(2) */
#define M_SQRT1_2	0.70710678118654752440	/* 1/sqrt(2) */
#define NAN		__builtin_nan("")
#define INFINITY	__builtin_inf()

#ifdef __cplusplus
EXPORT_C_PROTO(
#endif

extern double cos(double);
#define cosf		cos

extern double sin(double);
#define sinf		sin

extern double tan(double);
#define tanf		tan

extern double fabs(double);
#define fabsf		fabs

extern double fmod(double, double);
#define fmodf		fmod

extern double modf(double, double *);

extern float modff (float, float *);

extern double sqrt(double);

extern float sqrtf (float);

extern double cbrt(double);
#define cbrtf		cbrt

extern double hypot (double, double);
#define hypotf		hypot

extern double square(double);
#define squaref		square

extern double floor(double);
#define floorf		floor

extern double ceil(double);
#define ceilf		ceil

extern double frexp(double, int *);
#define frexpf		frexp

extern double ldexp(double, int);
#define ldexpf		ldexp

extern double exp(double);
#define expf		exp

extern double cosh(double);
#define coshf		cosh

extern double sinh(double);
#define sinhf		sinh

extern double tanh(double);
#define tanhf		tanh

extern double acos(double);
#define acosf		acos

extern double asin(double);
#define asinf		asin

extern double atan(double);
#define atanf		atan

extern double atan2(double, double);
#define atan2f		atan2

extern double log(double);
#define logf		log

extern double log10(double);
#define log10f		log10

extern double pow(double, double);
#define powf		pow

extern int isnan(double);
#define	isnanf		isnan

extern int isinf(double);
#define isinff		isinf

extern int signbit (double);
#define signbitf	signbit

extern double fdim (double, double);
#define fdimf		fdim

extern double fma (double, double, double);
#define fmaf		fma

extern double fmax (double, double);
#define fmaxf		fmax

extern double fmin (double, double);
#define fminf		fmin

extern double trunc (double);
#define truncf		trunc

extern double round (double);
#define roundf		round

extern long lround (double);
#define lroundf		lround

extern long lrint (double);
#define lrintf		lrint

#ifdef __cplusplus
)
#endif
