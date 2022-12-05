//*****************************************************************************
//* @file   SpriteRenderer.h
//* @brief  
//* @note   2Dスプライト描画
//* 
//* @author YadoumaruRyusei
//* @date   December 2022
//*****************************************************************************
#pragma once
#include <DirectXMath.h>
#include "macro.h"
#include "std.h"
#include "Graphics.h"

namespace GAME_SYSTEMS
{
	class SpriteRenderer : public Graphics
	{
		struct Vertex
		{
			DirectX::XMFLOAT3 Position	= { 0.0f, 0.0f, 0.0f };
			DirectX::XMFLOAT4 Color		= { 1.0f, 1.0f, 1.0f, 1.0f };
			DirectX::XMFLOAT2 Texcoord	= { 0.0f, 0.0f };
		};
	};
}

