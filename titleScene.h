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
	bool _isVolumeSetOn;

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

