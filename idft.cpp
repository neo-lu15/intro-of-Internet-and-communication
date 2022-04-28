#include <iostream>
#include <cmath>
#include <iostream>
#include <complex>
#include <time.h>
#define N 1024
using namespace std;
complex<double> v[N][N];
int main()
{
    int count = 0;
    double start, end;
    double t = 0;
    srand(time(NULL));
    
    for (int i = 0; i < N; ++i)
    {
        v[i][0].real(1);
        v[0][i].real(1);
    }
    for (int i = 1; i < N; ++i)
    {
        for (int j = 1; j < N; ++j)
        {
            v[i][j].real((cos(i * j * 2 * M_PI / N)));
            v[i][j].imag(sin(i * j * 2 * M_PI / N));
            // cout<<v[i][j].real()<<v[i][j].imag()<<endl;
        }
    }
    // for (int i = 0; i < N; ++i)
    // {
    //     for (int j = 0; j < N; ++j)
    //     {
    //         cout << v[i][j].real() << " " << v[i][j].imag() << endl;
    //     }
    // }
    //cout << "--------------------------------------------------------------------" << endl;
    while (t < 60)
    {
        complex<double> arr[N];
        for (int i = 0; i < N; ++i)
        {
            arr[i].real((double)rand()/RAND_MAX);
            arr[i].imag((double)rand()/(RAND_MAX));
        }
        complex<double> srr[N];
        for (int i = 0; i < N; ++i)
        {
            srr[i].real(0);
            srr[i].imag(0);
        }
        start = clock();
        for (int i = 0; i < N; ++i)
        {
            double im = 0;
            double re = 0;
            for (int j = 0; j < N; ++j)
            {
                im += v[i][j].real() * arr[j].imag() + arr[j].real() * v[i][j].imag();
                re += v[i][j].real() * arr[j].real() - v[i][j].imag() * arr[j].imag();
            }
            srr[i].imag(im);
            srr[i].real(re);
            //cout << srr[i].real() << " " << srr[i].imag() << endl;
        }

        end = clock();

        t += (double)(end - start) / (double)CLOCKS_PER_SEC;
        ++count;
        //cout << t <<endl;
    }
    cout << count;
    return 0;
}