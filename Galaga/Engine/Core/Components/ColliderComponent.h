#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H
#include "BaseComponent.h"
// STL
#include <functional>
// SDL
#include "SDL_rect.h"

enum class CollisionLayer;

class ColliderComponent : public BaseComponent
{
public:
	ColliderComponent(GameObject* _owner);
	virtual ~ColliderComponent();

	void Update(float deltaTime) override;

	inline void SetBounds(const SDL_Rect& _bounds) { bounds = _bounds; }
	SDL_Rect GetBounds() const;

	void SetLayer(CollisionLayer layer);
	inline CollisionLayer GetLayer() const { return collisionLayer; }

	inline void BindCollisionEnter(std::function<void(ColliderComponent* other)>& handler)
	{ collisionEnterHandler = handler; }

private:
	void OnCollisionEnter(ColliderComponent* other);

	SDL_Rect bounds;
	CollisionLayer collisionLayer;
	std::function<void(ColliderComponent* other)> collisionEnterHandler;

	friend class Physics;
};

#endif // !COLLIDERCOMPONENT_H
