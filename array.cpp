#include <iostream>
#include <ctime>
#include <cmath>

using namespace std;

class Array
{
    size_t *a;
    size_t m;

    public:
    // конструктор 1
    // mm – число элементов в массиве
    // t = 1 – неупорядоченный массив
    // t = 2 – массив, упорядоченный по неубыванию
    // t = 3 – массив, упорядоченный по невозрастанию
    // d – диапазон псевдослучайных чисел для неупорядоченного массива (при t = 1)
    Array(size_t mm = 1, int t = 1, int d = 10);

    // конструктор 2: по массиву
    Array(size_t *, size_t);
    Array(Array &);
    ~Array() {if(a != NULL) delete [] a; a = NULL;}
    Array& operator = (Array &);
    size_t &operator [](size_t);

    bool Test(); // проверка на упорядоченность по неубыванию
    bool operator == (Array); // равенство элементов массивов (но не порядка)

    friend istream & operator >> (istream &s, Array &a)
    {
        printf("Введите массив: ");
        for (size_t i = 0; i < a.m; i++)
        {
            s >> a.a[i];
        }
        return s;
    }

    friend ostream & operator << (ostream &s, Array &a)
    {
        s << a.a[0];
        for (size_t i = 1; i < a.m; i++)
        {
            printf(", ");
            s << a.a[i];
        }
        puts(";");
        return s;
    }

    void Shell_sort();
    void Shaker_sort();
    int Quick_sort(size_t, size_t);
    void Heap_sort();
    
};

Array:: Array(size_t mm, int t, int d)
{
    m = mm;
    a = new size_t[m];
    srand(time(0));
    switch (t)
    {
    case 1:
        for (size_t i = 0; i < m; i++)
        {
            a[i] = rand() % d;
        }
        break;
    case 2:
        a[0] = rand() % d;
        for (size_t i = 1; i < m; i++)
        {
            a[i] = a[i - 1] + rand() % d;
        }
        break;
    case 3:
        a[m - 1] = rand() % d;
        for (long long int i = m - 2; i >= 0; i--)
        {
            a[i] = a[i + 1] + rand() % d;
        }
        break;
    }
}

Array:: Array(size_t *mas, size_t n)
{
    m = n;
    a = new size_t[m];
    for (size_t i = 0; i < m; i++)
    {
        a[i] = mas[i];
    }   
}

Array:: Array(Array &b)
{
    m = b.m;
    a = new size_t[m];
    for (size_t i = 0; i < m; i++)
    {
        a[i] = b.a[i];

    }
}

Array& Array:: operator = (Array &mas)
{
    if (&mas == this)
    {
        return *this;
    }
    if (m != mas.m)
    {
        delete a;
        m = mas.m;
        a = new size_t[m];
    }
    for (size_t i = 0; i < m; i++)
    {
        a[i] = mas.a[i];
    }
    return *this;
}

size_t& Array:: operator [](size_t i)
{
    if ((i < 0) || (i >= m))
    {
        puts("Индекс за пределами ");
        exit(0);
    }
    return a[i];
}

bool Array:: Test()
{
    for (size_t i = 1; i < m; i++)
    {
        if (a[i] < a[i - 1])
        {
            return 1;
        }
    }
return 0;
}

bool Array:: operator == (Array mas)
{
    if (m != mas.m)
    {
        return 0;
    }
    
    for (size_t i = 0; i < m; i++)
    {
        size_t j = 0;
        size_t n = mas.m;
        for (j = 0; j < mas.m; j++)
        {
            if (a[i] == mas.a[j])
            {
                mas.a[j] = mas.a[mas.m - 1];
                mas.m--;
                break;
            }
        }
        if (j == n)
        {
            return 0;
        } 
    }
    return 1;
}

