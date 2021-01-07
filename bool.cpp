#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

// Класс булев вектор 
class Boolv {   
    unsigned int *b; 
    int nbit, m; 	 	// nbit – количество бит вектора, m – количество элементов массива b

    public: 
    Boolv (int nn = 1); 	 	// формируется булев вектор из nn бит; все биты со значениями 0 
    Boolv (const char*);        // формируется булев вектор по строке из нулей и единиц     
    Boolv (Boolv &);  
    ~Boolv () {if (b != NULL) delete b; b = NULL;};
    void Set1 (int); 	 	// устанавливает указанный бит в 1      
    void Set0 (int); 	 	// устанавливает указанный бит в 0      
    unsigned int operator[] (int); 
    Boolv operator = (Boolv);
    Boolv exp_boolv (int);
    int Len_boolv ();   
    Boolv operator | (Boolv &); 
    Boolv operator & (Boolv &); 
    Boolv operator ~ ();
    friend ostream& operator << (ostream &o, Boolv &b)
    {
        int j = -1;
        for (int i = 0; i < b.nbit; i++)	    
        {	    
            if (i % 32 == 0)	        
            {	       
                j++;	            
            }
            o << (char)(((unsigned int)1 & (b.b[j] >> i%32)) + '0');	        
        }
        o << "\n";
        return o;
    }
    friend istream& operator >> (istream &i, Boolv &b)
    {
        cout << "Ввеите длину вектора: ";
        int len = 0;
        i >> len;
        char *str = new char[len];
        cout << "Ввеите вектор: ";
        i >> str;
        Boolv a(str);
        b = a;
        return i;
    }
};

Boolv:: Boolv (int nn)
{
    nbit = nn;
    m = nbit/32 + (nbit%32 > 0);
    b = new unsigned int [m];
    for (int i = 0; i < m; i++)
    {
        b[i] = 0;
    }
}

Boolv:: Boolv (const char* a)
{
    nbit = strlen(a);
    m = nbit/32 + (nbit%32 > 0);
    b = new unsigned int [m];
    int j = -1;
    for (int i = 0; i < nbit; i++)	    
    {	    
        if (i % 32 == 0)	        
        {	       
            j++;	            
        }	        
        unsigned int c = a[i];
        b[j] |= (unsigned int)((c - '0') << (i%32)); 
    }
}

Boolv:: Boolv (Boolv &a)
{
    nbit = a.nbit; 
    m = a.m;   
    b = new unsigned int [m];  
    for (int i = 0; i < m; i++)
    {
        b[i] = a.b[i];
    } 
}

void Boolv:: Set1 (int a)
{
    if ((a < 0) || (a > nbit))
    {
        return;
    }
    int j = a/32 - (a%32 == 0);
    if (j == -1) j++;
    b[j] |= (unsigned int)1 << a%32;
}

void Boolv:: Set0 (int a)
{
    if ((a < 0) || (a > nbit))
    {
        return;
    }
    int j = a/32 - (a%32 == 0);
    if (j == -1) j++;
    b[j] &= ~(unsigned int)(1 << a%32);
}

unsigned int Boolv:: operator[] (int n)
{
    if ((n <0) || (n >= nbit))
    {
        return -1;
    }
    int j = n/32 - (n%32 == 0);
    if (j == -1) j++;
    return (b[j] >> n%32) & 1;
}

Boolv Boolv:: operator = (Boolv a)
{
    if (&a == this)
    {
        return *this;
    }
    if (m != a.m)
    {
        m = a.m;
        if (b != NULL) delete b;
        b = new unsigned int [m];
    }
    nbit = a.nbit;
    for (int i = 0; i < m; i++)
    {
        b[i] = a.b[i];
    }
    return *this;
}

Boolv Boolv:: exp_boolv (int k)
{
    if(k == 0)
    {
        return *this;
    }

    int nbit_new = nbit + k;
    int m_new = nbit_new/32 + (nbit_new%32 > 0);

    Boolv *a = new Boolv(nbit_new);

    int j = -1;
    for (int i = 0; i < nbit; i++)
    {
        if (i % 32 == 0)	        
        {	       
            j++;	            
        }

        bool c = (b[j] >> i%32) & 1;
        if (c)
        {
            a->Set1(i + k);
        }
        else
        {
            a->Set0(i + k);
        }
    }
    *this = *a;
    delete a;
    return *this;
}

