#include "stdafx.h"
#include "mainScene.h"


void mainScene::yoonghoUpdate()
{

	if (KEYMANAGER->isStayKeyDown(VK_UP) && CAMY > 0)
	{
		CAMERAMANAGER->setCameraY(CAMY - 5);
		if (CAMY < 0) CAMERAMANAGER->setCameraY(0);
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && CAMY < MAPSIZEY-WINSIZEY)
	{
		CAMERAMANAGER->setCameraY(CAMY + 5);
		if (CAMY > MAPSIZEY - WINSIZEY) CAMERAMANAGER->setCameraY(MAPSIZEY - WINSIZEY);
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && CAMX > 0)
	{
		CAMERAMANAGER->setCameraX(CAMX - 5);
		if (CAMX < 0) CAMERAMANAGER->setCameraX(0);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && CAMX < MAPSIZEX - WINSIZEX)
	{
		CAMERAMANAGER->setCameraX(CAMX + 5);
		if (CAMY > MAPSIZEX - WINSIZEX) CAMERAMANAGER->setCameraX(MAPSIZEX - WINSIZEX);
	}

	_camMap = RectMake(CAMX + 240*CAMX/MAPSIZEX, 580 + CAMY + 120* CAMY/MAPSIZEY, 240* 5.f / 8.f, 120 * 35.f / 48.f);
}