#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

class Num
{
public:
    int _rm;
    int _re;
    Num(int rm, int re) :_rm(rm), _re(re) {}
    Num operator+(const Num& rhs)
    {
        return Num(this->_rm + rhs._rm, this->_re + rhs._re);
    }
    void print()
    {
        if (_re > 0)
            printf("%d+%di\n", _rm, _re);
        else
            printf("%d%di\n", _rm, _re);
    }
};

int n = 0;

int main()
{
    scanf("%d", &n);
    while (n--)
    {
        int p, q, u, v;
        scanf("%d%d%d%d", &p, &q, &u, &v);
        Num c = Num(p, q) + Num(u, v);
        c.print();
    }
    return 0;
}