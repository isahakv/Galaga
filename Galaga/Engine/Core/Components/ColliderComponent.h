#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H
#include "BaseComponent.h"
// SDL
#include "SDL_rect.h"

enum class CollisionLayer;

class ColliderComponent : public BaseComponent
{
public:
	ColliderComponent(GameObject* _owner);
	~ColliderComponent();

	void Update(float deltaTime) override;

	void SetBounds(const SDL_Rect& _bounds);
	SDL_Rect GetBounds() const;

	inline void SetLayer(CollisionLayer layer) { collisionLayer = layer; }
	inline CollisionLayer GetLayer() const { return collisionLayer; }

private:
	SDL_Rect bounds;
	CollisionLayer collisionLayer;
};

#endif // !COLLIDERCOMPONENT_H
