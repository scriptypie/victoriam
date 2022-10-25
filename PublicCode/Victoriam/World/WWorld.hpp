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
	VIDECL CGameObject* CreateGameObject();
	VIDECL void DestroyGameObject(CGameObject* object);
	VIDECL CGameObject* FindGameObjectByUID(const UID& id);

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
