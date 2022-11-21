//*****************************************************************************
//* @file   Motion.h
//* @brief  
//* @note   モーションデータの基底クラス
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#pragma once
#include <DirectXMath.h>
#include "myMath.h"
#include "std.h"
#include "../BoneTransform.h"
#include "../KeyFrame.h"

class Skeleton;
class Animation;
class AssimpScene;
struct aiNodeAnim;


// アニメーションの補間用のデータ構造体
struct AnimationInterpolationInfo
{
	Int32 keyIndex1;
	Int32 keyIndex2;
	Float32 InterpolationRate;
};

namespace GAME_SYSTEMS
{
	class Motion
	{
	public:
		bool Load(AssimpScene* assimpScene, uInt32 animationIndex = 0);

		// アニメーション行列を計算
		void CalcAnimationMatrix(
			Animation* animation,
			Vector<myMath::Matrix4x4>* outputMatrix);

		virtual Float32 GetDuration(Animation* animation) abstract;

		virtual void CalcAnimationTransforms(
			Vector<BoneTransform>& output,
			Animation* animation,
			Float32 rate = 1.0f) abstract;

	public:
		T_String GetName() const noexcept { return m_name; };
		void SetName(T_String name) noexcept { m_name = name; }

		bool GetIsLoop() const noexcept { return m_isLoop; };

		bool IsLoad() const noexcept { return m_isLoad; }

	private:
		T_String m_name;
		bool m_isLoop = true;
		bool m_isLoad = false;
	};
}