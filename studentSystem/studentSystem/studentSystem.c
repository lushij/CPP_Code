#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include <assert.h>		//断言，判断指针是否空
#include <stdlib.h>
//封装自己需要用链式结构存储的数据
struct MM 
{
	char name[20];
	int age;
	int num;
	char tel[12];
	//.....
	//.....
	//.....
};
//结构体
struct Node 
{
	//int data;
	struct MM data;
	struct Node* next;
};
struct Node* list = NULL;
//链表就是结构体变量和结构体连接一起
//指针如何变成变量去使用？
//1.用指针指向变量
//2.动态内存申请，指向堆区的变量
struct Node* createHead() 
{
	//链表的表头做差异化处理
	struct Node* headNode = (struct Node*)malloc(sizeof(struct Node));
	assert(headNode);
	headNode->next = NULL;
	return headNode;
}
//创建节点(把用户的数据变成结构体变量)
struct Node* createNode(struct MM data) 
{
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	assert(newNode);
	/*
	//和下面代码类似作用，做防御性编程
		if(newNode==NULL)
			return NULL;
	*/
	//NULL->data=data; 错误
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}
//插入
void insertByHead(struct Node* headNode, struct MM data) 
{
	struct Node* newNode = createNode(data);
	newNode->next = headNode->next;
	headNode->next = newNode;
}
//删除： 指定位置删除
void deleteByName(struct Node* headNode,const char* name) 
{
	struct Node* preNode = headNode;
	struct Node* posNode = headNode->next;
	while (posNode != NULL && strcmp(posNode->data.name ,name)) 
	{
		preNode = posNode;
		posNode = preNode->next;
	}
	if (posNode != NULL) 
	{
		preNode->next = posNode->next;
		free(posNode);
		printf("删除成功!!!\n");
	}
}
struct Node* searchByNum(struct Node* headNode, int posData) 
{
	struct Node* pMove = headNode->next;
	while (pMove != NULL && pMove->data.num != posData) 
	{
		pMove = pMove->next;
	}
	return pMove;
}
//遍历
void printList(struct Node* headNode) 
{
	struct Node* pMove = headNode->next;
	printf("姓名\t年龄\t编号\t手机\n");
	while (pMove != NULL) 
	{
		//printf("%d\t", pMove->data);
		printf("%s\t%d\t%d\t%s\n",
			pMove->data.name, 
			pMove->data.age, 
			pMove->data.num
			, pMove->data.tel);
		pMove = pMove->next;
	}

}
//针对链表的文件读操作
void readFile(struct Node* headNode, const char* fileURL) 
{
	//C语言文件操作就是调用函数
	FILE* fp = fopen(fileURL, "r");   //第一运行打开失败 r:不具有创建功能
	if (fp == NULL) 
	{
		fp = fopen(fileURL, "w+");	  //w方式具有创建文件功能
		fclose(fp);
		return;
	}
	struct MM data;
	//读取表头
	int result=fscanf(fp, "%s\t%s\t%s\t%s\n", data.name, data.name, data.name, data.name);
	while (fscanf(fp, "%s\t%d\t%d\t%s\n", data.name, &data.age, &data.num, data.tel) != EOF) 
	{
		insertByHead(list, data);
	}
	fclose(fp);
}

//针对于链表文件写操作
void saveFile(struct Node* headNode, const char* fileURL) 
{
	FILE* fp = fopen(fileURL, "w");
	struct Node* pMove = headNode->next;
	//写入表头
	fprintf(fp, "%s\t%s\t%s\t%s\n", "姓名", "年龄", "编号", "电话");
	while (pMove != NULL) 
	{
		fprintf(fp, "%s\t%d\t%d\t%s\n", pMove->data.name,
			pMove->data.age,
			pMove->data.num,
			pMove->data.tel);
		pMove = pMove->next;
	}
	fclose(fp);
}


//用户交互
void makeMenu() 
{
	printf("--------------【MM管理系统】---------------\n");
	printf("\t\t0.退出系统\n");
	printf("\t\t1.录入信息\n");
	printf("\t\t2.浏览信息\n");
	printf("\t\t3.删除信息\n");
	printf("\t\t4.查找信息\n");
	printf("\t\t5.修改信息\n");
	printf("--------------------------------------------\n");
	printf("请输入你选择(0-5):");
}
void keyDown() 
{
	struct MM data;
	struct Node* result = NULL;
	int userKey = 0;
	scanf_s("%d", &userKey);   //增强版本的scanf
	switch (userKey) 
	{
	case 0:
		printf("退出成功!\n");
		system("pause");
		exit(0);
		break;
	case 1:
		printf("请输入美女信息(name,age,num,tel):");
		scanf("%s%d%d%s", data.name, &data.age, &data.num, data.tel);
		insertByHead(list, data);
		printf("录入成功!...\n");
		//保存到文件
		saveFile(list, "newMM.xls");
		break;
	case 2:
		printList(list);
		break;
	case 3:
		printf("请输入要删除的美女的姓名:");
		scanf_s("%s", data.name, 20);
		deleteByName(list, data.name);
		//保存到文件
		saveFile(list, "newMM.xls");
		break;
	case 4:
		printf("请输入要查找美女的编号:");
		scanf("%d", &data.num);
		result = searchByNum(list, data.num);
		if (result != NULL) 
		{
			printf("姓名\t年龄\t编号\t手机\n");
			printf("%s\t%d\t%d\t%s\n",
				result->data.name,
				result->data.age,
				result->data.num, 
				result->data.tel);
		}
		else 
		{
			printf("未找到相关信息!\n");
		}
		break;
	case 5:
		printf("请输入要修改小美女的编号:");
		scanf("%d", &data.num);
		result = searchByNum(list, data.num);
		if (result != NULL)
		{
			printf("请输入美女新的信息(name,age,num,tel):");
			scanf("%s%d%d%s",
				result->data.name,
				&result->data.age,
				&result->data.num,
				result->data.tel);
			//%s 从首地址开始 到\0
			//数组名: 数组的首地址
			//char array[10]; array: &array[0]
			printf("修改成功！\n");
			//保存到文件
			saveFile(list, "newMM.xls");
		}
		else
		{
			printf("未找到相关信息!无法修改\n");
		}
		break;
	default:
		printf("输入错误!..请重新输入\n");
		break;
	}
}
int main() 
{
	list = createHead();
	//运行的时候就需要读文件
	readFile(list, "newMM.xls");
	while (1) 
	{
		makeMenu();
		keyDown();
		system("pause");
		system("cls");
	}
	return 0;
}