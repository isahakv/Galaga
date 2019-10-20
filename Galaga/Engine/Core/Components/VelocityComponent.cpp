#include "VelocityComponent.h"
// STD
#include <math.h>
#include <iostream>
// Core
#include "Core/GameObjects/GameObject.h"
#include "Core/Components/TransformComponent.h"

VelocityComponent::VelocityComponent(GameObject* _owner)
	: BaseComponent(_owner)
{
}

void VelocityComponent::Update(float deltaTime)
{
	owner->GetTranform()->Translate(velocity * deltaTime);
}

void VelocityComponent::SetVelocity(const Vector2D& _velocity, Space space)
{
	float angle;
	switch (space)
	{
	case Space::Relative:
		angle = owner->GetTranform()->GetRotation();
		velocity = Vector2D::RotateVector(_velocity, angle);
		break;
	case Space::World:
		velocity = _velocity;
		break;
	}
}
