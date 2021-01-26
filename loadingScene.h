#pragma once
#include "gameNode.h"
#include "progressBar.h"
#include <string>

#define LOADINGMAX 30
#define ADDF IMAGEMANAGER->addFrameImage
#define MGT RGB(255,0,255)

class progressBar;

class loadingScene : public gameNode
{
private:
	progressBar* _loadingBar;
	image* _background;

public:
	loadingScene();
	~loadingScene();

	int _currentCount;
	bool _loadingEnd;
	bool _soundLoaded; // ���带 �ε��ߴ���?
	string _soundName; // ����� �׳� �Ű������� �ؽ�Ʈ �Է�����..

	HRESULT init();
	void release();
	void update();
	void render();

	void chanhoInit();
	void deokhoInit();
	void hyunjeonghoInit();
	void yoonghoInit();
	void younghanInit();

	void imgLoaded();
	void soundLoaded();
};

static DWORD CALLBACK threadFunction(LPVOID lpParameter);
