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
}