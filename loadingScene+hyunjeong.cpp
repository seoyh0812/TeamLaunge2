#include "stdafx.h"
#include "loadingScene.h"

void loadingScene::hyunjeonghoInit()
{
	IMAGEMANAGER->addImage("ü�¹ٵ�", "image/ui/progress_Bar/Hp_Bar_Blocked.bmp", 50, 6, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("�ʷ���", "image/ui/progress_Bar/full_Hp_Blocked.bmp", 50, 6, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("�����", "image/ui/progress_Bar/medium_Hp_Blocked.bmp", 50, 6, false, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addImage("������", "image/ui/progress_Bar/low_Hp_Blocked.bmp", 50, 6, false, RGB(255, 0, 255));
	imgLoaded();

	//################## ��ƺ�� ###################################################################
	IMAGEMANAGER->addFrameImage("��ƺ�� ����", "image/unit/diablo/Diablo_walk.bmp", 1631, 1352, 8, 8, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("��ƺ�� �ȱ�", "image/unit/diablo/Diablo_walk.bmp", 1631, 1352, 8, 8, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("��ƺ�� ��ȯ", "image/unit/diablo/Diablo_Summon.bmp", 2000, 2370, 8, 10, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("��ƺ�� ����", "image/unit/diablo/Diablo_Summon.bmp", 2000, 2370, 8, 10, true, RGB(255, 0, 255));
	imgLoaded();

	//################## �ذ񺴻� ###################################################################
	IMAGEMANAGER->addFrameImage("�ذ񺴻� ����", "image/unit/diablo_Bone/Bone_walk.bmp", 440, 220, 8, 4, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("�ذ񺴻� �ȱ�", "image/unit/diablo_Bone/Bone_walk.bmp", 440, 220, 8, 4, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("�ذ񺴻� ����", "image/unit/diablo_Bone/Bone_Attack.bmp", 400, 450, 8, 9, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("�ذ񺴻� ����", "image/unit/diablo_Bone/Bone_Dead.bmp", 640, 560, 8, 7, true, RGB(255, 0, 255));
	imgLoaded();
}