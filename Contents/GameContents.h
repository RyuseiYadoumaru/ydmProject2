//*****************************************************************************
//* @file   GameContents.h
//* @brief  ゲームに使用するコンテンツのインクルードをまとめる
//* @note   
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#pragma once

#include "std.h"
#include "macro.h"
#include "Tag.h"

// 数学
#include "myMath.h"

// コンポーネント
// 物理周り
#include "Transform.h"

// グラフィック周り
#include "Camera.h"
#include "MeshRenderer.h"
#include "SkinnedMeshRenderer.h"

// その他
#include "Animator.h"


// マネージャー
#include "SceneManager.h"
#include "GameObjectManager.h"
// 入力
#include "GamePad.h"
#include "Mouse.h"
#include "Keyboard.h"
// 時間
#include "Timer.h"
// リソース
#include "MeshManager.h"
#include "TextureManager.h"
#include "StaticMesh.h"
#include "SkeletalMesh.h"
#include "Material.h"
#include "Texture.h"
#include "AnimationClip.h"
#include "BlendAnimationClip.h"



// オブジェクト
#include "GameObject.h"
#include "DefaultCamera.h"
#include "Scene.h"
#include "Script.h"

// ツール
#include "Debug.h"