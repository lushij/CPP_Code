#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

void BFS()
{
    int n = 0, m = 0;
    if (scanf("%d%d", &n, &m) != 2) return 0;

    // 1. 构建邻接表
    vector<vector<int>> tree(n + 1);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    // 2. BFS 初始化
    queue<int> q;
    // dist 数组初始化为 -1，表示该节点尚未被访问
    vector<int> dist(n + 1, -1);

    q.push(m);       // 把根节点推入队列
    dist[m] = 0;     // 根节点到自己的距离是 0

    int max_dist = 0; // 用于记录最远距离

    // 3. 开始 BFS 遍历
    while (!q.empty())
    {
        int curr = q.front(); // 取出队头元素
        q.pop();              // 弹出队头

        // 遍历当前节点的所有邻接节点
        for (int i = 0; i < tree[curr].size(); ++i)
        {
            int neighbor = tree[curr][i];

            // 如果这个邻居还没有被访问过（防止走回头路）
            if (dist[neighbor] == -1)
            {
                dist[neighbor] = dist[curr] + 1;      // 邻居的距离 = 当前节点距离 + 1
                max_dist = max(max_dist, dist[neighbor]); // 更新最大距离
                q.push(neighbor);                     // 把邻居推入队列，等待后续扩展
            }
        }
    }

    // 4. 输出结果
    printf("%d\n", max_dist);

}

void DFS()
{
#include <iostream>
#include <vector>
#include <algorithm>

    using namespace std;

    // 将树和最大距离设为全局变量，方便在递归函数中直接使用
    vector<vector<int>> tree;
    int max_dist = 0;

    // DFS 函数
    // curr: 当前所在的节点
    // parent: 从哪个节点走过来的（用于防止走回头路）
    // depth: 当前距离根节点的距离
    void dfs(int curr, int parent, int depth)
    {
        max_dist = max(max_dist, depth);

        for (int i = 0; i < tree[curr].size(); ++i)
        {
            if (tree[curr][i] != parent)
            {
                dfs(tree[curr][i], curr, depth + 1);
            }
        }
    }

    int main()
    {
        int n = 0, m = 0;
        if (scanf("%d%d", &n, &m) != 2) return 0;

        // 分配好空间，节点编号是 1 到 n，所以开 n+1 的大小
        tree.resize(n + 1);

        for (int i = 1; i < n; ++i)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            tree[u].push_back(v);
            tree[v].push_back(u);
        }

        dfs(m, 0, 0);


        printf("%d\n", max_dist);

        return 0;
    }
}

int main()
{
    //BFS();
    DFS();
    return 0;
}