#include "stdafx.h"
#include "loadingScene.h"
#define ADDF IMAGEMANAGER->addFrameImage
#define MGT RGB(255,0,255)
#define ADDS SOUNDMANAGER->addSound
void loadingScene::deokhoInit()
{
	ADDS("������", "sound/BishopBirth.wav", false, false); 
	soundLoaded();
	ADDS("������", "sound/BishopAtk.wav", false, false);
	soundLoaded();
	ADDS("�����", "sound/BishopDie.wav", false, false);
	soundLoaded();

	ADDS("���۸�����", "sound/ZerglingBirth.wav", false, false);
	soundLoaded();
	ADDS("���۸�����", "sound/ZerglingAtk.wav", false, false);
	soundLoaded();
	ADDS("���۸�����", "sound/ZerglingDie.wav", false, false);
	soundLoaded();

	ADDS("��������", "sound/MarineBirth.wav", false, false);
	soundLoaded();
	ADDS("��������", "sound/MarineAtk.wav", false, false);
	soundLoaded();
	ADDS("�������", "sound/MarineDie.wav", false, false);
	soundLoaded();

	ADDS("���÷�����", "sound/TemplarBirth.wav", false, false);
	soundLoaded();
	ADDS("���÷����", "sound/TemplarDie.wav", false, false);
	soundLoaded();
	ADDS("���÷�����", "sound/TemplarAtk.wav", false, false);
	soundLoaded();

	ADDS("��׷θǻ���", "sound/CivilianBirth.wav", false, false);
	soundLoaded();
	ADDS("��׷θǻ��", "sound/CivilianDie.wav", false, false);
	soundLoaded();
	ADDS("��׷θǰ���", "sound/CivilianAtk.wav", false, false);
	soundLoaded();

	ADDS("��Ʈ����", "sound/GhostBirth.wav", false, false);
	soundLoaded();
	ADDS("��Ʈ����", "sound/GhostAtk.wav", false, false);
	soundLoaded();
	ADDS("��Ʈ���", "sound/GhostDie.wav", false, false);
	soundLoaded();

	ADDS("��ƺ�λ���", "sound/DiabloBirth.wav", false, false);
	soundLoaded();
	ADDS("��ƺ�ΰ���", "sound/DiabloAtk.wav", false, false);
	soundLoaded();
	ADDS("��ƺ�λ��", "sound/DiabloDie.wav", false, false);
	soundLoaded();

	ADDS("�ذ񺴻����", "sound/SkeletonBirth.wav", false, false);
	soundLoaded();
	ADDS("�ذ񺴻���", "sound/SkeletonDie.wav", false, false);
	soundLoaded();

	ADDS("�������", "sound/SkeletonDie.wav", false, false);
	soundLoaded();


	ADDF("�����̵��Ķ�", "image/unit/Marine/Marine_Walk_Blue.bmp", 288, 256, 9, 8, true, MGT);
	imgLoaded();
	ADDF("�����⺻�Ķ�", "image/unit/Marine/Marine_Idle_Blue.bmp", 32, 256, 1, 8, true, MGT);
	imgLoaded();
	ADDF("���������Ķ�", "image/unit/Marine/Marine_Attack_Blue.bmp", 288, 288, 8, 8, true, MGT);
	imgLoaded();
	ADDF("���������Ķ�", "image/unit/Marine/Marine_Dead_Blue.bmp", 472, 36, 8, 1, true, MGT);
	imgLoaded();
	ADDF("�����̵�����", "image/unit/Marine/Marine_Walk_Red.bmp", 288, 256, 9, 8, true, MGT);
	imgLoaded();
	ADDF("�����⺻����", "image/unit/Marine/Marine_Idle_Red.bmp", 32, 256, 1, 8, true, MGT);
	imgLoaded();
	ADDF("�������ݻ���", "image/unit/Marine/Marine_Attack_Red.bmp", 288, 288, 8, 8, true, MGT);
	imgLoaded();
	ADDF("������������", "image/unit/Marine/Marine_Dead_Red.bmp", 472, 36, 8, 1, true, MGT);
	imgLoaded();
}