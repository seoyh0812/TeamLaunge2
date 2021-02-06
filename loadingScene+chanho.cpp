#include "stdafx.h"
#include "loadingScene.h"

void loadingScene::chanhoInit()
{
	IMAGEMANAGER->addFrameImage("��������", "image/unit/bishop/redBishopIdle.bmp", 104, 24, 8, 1, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("�������̵�", "image/unit/bishop/redBishopWalk.bmp", 104, 184, 8, 8, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("��������", "image/unit/bishop/redBishopHeal.bmp", 56, 115, 4, 5, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("����������", "image/unit/bishop/redBishopDead.bmp", 84, 15, 4, 1, true, RGB(255, 0, 255));
	imgLoaded();

	IMAGEMANAGER->addFrameImage("�������", "image/unit/bishop/blueBishopIdle.bmp", 104, 24, 8, 1, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("������̵�", "image/unit/bishop/blueBishopWalk.bmp", 104, 184, 8, 8, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("�������", "image/unit/bishop/blueBishopHeal.bmp", 56, 115, 4, 5, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("���������", "image/unit/bishop/blueBishopDead.bmp", 84, 15, 4, 1, true, RGB(255, 0, 255));
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

    IMAGEMANAGER->addFrameImage("��������", "image/unit/naruto/narutoIdle.bmp", 128, 128, 8, 4, true, RGB(255, 0, 255));
    imgLoaded();
    IMAGEMANAGER->addFrameImage("�������̵�", "image/unit/naruto/narutoWalk.bmp", 192, 256, 8, 8, true, RGB(255, 0, 255));
    imgLoaded();
    IMAGEMANAGER->addFrameImage("���������", "image/unit/naruto/narutoAttack.bmp", 256, 288, 8, 9, true, RGB(255, 0, 255));
    imgLoaded();
    IMAGEMANAGER->addFrameImage("����������", "image/unit/naruto/narutoDead.bmp", 128, 80, 4, 4, true, RGB(255, 0, 255));
    imgLoaded();

	IMAGEMANAGER->addFrameImage("��", "image/sne/healEffect.bmp", 2016, 96, 21, 1, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("��", "image/sne/fireEffect.bmp", 288, 32, 9, 1, true, RGB(255, 0, 255));
	imgLoaded();
    IMAGEMANAGER->addFrameImage("����ȯ", "image/sne/narutoEffect.bmp", 1216, 64, 19, 1, true, RGB(255, 0, 255));
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