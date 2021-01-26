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
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		_stage = STAGE1;
		setStage(_stage);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		_stage = STAGE2;
		setStage(_stage);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F3))
	{
		_stage = STAGE3;
		setStage(_stage);
	}
}

void stageManager::render()
{
	for (int i = 0; i < TILEX * TILEY; ++i)
	{ // 각 타일마다 프레임대로 렌더
		IMAGEMANAGER->findImage("mapTiles")->frameRender(getMemDC(), _isoTile[i].drawX, _isoTile[i].drawY, _isoTile[i].fX, _isoTile[i].fY);
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
		ReadFile(file, _isoTile, sizeof(isoTile) * TILEX*TILEY, &read, NULL);
		memset(_sMove, 0, sizeof(STAGEMOVE) * TILEX * TILEY);
		for (int i = 0; i < TILEX * TILEY; ++i)
		{
			if (_isoTile[i].MUM == UNMOVE) _sMove[i] = S_UNMOVE;
		}
		CloseHandle(file);
		break;
	case STAGE2:
		file = CreateFile("stage2.map", GENERIC_READ, NULL, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		ReadFile(file, _isoTile, sizeof(isoTile) * TILEX*TILEY, &read, NULL);
		memset(_sMove, 0, sizeof(STAGEMOVE) * TILEX * TILEY);
		for (int i = 0; i < TILEX * TILEY; ++i)
		{
			if (_isoTile[i].MUM == UNMOVE) _sMove[i] = S_UNMOVE;
		}
		CloseHandle(file);
		break;
	case STAGE3:
		file = CreateFile("stage3.map", GENERIC_READ, NULL, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		ReadFile(file, _isoTile, sizeof(isoTile) * TILEX*TILEY, &read, NULL);
		memset(_sMove, 0, sizeof(STAGEMOVE) * TILEX * TILEY);
		for (int i = 0; i < TILEX * TILEY; ++i)
		{
			if (_isoTile[i].MUM == UNMOVE) _sMove[i] = S_UNMOVE;
		}
		CloseHandle(file);
		break;
	}
}
