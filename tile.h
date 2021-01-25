#pragma once

class tile // 그냥 구조체같이 쓰자
{
public:
	int _idX;		//타일의 인덱스 X
	int _idY;		//타일의 인덱스 Y
	int _number;

	POINT _center;	//타일의 중점 값
	RECT _rc;

	bool _isOpen;	//갈수있는 타일이니?
	
	int _frameX;
	int _frameY;


	tile();
	~tile();
};

