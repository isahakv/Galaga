#include "SpriteComponent.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_render.h"
#include "../../Render/Renderer.h"
#include "../GameObjects/GameObject.h"
#include "../Components/TransformComponent.h"

SpriteComponent::SpriteComponent(GameObject* _owner, SDL_Texture* _texture, int sortingOrder)
	: BaseComponent(_owner), Drawable(sortingOrder)
{
	Renderer::Get()->RegisterDrawable(this);
	SetTexture(_texture);
}

void SpriteComponent::Update(float deltaTime)
{
	if (texture == nullptr)
		return;

	// Renderer::Get()->Render(texture, owner->GetTranform()->GetPosition(), GetSize(), 0);
}

Vector2D SpriteComponent::GetSize() const
{
	int width, height;
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
	return Vector2D(width, height);
}

SDL_Texture* SpriteComponent::GetRenderTarget(Vector2D& pos, Vector2D& size)
{
	if (texture == nullptr)
		return nullptr;
	
	pos = owner->GetTranform()->GetPosition();
	size = GetSize();
	return texture;
}

SpriteComponent::~SpriteComponent()
{
	Renderer::Get()->UnregisterDrawable(this);
	SDL_DestroyTexture(texture);
}
