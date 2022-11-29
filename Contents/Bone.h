//*****************************************************************************
//* @file   Bone.h
//* @brief  
//* @note   ボーン情報
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#pragma once
#include "BoneTransform.h"
#include "Matrix4x4.h"
#include "std.h"
#include "macro.h"
namespace SYSTEMS
{
	class AssimpScene;
}

namespace GAME_SYSTEMS
{
	class Bone
	{
	public:
		// ボーンの親がいない場合のインデックス
		static constexpr Int32 NONE_PARENT = -1;

	public:
		Bone() :
			m_name(TEXT("NONAME")),
			m_parentIndex(NONE_PARENT),
			m_boneIndex(-1),
			m_offsetMatrix(myMath::Matrix4x4::CreateMatrixIdentity()) {}
		~Bone() = default;


	public:
		void AddChild(Bone* bone) noexcept { m_children.emplace_back(bone); }
		uInt32 GetChildCount() const noexcept { return static_cast<uInt32>(m_children.size()); }
		Bone* GetChild(Int32 index) noexcept { return  m_children[index]; }

		int GetBoneIndex() const noexcept { return m_boneIndex; }
		void SetBoneIndex(Int32 index) noexcept { m_boneIndex = index; }

		Int32 GetParentIndex() const noexcept { return m_parentIndex; };
		void SetParentIndex(Int32 index) noexcept { m_parentIndex = index; }

		T_String GetName() const noexcept { return m_name; };
		void SetName(std::string name) noexcept { m_name = name; }

		// 座標系
		void SetBoneTransform(const BoneTransform& transform) noexcept
		{
			m_transform.SetPosition(transform.GetPosition());
			m_transform.SetRotation(transform.GetRotation());
		}
		MY_MATH::Matrix4x4 GetBoneMatrix() noexcept { return m_transform.GetMatrix(); }

		// オフセット行列
		const MY_MATH::Matrix4x4& GetOffsetMatrix() const noexcept { return m_offsetMatrix; }
		void SetOffsetMatrix(MY_MATH::Matrix4x4 matrix) noexcept { m_offsetMatrix = matrix; }

	private:
		T_String m_name;					// ボーンの名前
		Int32 m_parentIndex;				// 親の番号
		Int32 m_boneIndex;					// 自分の番号
		Vector<Bone*> m_children;			// 子供のポインタ

		// 座標系
		BoneTransform m_transform;
		MY_MATH::Matrix4x4 m_offsetMatrix;
	};
}