//
// Created by Вячеслав Кривенко on 25.10.2022.
//

#ifndef VICTORIAM_WWORLD_HPP
#define VICTORIAM_WWORLD_HPP

#include <Victoriam/Core/CBase.hpp>
#include <Victoriam/World/WGameObject.hpp>
#include <Victoriam/Graphics/Structs/GWorldRendererSettings.hpp>
#include <Victoriam/Graphics/GUniformBuffer.hpp>

VISRCBEG

class CRenderer;
typedef UPtr<CRenderer> PRenderer;

class VIDECL CWorld
{
	friend class CGameObject;

	List<CGameObject*> m_Registry = {};
	SWorldRendererSettings m_RendererSettings = {};
	List<PUniformBuffer> m_RendererConstantsBuffers = {};
public:
	VIDECL VIREQOUT CGameObject* CreateGameObject();
	VIDECL VIREQOUT CGameObject* CreateGameObject(const String& name);
	VIDECL          void DestroyGameObject(CGameObject* object);
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
	VIDECL CGameObject* OneWith()
	{
		for (auto obj : m_Registry)
			if ((obj->HasComponent<T>() && ...))
				return obj;
		return nullptr;
	}

	VIDECL          explicit CWorld(PRenderer& renderer, const SWorldRendererSettings& rendererSettings);
	VIDECL VIREQOUT inline SWorldRendererSettings& GetRendererSettings() { return m_RendererSettings; }
	VIDECL VIREQOUT inline PUniformBuffer& GetConstantsBuffer(const UInt32& frameIndex) { return m_RendererConstantsBuffers.at(frameIndex); }
	VIDECL          void Update(const Float32& dt);
	VIDECL          void Clear();
	VIDECL VIREQOUT static SPtr<CWorld> Create(PRenderer& renderer, const SWorldRendererSettings& rendererSettings = SWorldRendererSettings());
private:
	VIDECL          void OnGameObjectCreated(CGameObject* object);
	VIDECL          void OnGameObjectDestroyed(CGameObject* object);
};

VIDECL typedef SPtr<CWorld> PWorld;

VISRCEND

#endif //VICTORIAM_WWORLD_HPP
