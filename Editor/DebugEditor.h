#pragma once
#include "EditorHeader.h"
namespace EDITOR_SYSTEMS
{
	class DebugEditor : public systems::Editor
	{
		EDITOR_CLASS;

	private:
		virtual void Update() override;

	};
}
