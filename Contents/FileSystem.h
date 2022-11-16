//*****************************************************************************
//* @file   FileSystem.h
//* @brief  ファイルシステム
//* @note   ファイルの便利関数をまとめる
//* 
//* @author YadoumaruRyusei
//* @date   August 2022
//*****************************************************************************
#pragma once
#include "std.h"
#include "macro.h"


/**
 * データの形式.
 */
namespace data
{
	enum class Type
	{
		File	= 0,
		Folder	= 1
	};
}

namespace TOOLS
{
	class FileSystem
	{
	public:

		/**
		 * ファイル名パスからファイルパスを取得する
		 * 第二引数をfalseにすることで拡張子を削除することが可能.
		 */
		static T_String GetFileName(T_StringView filePath, bool isExt = true) noexcept;

		/**
		 * ファイル拡張子取得.
		 */
		static T_String GetFileExt(T_StringView filePath) noexcept;

		/**
		 * フォルダかファイルかを返す.
		 */
		static data::Type JudgeFolderOrFile(T_StringView dataName) noexcept;


		/**
		 * フォルダから拡張子を探索し、全てのファイルパスをリストにして返す.
		 */
		static Vector<T_String> GetAllFileFromFolder(T_StringView folderPath, T_StringView extName);
	
		/**
		 * ファイルが存在するディレクトリを返す.
		*/
		static T_String GetDirectryPathFromFilePath(T_StringView filePath);
	
	private:
		constexpr static T_Char m_slash	= TEXT('/');
		constexpr static T_Char m_dot	= TEXT('.');

	};
}
