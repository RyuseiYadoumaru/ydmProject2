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
#include "BoneTransform.h"
#include "KeyFrame.h"

class Animation;
struct aiNodeAnim;
namespace SYSTEMS
{
	class AssimpScene;
}

// アニメーションの補間用のデータ構造体
struct AnimationInterpolationInfo
{
	Int32 keyIndex1;
	Int32 keyIndex2;
	Float32 InterpolationRate;
};

namespace GAME_SYSTEMS
{
	class Skeleton;
	class Motion
	{
	public:
		bool Load(SYSTEMS::AssimpScene* assimpScene, uInt32 animationIndex = 0);

		// アニメーション行列を計算
		void CalcAnimationMatrix(Vector<MY_MATH::Matrix4x4>& outMtxList ,const uInt32 boneNum, Float32 time = 0.0f);

		virtual Float32 GetDuration() abstract;

		virtual void CalcAnimationTransforms(
			Vector<BoneTransform>& output,
			const uInt32 boneNum,
			Float32 time,
			Float32 rate = 1.0f) abstract;

	public:
		// アニメーション名前
		T_String GetName() const noexcept { return m_name; };
		// ループフラグ
		bool GetIsLoop() const noexcept { return m_isLoop; };
		// ロードフラグ
		bool IsLoad() const noexcept { return m_isLoad; }

		// フレーム
		Float32 GetKeyFrameDuration() const noexcept { return m_keyFrameDuration - m_beginFrameOffset - m_endFrameOffset; }
		KeyFrame GetKeyFrame(Int32 boneIndex, Int32 frameIndex) const noexcept { return m_boneKeyFrameList[boneIndex][frameIndex]; }
		Int32 GetKeyFrameNum(Int32 boneIndex = 0) const noexcept { return static_cast<Int32>(m_boneKeyFrameList[boneIndex].size()); };

		// 開始フレーム
		int GetBeginFrameOffset() const noexcept { return m_beginFrameOffset; }
		void SetBeginFrameOffset(Int32 offset) noexcept { m_beginFrameOffset = offset; }
		
		// 終了フレーム
		int GetEndFrameOffset() const noexcept { return m_endFrameOffset; }
		void SetEndFrameOffset(Int32 offset) noexcept { m_endFrameOffset = offset; }

		// アニメーション時間
		Float32 GetTicksPerSecond() const noexcept { return m_ticksPerSecond; }

	private:
		void ResizeKeyFrameList(const Int32 boneNum); // キーフレーム配列のメモリを確保
		void InitPositionKeyFrame(aiNodeAnim* nodeAnim, const Int32 boneIndex);
		void InitRotationKeyFrame(aiNodeAnim* nodeAnim, const Int32 boneIndex);
		void InitLerpPositionKeyFrame(Int32 boneIndex);
		void InitSlerpRotationKeyFrame(Int32 boneIndex);


	protected:
		Float32 m_keyFrameDuration	= 0.0f;	// アニメーションの時間
		Float32 m_ticksPerSecond	= 0.0f;	// アニメーションの1フレームの時間
		Int32 m_beginFrameOffset	= 0;	// 始まりのフレームのオフセット
		Int32 m_endFrameOffset		= 0;	// 終わりのフレームのオフセット
		Vector<Vector<KeyFrame>> m_boneKeyFrameList;  // キーフレーム情報

	private:
		T_String m_name;
		bool m_isLoop = true;
		bool m_isLoad = false;
	};
}