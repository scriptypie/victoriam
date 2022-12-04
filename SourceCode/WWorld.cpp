//
// Created by Вячеслав Кривенко on 25.10.2022.
//

#include <Victoriam/World/WWorld.hpp>
#include <Victoriam/World/WGameObject.hpp>
#include <Victoriam/IO/IOInput.hpp>
#include <Victoriam/Graphics/GRenderer.hpp>
#include <utility>

VISRCBEG

PGameObject CWorld::CreateGameObject() {
	auto object = FMakeShared<CGameObject>(SharedFromThis());
	OnGameObjectCreated(object);
	return object;
}

PGameObject CWorld::CreateGameObject(const String &name) {
	auto obj = CreateGameObject();
	auto nc = obj->AddComponent<SComponentName>();
	nc->Name = name;
	return obj;
}

void CWorld::DestroyGameObject(const PGameObject& object) {
	object->Destroy();
}
void CWorld::OnGameObjectCreated(const PGameObject& object) {
	m_Registry.PushBack(object);
}


void CWorld::OnGameObjectDestroyed(const PGameObject& object) {
	for (auto it = m_Registry.begin(); it != m_Registry.end(); it++)
		if ((*it)->GetUID() == object->GetUID()) {
			m_Registry.Erase(it);
			return;
		}
}

PGameObject CWorld::FindGameObjectByUID(const UID &id) {
	auto found = std::all_of(m_Registry.begin(), m_Registry.end(), [&](const PGameObject& obj) -> Bool
	{
		return obj->GetUID() == id;
	});
	if (found)
		return m_Registry.At(id);
	else
	{
		ViLog("GameObject not found!\n");
		return nullptr;
	}
}

PWorld CWorld::Create(PRenderer& renderer, const SWorldRendererSettings& rendererSettings) {
	return FMakeShared<CWorld>(renderer, rendererSettings);
}

void CWorld::Clear() {
	m_Registry.Clear();
}

PGameObject CWorld::FindGameObjectByName(const String &name) {
	for (auto obj : m_Registry) {
		auto componentName = obj->GetComponent<SComponentName>();
		if (componentName && componentName->Name == name)
			return obj;
	}
	ViLog("GameObject \'" << name << "\' not found. Creating new one with the given name...");
	return CreateGameObject(name);
}

void CWorld::Update(const Float32 &dt) {}

CWorld::CWorld(PRenderer& renderer, SWorldRendererSettings  rendererSettings)
	: m_RendererSettings(FMove(rendererSettings)),
	  m_RendererConstantsBuffers(renderer->GetSwapchain()->GetMaxFramesInFlight()) {
	for (auto& m_RendererConstantsBuffer : m_RendererConstantsBuffers) {
		m_RendererConstantsBuffer = renderer->CreateUniformBuffer();
		m_RendererConstantsBuffer->Bind(nullptr); // command buffers on binding uniform buffers are unnecessary.
	}
}

PGameObject CWorld::CreateChild(const PGameObject &parent) {
	auto child = CreateGameObject();
	child->m_Parent = parent.Get();
	parent->m_Children.EmplaceBack(child.Get());
	return child;
}

void CWorld::RemoveChildren(const PGameObject &parent) {
	for (auto& child : parent->m_Children)
		child->Destroy();
	parent->m_Children.Clear();
}

void CWorld::RemoveChildAt(const PGameObject &parent, const UInt32 &index) {
	if (parent->m_Children.Size() > index)
		parent->m_Children[index]->Destroy();
}

void CWorld::AddChild(const PGameObject &parent, const PGameObject &child) {
	parent->m_Children.PushBack(child.Get());
	child->m_Parent = parent.Get();
}

void CWorld::AddChildren(const PGameObject &parent, const CSet<PGameObject> &children) {
	for (auto& child : children) {
		parent->m_Children.PushBack(child.Get());
		child->m_Parent = parent.Get();
	}
}

VISRCEND
