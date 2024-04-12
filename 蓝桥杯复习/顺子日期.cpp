#include <iostream>
#include <string.h>
using namespace std;
const int N = 10;
char s[N];
int ans;
int main()
{
	for(int month = 1; month <= 12 ; ++ month )
		for(int day = 1; day <= 31; ++ day)
		{
			if(month == 2 && day == 29) break;
			if((month == 4 || month == 6 || month ==9 || month ==11) && (day == 31)) break;
			sprintf(s+1,"2022%02d%02d",month,day);
			//еп╤о
			for(int i=1;i<=6;i++)
			{
				if(s[i+2] - s[i+1] == 1 && s[i+1] - s[i] == 1) 
				{
					ans++;
					cout<<s+1<<endl;
					break;
				}		
			}
		}
	cout<<ans<<endl;
}
