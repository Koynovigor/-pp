#include <iostream>
#include <cmath>
using namespace std;

class Complex
{
    double re = 0;
    double im = 0;
    public:
    Complex(double r = 0, double i = 0) {re = r; im = i;}
    Complex(Complex&);
    void Input();
    void Output();
    double Mod();
    double& Re() {return re;}
    double& Im() {return im;}
    Complex& operator +=(Complex&);
    Complex& operator -=(Complex&);
    Complex& operator *=(Complex&);
    Complex operator +(Complex&);
    Complex operator -(Complex&);
    Complex operator *(Complex&);
    int operator ==(Complex&);
    int operator >(Complex&);
    int operator >=(Complex&);
    int operator <(Complex&);
    int operator <=(Complex&);
    friend ostream & operator<<(ostream &r, Complex &c)
    {
        r << c.re;
        if (c.im > 0) 
        {
            r << "+";
        }
        r << c.im <<'i';
        return r;
    }
    friend istream & operator>>(istream &r, Complex &c)
    {
        cout << "input re, mi: ";
        r >> c.re >> c.im;
        return r;
    }   
};


inline int Complex:: operator ==(Complex& a)
{
    if ((re == a.re)&&(im == a.im))
    {
        return 1;
    }
    return 0;   
}

inline int Complex:: operator >(Complex& a)
{
    if (Mod() > a.Mod())
    {
        return 1;
    }
    return 0;   
}

inline int Complex:: operator >=(Complex& a)
{
    if (Mod() >= a.Mod())
    {
        return 1;
    }
    return 0;   
}

inline int Complex:: operator <(Complex& a)
{
    if (Mod() < a.Mod())
    {
        return 1;
    }
    return 0;   
}

inline int Complex:: operator <=(Complex& a)
{
    if (Mod() <= a.Mod())
    {
        return 1;
    }
    return 0;   
}

inline Complex Complex:: operator +(Complex& b)
{
    Complex c;
    c.re = re + b.re;
    c.im = im + b.im;
    return c;
}

inline Complex Complex:: operator -(Complex& b)
{
    Complex c;
    c.re = re - b.re;
    c.im = im - b.im;
    return c;
}

inline Complex Complex:: operator *(Complex& b)
{
    Complex c;
    c.re = re*b.re - im*b.im;
    c.im = re*b.im + im*b.re;    
    return c;
}

inline Complex& Complex:: operator *=(Complex& c)
{
    double _re = re;
    re = re*c.Re() - im*c.Im();
    im = _re*c.Im() + im*c.Re();
    return *this;
}

inline Complex:: Complex(Complex& c) 
{
    re = c.re;
    im = c.im;
}

inline Complex& Complex:: operator +=(Complex& c)
{
    re += c.re;
    im += c.im;
return *this;
}

inline Complex& Complex:: operator -=(Complex& c)
{
    re -= c.re;
    im -= c.im;
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
    (c3+=c2).Output();
    puts("");

    Complex c4(c1);
    printf("c1 - c2 = ");
    (c4-=c2).Output();
    puts("");

    Complex c5(c1);
    printf("c1 * c2 = ");
    (c5*=c2).Output();
    puts("");

    printf("|c1| %f\n", c1.Mod());

    Complex c7, c8;
    cin>>c7>>c8;
    cout<<c7<<"\n"<<c8<<"\n";

return 0;
}