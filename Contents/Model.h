//*****************************************************************************
//* @file   Model.h
//* @brief  
//* @note   モデルに必要なデータを保持する
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#pragma once
#include "std.h"
#include "macro.h"

namespace GAME_SYSTEMS
{
	class Skeleton;
	class Mesh;

	class Model
	{
	public:
		bool LoadModel(T_String filePath);
		void Releace();
		void RenderModel();

	private:
		SharedPtr<Mesh>		m_meshData	= nullptr;
		SharedPtr<Skeleton>	m_skelton	= nullptr;
	};
}

