#include "TransformComponent.h"

TransformComponent::TransformComponent(GameObject* owner)
	: BaseComponent(owner), position(0, 0), rotationAngle(0)
{

}

void TransformComponent::Update(float deltaTime)
{

}
