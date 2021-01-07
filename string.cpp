#include <iostream>
#include <cstring>
#include <cstdio>


using namespace std;

const int MS = 255;
class String
{
    char *line;  
    int len = 0;
    public:
    String(int l = 80); 
    String(const char *);
    String(String &); //Конструктор копирования
    ~ String() {delete [] line;}; //Деструктор. Очищает выделенную память    
    int Len() {return len;};
    void Print() {printf("%s", line);};
    String& operator +=(String &);
    int operator ==(String &);
    String& operator ~();
    char& operator [](int);
    String& operator =(String &s);
    String operator + (const String &s);
    friend ostream & operator<<(ostream &r, String &s)
    {
        r<<s.line;
        return r;
    }
    friend istream & operator>>(istream &r, String &s)
    {
        char *buf = new char[80];
        cout << "Введите строку, в конце Enter\n";
        r >> buf;
        String q(buf);
        s = q;
        delete buf;
        return r;
    }
    int BMH_poisk(String &);
    int KMP_poisk(String &);
};

String String:: operator + (const String &s)
{
	String z(len + s.len + 1);
	strcpy(z.line, line);
	strcat(z.line, s.line);
	z.len = strlen(z.line);
	return z;
}


String& String:: operator =(String &s)
{
	if (this != &s)
	{
		delete [] line;
        len = s.len;
		line = new char [len + 1];
		strcpy(line, s.line);
	}
	return *this;
}

inline char& String:: operator [](int i)
{
    if ((i<0) || (i>=len))
    {
        puts("Индекс за пределами ");
        exit(0);
    }
    return line[i];
}

String& String:: operator ~()
{
    char t = 0;
    for (int i = 0; i < len/2; i++)
    {
        t = line[i];
        line[i] = line[len - i - 1];
        line[len - i - 1] = t;
    }
return *this;
}


int String:: operator ==(String &s)
{
    if (strcmp(line, s.line))
    {
        return 0;
    }
return 1;
}

String& String:: operator +=(String &s2)
{
    char *t = new char[len = len + s2.len];
    strcpy(t, line);
    strcat(t, s2.line);
    delete [] line;
    line = t;
    return *this;
}

String:: String(const char *s)
{
    line = new char [strlen(s)+1];
    for (len = 0; line[len] = s[len]; len++);
}

String:: String(int l)
{
    line = new char[l + 1];
    len = 0;
    line[0] = '\0';
}

String:: String(String &s)
{
    line = new char[s.len + 1];
    for (len = 0; line[len] = s.line[len]; len++);
}



int String:: BMH_poisk(String &p)
{
    int *tabl = new int[256];
    for (int i = 0; i < 256; i++)
    {
        tabl[i] = p.len;
    }
    for (int i = 0; i < p.len - 1; i++)
    {
        tabl[p.line[i]] = p.len - 1 - i;
    }
    
    int i = p.len - 1;
    int j = p.len - 1;

    while (i < len)
    {
        int k = i;
        j = p.len - 1;
        for (int l = 0; l < p.len; l++)
        {
            if (line[k] == p.line[j])
            {
                j--;
                k--;
            }
        }
        if (j < 0)
        {
            break;
        }
        i += tabl[line[i]];
    }
    delete tabl;
    if (i >= len)
    {
        return -1;
    }
    return i - p.len + 1;
}

int String:: KMP_poisk(String &p)
{
    int *NewJ = new int[p.len];
    NewJ[0] = -1;

    int k = 0;
    for (int j = 0; j < p.len - 1;)
    {
        while (k >= 0)
        {
            if(p.line[j] == p.line[k])
            {
                break;
            }
            k = NewJ[k];
        }
        k++;
        j++;
        if (p.line[j] == p.line[k])
        {
            NewJ[j] = NewJ[k];
        }
        else
        {
            NewJ[j] = k;
        }
    }

    int i = 0;
    for (int j = 0; j < p.len;)
    {
        if (i >= len)
        {
            return -1;
        }

        while (j >= 0)
        {
            if (line[i] != p.line[j])
            {
                j = NewJ[j];
            }
            else
            {
                break;
            }
        }
        i++;
        j++;
    }
    delete NewJ;
    return i - p.len;
}

int main() 
{
    // String s1(10), s2, a3("Без слов");
    // String *s3;
    // s1.Fill("объект");
    // s2.Fill(" класса String ");
    // char O[3] = "О";
    // s1[0] = O[0];
    // s1[1] = O[1];
    // s1.Print();
    // printf("\n");
    
    // String str1("Объект "), str2("класса String");
    // String *str3 = new String(str1+=str2);
    // str3->Print();
    // cout<<"\n";

    // String s5("Help");
    // cout<<s5<<"\n";

    // String s6("kj[");
    // cin>>s6;
    // cout<<s6<<"\n";

    String a("Hello my friend!");
    String b("freend");
    printf("%d\n", a.BMH_poisk(b));
    printf("%d\n", a.KMP_poisk(b));
    return 0;

}



