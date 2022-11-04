//*****************************************************************************
//* @file   Object.h
//* @brief  オブジェクトクラス
//* @note   全てのオブジェクトの元となるクラス
//* 
//* @author YadoumaruRyusei
//* @date   July 2022
//*****************************************************************************
#pragma once
#include "std.h"
#include "Tag.h"

#define OBJECT_CLASS using systems::Object::Object;
namespace systems
{
	class Object
	{
	public:
		void SetActive(bool set) noexcept { m_isActive = set; }
		const bool IsActive() const noexcept { return m_isActive; }
		const String& ToString() const noexcept { return m_name; }

	public:
		Object(String name = "noname", bool active = true);
		~Object() = default;

	protected:
		String m_name;
		uInt32 m_id;
		bool m_isActive;

	private:
		static uInt32 m_objectCounter;
	};
}
