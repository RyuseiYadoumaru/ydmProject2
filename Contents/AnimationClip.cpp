#include <assimp\scene.h>
#include "AnimationClip.h"
#include "../System/ThirdParty/Assimp/Assimpscene.h"
//#include "dx11mathutil.h"
#include "Skeleton.h"

USING_GAME_SYSTEMS;

void AnimationClip::CalcAnimationInterpolationInfo(AnimationInterpolationInfo& output, Float32 currentTime)
{
	output.keyIndex1 = static_cast<Int32>(currentTime * m_ticksPerSecond) + m_beginFrameOffset;
	output.keyIndex2 = (output.keyIndex1 + 1) % GetKeyFrameNum();
	output.InterpolationRate = (currentTime * m_ticksPerSecond) - static_cast<Int32>(currentTime * m_ticksPerSecond);
}

void AnimationClip::CalcAnimationTransforms(
	Vector<BoneTransform>& output,
	const uInt32 boneNum,
	Float32 time,
	Float32 rate)
{
	// アニメーション行列用配列初期化
	output.clear();
	output.resize(boneNum);

	// 補間用の情報を取得
	AnimationInterpolationInfo info;
	CalcAnimationInterpolationInfo(info, time * rate);

	for (uInt32 i = 0; i < boneNum; i++)
	{
		KeyFrame& key1 = m_boneKeyFrameList[i][info.keyIndex1];
		KeyFrame& key2 = m_boneKeyFrameList[i][info.keyIndex2];

		BoneTransform trans1(key1.position, key1.rotation);
		BoneTransform trans2(key2.position, key2.rotation);

		output[i] = BoneTransform::Lerp(trans1, trans2, info.InterpolationRate);
	}
}

Float32 AnimationClip::GetDuration()
{
	return GetKeyFrameDuration() / m_ticksPerSecond;
}