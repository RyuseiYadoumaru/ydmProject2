//*****************************************************************************
//* @file   Color.cpp
//* @brief  カラークラス
//* @note   RGBAカラー表現
//* 
//* @author YadoumaruRyusei
//* @date   August 2022
//*****************************************************************************
#include "Color.h"
#include "Vector4.h"

namespace myMath
{
const Color Color::Black	(0.0f,	0.0f,	0.0f,	 1.0f);
const Color Color::Red		(1.0f,	0.0f,	0.0f,	 1.0f);
const Color Color::Green	(0.0f,	1.0f,	0.0f,	 1.0f);
const Color Color::Blue		(0.0f,	0.0f,	1.0f,	 1.0f);
const Color Color::Magenta	(1.0f,	0.0f,	1.0f,	 1.0f);
const Color Color::Yellow	(1.0f,	0.92f,	0.0016f, 1.0f);
const Color Color::Cyan		(0.0f,	1.0f,	1.0f,	 1.0f);
const Color Color::Gray		(0.5f,	0.5f,	0.5f,	 1.0f);
const Color Color::White	(1.0f,	1.0f,	1.0f,	 1.0f);
const Color Color::Clear	(0.0f,	0.0f,	0.0f,	 0.0f);

Color& Color::operator=(const Vector4& color) noexcept
{
	r = color.x; g = color.y; b = color.z; a = color.w; return *this;
}

Vector4 Color::GetVector4() noexcept
{
	Vector4 vec4;
	vec4.Set(r, g, b, a);
	return vec4;
}

}
