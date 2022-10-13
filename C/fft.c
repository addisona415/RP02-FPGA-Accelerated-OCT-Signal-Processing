#include <stdio.h>
#include <math.h>
#include <complex.h>

// Implementation found from https://rosettacode.org/wiki/Fast_Fourier_transform#C
// Further attempts will be made using the Cooley-Turkey FFT algorithm
// This is an in place implementation of the FFT

double PI;
typedef double complex cplx;

void _fft(cplx buff[], cplx out[], int n, int step)
{
    if (step < n)
    {
        _fft(out, buff, n, step * 2);
        _fft(out + step, buff + step, n, step * 2);

        for (int i = 0; i < n; i += 2 * step)
        {
            cplx t = cexp(-I * PI * i / n) * out[i + step];
            buff[i / 2] = out[i] + t;
            buff[(i + n) / 2] = out[i] - t;
        }
    }
}

void fft(cplx buff[], int n)
{
    cplx out[n];
    for (int i = 0; i < n; i++)
        out[i] = buff[i];

    _fft(buff, out, n, 1);
}

void printRealOrImaginary(const char *s, cplx buff[])
{
    printf("%s", s);
    for (int i = 0; i < 8; i++)
    {
        if (!cimag(buff[i]))
        {
            printf("%g, ", creal(buff[i]));
        }
        else
            printf("%g, %g, ", creal(buff[i]), cimag(buff[i]));
    }
}

int main()
{
    PI = atan2(1, 1) * 4;
    cplx buff[] = {1, 1, 1, 1, 0, 0, 0, 0};

    printRealOrImaginary("Input: ", buff);
    fft(buff, 8);
    printRealOrImaginary("\nFFT: ", buff);

    return 0;
}