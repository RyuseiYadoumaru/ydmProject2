#include "Object.h"
#include "macro.h"
USING_SYSTEMS;
uInt32 Object::m_objectCounter = 0;

systems::Object::Object(String name, bool active) : m_name(name), m_isActive(active)
{
	m_objectCounter++;
	m_id = m_objectCounter;
}
