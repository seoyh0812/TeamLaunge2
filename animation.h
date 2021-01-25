#pragma once
#include <vector>

//�ݹ��Լ�
typedef void(*CALLBACK_FUNCTION)(void);

//�Ű������� �ִ� �ݹ��Լ�
typedef void(*CALLBACK_FUNCTION_PARAMETER)(void*);

//void* ���̵� ������ -> ������ �� ���� �� �ִ�. �ٸ� �����_casting�� ������Ѵ�

class animation
{
public:
	typedef vector<POINT> vFrameList;	//������ ����Ʈ ���� ����
	typedef vector<int> vPlayList;		//�÷��� ����Ʈ ���� ����

private:
	int			_frameNum;		//������ �ѹ�
		
	vFrameList	_frameList;		//�ִϸ��̼� ������ ����Ʈ
	vPlayList	_playList;		//�ִϸ��̼� �÷��� �ε��� ����Ʈ

	int _frameWidth;
	int _frameHeight;

	BOOL _loop;

	float _frameUpdateSec;
	float _elapsedSec;

	DWORD _nowPlayIndex;
	BOOL _play;

	void*						_obj;
	CALLBACK_FUNCTION			_callbackFunction;
	CALLBACK_FUNCTION_PARAMETER	_callbackFunctionParameter;

public:
	animation();
	~animation();

	HRESULT init(int totalW, int totalH, int frameW, int frameH);
	void release();

	//����Ʈ �ִϸ��̼� ���
	void setDefPlayFrame(BOOL reverse = FALSE, BOOL loop = FALSE);
	void setDefPlayFrame(BOOL reverse, BOOL loop, CALLBACK_FUNCTION cbFunction);
	void setDefPlayFrame(BOOL reverse, BOOL loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj);

	//�迭�� �ִϸ��̼� ���
	void setPlayFrame(int* playArr, int arrLen, BOOL loop = FALSE);
	void setPlayFrame(int* playArr, int arrLen, BOOL loop, CALLBACK_FUNCTION cbFunction);
	void setPlayFrame(int* playArr, int arrLen, BOOL loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj);

	//���������Ӻ��� �������ӱ��� ������ �ִϸ��̼� ���
	void setPlayFrame(int start, int end, BOOL reverse = FALSE, BOOL loop = FALSE);
	void setPlayFrame(int start, int end, BOOL reverse, BOOL loop, CALLBACK_FUNCTION cbFunction);
	void setPlayFrame(int start, int end, BOOL reverse, BOOL loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj);

	
	//������ ����
	void setFPS(int framePerSec);
	//������ ��� �ӵ� ����
	void frameUpdate(float elapsedTime);

	void start();	//�ִϸ��̼� ���
	void stop();	//�ִϸ��̼� ��ž
	void pause();	//�ִϸ��̼� �Ͻ�����
	void resume();	//�ִϸ��̼� �ٽ����

	inline BOOL isPlay() { return _play; }
	inline POINT getFramePos() { return _frameList[_playList[_nowPlayIndex]]; }
	inline int getFrameWidth() { return _frameWidth; }
	inline int getFrameHeight() { return _frameHeight; }

};

