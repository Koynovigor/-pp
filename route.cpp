#include <iostream>

using namespace std;

class Route
{
    int* r = NULL;
    int n = 0;
    public:
    Route(int); // создается первый маршрут
    Route(const Route&); // конструктор копирования
    Route & operator = (const Route&); // операция присваивания
    ~Route() { if(r != NULL) delete [] r; r = NULL; } // деструктор
    int route_price(int **); // вычисляется стоимость маршрута по матрице стоимости
    bool next_route(); // вычисляется следующий маршрут, используя алгоритм Дейкстры
    friend ostream & operator << (ostream& a, Route& b) // вывод маршрута
    {
        for (int i = 0; i < b.n; i++)
        {
            a << b.r[i] << " -> ";
        }
        a << b.r[0];
        return a;
    }
};

Route:: Route(int a)
{
    n = a;
    r = new int[a];
    for (int i = 0; i < n; i++)
    {
        r[i] = i + 1;
    }
    
}

Route:: Route(const Route& a)
{
    n = a.n;
    r = new int[n];
    for (int i = 0; i < n; i++)
    {
        r[i] = a.r[i];
    }
}

Route& Route:: operator = (const Route& a)
{
    if (&a == this)
    {
        return *this;
    }
    if (n != a.n)
    {
        delete r;
        n = a.n;
        r = new int[n];
    }
    for (int i = 0; i < n; i++)
    {
        r[i] = a.r[i];
    }
    return *this;
}

int Route:: route_price(int **a)
{
    int len = 0;
    for (int i = 0; i < n - 1; i++)
    {
        len += a[r[i] - 1][r[i + 1] - 1];
    }
    len += a[r[n - 1] - 1][r[0] - 1];
    return len;
}

bool Route:: next_route()
{
    int max_i = -1;                  
    for (int i = n - 2; i > 0; i--)  
    {                                
        if (r[i] < r[i + 1])
        {
            max_i = i;              
            break;
        }
    }
    if (max_i == -1)
    {
        return 1;
    }
    
    int max_j = 0;
    for (int j = n - 1; j > max_i; j--)
    {
        if (r[j] > r[max_i])
        {
            max_j = j;
            break;
        }
    }
    
    int a = r[max_i];
    r[max_i] = r[max_j];
    r[max_j] = a;


    for (int i = 1; i < (n - max_i)/2 + ((n - max_i)%2 > 0); i++)
    {
        int a = r[max_i + i];
        r[max_i + i] = r[n - i];
        r[n - i] = a;
    }
    return 0;
}

int main()
{
    cout << "Введите количество вершин: ";
    int n = 0;
    cin >> n;
    Route a(n);

    int **matr = new int *[n];
    for (int i = 0; i < n; i++)
    {
        matr[i] = new int[n];
    }
    
    cout << "Введите стоимость маршрута:\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (j != i)
            {
                printf("%d -> %d = ", i + 1, j + 1);
                cin >> matr[i][j];
            }
            else
            {
                matr[i][j] = 0;
            }
        }
    }

    int len_min = a.route_price(matr);
    Route a_min(n);

    while (!a.next_route())
    {
        int len_cur = a.route_price(matr);
        if (len_cur < len_min)
        {
            len_min = len_cur;
            a_min = a;
        }
        cout << a << " = " << len_cur << "\n";
    }
    
    for (int i = 0; i < n; i++)
    {
        delete[] matr[i];
    }
    delete[] matr;
    
    cout << "Минимальная длина пути = " << len_min << "\n";
    cout << "Маршрут: " << a_min << "\n";

return 0;
}