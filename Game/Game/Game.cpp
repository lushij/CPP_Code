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
	int target = rand() % 10 + 1; // 随机生成1到10之间的数字    
	const int MAX_NUMS = 3; // 最多显示3个地鼠    
	while (true)    
	{        // 显示地鼠        
		cout << "\nGet ready...\n";       
		cout << "The target is " << target << ".\n";        
		cout << "Time's up!\n\n";        // 计时器        time++;        
		auto start_time = chrono::system_clock::now();        // 模拟打地鼠过程        
		while (cin >> target)        
		{            
			// 如果打中地鼠，则得分加1分，并重新开始计时器            
			score++;            
			if (target == 9) break; // 如果打中9号地鼠，则结束游戏            
			// 如果计时器超时，则结束游戏并输出失败信息            
			auto elapsed_time = chrono::system_clock::now() - start_time;            
			/*if (elapsed_time > 5.0) break;*/ // 如果计时器超过5秒钟，则结束游戏并输出失败信息            
			cout << target - 1 << "\n"; // 输出当前地鼠编号        
		}        
		// 如果游戏时间到了，则输出胜利信息并更新计时器和分数        
		if (time >= 10) break; // 如果游戏时间到了10秒钟，则结束游戏并输出胜利信息        
		// 在这里添加你自己的逻辑，比如打印战利品等操作    
	}   
	return 0;
}