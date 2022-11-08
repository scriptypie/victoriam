//
// Created by Вячеслав Кривенко on 25.10.2022.
//

#include <Victoriam/World/WWorld.hpp>
#include <Victoriam/World/WGameObject.hpp>
#include <Victoriam/Input/IInput.hpp>
#include <Victoriam/Graphics/GRenderer.hpp>

VISRCBEG

CGameObject* CWorld::CreateGameObject()
{
	return new CGameObject(this);
}

CGameObject* CWorld::CreateGameObject(const String &name)
{
	CGameObject* obj = CreateGameObject();
	auto nc = obj->AddComponent<SComponentName>();
	nc->Name = name;
	return obj;
}

void CWorld::DestroyGameObject(CGameObject* object)
{
	object->Destroy();
}
void CWorld::OnGameObjectCreated(CGameObject *object)
{
	m_Registry.push_back(object);
}


void CWorld::OnGameObjectDestroyed(CGameObject *object)
{
	for (auto it = m_Registry.begin(); it != m_Registry.end(); it++)
		if ((*it)->GetUID() == object->GetUID()) {
			m_Registry.erase(it);
			return;
		}
}

CGameObject* CWorld::FindGameObjectByUID(const UID &id)
{
	Bool found = std::all_of(m_Registry.begin(), m_Registry.end(), [&](CGameObject* obj) -> Bool
	{
		return obj->GetUID() == id;
	});
	if (found)
		return m_Registry.at(id);
	else
	{
		ViLog("GameObject not found. Creating new one...\n");
		return CreateGameObject();
	}
}

SPtr<CWorld> CWorld::Create(PRenderer& renderer, const SWorldRendererSettings& rendererSettings) {
	return CreateSPtr<CWorld>(renderer, rendererSettings);
}

void CWorld::Clear()
{
	for (auto object : m_Registry)
		object->Destroy();
}

CGameObject *CWorld::FindGameObjectByName(const String &name)
{
	for (auto obj : m_Registry)
	{
		auto componentName = obj->GetComponent<SComponentName>();
		if (componentName && componentName->Name == name)
			return obj;
	}
	ViLog("GameObject '%s' not found. Creating new one with the given name...\n", name.c_str());
	return CreateGameObject(name);
}

void CWorld::Update(const Float32 &dt)
{

}

CWorld::CWorld(PRenderer& renderer, const SWorldRendererSettings &rendererSettings) : m_RendererSettings(rendererSettings), m_RendererConstantsBuffers(renderer->GetSwapchain()->GetMaxFramesInFlight())
{
	for (auto& m_RendererConstantsBuffer : m_RendererConstantsBuffers)
	{
		m_RendererConstantsBuffer = renderer->CreateUniformBuffer();
		m_RendererConstantsBuffer->Bind(nullptr); // command buffers on binding uniform buffers are unnecessary.
	}
}

VISRCEND
