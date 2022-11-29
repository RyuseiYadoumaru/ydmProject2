//*****************************************************************************
//* @file   Motion.h
//* @brief  
//* @note   モーションデータの基底クラス
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#pragma once
#include "../System/ThirdParty/Assimp/AssimpScene.h"
#include "myMath.h"
#include "std.h"
#include "BoneTransform.h"
#include "KeyFrame.h"

namespace SYSTEMS
{
	class AssimpScene;
}
struct aiNodeAnim;
struct aiAnimation;

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
		using AnimationFrame = Unordered_Map<T_String, Vector<KeyFrame>>;

	public:
		bool Load(const aiAnimation* assimpAnimation);
		bool Load(T_String filePath);
		void Releace();

		// アニメーション行列を計算
		void CalcAnimationTransform(Skeleton* skeleton, Float32 time, Float32 rate = 1.0f);

		virtual Float32 GetDuration() abstract;


	public:
		// アニメーション名前
		T_String GetName() const noexcept { return m_name; };
		// ループフラグ
		bool GetIsLoop() const noexcept { return m_isLoop; };

		// フレーム
		Float32 GetKeyFrameDuration() const noexcept { return m_keyFrameDuration - m_beginFrameOffset - m_endFrameOffset; }
		KeyFrame GetKeyFrame(T_String boneName, Int32 frameIndex)  noexcept { return m_boneKeyFrameList[boneName][frameIndex]; }
		Int32 GetKeyFrameNum() const noexcept { return m_keyFrameNum; };

		// 開始フレーム
		int GetBeginFrameOffset() const noexcept { return m_beginFrameOffset; }
		void SetBeginFrameOffset(Int32 offset) noexcept { m_beginFrameOffset = offset; }
		
		// 終了フレーム
		int GetEndFrameOffset() const noexcept { return m_endFrameOffset; }
		void SetEndFrameOffset(Int32 offset) noexcept { m_endFrameOffset = offset; }

		// アニメーション時間
		Float32 GetTicksPerSecond() const noexcept { return m_ticksPerSecond; }

	private:
		void InitPositionKeyFrame(aiNodeAnim* nodeAnim, T_String boneName);
		void InitRotationKeyFrame(aiNodeAnim* nodeAnim, T_String boneName);
		void InitLerpPositionKeyFrame(T_String boneName);
		void InitSlerpRotationKeyFrame(T_String boneName);

	protected:
		virtual void CreateAnimationTransform(Float32 time, Float32 rate = 1.0f) abstract;

	protected:
		SYSTEMS::AssimpScene m_animationLoader;

		Float32 m_keyFrameDuration	= 0.0f;	// アニメーションの時間
		Float32 m_ticksPerSecond	= 0.0f;	// アニメーションの1フレームの時間
		Int32 m_beginFrameOffset	= 0;	// 始まりのフレームのオフセット
		Int32 m_endFrameOffset		= 0;	// 終わりのフレームのオフセット
		
		// アニメーション
		AnimationFrame m_boneKeyFrameList;
		Unordered_Map<T_String, BoneTransform> m_boneTransformList;
		Vector<T_String> m_keyNameList;
		
		// キーフレーム
		uInt32 m_keyFrameNum = 0;
	
	private:
		T_String m_name;
		bool m_isLoop = true;
	};
}