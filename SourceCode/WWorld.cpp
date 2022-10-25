//
// Created by Вячеслав Кривенко on 25.10.2022.
//

#include <Victoriam/World/WWorld.hpp>
#include <Victoriam/World/WGameObject.hpp>

VISRCBEG

CGameObject* CWorld::CreateGameObject()
{
	return new CGameObject(this);
}

CGameObject* CWorld::CreateGameObject(const CString &name)
{
	CGameObject* obj = CreateGameObject();
	auto& nc = obj->AddComponent<SComponentName>();
	nc.Name = name;
	return obj;
}

void CWorld::DestroyGameObject(CGameObject* object)
{
	object->Destroy();
}
void CWorld::OnGameObjectCreated(CGameObject *object)
{
	m_Registry.push_back(object);
}


void CWorld::OnGameObjectDestroyed(CGameObject *object)
{
	for (auto it = m_Registry.begin(); it != m_Registry.end(); it++)
		if ((*it)->GetUID() == object->GetUID()) {
			m_Registry.erase(it);
			return;
		}
}

CGameObject* CWorld::FindGameObjectByUID(const UID &id)
{
	Bool found = std::all_of(m_Registry.begin(), m_Registry.end(), [&](CGameObject* obj) -> Bool
	{
		return obj->GetUID() == id;
	});
	if (found)
		return m_Registry.at(id);
	else
	{
		ViLog("GameObject not found. Creating new one...");
		return CreateGameObject();
	}
}

SPtr<CWorld> CWorld::Create() {
	return CreateSPtr<CWorld>();
}

void CWorld::Clear()
{
	for (auto object : m_Registry)
		object->Destroy();
}

VISRCEND
