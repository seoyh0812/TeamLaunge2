#include "stdafx.h"
#include "endingScene.h"

endingScene::endingScene()
{
}

endingScene::~endingScene()
{
}

HRESULT endingScene::init()
{
	CAMERAMANAGER->setCameraX(0);
	CAMERAMANAGER->setCameraY(0);
	return S_OK;
}

void endingScene::release()
{
}

void endingScene::update()
{
	TextOut(getMemDC(), 500, 300, "���丮!", strlen("���丮!"));
}

void endingScene::render()
{
}
