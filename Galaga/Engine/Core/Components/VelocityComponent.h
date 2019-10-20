#ifndef VELOCITYCOMPONENT_H
#define VELOCITYCOMPONENT_H
#include "Core/TypeDefs.h"
#include "Core/Components/BaseComponent.h"
#include "Core/Math/Vector2D.h"

class VelocityComponent : public BaseComponent
{
public:
	VelocityComponent(GameObject* _owner);

	void Update(float deltaTime) override;

	inline Vector2D GetVelocity() const { return velocity; }
	void SetVelocity(const Vector2D& _velocity, Space space = Space::Relative);

private:
	Vector2D velocity;
};

#endif // !VELOCITYCOMPONENT_H
