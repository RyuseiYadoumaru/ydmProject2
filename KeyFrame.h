#pragma once
#include "std.h"
#include "macro.h"
#include "myMath.h"

// �L�[�t���[��
struct KeyFrame
{
	MY_MATH::Quaternion rotation;	// ��]
	MY_MATH::Vector3	position;	// ���W
	bool shouldSlerpRotation;		// ��]���Ԃ���ׂ����ǂ���
	bool shouldLerpPosition;		// ���W���Ԃ���ׂ����ǂ���
};