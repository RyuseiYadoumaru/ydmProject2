#pragma once
#include <DirectXMath.h>

#include "std.h"
#include "BoneTransform.h"
#include "KeyFrame.h"

class Skeleton;
class Animation;

// �A�j���[�V�����̕�ԗp�̃f�[�^�\����
struct AnimationInterpolationInfo
{
	int keyIndex1;
	int keyIndex2;
	float InterpolationRate;
};

// ���[�V�����̊�b�N���X
class Motion
{
public:
	// �A�j���[�V�����s����v�Z
	void CalcAnimationMatrix(
		Animation* animation,
		std::vector<DirectX::XMFLOAT4X4>& outputMatrix);

	virtual float GetDuration(Animation* animation) abstract;

	virtual void CalcAnimationTransforms(
		std::vector<BoneTransform>& output,
		Animation* animation,
		float rate = 1.0f) abstract;

public:
	// �Q�b�^�[�Z�b�^�[
	T_String GetName() const;
	void SetName(std::string name);

	bool GetIsLoop() const;

private:
	T_String m_name;
	bool m_isLoop = true;	// ���[�v���邩�ǂ���
};

