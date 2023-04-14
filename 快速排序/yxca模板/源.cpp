#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
/***************************Ä£°åËã·¨***********************************/
int  idxnum(int* q, int l, int r) {
    int idx = q[l];
    while (l < r) {
        while (l < r && q[r] >= idx) {
            --r;
        }
        q[l] = q[r];
        while (l < r && q[l] <= idx) {
            ++l;
        }
        q[r] = q[l];
    }
    q[l] = idx;
    return l;
}
void  quick_sort(int* q, int l, int r) {
    if (l >= r)return;
    int idx = idxnum(q, l, r);
    quick_sort(q, l, idx - 1);
    quick_sort(q, idx + 1, r);

}

/***************************************************************************/
int main() {
    int n = 0;
    scanf("%d", &n);
    int q[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &q[i]);
    }
    int l = 0, r = n - 1;
    quick_sort(q, l, r);
    for (int i = 0; i < n; i++) {
        printf("%d ", q[i]);
    }
    printf("\n");
}
