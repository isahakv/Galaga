#include "ColliderComponent.h"
// Core
#include "Physics/Physics.h"
#include "Render/Renderer.h"
#include "Core/GameObjects/GameObject.h"
#include "Core/Components/TransformComponent.h"

ColliderComponent::ColliderComponent(GameObject* _owner)
	: BaseComponent(_owner), bounds(), collisionLayer(CollisionLayer::None)
{
	Physics::Get()->RegisterCollider(this);
}

ColliderComponent::~ColliderComponent()
{
	Physics::Get()->UnregisterCollider(this);
}

void ColliderComponent::Update(float deltaTime)
{
	SDL_Rect rect = GetBounds();
	// Renderer::Get()->DrawDebugRect(&rect);
}

SDL_Rect ColliderComponent::GetBounds() const
{
	Vector2D pos = owner->GetTranform()->GetPosition();
	// Adding offset.
	pos += Vector2D((float)bounds.x, (float)bounds.y);
	return SDL_Rect{ (int)pos.x, (int)pos.y, bounds.w, bounds.h };
}

void ColliderComponent::SetLayer(CollisionLayer layer)
{
	Physics::Get()->UnregisterCollider(this);
	collisionLayer = layer;
	Physics::Get()->RegisterCollider(this);
}


void ColliderComponent::OnCollisionEnter(ColliderComponent* other)
{
	if (handlerCollisionEnter)
		handlerCollisionEnter(other);
}
