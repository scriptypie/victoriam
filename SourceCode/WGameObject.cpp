//
// Created by Вячеслав Кривенко on 25.10.2022.
//

#include <Victoriam/World/WGameObject.hpp>
#include <Victoriam/World/WWorld.hpp>

VISRCBEG

CGameObject::CGameObject(const PWorld& owner) {
	m_Owner = owner;
	m_ID = m_Owner->m_Registry.size();
}

UID CGameObject::GetUID() const {
	return m_ID;
}

void CGameObject::Destroy() {
	m_Owner->OnGameObjectDestroyed(SharedFromThis());
}

VISRCEND
