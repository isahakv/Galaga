#include "GameObject.h"
#include "../Components/BaseComponent.h"
#include "../Components/TransformComponent.h"

GameObject::GameObject() : active(true)
{
	transform = new TransformComponent(this);
	components.push_back(transform);
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
}
