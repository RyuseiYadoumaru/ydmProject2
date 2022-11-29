//*****************************************************************************
//* @file   MeshInfo.h
//* @brief  
//* @note   メッシュ情報をまとめる
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#pragma once
#include "macro.h"
#include "std.h"
#include "myMath.h"

namespace SYSTEMS
{
	// 全ての頂点情報
	struct VertexData
	{
		MY_MATH::Vector3 Position = { 0.0f, 0.0f, 0.0f };
		MY_MATH::Color	 Color = { 1.0f, 1.0f, 1.0f, 1.0f };
		MY_MATH::Vector2 Texcoord = { 0.0f, 0.0f };
		MY_MATH::Vector3 Normal = { 0.0f, 0.0f, 0.0f };
		Int32   BoneIndex[4] = { -1, -1, -1, -1 };
		Float32	BoneWeight[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
		Int32   BoneNum = 0;
	};

	// フェイス情報
	struct Face
	{
		Vector<uInt32> Indices;
	};
}


