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
	Renderer::Get()->DrawDebugRect(&rect);
}

void ColliderComponent::SetBounds(const SDL_Rect& _bounds)
{
	bounds = _bounds;
}

SDL_Rect ColliderComponent::GetBounds() const
{
	Vector2D pos = owner->GetTranform()->GetPosition();
	// Adding offset.
	pos += Vector2D((float)bounds.x, (float)bounds.y);
	return SDL_Rect{ (int)pos.x, (int)pos.y, bounds.w, bounds.h };
}
