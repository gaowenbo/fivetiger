#pragma once

//�׶γ���
static const int DROP_PHASE = 0;
static const int PICK_PHASE = 1;
static const int MOVE_PHASE = 2;

//����������
//�ɹ� - 0
static const int RESULT_UNKNOW_WIN = 0;
//��ʤ����� > 0
static const int RESULT_FENSIVE_WIN = 1;
static const int RESULT_DEFENSIVE_WIN = 2;
static const int RESULT_NOBODY_WIN = 3;  //�;�
//ʧ�� < 0
static const int RESULT_FLAG_ERR = -101;  //���巽����

static const int RESULT_PHRASE_DROP = -201; //��ʽ����������
static const int RESULT_PHRASE_MOVE = -202; //��ʽ����������
static const int RESULT_PHRASE_PICK = -203; //��ʽ����������

static const int RESULT_PHRASE_DROP_EXIST = -301; //������
static const int RESULT_PHRASE_MOVE_NOTSELF = -302; //�����Լ�����
static const int RESULT_PHRASE_MOVE_NOTBLANK = -303; //���ǿյ�
static const int RESULT_PHRASE_PICK_NOTOTHER = -304; //���ǶԷ�����


static const int FENSIVE_FLAG = 1;
static const int DEFENSIVE_FLAG = 2;	