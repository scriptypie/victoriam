//
// Created by Вячеслав Кривенко on 25.10.2022.
//

#ifndef VICTORIAM_WWORLD_HPP
#define VICTORIAM_WWORLD_HPP

#include <Victoriam/Core/CBase.hpp>
#include <Victoriam/World/WGameObject.hpp>

VISRCBEG

class CWorld
{
	friend class CGameObject;

	List<CGameObject*> m_Registry;
public:
	VIDECL VIREQOUT CGameObject* CreateGameObject();
	VIDECL VIREQOUT CGameObject* CreateGameObject(const String& name);
	VIDECL void DestroyGameObject(CGameObject* object);
	VIDECL VIREQOUT CGameObject* FindGameObjectByUID(const UID& id);
	VIDECL VIREQOUT CGameObject* FindGameObjectByName(const String& name);

	template<class T>
	VIDECL VIREQOUT List<CGameObject*> FindGameObjectsWithComponent()
	{
		List<CGameObject*> result;

		for (auto obj : m_Registry)
			if (obj->HasComponent<T>())
				result.push_back(obj);

		return result;
	}

	static SPtr<CWorld> Create();
	VIDECL void Clear();
private:
	void OnGameObjectCreated(CGameObject* object);
	void OnGameObjectDestroyed(CGameObject* object);
};

VIDECL typedef SPtr<CWorld> PWorld;

VISRCEND

#endif //VICTORIAM_WWORLD_HPP
