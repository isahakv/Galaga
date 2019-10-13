#include "VelocityComponent.h"
#include <math.h>
#include "Core/GameObjects/GameObject.h"
#include "Core/Components/TransformComponent.h"

VelocityComponent::VelocityComponent(GameObject* _owner)
	: BaseComponent(_owner), speed(0.f)
{
}

void VelocityComponent::Update(float deltaTime)
{
	if (speed == 0.f)
		return;

	owner->GetTranform()->Translate(velocity * deltaTime);
}

void VelocityComponent::SetSpeed(float speed)
{
	this->speed = speed;
	float angle = owner->GetTranform()->GetRotation();
	velocity.x = sin(angle) * speed;
	velocity.y = -cos(angle) * speed;
}
