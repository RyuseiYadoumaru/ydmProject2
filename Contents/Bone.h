//*****************************************************************************
//* @file   Bone.h
//* @brief  
//* @note   ボーン情報
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#pragma once
#include <DirectXMath.h>
#include "std.h"
#include "macro.h"

class AssimpScene;

namespace GAME_SYSTEMS
{
	class Bone
	{
	public:
		Bone();

	public:
		void AddChild(Bone* bone);
		unsigned int GetChildCount() const;
		Bone* GetChild(int index);

	public:
		// ゲッターセッター
		int GetBoneIndex() const;
		void SetBoneIndex(int index);

		int GetParentIndex() const;
		void SetParentIndex(int index);

		T_String GetName() const;
		void SetName(std::string name);

		DirectX::XMFLOAT4X4 GetOffsetMatrix() const;
		void SetOffsetMatrix(DirectX::XMFLOAT4X4 matrix);

	public:
		// ボーンの親がいない場合のインデックス
		static constexpr int NONE_PARENT = -1;

	private:
		int m_parentIndex = NONE_PARENT;	// 親の番号
		int m_boneIndex = -1;				// 自分の番号
		T_String m_name;					// ボーンの名前
		Vector<Bone*> m_children;		// 子供のポインタ

		DirectX::XMFLOAT4X4 m_offsetMatrix;	   // オフセット行列
	};
}