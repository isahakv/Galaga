#include "GameObject.h"
#include "Core/Components/BaseComponent.h"
#include "Core/Components/TransformComponent.h"
#include "Core/SceneManagement/SceneManager.h"
#include "Core/SceneManagement/Scene.h"

GameObject::GameObject() : active(true), pendingToDestroy(false)
{
	transform = AddComponent<TransformComponent>();
}

GameObject::~GameObject()
{
	for (auto component : components)
		delete component;
}

void GameObject::Update(float deltaTime)
{
	for (auto component : components)
		component->Update(deltaTime);

	if (pendingToDestroy)
		DestroyImmediate();
}

void GameObject::Destroy()
{
	pendingToDestroy = true;
}

void GameObject::DestroyImmediate()
{
	SceneManager::GetActiveScene()->Destroy(this);
}
