#include "stdafx.h"
#include "interaction.h"

vector<int> interaction::aStarPath(int fromTileNum, int toTileNum)
{
	_path.clear();
	_vTotalList.clear();
	_vOpenList.clear();
	_vCloseList.clear();
	for (int i = 0; i < 900; ++i)
	{
		tagAStarTile* aStarTile = new tagAStarTile;
		aStarTile->tileNum = i;
		aStarTile->parentNodeTileNum = -1;
		aStarTile->totalCost = 0;
		aStarTile->costFromStart = 0;
		aStarTile->costToGoal = 0;
		aStarTile->isOpen = true;
		_vTotalList.push_back(aStarTile);
	}
	_stop = 0;
	_startTile = fromTileNum;
	_endTile = toTileNum;
	_currentTile = _startTile;
	pathFinder(_currentTile);
	
	return _path;
}

// #############################################################

vector<tagAStarTile*> interaction::addOpenList(int currentTile)
{
	int startX = currentTile % 30 - 1;
	int startY = currentTile / 30 - 1;

	for (int i = 0; i < 3; ++i)
	{
		//// ############ ���� �������� #####################
		if (startY + i < 0)			continue;
		if (startY + i >= 30)		continue;
		for (int j = 0; j < 3; ++j)
		{
			if (startX + j < 0)		continue;
			if (startX + j >= 30)	continue;

			int checkIndex = (startY+i) * 30 + (startX + j);
			tagAStarTile* aStarTile = _vTotalList[checkIndex];
			
			//����ó��!
			if (!aStarTile->isOpen) continue;
			if (_sm->getIsoTile()[checkIndex].MUM == UNMOVE) continue;
			if (checkIndex == _startTile) continue;

			// ##################���� ����#############################
			moveUnMove nodeTop;
			if (startY < 0)				nodeTop = UNMOVE;
			else nodeTop = _sm->getIsoTile()[(startY * 30) + startX + 1].MUM;
			// ������������ �������� ������ ���� �������� i==0�� i==2�Ʒ� j==0�� j==2����
			if (i == 0 && nodeTop == UNMOVE)	continue;
			moveUnMove nodeBottom;
			if (startY + 2 >= 30)	nodeBottom = UNMOVE;
			else nodeBottom = _sm->getIsoTile()[(startY * 30) + startX + 61].MUM;
			// �Ʒ����������� ���ʾƷ��� ������ �Ʒ��� ��������
			if (i == 2 && nodeBottom == UNMOVE)	continue;
			moveUnMove nodeLeft;
			if (startX < 0)				nodeLeft = UNMOVE;
			else nodeLeft = _sm->getIsoTile()[(startY * 30) + startX + 30].MUM;
			// ���ʸ��������� �������� ���ʾƷ��� ��������
			if (j == 0 && nodeLeft == UNMOVE)	continue;
			moveUnMove nodeRight;
			if (startX + 2 >= 30)	nodeRight = UNMOVE;
			else nodeRight = _sm->getIsoTile()[(startY * 30) + startX + 32].MUM;
			// �����ʸ��������� ���������� ������ �Ʒ��� ��������
			if (j == 2 && nodeRight == UNMOVE)	continue;


			//���� Ÿ���� ��� �������ش�
			aStarTile->parentNodeTileNum = _currentTile;

			bool addObj = true;
			for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
			{
				if (*_viOpenList == aStarTile)
				{ // �ִ°Ÿ� �߰�����
					addObj = false;
					break;
				}
			}
			if (!addObj) continue;

			_vOpenList.push_back(aStarTile);
		}
	}

	return _vOpenList;
}

void interaction::pathFinder(int currentTile)
{
	//��κ���� �ſ� ���� �ϱ� ���ؼ� ������ ��κ���� ��
	int tempTotalCost = 5000;
	tagAStarTile* tempTile = nullptr;

	bool changed = false;

	//���� �ִ� ���� ���� ���� ���ο��� ���� ���� ��θ� �̾ƾ��Ѵ�
	for (int i = 0; i < addOpenList(currentTile).size(); ++i)
	{ // ���⼭ �ֺ����� ������ ���ÿ� �������� �ѿ��¸���Ʈ�� �������°�
		_vOpenList[i]->costToGoal = (abs(_endTile%30 - _vOpenList[i]->tileNum%30) +
				abs(_endTile/30 - _vOpenList[i]->tileNum / 30)) * 11;
		
		int cost;

		if (_vOpenList[i]->tileNum + 1 == _vOpenList[i]->parentNodeTileNum
			|| _vOpenList[i]->tileNum - 1 == _vOpenList[i]->parentNodeTileNum
			|| _vOpenList[i]->tileNum + 30 == _vOpenList[i]->parentNodeTileNum
			|| _vOpenList[i]->tileNum - 30 == _vOpenList[i]->parentNodeTileNum) cost = 11;
		else if (_vOpenList[i]->tileNum + 31 == _vOpenList[i]->parentNodeTileNum
			|| _vOpenList[i]->tileNum - 31 == _vOpenList[i]->parentNodeTileNum) cost = 10;
		else if (_vOpenList[i]->tileNum + 29 == _vOpenList[i]->parentNodeTileNum
			|| _vOpenList[i]->tileNum - 29 == _vOpenList[i]->parentNodeTileNum) cost = 20;

		_vOpenList[i]->costFromStart = cost;

		//F = G + H �ϱ�~ 
		_vOpenList[i]->totalCost = _vOpenList[i]->costToGoal + _vOpenList[i]->costFromStart;

		//��κ��(F)�� ���� ���� �ַ� ��� �������ش�
		if (tempTotalCost > _vOpenList[i]->totalCost)
		{
			tempTotalCost = _vOpenList[i]->totalCost;
			tempTile = _vOpenList[i];
		} // ��������Ʈ�� ��κ�� ���������ְ� Ž���Ǿ� ����Ÿ�Ϸ� ����

		bool addObj = true;
		for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
		{
			if (*_viOpenList == tempTile)
			{ // ��������Ʈ�� ����Ÿ���� �ִٸ� -> ���� ��������߿����� ��밪�� ������ ����?
				addObj = false;
				changed = true;
				break;
			} // �Ұ������ �������� ������ false�� ����� �������� �ȵ���������
		}
		_vOpenList[i]->isOpen = false; // ����
		if (!addObj) continue;

		_vOpenList.push_back(tempTile); // �߰��ؾߵȴٰ� ������ �߰��ϴ°�
	}

	// ############## ��� ��ã���� ������ �Լ� #####################
	if (!changed)
	{// �ƹ��͵� ������ϰ� ������ ������(?) ���Ҵٸ� ������
		_stop = true;
		return;
	}

	//�����ߴٸ�
	if (tempTile->tileNum == _endTile)
	{
		while (_currentTile != _startTile)
		{
			_currentTile = _vTotalList[_currentTile]->parentNodeTileNum;
			_path.push_back(_currentTile);
		}
		_stop = true;
		return;
	}

	_vCloseList.push_back(tempTile);
	// ����Ÿ���� ��������Ʈ�� �ְ� ���¸���Ʈ���� ����. �׸��� ����Ÿ�Ϸ� ����
	for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
	{
		if (*_viOpenList == tempTile)
		{
			_viOpenList = _vOpenList.erase(_viOpenList);
			break;
		}
	}

	_currentTile = tempTile->tileNum;

	if (!_stop) pathFinder(_currentTile);
}