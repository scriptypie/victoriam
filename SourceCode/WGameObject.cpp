//
// Created by Вячеслав Кривенко on 25.10.2022.
//

#include <Victoriam/World/WGameObject.hpp>
#include <Victoriam/World/WWorld.hpp>

VISRCBEG


CGameObject::CGameObject(CWorld *owner)
{
	m_Owner = owner;

	m_ID = m_Owner->m_Registry.size();
	m_Owner->OnGameObjectCreated(this);
}

UID CGameObject::GetUID() const
{
	return m_ID;
}

void CGameObject::Destroy()
{
	m_Owner->OnGameObjectDestroyed(this);
}


VISRCEND
