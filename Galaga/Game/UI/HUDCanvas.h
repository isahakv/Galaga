#ifndef HUDCANVAS_H
#define HUDCANVAS_H
#include "Core/GameObjects/GameObject.h"
#include "Core/Math/Vector2D.h"
// STL
#include <functional>

class SpriteComponent;
class ColliderComponent;

class UIText : public GameObject
{
public:
	UIText(const char* text, int size);

	void SetText(const char* text);
	void SetPos(const Vector2D& pos);
	inline void SetPivot(const Vector2D& pivot) { this->pivot = pivot; }

private:
	SpriteComponent* spriteComponent;

	const char* text;
	Vector2D pivot;
	int size;
};

class UIButton : public GameObject
{
public:
	UIButton(const char* texturePath);

	void Update(float deltaTime) override;
	inline void SetClickListener(std::function<void(void)> listener) { onButtonClicked = listener; }
	
private:
	SpriteComponent* spriteComponent;
	ColliderComponent* colliderComponent;

	std::function<void(void)> onButtonClicked;
	bool isMouseDown = false;
};

class HUDCanvas : public GameObject
{
public:
	HUDCanvas();
	void SetScoreText(int score);
	void SetHealthText(int health);
	void SetStageText(int stage, int maxStage);
	void ShowGameOverText();
	void ShowYouWinText();

private:
	void OnMenuButton_Clicked();

	UIButton* menuButton;
	UIText* scoreText;
	UIText* healthText;
	UIText* stageText;
	UIText* gameOverText;
	Vector2D windowSize;
};

#endif // !HUDCANVAS_H
