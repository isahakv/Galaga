#include "SpriteComponent.h"
// SDL
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_render.h"
// Core
#include "Render/Renderer.h"
#include "Core/Math/Vector2D.h"
#include "Core/Platform/Application.h"
#include "Core/GameObjects/GameObject.h"
#include "Core/Components/TransformComponent.h"

SpriteComponent::SpriteComponent(GameObject* _owner)
	: BaseComponent(_owner), Drawable(0), texture(nullptr),
	flip(SDL_RendererFlip::SDL_FLIP_NONE), color(SDL_Color{ 255, 255, 255, 255 })
{
	Renderer::Get()->RegisterDrawable(this);
	scaleFactor = Application::GetScaleFactor();
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
	return Vector2D((float)width, (float)height);
}

Vector2D SpriteComponent::GetScaledSize() const
{
	return GetSize() * scale * scaleFactor * 1.5f;
}

Vector2D SpriteComponent::GetOrigin(Space space) const
{
	Vector2D origin = GetScaledSize() / 2.f;
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

void SpriteComponent::SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	color = SDL_Color{ r, g, b, a };
}
void SpriteComponent::SetColor(Uint8 r, Uint8 g, Uint8 b)
{
	color = SDL_Color{ r, g, b, color.a };
}
void SpriteComponent::SetAlpha(Uint8 a)
{
	color = SDL_Color{ color.r, color.g, color.b, a };
}

SDL_Texture* SpriteComponent::GetRenderTarget(SDL_Rect& srcRect, SDL_Rect& dstRect, float& angle, SDL_RendererFlip& flip, SDL_Color& color)
{
	if (texture == nullptr)
		return nullptr;

	if (!owner->IsActive() || owner->IsPendingToDestroy())
		return NULL;
	
	Vector2D pos = owner->GetTranform()->GetPosition() + posOffset;
	Vector2D size = GetSize();
	Vector2D scaledSize = GetScaledSize();
	srcRect = SDL_Rect{ 0, 0, (int)size.x, (int)size.y };
	dstRect = SDL_Rect{ (int)pos.x, (int)pos.y, (int)scaledSize.x, (int)scaledSize.y };
	angle = owner->GetTranform()->GetRotation();
	flip = this->flip;
	color = this->color;
	return texture;
}

SpriteComponent::~SpriteComponent()
{
	Renderer::Get()->UnregisterDrawable(this);
}
