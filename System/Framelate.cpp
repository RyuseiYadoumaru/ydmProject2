//*****************************************************************************
//* @file   Framelate.h
//* @brief  
//* @note   �t���[���̊Ǘ����s���B
//* 
//* @author YadoumaruRyusei
//* @date   August 2022
//*****************************************************************************

#include <chrono>
#include <thread>
#include "Framelate.h"
#include "SystemTimer.h"
#include "Window.h"
#include "Debug.h"

USING_SYSTEMS;

/**============================================================================
//! @func   Initialize
//! @brief  ������
//! @retval true:����I���@false:�ُ�I��
============================================================================*/
bool gameSystems::Framelate::Initialize()
{
    m_deltaTime = 0.0f;
	m_currentTime = 0.0f;
	m_lastTime = 0.0f;
	m_totalFrameCount = 0;
	m_totalTime = 0.0f;
	m_gameTotalTime = 0.0f;
	m_scale = 1.0f;
	m_nowFPS = 0.0f;
	m_saveTime = 0.0f;

	return true;

}

/**============================================================================
//! @func   Run
//! @brief  �X�V
//! @retval true:����I���@false:�ُ�I��
============================================================================*/
bool gameSystems::Framelate::Run()
{
	auto systemTimer = systems::SystemTimer::GetInstance();
	//���ݎ��Ԏ擾
	Float32 nowTime = static_cast<Float32>(systemTimer->GetTime());
	m_currentTime = nowTime * 0.001f;

	//�f���^�^�C������
	m_deltaTime = m_currentTime - m_lastTime;

	//�O�t���[���̎��ԕۑ�
	m_lastTime = m_currentTime;

	//�t���[���J�E���g
	m_totalFrameCount++;

	//�g�[�^���^�C��
	m_totalTime += m_deltaTime;
	m_gameTotalTime += m_deltaTime * m_scale;

	/** �Œ�t���[���`�F�b�N */
	CheckFixedFrame();

	/** �ҋ@���� */
	Wait();

	/** FPS�o�� */
	PrintFPS();

	return true;
}


/**============================================================================
//! @func   Finalize
//! @brief  �I������
//! @retval true:����I���@false:�ُ�I��
============================================================================*/
bool gameSystems::Framelate::Finalize()
{
    return true;
}


/**============================================================================
//! @func   CheckFixedFrame
//! @brief  �Œ�t���[�����X�V���邩�`�F�b�N����
============================================================================*/
void gameSystems::Framelate::CheckFixedFrame()
{
	static Float32 fixedTime = 0.0f;
	fixedTime += m_deltaTime;
	m_isfixed = false;
	if (fixedTime >= SystemTimer::m_FPS)
	{
		m_isfixed = true;
		fixedTime = 0.0f;
	}
}


/**============================================================================
//! @func   Wait
//! @brief  �ҋ@����
============================================================================*/
void gameSystems::Framelate::Wait()
{
	Float32 frameParam = (1.0f / static_cast<Float32>(SystemTimer::m_FPS)) * 1000000.0f;
	Float32 sleep_time = frameParam - m_deltaTime;

	if (sleep_time > 0)
	{
		float tt = sleep_time / 1000.0f;

		std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(tt)));
	}

}

/**============================================================================
//! @func   PrintFPS
//! @brief  FPS���o�͂���
============================================================================*/
void gameSystems::Framelate::PrintFPS()
{
	uInt32 IntervalFrame = 60;

	/*	FPS�v��	*/
	if (m_totalFrameCount % IntervalFrame == 0)
	{
		m_nowFPS = IntervalFrame / (m_currentTime - m_saveTime);
		m_saveTime = m_currentTime;

		/****	FPS�\���ݒ�	****/
		std::stringstream ss;
		ss << "FPS�F" << m_nowFPS;
		std::string text = ss.str();
		systems::Window::GetInstance()->ChangeWindowText(text);
		
	}
}





