//*****************************************************************************
//* @file   Debug.cpp
//* @brief  �f�o�b�O�N���X
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


/****	�f�o�b�N�u���C�N	****/
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
//!	@brief	���O
//!	@note	�R���\�[���ɕ�������o�͂���
//!	@param	log�F������
//==============================================================================
void tools::Debug::Log(String log)
{
	systems::Console* console = systems::Console::GetInstance();
	console->TextColor(LOG_COLOR);
	std::cout << log << std::endl;
}

//==============================================================================
//!	@fn		LogError
//!	@brief	���O�G���[
//!	@note	�R���\�[���ɃG���[�����o�͂���
//!	@param	log�F������
//==============================================================================
void tools::Debug::LogError(String log)
{
	systems::Console* console = systems::Console::GetInstance();
	console->TextColor(ERROR_COLOR);
	std::cout << log << std::endl;

}

//==============================================================================
//!	@fn		LogWarning
//!	@brief	���O�x��
//!	@note	�R���\�[���Ɍx�������o�͂���
//!	@param	log�F������
//==============================================================================
void tools::Debug::LogWarning(String log)
{
	systems::Console* console = systems::Console::GetInstance();
	console->TextColor(WARNING_COLOR);
	std::cout << log << std::endl;

}

//==============================================================================
//!	@fn		Stop
//!	@brief	�������X�g�b�v����
//==============================================================================
void tools::Debug::Stop()
{
	DEBUG_BREAK;
}


//==============================================================================
//!	@fn		Assert
//!	@brief	�����̎��������X�g�b�v����
//! //!	@param	flag : ������
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
//! @brief  �����̎��������X�g�b�v����
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
	// X��
	v[0].Position.x = mtx._41 + mtx._11 * -length / 2.0f;
	v[0].Position.y = mtx._42 + mtx._12 * -length / 2.0f;
	v[0].Position.z = mtx._43 + mtx._13 * -length / 2.0f;

	v[1].Position.x = mtx._41 + mtx._11 * length / 2.0f;
	v[1].Position.y = mtx._42 + mtx._12 * length / 2.0f;
	v[1].Position.z = mtx._43 + mtx._13 * length / 2.0f;

	v[0].Color = v[1].Color = DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	line->SetVertex(v);
	line->Render();


	// Y��
	v[0].Position.x = mtx._41 + mtx._21 * -length / 2.0f;
	v[0].Position.y = mtx._42 + mtx._22 * -length / 2.0f;
	v[0].Position.z = mtx._43 + mtx._23 * -length / 2.0f;

	v[1].Position.x = mtx._41 + mtx._21 * length / 2.0f;
	v[1].Position.y = mtx._42 + mtx._22 * length / 2.0f;
	v[1].Position.z = mtx._43 + mtx._23 * length / 2.0f;

	v[0].Color = v[1].Color = DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	line->SetVertex(v);
	line->Render();

	// Z��
	v[0].Position.x = mtx._41 + mtx._31 * -length / 2.0f;
	v[0].Position.y = mtx._42 + mtx._32 * -length / 2.0f;
	v[0].Position.z = mtx._43 + mtx._33 * -length / 2.0f;

	v[1].Position.x = mtx._41 + mtx._31 * length / 2.0f;
	v[1].Position.y = mtx._42 + mtx._32 * length / 2.0f;
	v[1].Position.z = mtx._43 + mtx._33 * length / 2.0f;

	v[0].Color = v[1].Color = DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
	line->SetVertex(v);
	line->Render();
}

void tools::Debug::DrawRay(const MY_MATH::Vector3& pos, const MY_MATH::Vector3 dir, Float32 length, MY_MATH::Color color)
{
	auto line = developer::DeveloperMenu::GetLine();
	Vector<gameSystems::Line::Vertex> v;
	v.resize(2);
	// X��
	v[0].Position.x = pos.x + dir.x * -length / 2.0f;
	v[0].Position.y = pos.y + dir.y * -length / 2.0f;
	v[0].Position.z = pos.z + dir.z * -length / 2.0f;

	v[1].Position.x = pos.x + dir.x * length / 2.0f;
	v[1].Position.y = pos.y + dir.y * length / 2.0f;
	v[1].Position.z = pos.z + dir.z * length / 2.0f;

	v[0].Color = v[1].Color = color.GetXMFLOAT();
	line->SetVertex(v);
	line->Render();
}


#else
//==============================================================================
//!	@fn		Log
//!	@brief	���O
//!	@note	�R���\�[���ɕ�������o�͂���
//!	@param	log�F������
//==============================================================================
void tools::Debug::Log(String log)
{
}

//==============================================================================
//!	@fn		LogError
//!	@brief	���O�G���[
//!	@note	�R���\�[���ɃG���[�����o�͂���
//!	@param	log�F������
//==============================================================================
void tools::Debug::LogError(String log)
{

}

//==============================================================================
//!	@fn		LogWarning
//!	@brief	���O�x��
//!	@note	�R���\�[���Ɍx�������o�͂���
//!	@param	log�F������
//==============================================================================
void tools::Debug::LogWarning(String log)
{

}

//==============================================================================
//!	@fn		Stop
//!	@brief	�������X�g�b�v����
//==============================================================================
void tools::Debug::Stop()
{
}


//==============================================================================
//!	@fn		Assert
//!	@brief	�����̎��������X�g�b�v����
//! //!	@param	flag : ������
//==============================================================================
void tools::Debug::Assert(bool flag) noexcept
{
}


/**============================================================================
//! @func   Assert
//! @brief  �����̎��������X�g�b�v����
//! @param flag
//! @param log
============================================================================*/
void tools::Debug::Assert(bool flag, String log) noexcept
{
}

void tools::Debug::DrawAxis(const MY_MATH::Matrix4x4& mtx, Float32 length)
{
}

void tools::Debug::DrawRay(const MY_MATH::Vector3& pos, const MY_MATH::Vector3 dir, Float32 length, MY_MATH::Color color)
{
}


#endif // _DEBUG