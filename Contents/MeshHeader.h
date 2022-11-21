//*****************************************************************************
//* @file   MeshHeader.h
//* @brief  
//* @note   派生するメッシュクラスで定義するヘッダー
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#pragma once
#include "std.h"
#include "macro.h"

#include "Mesh.h"
#include "Polygon.h"

#include <d3d11.h>
#include <DirectXMath.h>

namespace GAME_SYSTEMS
{
	class Skeleton;
	class AnimationClip;
}
//class Animation;

struct aiNode;
struct aiMesh;
