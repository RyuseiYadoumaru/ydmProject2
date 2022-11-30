//******************************************************************************
//* @file   Color.h
//* @brief  カラークラス
//* @note   RGBAカラー表現
//* 
//* @author YadoumaruRyusei
//* @date   August 2022
//*****************************************************************************
#pragma once

#include <DirectXMath.h>
#include "std.h"


namespace myMath
{
	class Vector4;
	class Color
	{
	public:
		void Set(float _r, float _g, float _b, float _a) noexcept { r = _r; g = _g; b = _b; a = _a; }

	public:
		float r;
		float g;
		float b;
		float a;

	public:
		Float32* GetFloat() noexcept
		{
			m_colorFloat[0] = r;
			m_colorFloat[1] = g;
			m_colorFloat[2] = b;
			m_colorFloat[3] = a;
			return m_colorFloat;
		}



	public:
		static const Color Black;
		static const Color Red;
		static const Color Green;
		static const Color Blue;
		static const Color Magenta;
		static const Color Yellow;
		static const Color Cyan;
		static const Color Gray;
		static const Color White;
		static const Color Clear;

	public:

		Color() : r(1.0f), g(1.0f), b(1.0f), a(1.0f) {}
		Color(float _r, float _g, float _b, float _a) : r(_r), g(_g), b(_b), a(_a) {}
		Color(Color& color) : r(color.r), g(color.g), b(color.b), a(color.a) {}
		Color(const Color&) = default;

		Color& operator=(const Color& color) noexcept { r = color.r; g = color.g; b = color.b; a = color.a; return *this; }
		Color operator+(const Color& color) const noexcept { return Color(r + color.r, g + color.g, b + color.b, a + color.a); }
		Color operator-(const Color& color) const noexcept { return Color(r - color.r, g - color.g, b - color.b, a - color.a); }
		Color operator*(const Color& color) const noexcept { return Color(r * color.r, g * color.g, b * color.b, a * color.a); }
		Color operator/(const Color& color) const noexcept { return Color(r / color.r, g / color.g, b / color.b, a / color.a); }
		bool operator!=(const Color& color) const noexcept { return (r != color.r && g != color.g && b != color.b && a != color.a); }
		bool operator==(const Color& color) const noexcept { return (r == color.r && g == color.g && b == color.b && a == color.a); }

	public:
		// ベクトル周りの関数
		Color& operator=(const Vector4& color) noexcept;
		Vector4 GetVector4() noexcept;


	private:
		Float32 m_colorFloat[4] = {0.0f, 0.0f, 0.0f, 0.0f};
	};

}

