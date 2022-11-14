//*****************************************************************************
//* @file   Model.cpp
//* @brief  
//* @note   ���f���ɕK�v�ȃf�[�^��ێ�����
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#include "Model.h"
#include "Mesh.h"
#include "Skeleton.h"

#include "../Assimpscene.h"
#include "../System/DirectXGraphics.h"

USING_SYSTEMS;

bool GAME_SYSTEMS::Model::LoadModel(T_String filePath)
{
    // Assimp�Ń{�[���ƃ��b�V�������[�h����
    AssimpScene assimpScene;
    assimpScene.Init(filePath);
    m_meshData = std::make_shared<Mesh>();
    m_meshData->Load(&assimpScene);
    m_skelton = std::make_shared<Skeleton>();
    m_skelton->Load(&assimpScene);
    assimpScene.Exit();
    return true;
}

void GAME_SYSTEMS::Model::Releace()
{
    if (m_meshData != nullptr)
    {
        m_meshData->Unload();
        m_meshData = nullptr;
    }
    if (m_skelton != nullptr)
    {
        m_skelton = nullptr;
    }
}

void GAME_SYSTEMS::Model::RenderModel()
{
    // ���b�V���`��
    ID3D11DeviceContext& deviceContext = DirectXGraphics::GetInstance()->GetImmediateContext();
    m_meshData->Draw();
}
