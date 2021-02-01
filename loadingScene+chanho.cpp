#include "stdafx.h"
#include "loadingScene.h"

void loadingScene::chanhoInit()
{
	IMAGEMANAGER->addFrameImage("��������", "image/unit/bishop/redBishopIdle.bmp", 100, 24, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�������̵�", "image/unit/bishop/redBishopWalk.bmp", 100, 186, 8, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��������", "image/unit/bishop/redBishopHeal.bmp", 55, 117, 4, 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����������", "image/unit/bishop/redBishopDead.bmp", 83, 15, 4, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("��������", "image/unit/bishop/blueBishopIdle.bmp", 100, 24, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�������̵�", "image/unit/bishop/blueBishopWalk.bmp", 100, 186, 8, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��������", "image/unit/bishop/blueBishopHeal.bmp", 55, 117, 4, 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����������", "image/unit/bishop/blueBishopDead.bmp", 83, 15, 4, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("��", "image/sne/healEffect.bmp", 2016, 96, 21, 1, true, RGB(255, 0, 255));
}