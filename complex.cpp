#include <iostream>
#include <cmath>
using namespace std;

class Complex
{
    double re = 0;
    double im = 0;
    public:
    Complex() {re = 0; im = 0;}
    Complex(Complex&);
    void Input();
    void Output();
    double Mod();
    double& Re() {return re;}
    double& Im() {return im;}
    Complex& operator +(Complex&);
    Complex& operator -(Complex&);
    Complex& operator *(Complex&);   
};

Complex& Complex:: operator *(Complex& c)
{
    double _re = re;
    re = re*c.Re() - im*c.Im();
    im = _re*c.Im() + im*c.Re();
    return *this;
}

Complex:: Complex(Complex& c) 
{
    re = c.Re();
    im = c.Im();
}

Complex& Complex:: operator +(Complex& c)
{
    re += c.Re();
    im += c.Im();
return *this;
}

Complex& Complex:: operator -(Complex& c)
{
    re -= c.Re();
    im -= c.Im();
return *this;
}

inline void Complex:: Input()
{
    cout<<"input re, mi: ";
    cin>>re>>im;
}

inline double Complex:: Mod()
{
    return sqrt(re*re + im*im);
}

inline void Complex:: Output()
{
    cout<<re;
    if (im > 0) 
    {
        cout<<"+";
    }
    cout<<im<<'i';
}

int main()
{
    Complex c1, c2;
    c1.Input();
    c2.Input();

    Complex c3(c1);
    printf("c1 + c2 = ");
    (c3+c2).Output();
    puts("");

    Complex c4(c1);
    printf("c1 - c2 = ");
    (c4-c2).Output();
    puts("");

    Complex c5(c1);
    printf("c1 * c2 = ");
    (c5*c2).Output();
    puts("");

    printf("|c1| %f\n", c1.Mod());

return 0;
}