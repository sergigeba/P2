#include <math.h>
#include "pav_analysis.h"

float compute_power(const float *x, unsigned int N) {
    if (N == 0) return NAN;
    double suma = 0.0;
    for (unsigned int n = 0; n < N; ++n) suma += (double)x[n] * x[n];
    /* El silenci digital té potència nul·la: -infinit dB. */
    return suma > 0.0 ? (float)(10.0 * log10(suma / N)) : -INFINITY;
}

float compute_am(const float *x, unsigned int N) {
    if (N == 0) return NAN;
    double suma = 0.0;
    for (unsigned int n = 0; n < N; ++n) suma += fabsf(x[n]);
    return (float)(suma / N);
}

float compute_zcr(const float *x, unsigned int N, float fm) {
    if (N < 2) return 0.0f;
    unsigned int cruces = 0;
    /* Conveni binari: el zero pertany al signe positiu. */
    for (unsigned int n = 1; n < N; ++n)
        if ((x[n] < 0.0f) != (x[n - 1] < 0.0f)) ++cruces;
    return (fm / 2.0f) * ((float)cruces / (float)(N - 1));
}
