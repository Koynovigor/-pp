#include <iostream>
#include <ctime>
using namespace std;

class Door
{
    int n;     //Размер матрицы стоимости
    int **mas; //Матрица стоимости
public:
    Door(int a = 1);               //Конструктор по умолчанию
    Door(const Door &);            //Конструктор копирования
    Door &operator=(const Door &); //Присвоение
    ~Door();                       //Деконструктор
    void fillmatr();               //Заполнение матрицы стоимости
    void randmatr();
    int *route_search(int a = 1);  //Поиск пути. а - вершина с кторой начинается поиск (эвристический метод)
};

Door::Door(int a)
{
    n = a;
    mas = new int *[n];
    for (int i = 0; i < n; i++)
    {
        mas[i] = new int[n];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            mas[i][j] = 0;
        }
    }
}

Door::Door(const Door &a)
{
    n = a.n;
    mas = new int *[n];
    for (int i = 0; i < n; i++)
    {
        mas[i] = new int[n];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            mas[i][j] = a.mas[i][j];
        }
    }
}

Door &Door::operator=(const Door &a)
{
    if (n != a.n)
    {
        for (int i = 0; i < n; i++)
        {
            delete mas[i];
        }
        delete mas;

        n = a.n;
        mas = new int *[n];
        for (int i = 0; i < n; i++)
        {
            mas[i] = new int[n];
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            mas[i][j] = a.mas[i][j];
        }
    }
    return *this;
}

Door::~Door()
{
    for (int i = 0; i < n; i++)
    {
        delete[] mas[i];
    }
    delete[] mas;
}

void Door::fillmatr()
{
    cout << "Введите стоимость маршрута:\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d -> %d = ", i + 1, j + 1);
            cin >> mas[i][j];
        }
    }
}

void Door:: randmatr()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            mas[i][j] = rand() % 100 + 1;
        }
    }
}

int *Door::route_search(int a)
{
    int *visit = new int[n]; //Массив, в котором отмечаются посещённые вершины
    for (int i = 0; i < n; i++)
    {
        visit[i] = 1;
    }
    if ((a > 0) && (a <= n))
    {
        visit[a - 1] = 0;
    }
    int len = 0;                 //длина пути
    int *route = new int[n + 1]; //путь. в конце длина пути

    for (int i = 0; i < n; i++)
    {
        route[i] = a;
        visit[a - 1] = 0;
        int min = 0;
        for (int j = 0; j < n; j++)
        {
            if ((mas[a - 1][j] != 0) && (visit[j] == 1))
            {
                min = mas[a - 1][j];
                break;
            }
        }
        int city = -1;
        for (int j = 0; j < n; j++)
        {
            if ((mas[a - 1][j] <= min) && (mas[a - 1][j] != 0) && (visit[j] == 1))
            {
                min = mas[a - 1][j];
                city = j;
            }
        }
        if ((city == -1) && (i != n - 1))
        {
            return NULL;                    //Зашёл в тупик!
        }

        len += min;
        a = city + 1;
    }
    route[n] = len;
    delete visit;
    return route;
}

int main()
{
    int start = clock();

    cout << "Введите количество вершин: ";
    int n = 0;
    cin >> n;
    Door a(n);
    a.fillmatr();
    int *min = NULL;

    try
    {
        min =  new int[n + 1];
    }
    catch(const std::bad_alloc)
    {
        cout << "Ошибка выделения памяти";
        return 1;
    }
    
         
    for (int i = 0; i < n + 1; i++)
    {
        min[i] = 0;
    }

    for (int i = 1; i <= n; i++)
    {
        int *res = a.route_search(i);
        if (res == NULL)
        {
            delete res;
            continue;
        }
        if ((res[n] < min[n]) || (min[n] == 0))
        {
            for (size_t j = 0; j < n + 1; j++)
            {
                min[j] = res[j];
            }
        }
        delete res;
    }

    cout << min[0];
    for (int i = 1; i < n; i++)
    {
        cout << " -> " << min[i];
    }
    cout << "\n"<< "len = " << min[n] << "\n";
    delete min;

    int end = clock();
    int t = (end - start) / CLOCKS_PER_SEC;
    cout << "time: " << t <<" sec\n";

    return 0;
}