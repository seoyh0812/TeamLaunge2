#pragma once
#include "skillNEffect.h"

class narutoEffect : public skillNEffect
{
private:

public:
    narutoEffect() {};
    ~narutoEffect() {};

    virtual HRESULT init(S_BELONG belong, float x, float y);	//�ʱ�ȭ ���� �Լ�
    virtual void release();	//�޸� ���� �Լ�
    virtual void update();	//���� ����
    virtual void render();	//�׸��� ����
};

