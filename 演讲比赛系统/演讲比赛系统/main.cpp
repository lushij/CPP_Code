#include"speekManger.h"
int main()
{
	speekManger sm;
	
	int choice = 0; //�����洢�û���ѡ��
	while (true)
	{
		sm.initMenu();
		cout << "����������ѡ�� " << endl;
		cin >> choice; // �����û���ѡ��
		switch (choice)
		{
		case 1: //��ʼ����
			sm.startSystem();
			break;
		case 2: //�鿴��¼
			break;
		case 3: //��ռ�¼
			break;
		case 0: //�˳�ϵͳ
			sm.exitSystem();
			break;
		}
	}
	system("pause");
	return 0;
}
