#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

//类的声明: 在类中只要有一个成员函数没有实现
//都称为类的声明，而不能叫类的定义
class Computer
{
public:
	//如果是系统提供的，就是这样一个形态
	Computer()
	{	cout << "Computer()" << endl;	}

	Computer(const char * brand, float price)
	{
		cout << "Computer(const char*, float)" << endl;
		strcpy(_brand, brand);
		_price = price;
	}
    ~Computer()
    {
        cout<<"~Computer()"<<endl;
    }
	void setBrand(const char * brand);
	void setPrice(float price);
	void print();
private:
	char _brand[20];// m_brand
	float _price;	// price_
};
 
//在类之外实现(定义)成员函数
void Computer::setBrand(const char * brand) {
	strcpy(_brand, brand);
}

void Computer::setPrice(float price) {
	_price = price;
}

void Computer::print() {
	cout << "brand:" <<  _brand << endl
		 << "price:" << _price << endl;
}

void test()
{
    Computer c1;//创建对象  ==> 调用的是默认构造函数
    /* c1.setPrice(7999); */
}
 
int main(void)
{
    test();
	return 0;
}
