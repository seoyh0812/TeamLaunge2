#include "stdafx.h"
#include "loadingScene.h"

void loadingScene::chanhoInit()
{
	IMAGEMANAGER->addFrameImage("��������", "image/unit/bishop/redBishopIdle.bmp", 400, 93, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�������̵�", "image/unit/bishop/redBishopWalk.bmp", 400, 744, 8, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��������", "image/unit/bishop/redBishopHeal.bmp", 220, 465, 4, 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����������", "image/unit/bishop/redBishopDead.bmp", 332, 59, 4, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("�������", "image/unit/bishop/blueBishopIdle.bmp", 400, 93, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("������̵�", "image/unit/bishop/blueBishopWalk.bmp", 400, 744, 8, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�������", "image/unit/bishop/blueBishopHeal.bmp", 220, 465, 4, 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���������", "image/unit/bishop/blueBishopDead.bmp", 332, 59, 4, 1, true, RGB(255, 0, 255));
}