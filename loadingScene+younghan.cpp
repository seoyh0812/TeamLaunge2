#include "stdafx.h"
#include "loadingScene.h"

void loadingScene::younghanInit()
{
	//이미지 영역
	IMAGEMANAGER->addFrameImage("mapTiles", "image/maptool/iso256X160.bmp", 0, 0, 256, 160, 4, 5, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("save1", "image/maptool/save1.bmp", 64, 32, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("save2", "image/maptool/save2.bmp", 64, 32, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("save3", "image/maptool/save3.bmp", 64, 32, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("load1", "image/maptool/load1.bmp", 64, 32, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("load2", "image/maptool/load2.bmp", 64, 32, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("load3", "image/maptool/load3.bmp", 64, 32, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("move", "image/maptool/move.bmp", 64, 32, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("unmove", "image/maptool/unmove.bmp", 64, 32, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("undo", "image/maptool/undo.bmp", 64, 32, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("fill", "image/maptool/fill.bmp", 64, 32, false, RGB(255, 0, 255));
	imgLoaded();
}

