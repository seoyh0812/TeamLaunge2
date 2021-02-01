#pragma once
#include "gameNode.h"
class titleScene : public gameNode
{
private:

	image* _titleImage;
	image* _volumeSetImage;
	RECT _gameStart;
	RECT _mapTool;
	RECT _option;
	RECT _exit;
	RECT _volumeExit; 
	RECT _volumRect;
	POINT _point;

	RECT _testBgm;
	RECT _testEffect;

	RECT _bgmPlus;
	RECT _bgmBar;
	RECT _bgmMinus;
	RECT _effectPlus;
	RECT _effectBar;
	RECT _effectMinus;

	bool _isVolumeSetOn;
	bool _isStart;
	bool _isEnd;
	int _alpha; // ��ο����� ��������

public:
	titleScene();
	~titleScene();

	virtual HRESULT init();	//�ʱ�ȭ ���� �Լ�
	virtual void release();	//�޸� ���� �Լ�
	virtual void update();	//���� ����
	virtual void render();	//�׸��� ����

	RECT getGameStart() { return _gameStart; }
	RECT getMaptool() { return _mapTool; }
	RECT getOption() { return _option; }
	RECT getExit() { return _exit; }
};

