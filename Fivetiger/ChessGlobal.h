#pragma once

//阶段常量
static const int DROP_PHASE = 0;
static const int PICK_PHASE = 1;
static const int MOVE_PHASE = 2;

//走棋结果常量
//成功 - 0
static const int RESULT_UNKNOW_WIN = 0;
//有胜负结果 > 0
static const int RESULT_FENSIVE_WIN = 1;
static const int RESULT_DEFENSIVE_WIN = 2;
static const int RESULT_NOBODY_WIN = 3;  //和局
//失败 < 0
static const int RESULT_FLAG_ERR = -101;  //走棋方错误

static const int RESULT_PHRASE_DROP = -201; //方式错误，请落子
static const int RESULT_PHRASE_MOVE = -202; //方式错误，请移子
static const int RESULT_PHRASE_PICK = -203; //方式错误，请提子

static const int RESULT_PHRASE_DROP_EXIST = -301; //已有子
static const int RESULT_PHRASE_MOVE_NOTSELF = -302; //不是自己的子
static const int RESULT_PHRASE_MOVE_NOTBLANK = -303; //不是空地
static const int RESULT_PHRASE_PICK_NOTOTHER = -304; //不是对方的子


static const int FENSIVE_FLAG = 1;
static const int DEFENSIVE_FLAG = 2;	