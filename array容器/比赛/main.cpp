#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
#include<cstdio>
using namespace std;

//ԭ�����
void test()
{
    char n,c;
    cin >> n;
    c = (n - 'a' + 1) % 26 + 'a';
    printf("%c\n", (n - 'a' + 1) % 26 + 'a');
    cout << c ;//���ݼ�������ݣ����о��Ȼ��ʽ��C���Ե������������
}

void test1()
{
    int n = 0;
    string m;
    cin >> n;
    getchar();
    getline(cin, m);
    for (char& c : m)
    {
        //���ǽ���ת��Ϊ�������ĸ��˳���е�λ�ã�����ȥ 'a'���������ƶ�λ�� n��Ȼ���ٶ� 26 ȡ����������ټ��� 'a' ���õ��µ��ַ���
        c = (c - 'a' + n) % 26 + 'a';//���ݵ�ǰ��ĸ��ȥa�ó���Ӧ��
        cout << c;
    }
    cout << endl;
}


void test2()
{

    int n = 0;
    cin >> n;
    int num[10000];
    int i = 0;
    for (i = 0; i < n; i++)
    {
        cin >> num[i];
    }
    num[i] = 0;
    for (i = 0; i < n; i++)
    {
        int a = 2 * num[i] - 1;
        cout << ((num[i] * (1 + a)) / 2) % 10000 << endl;
    }
}
//��Ŀ
int main()
{
    //test();
    //test1();
    test2();
    return 0;
}

