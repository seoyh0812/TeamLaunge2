#include "stdafx.h"
#include "loadingScene.h"

void loadingScene::yoonghoInit()
{ // �ε�尡 ���ĸ� �ε��� �ø���� �Լ�. �̹��� �߰��ҋ����� �־��ֱ�	

	SOUNDMANAGER->addSound("�����߰�����", "PTeSto00.wav", false, false);
	soundLoaded();

	IMAGEMANAGER->addFrameImage("tile", "isoprac.bmp", 448, 32, 7, 1, true, RGB(255, 0, 255));
	imgLoaded();	
	IMAGEMANAGER->addImage("�ε����", "���׿��극����ε�.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("���۸��̵����", "image/unit/zergling/zerglingwalkblue.bmp", 320, 273, 8, 7, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("���۸��̵�����", "image/unit/zergling/zerglingwalk.bmp", 320, 273, 8, 7, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("���۸����ݺ��", "image/unit/zergling/zerglingattackblue.bmp", 320, 195, 8, 5, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("���۸���������", "image/unit/zergling/zerglingattack.bmp", 320, 195, 8, 5, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("���۸�����", "image/unit/zergling/zerglingdead.bmp", 455, 53, 7, 1, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("���̿��н���", "image/sne/psionic.bmp", 2590, 150, 14, 1, true, RGB(255, 0, 255));
	imgLoaded();
}