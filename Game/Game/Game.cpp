#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;

int main()
{ 
	int score = 0;    
	int time = 0;    
	int target = rand() % 10 + 1; // �������1��10֮�������    
	const int MAX_NUMS = 3; // �����ʾ3������    
	while (true)    
	{        // ��ʾ����        
		cout << "\nGet ready...\n";       
		cout << "The target is " << target << ".\n";        
		cout << "Time's up!\n\n";        // ��ʱ��        time++;        
		auto start_time = chrono::system_clock::now();        // ģ���������        
		while (cin >> target)        
		{            
			// ������е�����÷ּ�1�֣������¿�ʼ��ʱ��            
			score++;            
			if (target == 9) break; // �������9�ŵ����������Ϸ            
			// �����ʱ����ʱ���������Ϸ�����ʧ����Ϣ            
			auto elapsed_time = chrono::system_clock::now() - start_time;            
			/*if (elapsed_time > 5.0) break;*/ // �����ʱ������5���ӣ��������Ϸ�����ʧ����Ϣ            
			cout << target - 1 << "\n"; // �����ǰ������        
		}        
		// �����Ϸʱ�䵽�ˣ������ʤ����Ϣ�����¼�ʱ���ͷ���        
		if (time >= 10) break; // �����Ϸʱ�䵽��10���ӣ��������Ϸ�����ʤ����Ϣ        
		// ������������Լ����߼��������ӡս��Ʒ�Ȳ���    
	}   
	return 0;
}