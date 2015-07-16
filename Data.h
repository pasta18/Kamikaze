#ifndef _DATA
#define _DATA

#include<Siv3D.hpp>
#include<math.h>

// 各種速度
const double Speed = 3.0;
const double BulletSpeed = 5.0;

// ステージ縦横の最大値
const double widthMax = 640 - 200;
const double heightMax = 480 - 30;

// プレイヤーの初期位置
const double firstX = widthMax / 2;
const double firstY = 400;

// ボスの出現時間
const int createBoss = 40;

#endif