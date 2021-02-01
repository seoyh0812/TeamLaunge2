#pragma once
#include "singletonBase.h"
#include <string>
#include <map>

class gameNode;

class sceneManager : public singletonBase<sceneManager>
{
public:
	typedef map<string, gameNode*> mapSceneList;
	typedef map<string, gameNode*>::iterator mapSceneIter;

private:
	static gameNode* _currentScene;

	mapSceneList _mSceneList;

	int _alpha;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	//���߰� �Լ�
	gameNode* addScene(string sceneName, gameNode* scene);
	int getAlpha() { return _alpha; }

	//�� ���� �Լ�
	HRESULT changeScene(string sceneName);

	bool getMinimapScene(); // �̴ϸ��� �׷����ϴ� ������?

	sceneManager() {};
	~sceneManager() {};
};

