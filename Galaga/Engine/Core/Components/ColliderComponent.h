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
	typedef std::function<void(ColliderComponent*)> HandlerCollisionEnterType;

	ColliderComponent(GameObject* _owner);
	virtual ~ColliderComponent();

	void Update(float deltaTime) override;

	inline void SetBounds(const SDL_Rect& _bounds) { bounds = _bounds; }
	SDL_Rect GetBounds() const;

	void SetLayer(CollisionLayer layer);
	inline CollisionLayer GetLayer() const { return collisionLayer; }

	inline void BindCollisionEnter(const HandlerCollisionEnterType& handler)
	{ handlerCollisionEnter = handler; }

private:
	void OnCollisionEnter(ColliderComponent* other);

	SDL_Rect bounds;
	CollisionLayer collisionLayer;
	HandlerCollisionEnterType handlerCollisionEnter;

	friend class Physics;
};

#endif // !COLLIDERCOMPONENT_H