int Boolv:: Len_boolv()
{
    return nbit;
} 

Boolv Boolv:: operator | (Boolv &a)             // 1010 -> 0101
{                                               // 1 -> 0001
    if(nbit < a.Len_boolv())
    {
        exp_boolv(a.Len_boolv() - nbit);
    }
    else
    {
        a.exp_boolv(nbit - a.Len_boolv());
    }

    for (int i = 0; i < m; i++)
    {
        b[i] |= a.b[i];
    } 
    return *this;
}

Boolv Boolv:: operator & (Boolv &a)      //1010 & 1 = 0; 1010 & 11 = 10;
{                                       //0101 & 0001
    if(nbit < a.Len_boolv())
    {
        exp_boolv(a.Len_boolv() - nbit);
    }
    else
    {
        a.exp_boolv(nbit - a.Len_boolv());
    }

    for (int i = 0; i < m; i++)
    {
        b[i] &= a.b[i];
    } 
    return *this;
}

Boolv Boolv:: operator ~ ()
{
    int j = -1;
    for (int i = 0; i < nbit; i++)
    {
        if (i % 32 == 0)	        
        {	       
            j++;	            
        }

        bool c = (b[j] >> i%32) & 1;
        if (c)
        {
            Set0(i);
        }
        else
        {
            Set1(i);
        }
    }
    return *this;
}

// Класс булева матрица 
class BoolM 
{ 
    Boolv *v;  
    int m, n; 	 	// m – количество строк, n – количество столбцов 
    public: 
    BoolM(int k, int l); // формируется нулевая булева матрица размера k*l 
    BoolM(BoolM &); 
    Boolv & operator[] (int q) { return v[q];}   
    BoolM operator = (BoolM &); 
    friend ostream & operator << (ostream &o, BoolM &b)
    {
        for (int i = 0; i < b.m; i++)
        {
            for (int j = 0; j < b.n; j++)
            {
                o << b.v[i][j] << "  ";
            }
            o << "\n";
        }
        return o;
    }
}; 

BoolM:: BoolM(int k, int l)
{                           // Boolv   
                 	 	    // unsigned int *b;    
    m = k;                  // nbit – количество бит вектора   
    n = l;                  // m – количество элементов массива b
    v = new Boolv [k];
    for (int i = 0; i < k; i++)
    {
        Boolv a(l);
        v[i] = a;
    }
}

BoolM:: BoolM(BoolM &q)
{
    m = q.m;
    n = q.n;
    v = new Boolv [m];
    for (int i = 0; i < m; i++)
    {
        v[i] = q.v[i];
    }
}

BoolM BoolM:: operator = (BoolM &q)
{
    if (&q == this)
    {
        return *this;
    }
    if (m != q.m)
    {
        m = q.m;
        v = new Boolv [m];
    }
    n = q.n;
    for (int i = 0; i < m; i++)
    {
        v[i] = q.v[i];
    }
    return *this;
}

void Topsort(BoolM &M, int m, int *a) 	 	// a – результат сортировки; Нет провреки на наличие цикла в графе
{
    Boolv A(m), v0(m), v1(m);
    for (int i = 0; i < m; i++)
    {
        A.Set1(i);
    }
    int q = 0;

    while (q < m)
    {
        for (int i = 0; i < m; i++)
        {
            v1.Set0(i);
        }
        for (int i = 0; i < m; i++)
        {
            if (A[i]) v1 | M[i];
        }
        v0 | v1;
        ~v0;
        for (int i = 0; i < m; i++)
        {
            if (A[i] && v0[i])
            {
                A.Set0(i);
                a[q] = i + 1;
                q++;
            }
        }
    } 
}

int main()
{
    int m;
    ifstream f("graph.txt", ios_base::in);
    if (!f.is_open()) 
    {
        cout << "Файл graph.txt не может быть открыт!\n";
        return 1;
    }
    f >> m;
    BoolM q(m, m);
    while (f)
    {
        int a, b;
        f >> a >> b;
        q[a - 1].Set1(b - 1);
    }
    f.close();

    int *w = new int[m];

    Topsort(q, m, w);

    ofstream result("result.txt", ios_base::trunc);
    if (!result.is_open()) 
    {
        cout << "Файл result.txt не может быть создан!\n";
        return 1;
    }

    for (int i = 0; i < m; i++)
    {
        result << w[i] << " ";
    }
    delete w;

    result.close();
    return 0;
}