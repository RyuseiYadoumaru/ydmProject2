//*****************************************************************************
//* @file   EditorManager.h
//* @brief  
//* 
//* @author YadoumaruRyusei
//* @date   November 2022
//*****************************************************************************
#pragma once
#include "macro.h"
#include "std.h"
#include "Debug.h"
#include "GuiSystem.h"
#include "Core/Editor.h"

namespace SYSTEMS
{
	template<class T>
	concept TEditor = requires(T editor)
	{
		editor.Render();
	};

	class EditorManager
	{
		SINGLETON_CLASS(EditorManager);
		friend systems::GuiSystem;
		using EditorContainer = Unordered_Map<T_String, SharedPtr<Editor>>;

	public:
		/**
		 * エディターの生成.
		 */
		template<TEditor TYPE>
		SharedPtr<TYPE> Create(T_String windowName, Float32 posX, Float32 posY)
		{
			if (m_editorList.contains(windowName.c_str()) == true)
			{
				return nullptr;
			}
			auto buff = std::make_shared<TYPE>(windowName, posX, posY);
			m_editorList[windowName] = buff;
		}


		/**
		 *  エディター取得.
		 * 
		 * !@param windowName
		 * !@return 
		 */
		template <TEditor TYPE = Editor>
		SharedPtr<TYPE> GetEditor(T_String windowName)
		{
			if (m_editorList.contains(windowName) == true)
			{
				auto buff = std::dynamic_pointer_cast<TYPE>(m_editorList[windowName]);
				return buff;
			}	
			return nullptr;
		}

	private:
		EditorContainer m_editorList;

	};
}

