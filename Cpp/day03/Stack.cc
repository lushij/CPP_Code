#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;
class Stack
{
public:
    Stack(int capacity=10)
        :_top(-1)
         ,_data(new int[capacity]() )
         ,_capacity(capacity)
    {
        cout<<"Stack()"<<endl;
    }
    void push(int num);
    void pop();
    int front()const;
    int size()const;
    bool empty()const;
    bool full()const;

    ~Stack()
    {
        if(_data)
        {
            delete _data;
            _data=nullptr;
        }
        cout<<"~Stack()"<<endl;
    }
private:
    int _top;
    int *_data;
    int _capacity;

};
void Stack::push(int num)
{
    if(!full())
    {
        _data[++_top]=num;
    }
}

bool Stack::full()const
{
    return (_top+1)==_capacity;
}
bool Stack::empty()const
{
    return _top==-1;
}
int Stack::front()const
{
    return _data[_top];
}
void Stack::pop()
{
    if(!empty())
    {
        --_top;
    }
}
int Stack::size()const
{
    return _top+1;
}
void test()
{
    Stack st;
    st.push(1);
    cout<<"st.front() is "<<st.front()<<endl;
    cout<<"st.size is "<<st.size()<<endl;
    st.pop();
    cout<<"pop after st.size is "<<st.size()<<endl;
    for(int i=0;i<10;++i)
    {
        st.push(i);
    }
    cout<<st.front()<<endl;
    cout<<st.full()<<endl;
    cout<<st.size()<<endl;
}
int main()
{
    test();
    return 0;
}

