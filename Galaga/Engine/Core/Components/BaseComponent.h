#ifndef BASECOMPONENT_H
#define BASECOMPONENT_H

class GameObject;

class BaseComponent
{
public:
	BaseComponent(GameObject* owner);
	virtual ~BaseComponent() {}

	virtual void Update(float deltaTime) = 0;

	inline GameObject* GetOwner() const { return owner; }

protected:
	GameObject* owner;
};

#endif // !BASECOMPONENT_H
