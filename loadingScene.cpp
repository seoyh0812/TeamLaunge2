#include "stdafx.h"
#include "loadingScene.h"

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
	_loadingSkip = 0;
	CAMERAMANAGER->setCameraX(0);
	CAMERAMANAGER->setCameraY(0);
	_loadingBar = new progressBar;
	_loadingBar->init(0, WINSIZEY / 2 - 50, WINSIZEX, 50);
	_loadingBar->setGauge(0, 0);
	_background = IMAGEMANAGER->addImage("로딩배경", "image/titleTemp.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));


	//쓰레드를 사용해보자
	CreateThread(
		NULL,			
		NULL,			
		threadFunction,	
		this,			
		NULL,			
		NULL			
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

	if (KEYMANAGER->isStayKeyDown(VK_F1) && !_loadingSkip)
	{
		_loadingSkip = true;
	}
	//로딩이 다 되면
	if (_loadingEnd)
	{
		SCENEMANAGER->changeScene("타이틀씬");
	}
}

void loadingScene::render()
{
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
	TextOut(getMemDC(), 0, WINSIZEY -70, cstr, strlen(cstr));
	sprintf_s(cstr, "진행상황 : %d/%d", _currentCount, LOADINGMAX);
	TextOut(getMemDC(), 0, WINSIZEY - 55, cstr, strlen(cstr));
	sprintf_s(cstr, "로딩스킵 : F1버튼");
	TextOut(getMemDC(), 0, WINSIZEY - 40, cstr, strlen(cstr));
}


DWORD CALLBACK threadFunction(LPVOID lpParameter)
{
	//여기에다가
	//이미지매니저나, 사운드 매니저 써서
	//add 해주면 된다.
	loadingScene* loadingHelper = (loadingScene*)lpParameter;

	loadingHelper->chanhoInit();
	loadingHelper->deokhoInit();
	loadingHelper->hyunjeonghoInit();
	loadingHelper->yoonghoInit();
	loadingHelper->younghanInit();


	//Sleep(1000);

	// 로딩 완료시
	loadingHelper->_loadingEnd = true;
	return 0;
}

void loadingScene::imgLoaded()
{
	_soundLoaded = false;
	++_currentCount;
	if (!_loadingSkip) Sleep(30);
}

void loadingScene::soundLoaded()
{
	_soundLoaded = true;
	++_currentCount;
	if (!_loadingSkip) Sleep(30);
}
