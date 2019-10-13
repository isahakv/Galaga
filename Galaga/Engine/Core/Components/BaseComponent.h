#ifndef BASECOMPONENT_H
#define BASECOMPONENT_H

class GameObject;

class BaseComponent
{
public:
	BaseComponent(GameObject* owner);

	virtual void Update(float deltaTime) = 0;

protected:
	GameObject* owner;
};

#endif // !BASECOMPONENT_H
