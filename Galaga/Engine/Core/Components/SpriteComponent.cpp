#include "SpriteComponent.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_render.h"
#include "../../Render/Renderer.h"
#include "../GameObjects/GameObject.h"
#include "../Components/TransformComponent.h"

SpriteComponent::SpriteComponent(GameObject* _owner)
	: BaseComponent(_owner), Drawable(0), texture(nullptr), flip(SDL_RendererFlip::SDL_FLIP_NONE)
{
	Renderer::Get()->RegisterDrawable(this);
}

void SpriteComponent::Update(float deltaTime)
{
}

void SpriteComponent::SetTexture(SDL_Texture* _texture, SDL_RendererFlip _flip)
{ 
	SetTexture(_texture);
	flip = _flip;
}

Vector2D SpriteComponent::GetSize() const
{
	int width, height;
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
	return Vector2D(width, height);
}

Vector2D SpriteComponent::GetOrigin(Space space) const
{
	Vector2D origin = GetSize() / 2;
	switch (space)
	{
	case Space::Relative:
		return origin;
		break;
	case Space::World:
		return owner->GetTranform()->GetPosition() + origin;
		break;
	default:
		return Vector2D();
	}
}

SDL_Texture* SpriteComponent::GetRenderTarget(Vector2D& pos, float& angle, SDL_RendererFlip& flip, Vector2D& size)
{
	if (texture == nullptr)
		return nullptr;
	
	pos = owner->GetTranform()->GetPosition();
	angle = owner->GetTranform()->GetRotation();
	size = GetSize();
	flip = this->flip;
	return texture;
}

SpriteComponent::~SpriteComponent()
{
	Renderer::Get()->UnregisterDrawable(this);
	if (texture)
		SDL_DestroyTexture(texture);
}
