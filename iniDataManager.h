#pragma once
#include "singletonBase.h"
#include <vector>

using namespace std;

struct tagIniData
{
	const char* subject;	//�׸�   ����
	const char* title;		//����   ����
	const char* body;		//��     100
};

class iniDataManager : public singletonBase<iniDataManager>
{
private:
	typedef vector<tagIniData>				arrIniData;
	typedef vector<tagIniData>::iterator	arrIniDataIter;

	typedef vector<arrIniData>				arrIniDatas;
	typedef vector<arrIniData>::iterator	arrIniDatasIter;

private:
	arrIniDatas _vIniData;


public:
	iniDataManager();
	~iniDataManager();

	HRESULT init();
	
	//������ �߰� �Լ�
	void addData(const char* subject, const char* title, const char* body);
	//ini���� ������ִ� �Լ�
	void iniSave(const char* fileName);

	//���ڿ� ������ �ҷ����� �Լ�
	string loadDataString(const char* fileName, const char* subject, const char* title);

	//���� ������ �ҷ����� �Լ�
	int loadDataInterger(const char* fileName, const char* subject, const char* title);

};

