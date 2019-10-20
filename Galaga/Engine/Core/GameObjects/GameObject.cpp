#include "GameObject.h"
#include "Core/Components/BaseComponent.h"
#include "Core/Components/TransformComponent.h"
#include "Core/SceneManagement/SceneManager.h"
#include "Core/SceneManagement/Scene.h"
#include <vector>

GameObject::GameObject() : active(true), pendingToDestroy(false)
{
	transform = AddComponent<TransformComponent>();
}

GameObject::~GameObject()
{
	for (auto component : components)
		delete component;
	for (auto child : childObjects)
		delete child;
}

void GameObject::Update(float deltaTime)
{
	if (!active)
		return;

	for (auto component : components)
		component->Update(deltaTime);
	for (auto child : childObjects)
		child->Update(deltaTime);
}

void GameObject::Destroy()
{
	pendingToDestroy = true;
}

bool GameObject::IsPendingToDestroy()
{
	if (pendingToDestroy)
		return true;
	else
	{
		// Check for children.
		auto itr = childObjects.begin();
		while (itr != childObjects.end())
		{
			GameObject* child = *itr;
			if (child->IsPendingToDestroy())
			{
				delete child;
				itr = childObjects.erase(itr);
			}
			else
				itr++;
		}
		return false;
	}
}
