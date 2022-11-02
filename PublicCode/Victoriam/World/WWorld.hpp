//
// Created by Вячеслав Кривенко on 25.10.2022.
//

#ifndef VICTORIAM_WWORLD_HPP
#define VICTORIAM_WWORLD_HPP

#include <Victoriam/Core/CBase.hpp>
#include <Victoriam/World/WGameObject.hpp>
#include <Victoriam/Graphics/Structs/GWorldRendererSettings.hpp>
#include <Victoriam/Graphics/GBuffer.hpp>

VISRCBEG

class CWorld
{
	friend class CGameObject;

	List<CGameObject*> m_Registry = {};
	SWorldRendererSettings m_RendererSettings = {};
	PBuffer m_RendererConstantsBuffer = nullptr;
public:
	VIDECL VIREQOUT CGameObject* CreateGameObject();
	VIDECL VIREQOUT CGameObject* CreateGameObject(const String& name);
	VIDECL void DestroyGameObject(CGameObject* object);
	VIDECL VIREQOUT CGameObject* FindGameObjectByUID(const UID& id);
	VIDECL VIREQOUT CGameObject* FindGameObjectByName(const String& name);

	template<class...T>
	VIDECL VIREQOUT List<CGameObject*> AllWith()
	{
		List<CGameObject*> result;

		for (auto obj : m_Registry)
			if ((obj->HasComponent<T>() && ...))
				result.push_back(obj);

		return result;
	}

	template<class...T>
	VIDECL VIREQOUT CGameObject* OneWith()
	{
		for (auto obj : m_Registry)
			if ((obj->HasComponent<T>() && ...))
				return obj;
		return nullptr;
	}

	explicit CWorld(const PBuffer& constantsUniformBuffer, const SWorldRendererSettings& rendererSettings);
	static SPtr<CWorld> Create(const PBuffer& constantsUniformBuffer, const SWorldRendererSettings& rendererSettings = SWorldRendererSettings());
	VIDECL VIREQOUT inline SWorldRendererSettings GetRendererSettings() const { return m_RendererSettings; }
	VIDECL VIREQOUT inline PBuffer& GetConstantBuffer() { return m_RendererConstantsBuffer; }
	void Update(const Float32& dt);
	VIDECL void Clear();
private:

	void OnGameObjectCreated(CGameObject* object);
	void OnGameObjectDestroyed(CGameObject* object);
};

VIDECL typedef SPtr<CWorld> PWorld;

VISRCEND

#endif //VICTORIAM_WWORLD_HPP
