#include <iostream>
#include <string>
#include <stdio.h>
#include<fstream>
#include<sstream>
#include<vector>
using namespace std;
class Student
{
public:
    Student(int id,string name,string core)
        :_id(id)
         ,_name(name)
         ,_core(core)
    {}
    /* Student(string name) */
    /* { */
    /*     //从文件里导入 */
    /*     ifstream ifs(name); */
    /*     if(!ifs) */
    /*     { */
    /*         cout<<"open duc fail"<<endl; */
    /*         return; */
    /*     } */
    /*     string Info; */
    /*     getline(ifs,Info); */
    /*     istringstream iss(Info); */
    /*     iss>>_id>>_name>>_core; */
    /*     ifs.close(); */
        
    /* } */
    void setId(int id)
    {
        _id=id;
    }
    void setName(string name)
    {
        _name=name;
    }
    void setCore(string core)
    {
        _core=core;
    }
    int getId()const
    {
        return _id;
    }
    string getName()const
    {
        return _name;
    }
    string getCore()const
    {
        return _core;
    }
    void printInfo()const
    {
        cout<<_id<<" "<<_name<<" "<<_core<<endl;
    }
    void save(string filename)
    {
        //保存在文件里
        //以不存在就创建并且以追加的方式进行编写
        ofstream ofs(filename,std::ios::out | std::ios::app);
        if(!ofs)
        {
            cout<<"erro ofs"<<endl;
        }
        ofs<<_id<<" "<<_name<<" "<<_core<<'\n';
        ofs.close();
    }

    ~Student(){}
private:
    int _id;
    string _name;
    string _core;
};

void newInfo(vector<Student>&s)
{
    cout<<"请输入你要存入的信息\n顺序格式为：id name core\n";
    string info;
    int id;
    string name,core;
    cin.ignore();
    getline(std::cin,info);
    istringstream iss(info);//将字符串转变为其他类型
    iss>>id>>name>>core;
    Student stu(id,name,core);
    cout<<"是否要保存在文件，若是输入1，不是输入0"<<endl;
    int cmd=0;
    cin>>cmd;
    if(cmd)
    {
        cout<<"请输入你要保存的文件名字:";
         string filename;
         cin>>filename;
         stu.save(filename);
    }
       s.push_back(stu);
}
void checkInfo()
{
    ifstream ifs("stuInfo.txt");
    string line;
    if(!ifs)
    {
        cout<<"ifs erro"<<endl;
        return;
    }
    while(getline(ifs,line))
    {
        cout<<line<<endl;
    }
    ifs.close();
}
void  importInfo()
{

}

void test()
{
    printf("/*******************************/\n");
    printf("/*******  管理系统  ************/\n");
    printf("/******* 1.新建信息 ************/\n");
    printf("/******* 2.查看信息 ************/\n");
    printf("/******* 3.导入信息 ************/\n");
    printf("/******* 0.退出系统 ************/\n");
    printf("/*******************************/\n");
    vector<Student>stuInfo;
    printf("输入命令：");
    int choice=0;
    cin>>choice;
    switch(choice)
    {
    case 1:
        newInfo(stuInfo);
        break;
    case 2:
        checkInfo();
        break;
    case 3:
        importInfo();
        break;
    case 0:
        return;
        break;
    }
}
int main()
{
    test();
    return 0;
}


/* 在linux/unix平台的经常使用scanf从键盘获取字符， */
/* 输出字符后按Backspace键删除时，会出现^H， */
/* 这对习惯了按Backspace键删除的用户来说，感觉非常别扭, */
/* 虽然可以通过Ctrl+Backspace组合键实现删除功能 */
