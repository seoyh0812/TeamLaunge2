#include "stdafx.h"
#include "stageManager.h"

stageManager::stageManager()
{
}

stageManager::~stageManager()
{
}

HRESULT stageManager::init()
{
	_stage = STAGE1;
	setStage(_stage);
	return S_OK;
}

void stageManager::release()
{
}

void stageManager::update()
{
}

void stageManager::render()
{
	for (int i = 0; i < TILEX * TILEY; ++i)
	{ // 각 타일마다 프레임대로 렌더
		IMAGEMANAGER->findImage("tile")->frameRender(getMemDC(),
			_tiles[i]._rc.left, _tiles[i]._rc.top, _tiles[i]._frameX, _tiles[i]._frameY);
	}
}

void stageManager::setStage(STAGE stage)
{
	HANDLE file;
	DWORD read;
	switch (stage)
	{
	case STAGE1:
		file = CreateFile("stage1.map", GENERIC_READ, NULL, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		ReadFile(file, _tiles, sizeof(tile) * TILEX*TILEY, &read, NULL);
		CloseHandle(file);
		break;
	case STAGE2:
		file = CreateFile("stage2.map", GENERIC_READ, NULL, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		ReadFile(file, _tiles, sizeof(tile) * TILEX*TILEY, &read, NULL);
		CloseHandle(file);
		break;
	}
}
