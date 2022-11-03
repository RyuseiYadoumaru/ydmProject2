//*****************************************************************************
//* @file   Color.cpp
//* @brief  カラークラス
//* @note   RGBAカラー表現
//* 
//* @author YadoumaruRyusei
//* @date   August 2022
//*****************************************************************************
#include "Color.h"

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

}
