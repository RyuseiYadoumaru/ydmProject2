//*****************************************************************************
//* @file   FileSystem.h
//* @brief  �t�@�C���V�X�e��
//* @note   �t�@�C���֗̕��֐����܂Ƃ߂�
//* 
//* @author YadoumaruRyusei
//* @date   August 2022
//*****************************************************************************
#pragma once
#include "std.h"
#include "macro.h"


/**
 * �f�[�^�̌`��.
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
		 * �t�@�C�����p�X����t�@�C���p�X���擾����
		 * ��������false�ɂ��邱�ƂŊg���q���폜���邱�Ƃ��\.
		 */
		static T_String GetFileName(T_StringView filePath, bool isExt = true) noexcept;

		/**
		 * �t�@�C���g���q�擾.
		 */
		static T_String GetFileExt(T_StringView filePath) noexcept;

		/**
		 * �t�H���_���t�@�C������Ԃ�.
		 */
		static data::Type JudgeFolderOrFile(T_StringView dataName) noexcept;


		/**
		 * �t�H���_����g���q��T�����A�S�Ẵt�@�C���p�X�����X�g�ɂ��ĕԂ�.
		 */
		static Vector<T_String> GetAllFileFromFolder(T_StringView folderPath, T_StringView extName);
	
		/**
		 * �t�@�C�������݂���f�B���N�g����Ԃ�.
		*/
		static T_String GetDirectryPathFromFilePath(T_StringView filePath);
	
	private:
		constexpr static T_Char m_slash	= TEXT('/');
		constexpr static T_Char m_dot	= TEXT('.');

	};
}
