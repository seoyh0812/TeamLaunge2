#include "stdafx.h"
#include "loadingScene.h"

//���ҽ� ���� ��ƸԴ� �������� �׸�����.. 3d�𵨸�����
//�̱���->�޸� ���ֽ�Ű�°�.
//�޸� �����ϸ� �װ� �ε��̾�

loadingScene::loadingScene()
	: _background(nullptr), _loadingBar(nullptr),
	_currentCount(0), _loadingEnd(0), _soundLoaded(0)
{
}


loadingScene::~loadingScene()
{
}

HRESULT loadingScene::init()
{
	CAMERAMANAGER->setCameraX(0);
	CAMERAMANAGER->setCameraY(0);
	_loadingBar = new progressBar;
	_loadingBar->init(0, WINSIZEY / 2 - 50, WINSIZEX, 50);
	_loadingBar->setGauge(0, 0);
	_background = IMAGEMANAGER->addImage("�ε����", "image/titleTemp.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));


	//�����带 ����غ���
	CreateThread(
		NULL,				//�������� ���ȼӼ�(�ڽ������찡 �����Ҷ�)
		NULL,				//�������� ����ũ��(NULL�� �θ� ���ξ����� ũ��� ����)
		threadFunction,		//������ ����� �Լ� ��
		this,				//������ �Ű�����(this�� �θ� �� Ŭ����)
		NULL,				//�������� Ư��(��ٸ���, �ٷ� ����(NULL�̸� ��� �ش�))
		NULL				//������ ���� �� �������� ID �Ѱ��� ������ NULL�� �д�
	);

	return S_OK;
}

void loadingScene::release()
{
	SAFE_DELETE(_loadingBar);
}

void loadingScene::update()
{
	_loadingBar->update();
	_loadingBar->setGauge(_currentCount, LOADINGMAX);

	//�ε��� �� �Ǹ�
	if (_loadingEnd)
	{
		SCENEMANAGER->changeScene("Ÿ��Ʋ��");
	}
}

void loadingScene::render()
{
	//�׸����� �̹��� ��θ� �ؽ�Ʈ�� �����൵ �ǰ�


	_background->render(getMemDC());
	_loadingBar->render();
	char cstr[128];
	ZeroMemory(cstr, 126);
	if (!_soundLoaded)
	{
		strcpy_s(cstr, IMAGEMANAGER->getLoading().c_str());
	}
	else
	{
		strcpy_s(cstr, SOUNDMANAGER->getLatestAdded().c_str());
	}
	TextOut(getMemDC(), 0, WINSIZEY -50, cstr, strlen(cstr));
}


DWORD CALLBACK threadFunction(LPVOID lpParameter)
{
	//���⿡�ٰ�
	//�̹����Ŵ�����, ���� �Ŵ��� �Ἥ
	//add ���ָ� �ȴ�.
	loadingScene* loadingHelper = (loadingScene*)lpParameter;



	//while (loadingHelper->_currentCount != LOADINGMAX)
	//{
	//	IMAGEMANAGER->addImage("�ΰ���", "����ȭ��.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	//	IMAGEMANAGER->addImage("�ε����", "���׿��극����ε�.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	//	//���⿡ ���Ϲ� ���������� �̹����� ���� �� ���ҽ� ���� �߰��ض�

	//	//CPU ��� �����Ŵ°ǵ�
	//	//�̰� �Ȱɸ� �ʹ� �������� �� �����̸� �Ѿ���� (1000������)
	//	Sleep(1);
	//	loadingHelper->_currentCount++;
	//}

	loadingHelper->chanhoInit();
	loadingHelper->deokhoInit();
	loadingHelper->hyunjeonghoInit();
	loadingHelper->yoonghoInit();
	loadingHelper->younghanInit();


	// �ε� �Ϸ��
	loadingHelper->_loadingEnd = true;

	return 0;
}

void loadingScene::imgLoaded()
{
	_soundLoaded = false;
	++_currentCount;
	Sleep(20);
}

void loadingScene::soundLoaded()
{
	_soundLoaded = true;
	++_currentCount;
	Sleep(20);
}
