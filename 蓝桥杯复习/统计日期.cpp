#include <bits/stdc++.h>
using namespace std;

string str="5686916124919823647759503875815861830379270588570991944686338516346707827689565614010094809128502533";
char s[10];

bool check(char * s)
{
	int idx = 1;
	for(int i=1;i<=100;++i)
	{
		if(str[i] == s[idx])
		{
			++idx;
		}
		if(idx == 9) return true;
	}
	return false;
}
int main()
{
	int cnt = 0;
	for(int month = 1; month <= 12; ++ month)
		for(int day = 1; day <= 31; ++ day)
		{
			if(month == 2 && day ==29) break;
			if((month == 4 || month == 6 || month == 9 || month == 11) && day == 31) break;
			sprintf(s+1,"2023%02d%02d",month,day);
			if(check(s)) cnt++;
		}
	cout<<cnt<<endl;
} 
