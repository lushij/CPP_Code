#include <iostream>
#include <string>
#include <stdio.h>
#include<unordered_map>
#include<queue>
#include<functional>
#include<vector>


using namespace std;
using uint=unsigned int;
class HuffmanTree
{
public:
    HuffmanTree()
        :_root(nullptr)
         ,_minHeap([](Node_t*lhs,Node_t*rhs){return lhs->_weight > rhs->_weight;})
         {}

    void createHuffmanTree(string str)
    {
        //第一步读取字符并统计频率
        unordered_map<char,int>dataMap;
        for(auto &ch:str)
        {
            dataMap[ch]++;
        }
        //第二步 生成节点放入小根堆中
        for(auto &pair:dataMap)
        {
            _minHeap.push(new Node_t(pair.first,pair.second));
        }
        //第三步 调整树
        while(_minHeap.size()>1)
        {
            Node_t*n1=_minHeap.top();
            _minHeap.pop();
            Node_t*n2=_minHeap.top();
            _minHeap.pop();
            Node_t*node=new Node_t('\0',n1->_weight + n2->_weight);//父节点等于孩子节点权值和
            node->_left=n1;
            node->_right=n2;
            _minHeap.push(node);//重新放入小根堆 
        }
        _root=_minHeap.top();//循环结束表示哈夫曼树已经建好，进行赋值即可
        _minHeap.pop();//清空小根堆
    }
    
    string getHuffMan(string str)
    {
        string strCode;//先获取哈夫曼树的每个数据对应的哈夫曼码
        string encodeStr;//然后返回
        getHuffMan(_root,strCode);
        for(auto &ch:str)
        {
            encodeStr.append(_codeMap[ch]);
        }
        return encodeStr;
    }

    string decode(string encode)
    {
        string decodeStr;
        Node_t*cur=_root;
        for(auto &ch:encode)
        {
            if(ch=='0')//左节点
            {
                cur=cur->_left;
            }
            else// ‘1’右节点
            {
                cur=cur->_right;
            }
            if(cur->_left == nullptr && cur->_right==nullptr)
            {
                decodeStr.push_back(cur->_ch);
                cur=_root;//每次都要重新开始
            }
        }
        return decodeStr;
    }


    ~HuffmanTree()
    {

    }
private:
    struct Node_t{
        Node_t(char ch,uint weight)
            :_ch(ch)
             ,_weight(weight)
             ,_left(nullptr)
             ,_right(nullptr)
        {

        }
        char _ch;//字符数据
        uint _weight;//权重
        Node_t*_left;//左节点
        Node_t*_right;//右节点
    };
    void getHuffMan(Node_t* &root,string str)
    {
        if(root->_left==nullptr && root->_right==nullptr)
        {
            _codeMap[root->_ch]=str;//更新字符对应的哈夫曼编码
            return;
        }
        getHuffMan(root->_left,str+"0");
        getHuffMan(root->_right,str+"1");
    }
private:
    Node_t*_root;//根节点
    unordered_map<char,string>_codeMap;//存储字符对应的哈夫曼编码
    //priority_queue是容器适配器，底层根据容器进行改造合适的功能
    //参数含义: 存储数据的类型，优先队列使用的底层容器，比较器
    using MinHeap=priority_queue<Node_t*
        ,vector<Node_t*>
        ,function<bool(Node_t*,Node_t*)>>;
    MinHeap _minHeap;//小根堆
    //用小跟堆的原因
    //  是每次取得是最小的两个数组件一个树
    //，是的频率最低的处于树深度较深的节点上
};



void test()
{
    string str = "ABACDAEF";
    HuffmanTree htree;
    htree.createHuffmanTree(str);
    string encode = htree.getHuffMan(str);
    cout << "encode:" << encode << endl;
    cout<<"字符还原:"<<htree.decode(encode)<<endl;
}
int main()
{
    test();
    return 0;
}

