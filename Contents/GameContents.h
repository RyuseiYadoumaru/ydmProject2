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
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Color.h"
#include "Matrix4x4.h"
#include "Quaternion.h" 
#include "Easing.h"


// コンポーネント
// 物理周り
#include "Transform.h"

// グラフィック周り
#include "Camera.h"
#include "MeshRenderer.h"


// マネージャー
#include "SceneManager.h"
#include "RenderManager.h"
#include "GameObjectManager.h"
// 入力
#include "GamePad.h"
#include "Mouse.h"
#include "Keyboard.h"


// オブジェクト
#include "GameObject.h"
#include "DefaultCamera.h"
#include "Scene.h"
#include "Script.h"

// ツール
#include "Debug.h"