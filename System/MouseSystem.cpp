//*****************************************************************************
//* @file   MouseSystem.cpp
//* @brief  �}�E�X�V�X�e��
//* @note   �}�E�X���͎���̍X�V���s��
//* 
//* @author YadoumaruRyusei
//* @date   September 2022
//*****************************************************************************

#include "MouseSystem.h"
#include "Debug.h"
#include "Inputsystem.h"


/**
 *  �}�E�X�f�o�C�X�̎擾�𖈃t���[���s���܂� .
 * 
 * !@return�@true : ����I��
 */
bool GAME_SYSTEMS::MouseSystem::Initialize()
{
    return true;
}
bool GAME_SYSTEMS::MouseSystem::Run()
{
    HRESULT hr = S_OK;
    auto mouseDevice = systems::Inputsystem::GetInstance()->GetDirectMouse();
    
    // �}�E�X��Ԏ擾 
    m_oldMouseState = m_mouseState;
    hr = mouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), &m_mouseState);
    if (FAILED(hr))
    {
        // �f�o�C�X�̍ĔF��
        mouseDevice->Acquire();
        return false;
    }

    return true;
}

bool GAME_SYSTEMS::MouseSystem::Finalize()
{
    return true;
}
