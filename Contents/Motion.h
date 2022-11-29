//*****************************************************************************
//* @file   Motion.h
//* @brief  
//* @note   ���[�V�����f�[�^�̊��N���X
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

// �A�j���[�V�����̕�ԗp�̃f�[�^�\����
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

		// �A�j���[�V�����s����v�Z
		void CalcAnimationMatrix(Vector<MY_MATH::Matrix4x4>& outMtxList ,const uInt32 boneNum, Float32 time = 0.0f);

		virtual Float32 GetDuration() abstract;

		virtual void CalcAnimationTransforms(
			Vector<BoneTransform>& output,
			const uInt32 boneNum,
			Float32 time,
			Float32 rate = 1.0f) abstract;

	public:
		// �A�j���[�V�������O
		T_String GetName() const noexcept { return m_name; };
		// ���[�v�t���O
		bool GetIsLoop() const noexcept { return m_isLoop; };
		// ���[�h�t���O
		bool IsLoad() const noexcept { return m_isLoad; }

		// �t���[��
		Float32 GetKeyFrameDuration() const noexcept { return m_keyFrameDuration - m_beginFrameOffset - m_endFrameOffset; }
		KeyFrame GetKeyFrame(Int32 boneIndex, Int32 frameIndex) const noexcept { return m_boneKeyFrameList[boneIndex][frameIndex]; }
		Int32 GetKeyFrameNum(Int32 boneIndex = 0) const noexcept { return static_cast<Int32>(m_boneKeyFrameList[boneIndex].size()); };

		// �J�n�t���[��
		int GetBeginFrameOffset() const noexcept { return m_beginFrameOffset; }
		void SetBeginFrameOffset(Int32 offset) noexcept { m_beginFrameOffset = offset; }
		
		// �I���t���[��
		int GetEndFrameOffset() const noexcept { return m_endFrameOffset; }
		void SetEndFrameOffset(Int32 offset) noexcept { m_endFrameOffset = offset; }

		// �A�j���[�V��������
		Float32 GetTicksPerSecond() const noexcept { return m_ticksPerSecond; }

	private:
		void ResizeKeyFrameList(const Int32 boneNum); // �L�[�t���[���z��̃��������m��
		void InitPositionKeyFrame(aiNodeAnim* nodeAnim, const Int32 boneIndex);
		void InitRotationKeyFrame(aiNodeAnim* nodeAnim, const Int32 boneIndex);
		void InitLerpPositionKeyFrame(Int32 boneIndex);
		void InitSlerpRotationKeyFrame(Int32 boneIndex);


	protected:
		Float32 m_keyFrameDuration	= 0.0f;	// �A�j���[�V�����̎���
		Float32 m_ticksPerSecond	= 0.0f;	// �A�j���[�V������1�t���[���̎���
		Int32 m_beginFrameOffset	= 0;	// �n�܂�̃t���[���̃I�t�Z�b�g
		Int32 m_endFrameOffset		= 0;	// �I���̃t���[���̃I�t�Z�b�g
		Vector<Vector<KeyFrame>> m_boneKeyFrameList;  // �L�[�t���[�����

	private:
		T_String m_name;
		bool m_isLoop = true;
		bool m_isLoad = false;
	};
}