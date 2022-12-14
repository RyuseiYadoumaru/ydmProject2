//*****************************************************************************
//* @file   Debug.cpp
//* @brief  デバッグクラス
//* @note   
//* 
//* @author YadoumaruRyusei
//* @date   July 2022
//*****************************************************************************
#include <iostream>
#include "Debug.h"
#include "DeveloperMenu.h"
#include "Line.h"
#include "../System/DX11Settransform.h"
#include "../System/Console.h"


/****	デバックブレイク	****/
#ifdef  _DEBUG
#ifdef _M_IX86 ||_M_IX86FP
#define DEBUG_BREAK _asm{ int 3 }
#else
#define DEBUG_BREAK __debugbreak()
#endif // _M_IX86 || _M_IX86FP
#else
#define DEBUG_BREAK
#endif //  _DEBUG

#define LOG_COLOR		(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY)
#define ERROR_COLOR		(FOREGROUND_RED | FOREGROUND_INTENSITY)
#define WARNING_COLOR	(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY)


#ifdef  _DEBUG
//==============================================================================
//!	@fn		Log
//!	@brief	ログ
//!	@note	コンソールに文字列を出力する
//!	@param	log：文字列
//==============================================================================
void tools::Debug::Log(String log)
{
	systems::Console* console = systems::Console::GetInstance();
	console->TextColor(LOG_COLOR);
	std::cout << log << std::endl;
}

//==============================================================================
//!	@fn		LogError
//!	@brief	ログエラー
//!	@note	コンソールにエラー文を出力する
//!	@param	log：文字列
//==============================================================================
void tools::Debug::LogError(String log)
{
	systems::Console* console = systems::Console::GetInstance();
	console->TextColor(ERROR_COLOR);
	std::cout << log << std::endl;

}

//==============================================================================
//!	@fn		LogWarning
//!	@brief	ログ警告
//!	@note	コンソールに警告文を出力する
//!	@param	log：文字列
//==============================================================================
void tools::Debug::LogWarning(String log)
{
	systems::Console* console = systems::Console::GetInstance();
	console->TextColor(WARNING_COLOR);
	std::cout << log << std::endl;

}

//==============================================================================
//!	@fn		Stop
//!	@brief	処理をストップする
//==============================================================================
void tools::Debug::Stop()
{
	DEBUG_BREAK;
}


//==============================================================================
//!	@fn		Assert
//!	@brief	条件の時処理をストップする
//! //!	@param	flag : 条件式
//==============================================================================
void tools::Debug::Assert(bool flag) noexcept
{
	if (flag == false) return;
	else
	{
		DEBUG_BREAK;
	}
}


/**============================================================================
//! @func   Assert
//! @brief  条件の時処理をストップする
//! @param flag
//! @param log
============================================================================*/
void tools::Debug::Assert(bool flag, String log) noexcept
{
	if (flag == false) return;
	else
	{
		LogError(log);
		DEBUG_BREAK;
	}
}

void tools::Debug::DrawAxis(const MY_MATH::Matrix4x4& mtx, Float32 length)
{	
	auto line = developer::DeveloperMenu::GetLine();
	Vector<gameSystems::Line::Vertex> v;
	v.resize(2);
	// X軸
	v[0].Position.x = mtx._41;
	v[0].Position.y = mtx._42;
	v[0].Position.z = mtx._43;

	v[1].Position.x = mtx._41 + (mtx._11 * length);
	v[1].Position.y = mtx._42 + (mtx._12 * length);
	v[1].Position.z = mtx._43 + (mtx._13 * length);

	v[0].Color = v[1].Color = DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	line->SetVertex(v);
	line->Render();


	// Y軸
	v[0].Position.x = mtx._41;
	v[0].Position.y = mtx._42;
	v[0].Position.z = mtx._43;

	v[1].Position.x = mtx._41 + (mtx._21 * length);
	v[1].Position.y = mtx._42 + (mtx._22 * length);
	v[1].Position.z = mtx._43 + (mtx._23 * length);

	v[0].Color = v[1].Color = DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	line->SetVertex(v);
	line->Render();

	// Z軸
	v[0].Position.x = mtx._41;
	v[0].Position.y = mtx._42;
	v[0].Position.z = mtx._43;

	v[1].Position.x = mtx._41 + (mtx._31 * length);
	v[1].Position.y = mtx._42 + (mtx._32 * length);
	v[1].Position.z = mtx._43 + (mtx._33 * length);

	v[0].Color = v[1].Color = DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
	line->SetVertex(v);
	line->Render();
}

void tools::Debug::DrawAxis(const MY_MATH::Vector3& pos, const MY_MATH::Vector4& dir, Float32 length, MY_MATH::Color color)
{
	auto line = developer::DeveloperMenu::GetLine();
	Vector<gameSystems::Line::Vertex> v;
	v.resize(2);

	v[0].Position.x = pos.x;
	v[0].Position.y = pos.y;
	v[0].Position.z = pos.z;

	v[1].Position.x = pos.x + (length * dir.x);
	v[1].Position.y = pos.y + (length * dir.y);
	v[1].Position.z = pos.z + (length * dir.z);

	v[0].Color = v[1].Color = color.GetXMFLOAT();
	line->SetVertex(v);
	line->Render();
}

void tools::Debug::DrawAxis(const MY_MATH::Vector3& pos, const MY_MATH::Vector3& dir, Float32 length, MY_MATH::Color color)
{
	auto line = developer::DeveloperMenu::GetLine();
	Vector<gameSystems::Line::Vertex> v;
	v.resize(2);

	v[0].Position.x = pos.x;
	v[0].Position.y = pos.y;
	v[0].Position.z = pos.z;

	v[1].Position.x = pos.x + (length * dir.x);
	v[1].Position.y = pos.y + (length * dir.y);
	v[1].Position.z = pos.z + (length * dir.z);

	v[0].Color = v[1].Color = color.GetXMFLOAT();
	line->SetVertex(v);
	line->Render();
}

void tools::Debug::DrawRay(const MY_MATH::Vector3& startPos, const MY_MATH::Vector3 endPos, MY_MATH::Color color)
{
	auto line = developer::DeveloperMenu::GetLine();
	Vector<gameSystems::Line::Vertex> v;
	v.resize(2);

	v[0].Position.x = startPos.x;
	v[0].Position.y = startPos.y;
	v[0].Position.z = startPos.z;

	v[1].Position.x = startPos.x + endPos.x;
	v[1].Position.y = startPos.y + endPos.y;
	v[1].Position.z = startPos.z + endPos.z;

	v[0].Color = v[1].Color = color.GetXMFLOAT();
	line->SetVertex(v);
	line->Render();
}


#else
void tools::Debug::Log(String log)
{
}

void tools::Debug::LogError(String log)
{

}

void tools::Debug::LogWarning(String log)
{

}

void tools::Debug::Stop()
{
}

void tools::Debug::Assert(bool flag) noexcept
{
}

void tools::Debug::Assert(bool flag, String log) noexcept
{
}

void tools::Debug::DrawAxis(const MY_MATH::Matrix4x4& mtx, Float32 length)
{
}

void tools::Debug::DrawAxis(const MY_MATH::Vector3& pos, const MY_MATH::Vector4& dir, Float32 length, MY_MATH::Color color)
{
}

void tools::Debug::DrawRay(const MY_MATH::Vector3& startPos, const MY_MATH::Vector3 endPos, MY_MATH::Color color)
{
}

#endif // _DEBUG