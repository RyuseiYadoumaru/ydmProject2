//******************************************************************************
//* @file   myMath.h
//* @brief  数学ヘッダーをインクルードする
//* @note   
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Color.h"
#include "Matrix4x4.h"
#include "Quaternion.h" 
#include "Easing.h"


namespace myMath
{
	class Math
	{
	public:
		static constexpr Float32 _PI	= 3.141592654f;
		static constexpr Float32 _2PI	= 6.283185307f;

		static Float32 DegreesToRadians(Float32 degrees) noexcept
		{
			 return (_PI / 180.0f) * degrees;
		}

		static Float32 RadiansToDegrees(Float32 radians) noexcept
		{
			 return (180.0f / _PI) * radians;
		}

	};
}
