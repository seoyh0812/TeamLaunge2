#include "stdafx.h"
#include "loadingScene.h"
#define ADDF IMAGEMANAGER->addFrameImage
#define MGT RGB(255,0,255)
void loadingScene::deokhoInit()
{
	ADDF("�����̵��Ķ�", "image/unit/Marine/Marine_Walk_Blue.bmp", 288, 256, 9, 8, true, MGT);
	ADDF("�����⺻�Ķ�", "image/unit/Marine/Marine_Walk_Blue.bmp", 32, 256, 1, 8, true, MGT);
	ADDF("���������Ķ�", "image/unit/Marine/Marine_Walk_Blue.bmp", 288, 288, 8, 8, true, MGT);
	ADDF("���������Ķ�", "image/unit/Marine/Marine_Walk_Blue.bmp", 472, 36, 8, 1, true, MGT);

	ADDF("�����̵�����", "image/unit/Marine/Marine_Walk_Red.bmp", 288, 256, 9, 8, true, MGT);
	ADDF("�����⺻����", "image/unit/Marine/Marine_Walk_Red.bmp", 32, 256, 1, 8, true, MGT);
	ADDF("�������ݻ���", "image/unit/Marine/Marine_Walk_Red.bmp", 288, 288, 8, 8, true, MGT);
	ADDF("������������", "image/unit/Marine/Marine_Walk_Red.bmp", 472, 36, 8, 1, true, MGT);
}