#include "GameSystemManager.h"

void gameSystems::GameSystemManager::Releace()
{
	for (auto& stage : m_gameSubSystemList)
	{
		for (auto& subSystem : stage.second)
		{
			for (auto& system : subSystem.second)
			{
				system.second->Finalize();
			}
		}
	}
	m_gameSubSystemList.clear();
}

