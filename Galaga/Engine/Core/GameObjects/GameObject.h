#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <memory>
#include <vector>
#include "../Components/BaseComponent.h"

struct SDL_Renderer;
class BaseComponent;
class TransformComponent;

class GameObject
{
public:
	GameObject();
	~GameObject();
	virtual void Update(float deltaTime);
	
	inline bool IsActive() const { return active; }
	inline void SetActive(bool _active) { active = _active; }

	/** Component management. */
	template<typename T> T* AddComponent()
	{
		// This ensures that we only try to add a class the derives 
		// from Component. This is tested at compile time.
		static_assert(std::is_base_of<BaseComponent, T>::value, "T must derive from BaseComponent");
	
		// Check that we don't already have a component of this type.
		for (auto exisitingComponent : components)
		{
			if (T* component = dynamic_cast<T*>(exisitingComponent))
				return component;
		}

		// The object does not have this component so we create it and 
		// add it to our list.
		T* component = new T(this);
		components.push_back(component);
		return component;
	}

	template<typename T> T* GetComponent()
	{
		static_assert(std::is_base_of<BaseComponent, T>::value, "T must derive from BaseComponent");
		for (auto exisitingComponent : components)
		{
			if (T* component = dynamic_cast<T*>(exisitingComponent))
				return component;
		}
		return nullptr;
	}

	inline TransformComponent* GetTranform() const { return transform; }
protected:
	TransformComponent* transform;
	std::vector<BaseComponent*> components;
	bool active;
};

#endif // !GAMEOBJECT_H
