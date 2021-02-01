#pragma once
#include "gameNode.h"
class titleScene : public gameNode
{
private:

	image* _image;
	RECT _gameStart;
	RECT _mapTool;
	RECT _option;
	RECT _exit;
	POINT _point;

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