void Array:: Shell_sort()
{
    // if (!(Test()))
    // {
    //     return;
    // }
    size_t t = log2(m);
    size_t *h = new size_t[t];
   
    h[0] = m/2;
    for (size_t i = 1; i < t; i++)
    {
        h[i] = h[i - 1]/2;
    }
    
    for (size_t i = 0; i < t; i++)
    {
        size_t s = h[i];
        for (size_t b = 0; b < s; b++)
        {
            for (size_t j = b + s; j < m; j += s)
            {
                size_t x = a[j];
                long long int k = j - s;
                while ((k >= 0) && (a[k] > x))
                {
                    a[k + s] = a[k];
                    k -= s;
                }
                a[k + s] = x;
            }  
        }
    }
    delete [] h;
}

void Array:: Shaker_sort()
{
    size_t l = 0;
    size_t r = m - 1;
    while (l < r)
    {
        size_t r1 = l;
        for (size_t i = l; i < r; i++)
        {
            if (a[i] > a[i + 1])
            {
                size_t q = a[i];
                a[i] = a[i + 1];
                a[i + 1] = q;
                r1 = i;
            }
        }
        r = r1;
        size_t l1 = r;
        for (size_t i = r; i > l; i--)
        {
            if (a[i] < a[i - 1])
            {
                size_t q = a[i];
                a[i] = a[i - 1];
                a[i - 1] = q;
                l1 = i;
            } 
        }
        l = l1;
    }   
}

int Array:: Quick_sort(size_t mas_beg, size_t mas_end)
{
    long long int l = mas_beg;
    long long int r = mas_end;
    if (l >= r)
    {
        return 1;
    }
    long long int i = l + 1;
    long long int j = r;
    long long int x = a[l];
    while (i <= j)
    {
        while ((i <= j) && (a[i] <= x))
        {
            i++;
        }
        while ((j >= i) && (a[j] > x))
        {
            j--;
        }
        if (i < j)
        {
            size_t q = a[i];
            a[i] = a[j];
            a[j] = q;
            i++;
            j--; 
        }
    }
   
    size_t q = a[l];
    a[l] = a[j];
    a[j] = q;
    j--;

    Quick_sort(l, j);
    Quick_sort(i, r);
    return 0;
}

void Shift2(size_t *a, size_t n, size_t i)
{
    int j = 2*i + 1;
    int x = a[i];
    while (j < n)
    {
        if (((j + 1) < n) && a[j+1] > a[j])
        {
            j++;
        }
        if (a[j] > x)
        {
            a[i] = a[j];
            i = j;
            j = 2*i + 1;
        }
        else
        {
            break;
        }
    }
    a[i] = x;
}

void Array:: Heap_sort()
{
    for (long long int i = m/2 - 1; i >= 0; i--)
    {
        Shift2(a, m, i);
    }
    
    for (size_t i = m - 1; i > 0; i--)
    {
        size_t q = a[0];
        a[0] = a[i];
        a[i] = q;
        Shift2(a, i, 0);
    }       
}



int main()
{

Array a(15000, 1, 10);
Array b(a);
// a.Quick_sort(0, 14);

// if (a.Test(), !(a == b))
// {
//     perror("Error sort");
//     return 1;
// }

Array c(a);
Array d(a);
Array e(a);

int start = clock();
b.Quick_sort(0, 14999);
int quick_end = clock();

c.Heap_sort();
int heap_end = clock();

d.Shaker_sort();
int shaker_end = clock();

e.Shell_sort();
int shell_end = clock();

if (b.Test() || c.Test() || d.Test() || e.Test() || !(a == b) || !(a == d) || !(a == c) || !(a == e))
{
    perror("Error sort");
    return 1;
}

printf("Quick_sort  = %.3f sec\n", (float)(quick_end - start)/CLOCKS_PER_SEC);
printf("Heap_sort   = %.3f sec\n", (float)(heap_end - quick_end)/CLOCKS_PER_SEC);
printf("Shaker_sort = %.3f sec\n", (float)(shaker_end - heap_end)/CLOCKS_PER_SEC);
printf("Shell_sort  = %.3f sec\n", (float)(shell_end - shaker_end)/CLOCKS_PER_SEC);

return 0;  
}