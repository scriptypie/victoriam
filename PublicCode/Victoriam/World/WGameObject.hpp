//
// Created by Вячеслав Кривенко on 25.10.2022.
//

#ifndef VICTORIAM_WGAMEOBJECT_HPP
#define VICTORIAM_WGAMEOBJECT_HPP

#include <Victoriam/Core/CBase.hpp>
#include <Victoriam/World/Components/Components.hpp>

VISRCBEG

class CWorld;

class VIDECL CGameObject
{
	friend class CWorld;

	UID m_ID;
	CWorld* m_Owner;
	CList<SComponentBase*> m_Components;
public:
	VIDECL ~CGameObject() { m_Components.clear(); }
	VIDECL VIREQOUT UID GetUID() const;

	template<class T, class...Args>
	VIDECL T* AddComponent(Args&&...args)
	{
		if (HasComponent<T>()) return nullptr;
		T* component = new T(std::forward<Args>(args)...);
		m_Components.push_back(component);
		return component;
	}
	template<class...T>
	VIDECL VIREQOUT CTuple<T*...> Group()
	{
		return FCreateTuple<T *...>(GetComponent<T>()...);
	}
	template<class...T>
	VIDECL VIREQOUT Bool HasComponent() const
	{
		if (m_Components.empty()) return false;
		for (auto component : m_Components)
			if (((component->GetComponentID() == T::GetStaticComponentID()) && ...))
				return true;
		return false;
	}
	template<class T>
	VIDECL T* GetComponent()
	{
		for (auto component : m_Components)
			if (component->GetComponentID() == T::GetStaticComponentID())
				return CCast<T*>(component);
		return nullptr;
	}
private:
	VIDECL explicit CGameObject(CWorld* owner);
	VIDECL void Destroy();
};

VISRCEND

#endif //VICTORIAM_WGAMEOBJECT_HPP
