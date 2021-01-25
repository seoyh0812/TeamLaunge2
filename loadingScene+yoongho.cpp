#include "stdafx.h"
#include "loadingScene.h"

void loadingScene::yoonghoInit()
{ // 로디드가 뭐냐면 로딩바 올리기용 함수. 이미지 추가할떄마다 넣어주길	

	SOUNDMANAGER->addSound("사운드추가예시", "PTeSto00.wav", false, false);
	soundLoaded();

	IMAGEMANAGER->addFrameImage("tile", "isoprac.bmp", 448, 32, 7, 1, true, RGB(255, 0, 255));
	imgLoaded();	
	IMAGEMANAGER->addImage("로딩배경", "리그오브레전드로딩.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("저글링이동블루", "image/unit/zergling/zerglingwalkblue.bmp", 320, 273, 8, 7, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("저글링이동퍼플", "image/unit/zergling/zerglingwalk.bmp", 320, 273, 8, 7, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("저글링공격블루", "image/unit/zergling/zerglingattackblue.bmp", 320, 195, 8, 5, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("저글링공격퍼플", "image/unit/zergling/zerglingattack.bmp", 320, 195, 8, 5, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("저글링죽음", "image/unit/zergling/zerglingdead.bmp", 455, 53, 7, 1, true, RGB(255, 0, 255));
	imgLoaded();
	IMAGEMANAGER->addFrameImage("사이오닉스톰", "image/sne/psionic.bmp", 2590, 150, 14, 1, true, RGB(255, 0, 255));
	imgLoaded();
}