//
// Created by Вячеслав Кривенко on 25.10.2022.
//

#ifndef VICTORIAM_WGAMEOBJECT_HPP
#define VICTORIAM_WGAMEOBJECT_HPP

#include <Victoriam/Core/CBase.hpp>
#include <Victoriam/World/Components/Components.hpp>

VISRCBEG

class CWorld;
VIDECL typedef CShared<CWorld> PWorld;

class VIDECL CGameObject : public CEnableSharedFrom<CGameObject>
{
	friend class CWorld;

	UID m_ID = {};
	PWorld m_Owner = {};
	CSet<CShared<SComponentBase>> m_Components = {};
	CGameObject* m_Parent = {};
	CSet<CGameObject*> m_Children = {};
public:
	VIDECL explicit CGameObject(const PWorld& owner);
	VIDECL ~CGameObject() = default;
	VIDECL VIREQOUT UID GetUID() const;

	template<class T, class...Args>
	VIDECL T* AddComponent(Args&&...args) {
		if (HasComponent<T>()) return nullptr;
		auto component = FMakeShared<T>(std::forward<Args>(args)...);
		m_Components.PushBack(component);
		return component.Get();
	}

	template<class...T>
	VIDECL void RemoveComponent() {
		for (auto it = m_Components.begin(); it != m_Components.end(); it++)
			if ((((*it)->GetComponentID() == T::GetStaticComponentID()) || ...)) {
				m_Components.Erase(it);
				return;
			}
	}

	template<class...T>
	VIDECL VIREQOUT CTuple<T*...> Group() {
		return FCreateTuple<T*...>(GetComponent<T>()...);
	}
	template<class...T>
	VIDECL VIREQOUT Bool HasComponent() const {
		if (m_Components.Empty()) return false;
		return std::any_of(m_Components.begin(), m_Components.end(), [&](const auto &item) {
			return (((item->GetComponentID() == T::GetStaticComponentID()) && ...));
		});
	}
	template<class T>
	VIDECL T* GetComponent() {
		for (auto& component : m_Components)
			if (component->GetComponentID() == T::GetStaticComponentID())
				return CCast<T*>(component.Get());
		return nullptr;
	}
private:
	VIDECL void Destroy();
};

VIDECL typedef CShared<CGameObject> PGameObject;

VISRCEND

#endif //VICTORIAM_WGAMEOBJECT_HPP
