//
// Created by Вячеслав Кривенко on 25.10.2022.
//

#ifndef VICTORIAM_WGAMEOBJECT_HPP
#define VICTORIAM_WGAMEOBJECT_HPP

#include <Victoriam/Core/CBase.hpp>
#include <Victoriam/World/Components/Components.hpp>

VISRCBEG

class CWorld;

class CGameObject
{
	friend class CWorld;

	UID m_ID;
	CWorld* m_Owner;
	List<SComponentBase*> m_Components;

	VIDECL explicit CGameObject(CWorld* owner);
	VIDECL void Destroy();
public:
	VIDECL ~CGameObject() {}
	VIDECL VIREQOUT UID GetUID() const;

	template<class T>
	VIDECL T& AddComponent()
	{
		T* component = new T();
		m_Components.push_back(component);
		return *component;
	}
	template<class T>
	VIDECL VIREQOUT Bool HasComponent() const
	{
		if (m_Components.empty()) return false;
		for (auto component : m_Components)
			if (component->GetComponentID() == T::GetStaticComponentID())
				return true;
		return false;
	}
	template<class T>
	VIDECL T& GetComponent()
	{
		for (auto component : m_Components)
			if (component->GetComponentID() == T::GetStaticComponentID())
				return *(T*)component;
		ViLog("GameObject doesn't have such component! Creating new one...\n");
		return AddComponent<T>();
	}

};

VISRCEND

#endif //VICTORIAM_WGAMEOBJECT_HPP
