//*****************************************************************************
//!	@file	std.h
//!	@brief	標準ライブラリ
//!	@author	YadoumaruRyusei
//*****************************************************************************
#pragma once
#define __STDC_WANT_LIB_EXT1__ 1
#include	<string>
#include	<string_view>
#include	<memory>
#include	<array>
#include	<vector>
#include	<list>
#include	<stack>
#include	<queue>
#include	<stack>
#include	<map>
#include	<unordered_map>
#include	<functional>
#include	<cinttypes>
#include	<cassert>
#include	<sstream>

#include	<wrl/client.h>
#include	<stdint.h>
#include	<tchar.h>
#include	<string.h>

#include	<d3d11.h>

using Int8			=	signed char;
using uInt8			=	unsigned char;
using Int16			=	short;
using uInt16		=	unsigned short;
using Int32			=	int;
using uInt32		=	unsigned int;
using Int64			=	long long;
using uInt64		=	unsigned long long;
using Float32		=	float;
using Float64		=	double;
using Byte			=	unsigned char;

/**
 * 文字コード.
 */
using Char = char;
using String = std::string;
using StringView = std::string_view;
using W_Char = wchar_t;
using W_String = std::wstring;
using W_StringView = std::wstring_view;

#ifdef _UNICODE
using T_Char = wchar_t;
using T_String = std::wstring;
using T_StringView = std::wstring_view;
#else 
using T_Char = char;
using T_String = std::string;
using T_StringView = std::string_view;

#endif


template<class T>
using Vector = std::vector<T, std::allocator<T>>;
template<class T>
using List = std::list<T, std::allocator<T>>;
template<class T>
using Queue = std::queue<T, std::deque<T, std::allocator<T>>>;
template<class T>
using Stack = std::stack<T, std::deque<T, std::allocator<T>>>;
template<class T, class U>
using Map = std::map<T, U, std::less<T>, std::allocator<std::pair<const T, U>>>;
template<class T, class U>
using Unordered_Map = std::unordered_map<T, U, std::hash<T>, std::equal_to<T>, std::allocator<std::pair<const T, U>>>;
template<class T>
using UniquePtr = std::unique_ptr<T>;
template<class T>
using SharedPtr = std::shared_ptr<T>;
template<class T, std::size_t N>
using Array = std::array<T, N>;

using Microsoft::WRL::ComPtr;

#define USE_DIRECTMATH (FALSE)
