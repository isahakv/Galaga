#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H
#include "BaseComponent.h"
#include "../Math/Vector2D.h"

class TransformComponent : public BaseComponent
{
public:
	TransformComponent(GameObject* owner);

	void Update(float deltaTime) override;

	inline Vector2D& GetPosition() { return position; }
	inline void SetPosition(const Vector2D& pos) { position = pos; }
	inline void SetPosition(int x, int y) { position = Vector2D(x, y); }
	inline void Translate(const Vector2D& translation) { position += translation; }
private:
	Vector2D position;
};

#endif // !TRANSFORMCOMPONENT_H
