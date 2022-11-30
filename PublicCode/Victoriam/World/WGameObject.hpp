//
// Created by Вячеслав Кривенко on 25.10.2022.
//

#ifndef VICTORIAM_WGAMEOBJECT_HPP
#define VICTORIAM_WGAMEOBJECT_HPP

#include <Victoriam/Core/CBase.hpp>
#include <Victoriam/World/Components/Components.hpp>

VISRCBEG

class CWorld;
VIDECL typedef SShared<CWorld> PWorld;

class VIDECL CGameObject : public std::enable_shared_from_this<CGameObject>
{
	friend class CWorld;

	UID m_ID = {};
	PWorld m_Owner = {};
	CList<SShared<SComponentBase>> m_Components = {};
	CGameObject* m_Parent = {};
	CList<CGameObject*> m_Children = {};
public:
	VIDECL explicit CGameObject(const PWorld& owner);
	VIDECL ~CGameObject() { m_Components.clear(); }
	VIDECL VIREQOUT UID GetUID() const;

	template<class T, class...Args>
	VIDECL T* AddComponent(Args&&...args) {
		if (HasComponent<T>()) return nullptr;
		auto component = FCreateShared<T>(std::forward<Args>(args)...);
		m_Components.push_back(component);
		return component.get();
	}

	template<class...T>
	VIDECL void RemoveComponent() {
		for (auto it = m_Components.begin(); it != m_Components.end(); it++)
			if ((((*it)->GetComponentID() == T::GetStaticComponentID()) || ...)) {
				m_Components.erase(it);
				return;
			}
	}

	template<class...T>
	VIDECL VIREQOUT CTuple<T*...> Group() {
		return FCreateTuple<T*...>(GetComponent<T>()...);
	}
	template<class...T>
	VIDECL VIREQOUT Bool HasComponent() const {
		if (m_Components.empty()) return false;
		return std::any_of(m_Components.begin(), m_Components.end(), [&](const auto &item) {
			return (((item->GetComponentID() == T::GetStaticComponentID()) && ...));
		});
	}
	template<class T>
	VIDECL T* GetComponent() {
		for (auto& component : m_Components)
			if (component->GetComponentID() == T::GetStaticComponentID())
				return CCast<T*>(component.get());
		return nullptr;
	}
private:
	VIDECL void Destroy();
};

VIDECL typedef SShared<CGameObject> PGameObject;

VISRCEND

#endif //VICTORIAM_WGAMEOBJECT_HPP
