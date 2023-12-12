#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
using namespace std;

void test()
{
    //文件输入流:就是从文件读取内容
    //	//ifstream要求打开的文件必须存在
    ifstream ifs("hello.txt");
    if(!ifs)
    {
        cout<<"error"<<endl;
        return;
    }
    string word;
    //输入流运算符是以空格、制表符作为分隔字符
    while(ifs>>word)
    {
        cout<<word<<" ";
    }
    cout<<endl;
    ifs.close();
}
void test1()                                        
{                                                  
    //文件输入流  
    //	//ifstream要求打开的文件必须存在
    ifstream ifs("hello.txt");                     
    if(!ifs)                                       
    {                                              
        cout<<"error"<<endl;                       
        return;                                    
    }                                              
    //输入流运算符是以空格、制表符作为分隔字符     
    //按行读取                                     
    string line;                                   
    while(getline(ifs,line))                       
    {                                              
        cout<<line;                                
    }                                              
    cout<<endl;                                    
    ifs.close();                                   
}                                                  
int main()   
{            
    test();  
    test1();  
    return 0;
}            
             
             
