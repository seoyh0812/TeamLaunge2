#include "stdafx.h"
#include "mainScene.h"

mainScene::mainScene()
{
}

mainScene::~mainScene()
{
}

HRESULT mainScene::init()
{
	CAMERAMANAGER->setCameraX(0);
	CAMERAMANAGER->setCameraY(0);
	_sm = new stageManager;
	_sm->init();
	_um = new unitManager;
	_um->init();
	_se = new skillNEffectManager;
	_se->init();
	_ia = new interaction;
	_ia->init();

	_ia->umLink(_um);
	_ia->smLink(_sm);
	_ia->seLink(_se);

	_um->createZergling(ENEMY, 300, 300);
	_um->createZergling(ENEMY, 400, 300);
	_um->createZergling(ENEMY, 200, 300);
	_um->createZergling(PLAYER, 210, 270);
	_um->createZergling(PLAYER, 310, 430);
	_um->createZergling(PLAYER, 270, 400);
	_um->createMarine(ENEMY, 200, 300);
	_um->createMarine(PLAYER, 210, 270);
	_um->createCivilian(ENEMY, 100, 300);
	_um->createCivilian(PLAYER, 110, 270);
	_se->createPsionic(S_PLAYER, 200, 200);

	_um->setLinkSm(_sm);								//유닛 매니저와 스테이지 매니저를 링크로 연결해줌

	for (int i = 0; i < TILEX*TILEY; ++i)
	{
		if (_sm->getTileObj()[i] == ZERGLING)
		{
			_um->createZergling(ENEMY, _sm->getIsoTile()[i].drawX + 10, _sm->getIsoTile()[i].drawY - 5);
		}
	}

	// 카메라 초기화입니당
	_camStartX = 0;
	_camStartY = WINSIZEY - WINSIZEY * 0.2;
	_camEndX = WINSIZEX * 0.1;
	_camEndY = WINSIZEY * 0.1;

	_miniMap = RectMake(0, WINSIZEY - WINSIZEY * 0.2, WINSIZEX * 0.2, WINSIZEY * 0.2);
	_camMap = RectMake(_camStartX, _camStartY, _camEndX, _camEndY);

	return S_OK;
}

void mainScene::release()
{
	_sm->release();
	_um->release();
	_se->release();
	_ia->release();
}

void mainScene::update()
{
	_sm->update();
	_um->update();
	_se->update();
	_ia->update();

	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
	{
		for (int i = 0; i < _um->getVUnit().size(); ++i)
		{
			_um->getVUnit()[i]->setState(DEAD);
		}
	}

	miniMap();

}

void mainScene::render()
{
	_sm->render();
	_ia->render();
	_um->render();
	_se->render();

	uiRender();

	Rectangle(getMemDC(), _miniMap);
	Rectangle(getMemDC(), _camMap);

}

void mainScene::miniMap()
{
	if (KEYMANAGER->isStayKeyDown(VK_UP) && _camMap.top > _miniMap.top)
	{
		OffsetRect(&_camMap, 0, -1);
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _camMap.bottom < _miniMap.bottom)
	{
		OffsetRect(&_camMap, 0, 1);
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _camMap.left > _miniMap.left)
	{
		OffsetRect(&_camMap, -1, 0);
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _camMap.right < _miniMap.right)
	{
		OffsetRect(&_camMap, 1, 0);
	}
}