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
typedef SUnique<CRenderer> PRenderer;

class VIDECL CWorld : public std::enable_shared_from_this<CWorld>
{
	friend class CGameObject;

	CList<PGameObject> m_Registry = {};
	SWorldRendererSettings m_RendererSettings = {};
	CList<PUniformBuffer> m_RendererConstantsBuffers = {};
public:
	VIDECL VIREQOUT PGameObject CreateGameObject();
	VIDECL VIREQOUT PGameObject CreateGameObject(const String& name);
	VIDECL          void DestroyGameObject(const PGameObject& object);
	VIDECL VIREQOUT PGameObject FindGameObjectByUID(const UID& id);
	VIDECL VIREQOUT PGameObject FindGameObjectByName(const String& name);

	VIDECL VIREQOUT PGameObject CreateChild(const PGameObject& parent);
	VIDECL void AddChild(const PGameObject& parent, const PGameObject& child);
	VIDECL void AddChildren(const PGameObject& parent, const CList<PGameObject>& children);
	VIDECL void RemoveChildren(const PGameObject& parent);
	VIDECL void RemoveChildAt(const PGameObject& parent, const UInt32& index);

	template<class...T>
	VIDECL VIREQOUT CList<PGameObject> AllWith()
	{
		CList<PGameObject> result;

		for (auto obj : m_Registry)
			if ((obj->HasComponent<T>() && ...))
				result.push_back(obj);

		return result;
	}

	template<class...T>
	VIDECL PGameObject OneWith()
	{
		for (auto obj : m_Registry)
			if ((obj->HasComponent<T>() && ...))
				return obj;
		return nullptr;
	}

	VIDECL          explicit CWorld(PRenderer& renderer, SWorldRendererSettings  rendererSettings);
	VIDECL VIREQOUT inline SWorldRendererSettings& GetRendererSettings() { return m_RendererSettings; }
	VIDECL VIREQOUT inline PUniformBuffer& GetConstantsBuffer(const UInt32& frameIndex) { return m_RendererConstantsBuffers.at(frameIndex); }
	VIDECL          void Update(const Float32& dt);
	VIDECL          void Clear();
	VIDECL VIREQOUT static SShared<CWorld> Create(PRenderer& renderer, const SWorldRendererSettings& rendererSettings = SWorldRendererSettings());
private:
	VIDECL          void OnGameObjectCreated(const PGameObject& object);
	VIDECL          void OnGameObjectDestroyed(const PGameObject& object);
};

VIDECL typedef SShared<CWorld> PWorld;

VISRCEND

#endif //VICTORIAM_WWORLD_HPP
