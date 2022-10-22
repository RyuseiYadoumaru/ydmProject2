//******************************************************************************
//* @file   macro.h
//* @brief  マクロ定義
//* @note   通用的な便利マクロをまとめる
//* 
//* @author YadoumaruRyusei
//* @date   July 2022
//*****************************************************************************
#pragma once
#include "std.h"


/**
 * ポインタをデリートする
 */
#define SAFE_DELETE(value)	\
if(value != nullptr){		\
	delete value;			\
	value = nullptr;		\
}							\

#define SAFE_DELETE_ARRAY(value)	\
if(value != NULL){					\
	delete[] value;					\
	value = NULL;					\
}									

/**
 * アラインメント
 */
#define ALIGN(N) _declspec(align(N))
#define ALIGN16 ALIGN(16)


/**
 * コピー禁止クラス
 */
#define COPY_PROHIBITED(CLASS)				 \
CLASS(const CLASS&) = delete;				 \
CLASS& operator=(const CLASS&) = delete;	 \


/**
 * シングルトンクラス.
 */
#define SINGLETON_CLASS(CLASS)				\
public:										\
static CLASS* GetInstance() noexcept{		\
static CLASS instance;						\
return &instance;							\
}											\
private:									\
CLASS() = default;							\
CLASS(const CLASS&) = delete;				\
CLASS& operator=(const CLASS&) = delete;	


#define USING_SYSTEMS		using namespace systems;
#define USING_GAME_SYSTEMS	using namespace gameSystems;
#define USING_TOOLS			using namespace tools;
