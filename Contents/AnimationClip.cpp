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

void AnimationClip::CreateAnimationTransform(Float32 time, Float32 rate)
{
	// ï‚ä‘ópÇÃèÓïÒÇéÊìæ
	AnimationInterpolationInfo info;
	CalcAnimationInterpolationInfo(info, time * rate);

	for (const auto& keyName : m_keyNameList)
	{
		KeyFrame& key1 = m_boneKeyFrameList[keyName][info.keyIndex1];
		KeyFrame& key2 = m_boneKeyFrameList[keyName][info.keyIndex2];

		BoneTransform trans1(key1.position, key1.rotation);
		BoneTransform trans2(key2.position, key2.rotation);

		m_boneTransformList[keyName] = BoneTransform::Lerp(trans1, trans2, info.InterpolationRate);
	}
}

Float32 AnimationClip::GetDuration()
{
	return GetKeyFrameDuration() / m_ticksPerSecond;
}