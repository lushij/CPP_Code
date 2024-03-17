#ifndef __WD_TEMPLATE_SINGLETON_H__
#define __WD_TEMPLATE_SINGLETON_H__

#include <iostream>
using std::cout;
using std::endl;
#if 0
class Singleton
{
public:
    static Point *getInstance(int ix, int iy)
    {
		if(nullptr == _pInstance) 
        {
			_pInstance = new Point(ix, iy);
			_ar;//为了在模板参数推导时创建ar对象
		}
		return _pInstance;

    }
};
#endif
template <class T>
class Singleton
{
public:
	template <class... Args>
	static T *getInstance(Args... args)
	{
		if(nullptr == _pInstance) 
        {
			_pInstance = new T(args...);
			_ar;//为了在模板参数推导时创建ar对象
		}
		return _pInstance;
	}

private:
	class AutoRelease
	{
	public:
		AutoRelease() 
        {	
            cout << "AutoRelease()" << endl;	
        }

		~AutoRelease() 
        {
			cout << "~AutoRelease()" << endl;
			if(_pInstance)
            {
				delete _pInstance;
                _pInstance = nullptr;
			}
		}
	};


private:
	Singleton()
    { 
        cout << "Singleton()" << endl;	
        /* _ar; */
    }

	~Singleton()
    {	
        cout << "~Singleton()" << endl;
    }

private:
	static T *_pInstance;
	static AutoRelease _ar;
};

template <class T> 
T * Singleton<T>::_pInstance = nullptr;

template <class T>
typename  Singleton<T>::AutoRelease Singleton<T>::_ar;//typename表名是一个类型

#endif
