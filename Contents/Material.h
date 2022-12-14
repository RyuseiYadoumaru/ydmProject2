//*****************************************************************************
//* @file   Material.h
//* @brief  マテリアル
//* @note   
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include "std.h"
#include "macro.h"
#include "Color.h"


namespace GAME_SYSTEMS
{
	class VertexShader;
	class PixelShader;
	class Texture;

	class Material
	{
	public:
		Material() :
			m_ambientColor (1.0f, 1.0f, 1.0f, 1.0f),
			m_diffuseColor (1.0f, 1.0f, 1.0f, 1.0f),
			m_specularColor(1.0f, 1.0f, 1.0f, 1.0f) {}

		~Material() = default;

	public:
		const myMath::Color& GetAmbientColor() const noexcept { return m_ambientColor; }
		void SetAmbientColor(Float32 r, Float32 g, Float32 b, Float32 a) noexcept { m_ambientColor.Set(r, g, b, a); }
		const myMath::Color& GetDiffuseColor() const noexcept { return m_diffuseColor; }
		void SetDiffuseColor(Float32 r, Float32 g, Float32 b, Float32 a) noexcept { m_diffuseColor.Set(r, g, b, a); }
		const myMath::Color& GetSpecularColor() const noexcept { return m_specularColor; }
		void SetSpecularColor(Float32 r, Float32 g, Float32 b, Float32 a) noexcept { m_specularColor.Set(r, g, b, a); }

	public:
		bool LoadShader(T_String vertexShaderName, T_String pixelShaderName);
		bool SetPixelShader(T_String pixelShaderName);
		bool SetVertexShader(T_String vertexShaderName);
		void AddTexture(SharedPtr<Texture> texture, uInt32 slot);
		void Unload();
		void SetShader();

	public:
		Material& operator=(const Material& mat) noexcept;

	private:
		myMath::Color m_ambientColor;
		myMath::Color m_diffuseColor;
		myMath::Color m_specularColor;

	private:
		SharedPtr<VertexShader>		m_vertexShader	= nullptr;
		SharedPtr<PixelShader>		m_pixelShader	= nullptr;
		Unordered_Map<uInt32, SharedPtr<Texture>>	m_textureList;
	};
}


