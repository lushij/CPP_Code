#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;
class Queue
{
public:
    Queue(int capacity=10)
        :_front(0)
         ,_rear(0)
         ,_capacity(capacity)
         ,_data(new int[_capacity]())
    {
        cout<<"Queue()"<<endl;
    }
    void push(int num);//入队
    void pop();//出队
    bool empty() const;//判断是否为空
    bool full() const;//判断是否为满
    int  size() const;//返回大小
    int front() const;//返回队头元素
    int back() const;//返回队尾元素
    ~Queue()
    {
        if(_data)
        {
            delete _data;
            _data=nullptr;
        }
        cout<<"~Queue()"<<endl;
    }
private:
    int _front;//队头
    int _rear;//队尾
    int _capacity;//容量
    int *_data;
};
void Queue:: push(int num)
{
    if(!full())
    {
        _data[_rear]=num;
        _rear=(_rear+1)%_capacity;
    }
    else
    {
        cout<<"que is full "<<endl;
    }
}
void Queue:: pop()
{
    if(!empty())
    {
       _front=(_front+1)%_capacity;
       /* cout<<"_front is "<<_front<<endl; */
    }
}
bool Queue:: empty() const//判断是否为空
{
    return _rear==_front;
}
bool Queue:: full() const//判断是否为满
{
    return (_rear+1)%_capacity==_front;
}
int Queue:: size() const//返回大小
{
    return (_rear-_front+_capacity)%_capacity;
}
int Queue::front() const//返回队头元素
{
    return _data[_front];
}
int Queue::back() const
{
    /* cout<<"_rear = "<<_rear<<endl; */
    return _data[(_rear-1+_capacity)%_capacity];
}
void test()
{
    Queue que;
    cout<<"que.size is "<<que.size()<<endl;
    que.push(1);
    cout<<"push after que.size is "<<que.size()<<endl;
    que.push(2);
    cout<<"push after que.size is "<<que.size()<<endl;
    que.push(3);
    cout<<"push after que.size is "<<que.size()<<endl;
    cout<<"que.front() "<<que.front()<<endl;
    cout<<"que.back() "<<que.back()<<endl;
    que.pop();
    cout<<"pop after que.size is "<<que.size()<<endl;
    cout<<"que.front() "<<que.front()<<endl;
    cout<<"que.back() "<<que.back()<<endl;

}
int main()
{
    test();
    return 0;
}

