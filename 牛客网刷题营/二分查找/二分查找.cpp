#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <cstring>
#include <algorithm>//Ëã·¨¿âº¯Êý
#include<vector>//ÈÝÆ÷
using namespace std;


int BinarySearch(vector<int>& nums, int target)
{
    int l = 0;
    int r = nums.size() - 1;
    while (l <= r)
    {
        int mid = (l + r) / 2;
        if (nums[mid] < target)
        {
            l = mid + 1;
        }
        else if (nums[mid] > target)
        {
            r = mid - 1;
        }
        else if (nums[mid] == target)
        {
            return mid;
        }
    }
    return -1;
}
int main()
{
    vector<int> num({ 1,2,3,5,7,9,90,100,120,160 });
    int target = 9;
    int ret = BinarySearch(num, target);
    cout << ret << endl;
    return 0;
}