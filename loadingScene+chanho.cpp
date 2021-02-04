#include "stdafx.h"
#include "loadingScene.h"

void loadingScene::chanhoInit()
{
	IMAGEMANAGER->addFrameImage("��������", "image/unit/bishop/redBishopIdle.bmp", 100, 24, 8, 1, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("�������̵�", "image/unit/bishop/redBishopWalk.bmp", 100, 186, 8, 8, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("��������", "image/unit/bishop/redBishopHeal.bmp", 55, 117, 4, 5, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("����������", "image/unit/bishop/redBishopDead.bmp", 83, 15, 4, 1, true, RGB(255, 0, 255));
	imgLoaded();

	IMAGEMANAGER->addFrameImage("�������", "image/unit/bishop/blueBishopIdle.bmp", 100, 24, 8, 1, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("������̵�", "image/unit/bishop/blueBishopWalk.bmp", 100, 186, 8, 8, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("�������", "image/unit/bishop/blueBishopHeal.bmp", 55, 117, 4, 5, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("���������", "image/unit/bishop/blueBishopDead.bmp", 83, 15, 4, 1, true, RGB(255, 0, 255));
	imgLoaded();

	IMAGEMANAGER->addFrameImage("����巡����", "image/unit/dragon/redDragonIdle.bmp", 336, 40, 8, 1, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("����巡���̵�", "image/unit/dragon/redDragonFly.bmp", 344, 80, 8, 2, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("����巡�����", "image/unit/dragon/redDragonAttack.bmp", 344, 80, 8, 2, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("����巡������", "image/unit/dragon/redDragonDead.bmp", 344, 40, 8, 1, true, RGB(255, 0, 255));
	imgLoaded();

	IMAGEMANAGER->addFrameImage("���巡����", "image/unit/dragon/blueDragonIdle.bmp", 336, 40, 8, 1, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("���巡���̵�", "image/unit/dragon/blueDragonFly.bmp", 344, 80, 8, 2, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("���巡�����", "image/unit/dragon/blueDragonAttack.bmp", 344, 80, 8, 2, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("���巡������", "image/unit/dragon/blueDragonDead.bmp", 344, 40, 8, 1, true, RGB(255, 0, 255));
	imgLoaded();

	IMAGEMANAGER->addFrameImage("��", "image/sne/healEffect.bmp", 2016, 96, 21, 1, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("��", "image/sne/fireEffect.bmp", 288, 32, 9, 1, true, RGB(255, 0, 255));
	imgLoaded();

	IMAGEMANAGER->addFrameImage("��", "image/sne/fireEffect.bmp", 288, 32, 9, 1, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("��", "image/sne/fireEffect.bmp", 288, 32, 9, 1, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("��", "image/sne/fireEffect.bmp", 288, 32, 9, 1, true, RGB(255, 0, 255));
	imgLoaded();

	IMAGEMANAGER->addImage("����", "image/stage/jungle.bmp", 1920, 960, false, RGB(0, 0, 0));
	imgLoaded();
	IMAGEMANAGER->addImage("����", "image/stage/cyberSpace.bmp", 1920, 960, false, RGB(0, 0, 0));
	imgLoaded();
	IMAGEMANAGER->addImage("����", "image/stage/snowMountain.bmp", 1920, 960, false, RGB(0, 0, 0));
	imgLoaded();
	IMAGEMANAGER->addImage("����", "image/stage/space.bmp", 1920, 960, false, RGB(0, 0, 0));
	imgLoaded();
	IMAGEMANAGER->addImage("ȭ��", "image/stage/volcano.bmp", 1920, 960, false, RGB(0, 0, 0));
	imgLoaded();
	IMAGEMANAGER->addImage("�縷", "image/stage/wilderness.bmp", 1920, 960, false, RGB(0, 0, 0));
	imgLoaded();
}