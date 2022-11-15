//*****************************************************************************
//* @file   Mesh.h
//* @brief  
//* @note   メッシュの基底クラス
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#pragma once
#include "../System/ThirdParty/Assimp/Assimpscene.h"

namespace GAME_SYSTEMS
{
	class Mesh
	{
	public:
		virtual void Load(T_String meshName) = 0;
		virtual void Releace() = 0;
		virtual void Render() = 0;

	protected:
		AssimpScene m_assimpScene;

	};
}


