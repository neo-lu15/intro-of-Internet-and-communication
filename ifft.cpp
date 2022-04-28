#include <iostream>
#include <cmath>
#include <iostream>
#include <complex>
#include <time.h>
#define N 1024
using namespace std;
complex<double> v[N][N];
complex<double> arr[N];

void ifft(int n, complex<double> *srr, complex<double> *arr)
{
    complex<double> srr1[N];
    complex<double> srr2[N];
    if (n != 2)
    {
        complex<double> a1[n / 2];
        complex<double> a2[n / 2];
        for (int i = 0; i < n; ++i)
        {
            if (i % 2)
            {
                a1[i / 2] = arr[i];
            }
            else
            {
                a2[i / 2] = arr[i];
            }
        }
        ifft(n / 2, srr1, a1);
        ifft(n / 2, srr2, a2);
        for (int i = 0; i < N; ++i)
        {
            complex<double> omega{cos(2 * M_PI * i / N), sin(2 * M_PI * i / N)};
            srr[i] = srr1[i % (N / 2)] + omega * srr2[i % (N / 2)];
            // cout << srr[i].real() << " " << srr[i].imag() << endl;
        }
    }

    else
    {

        for (int i = 0; i < n; ++i)
        {
            v[i][0].real(1);
            v[0][i].real(1);
        }
        for (int i = 1; i < n; ++i)
        {
            for (int j = 1; j < n; ++j)
            {
                v[i][j].real((cos(i * j * 2 * M_PI / N)));
                v[i][j].imag(sin(i * j * 2 * M_PI / N));
                // cout<<v[i][j].real()<<v[i][j].imag()<<endl;
            }
        }

        for (int i = 0; i < n; ++i)
        {
            double im = 0;
            double re = 0;
            for (int j = 0; j < n; ++j)
            {
                im += v[i][j].real() * arr[j].imag() + arr[j].real() * v[i][j].imag();
                re += v[i][j].real() * arr[j].real() - v[i][j].imag() * arr[j].imag();
            }
            srr[i].imag(im);
            srr[i].real(re);
        }
    }
}

int main()
{
    int count = 0;
    double start, end;
    double t = 0;
    srand(time(NULL));

    // for (int i = 0; i < N; ++i)
    // {
    //     for (int j = 0; j < N; ++j)
    //     {
    //         cout << v[i][j].real() << " " << v[i][j].imag() << endl;
    //     }
    // }
    // cout << "--------------------------------------------------------------------" << endl;
    while (t < 60)
    {

        for (int i = 0; i < N; ++i)
        {
            arr[i].real((double)rand() / RAND_MAX);
            arr[i].imag((double)rand() / (RAND_MAX));
        }
        complex<double> srr[N];

        for (int i = 0; i < N; ++i)
        {
            srr[i].real(0);
            srr[i].imag(0);
        }
        start = clock();
        int n = N;
        ifft(n, srr, arr);
        end = clock();

        t += (double)(end - start) / (double)CLOCKS_PER_SEC;
        ++count;
        // cout << t << endl;
    }
    cout << count;
    return 0;
}