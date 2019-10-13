#ifndef VELOCITYCOMPONENT_H
#define VELOCITYCOMPONENT_H
#include "Core/Components/BaseComponent.h"
#include "Core/Math/Vector2D.h"

class VelocityComponent : public BaseComponent
{
public:
	VelocityComponent(GameObject* _owner);

	void Update(float deltaTime) override;
	inline float GetSpeed() const { return speed; }
	void SetSpeed(float speed);

private:
	float speed;
	Vector2D velocity;
};

#endif // !VELOCITYCOMPONENT_H
