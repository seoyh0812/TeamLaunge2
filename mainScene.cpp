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
	_um->createZergling(PLAYER, 310, 430);
	_um->createZergling(PLAYER, 270, 400);
	_se->createPsionic(S_PLAYER, 200, 200);
	SOUNDMANAGER->play("사운드추가예시");

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
}

void mainScene::render()
{
	_sm->render();
	_ia->render();
	_um->render();
	_se->render();

	uiRender();
}

