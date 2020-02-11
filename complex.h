class complex_number {
    public:
        long double real;
        long double im;
        complex_number(long double real_a, long double im_a);  // This is the constructor
        complex_number operator+(const complex_number& target);
        complex_number operator-(const complex_number& target);
        complex_number sqr();

};

