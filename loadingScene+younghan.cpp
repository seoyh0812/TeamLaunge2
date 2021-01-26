#include "stdafx.h"
#include "loadingScene.h"

void loadingScene::younghanInit()
{
	//이미지 영역
	IMAGEMANAGER->addFrameImage("mapTiles", "image/maptool/tile512x384.bmp", 0, 0, 512, 384, 8, 12, true, RGB(255, 0, 255));
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
	IMAGEMANAGER->addImage("tileMenu", "image/maptool/tilemenu.bmp", 522, 394, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("open", "image/maptool/open.bmp", 64, 32, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("close", "image/maptool/close.bmp", 64, 32, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("small", "image/maptool/10x10.bmp", 64, 32, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("medium", "image/maptool/20x20.bmp", 64, 32, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("max", "image/maptool/max.bmp", 64, 32, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("leftBt", "image/maptool/left.bmp", 32, 32, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("rightBt", "image/maptool/right.bmp", 32, 32, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("tree", "image/maptool/tree.bmp", 107, 113, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("objDel", "image/maptool/objdel.bmp", 64, 32, false, RGB(255, 0, 255));
	imgLoaded();
}

