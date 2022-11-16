//*****************************************************************************
//* @file   DefaultStaticMesh.h
//* @brief  
//* @note   Cube,Terrain,SphareÇê∂ê¨Ç∑ÇÈ
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#pragma once
#include "StaticMesh.h"

#define CUBE		TEXT("Cube")
#define SPHERE		TEXT("Sphere")
#define TERRAIN		TEXT("Terrain")

namespace GAME_SYSTEMS
{
	class DefaultStaticMesh : public StaticMesh
	{
	public:
		virtual void Load(T_String meshName) override;
		virtual void Render() override;

	private:
		constexpr static Float32 m_polygonSize = 1.0f;
		constexpr static uInt32 m_terrainSizeX = 20;
		constexpr static uInt32 m_terrainSizeY = 20;

	private:
		void CreateCube();
		void CreateSphere();
		void CreateTerrain();
	};
}

