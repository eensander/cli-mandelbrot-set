#include "complex.h"


complex_number::complex_number(long double real_a, long double im_a)
{
    //cout << "Created complex number with " << real_a << " and " << im_a << "\t " << real_a << "+" << im_a << "i"  << endl;
    real = real_a;
    im = im_a;
}


complex_number complex_number::operator+(const complex_number& target)
{
    long double result_real = real + target.real;
    long double result_im = im + target.im ;
    return complex_number( result_real, result_im );
}
complex_number complex_number::operator-(const complex_number& target)
{
    long double result_real = real - target.real;
    long double result_im = im - target.im;
    return complex_number( result_real, result_im );
}

complex_number complex_number::sqr()
{
    long double result_real = (real * real) - (im * im);
    long double result_im = 2 * real * im;
    return complex_number( result_real, result_im );
}
