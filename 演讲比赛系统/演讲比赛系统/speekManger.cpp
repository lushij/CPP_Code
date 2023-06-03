#include "speekManger.h"

speekManger::speekManger()
{
	//������֤Ϊ��
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();
	//��ʼ����������
	this->m_Index = 1;
}

void speekManger::initMenu()
{
	cout <<"***********************************************" << endl;
	cout <<"************* ��ӭ�μ��ݽ����� ****************" << endl;
	cout <<"************* 1.��ʼ�ݽ����� ******************" << endl;
	cout <<"************* 2.�鿴�����¼ ******************" << endl;
	cout <<"************* 3.��ձ�����¼ ******************" << endl;
	cout <<"************* 0.�˳��������� ******************" << endl;
	cout <<"***********************************************" << endl;
	cout << endl;
}

void speekManger::startSystem()
{
}

void speekManger::createSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "ѡ��";
		name += nameSeed[i];
		Speaker sp;
		sp.name = name;
		for (int i = 0; i < 2; i++)
		{
			sp.Score[i] = 0;
		}
		//12��ѡ�ֱ��
		this->v1.push_back(i + 10001);
		//ѡ�ֱ�� �Լ���Ӧ��ѡ�� ��ŵ�map������
		this->m_Speaker.insert(make_pair(i + 10001, sp));
	}
}

void speekManger::exitSystem()
{
	cout << "�˳��ɹ�" << endl;
	cout << "��ӭ�´�ʹ��" << endl;
	exit(0);
}

speekManger::~speekManger()
{
}
