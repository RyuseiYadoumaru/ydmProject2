#pragma once
#include "std.h"
#include "macro.h"
#include "myMath.h"

// キーフレーム
struct KeyFrame
{
	MY_MATH::Quaternion rotation;	// 回転
	MY_MATH::Vector3	position;	// 座標
	bool shouldSlerpRotation;		// 回転を補間するべきかどうか
	bool shouldLerpPosition;		// 座標を補間するべきかどうか
};