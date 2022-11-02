//*****************************************************************************
//* @file   Debug.h
//* @brief  デバッグクラス
//* @note   
//* 
//* @author YadoumaruRyusei
//* @date   July 2022
//*****************************************************************************
#pragma once
#include "std.h"

namespace tools
{
	class Debug final
	{
	public:
		template<class T>
		static void Log(T log)
		{
			std::stringstream stream;
			stream << log;
			Log(stream.str());
		}
		template<class T>
		static void Log(String logStr, T log)
		{
			std::stringstream stream;
			stream << logStr << log;
			Log(stream.str());
		}

		template<class T>
		static void LogWarning(T log)
		{
			std::stringstream stream;
			stream << log;
			LogWarning(stream.str());
		}

		template<class T>
		static void LogWarning(String logStr, T log)
		{
			std::stringstream stream;
			stream << logStr << log;
			LogWarning(stream.str());
		}

		template<class T>
		static void LogError(T log)
		{
			std::stringstream stream;
			stream << log;
			LogError(stream.str());
		}

		template<class T>
		static void LogError(String logStr, T log)
		{
			std::stringstream stream;
			stream << logStr << log;
			LogError(stream.str());
		}

	public:
		static void Log(String log);
		static void LogError(String log);
		static void LogWarning(String log);
		static void LogClear() noexcept { std::system("cls"); }

		static void Stop();
		static void Assert(bool flag) noexcept;
		static void Assert(bool flag, String log) noexcept;
	};

}