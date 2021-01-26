#include "stdafx.h"
#include "playGround.h"

playGround::playGround()
{
}


playGround::~playGround()
{
}

HRESULT playGround::init()
{
	gameNode::init(true);

	_x = _y = 0;

	SCENEMANAGER->addScene("로딩씬", new loadingScene);
	SCENEMANAGER->addScene("메인씬", new mainScene);
	SCENEMANAGER->addScene("맵툴", new mapTool);
	SCENEMANAGER->addScene("타이틀씬", new titleScene);
	SCENEMANAGER->addScene("엔딩씬", new endingScene);

	SCENEMANAGER->changeScene("로딩씬");

	
	return S_OK;
}


void playGround::release()
{
	gameNode::release();

	
}

void playGround::update()
{
	gameNode::update();

	SCENEMANAGER->update();
	
}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, CAMX+WINSIZEX, CAMY + WINSIZEY, WHITENESS);
	//================ 위에 건들지 마라 ==============================

	SCENEMANAGER->render();
	if (KEYMANAGER->isToggleKey(VK_TAB)) TIMEMANAGER->render(getMemDC(), CAMX, CAMY);
	//================= 아래도 건들지 마라 ==============================
	_backBuffer->render(getHDC(), 0, 0, CAMX, CAMY, WINSIZEX, WINSIZEY);
}