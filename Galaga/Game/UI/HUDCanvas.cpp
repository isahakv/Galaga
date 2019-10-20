#include "HUDCanvas.h"
#include "Core/Components/TransformComponent.h"
#include "Core/Components/SpriteComponent.h"
#include "Core/Components/ColliderComponent.h"
#include "Core/AssetManagement/AssetManager.h"
#include "GalagaApplication.h"
#include "Core/Input/Input.h"

#include <iostream>

UIText::UIText(const char* text, int size) : text(text), pivot(Vector2D(0.f, 0.f)), size(size)
{
	// Setup SpriteComponent.
	SDL_Texture* texture = AssetManager::Get()->GetText(text, "Game/Assets/fonts/arcade.ttf", size);
	spriteComponent = AddComponent<SpriteComponent>();
	spriteComponent->SetTexture(texture);
	spriteComponent->SetSortOrder(100);
}

void UIText::SetText(const char* text)
{
	//if (strcmp(this->text, text))
	//	return;

	// Destroy old texture.
	SDL_Texture* texture = spriteComponent->GetTexture();
	if (texture)
		SDL_DestroyTexture(texture);

	texture = AssetManager::Get()->GetText(text, "Game/Assets/fonts/arcade.ttf", size);
	spriteComponent->SetTexture(texture);
}

void UIText::SetPos(const Vector2D& pos)
{
	SDL_Texture* texture = spriteComponent->GetTexture();
	int width, height;
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
	Vector2D delta = Vector2D(pivot.x * width, pivot.y * height);
	GetComponent<TransformComponent>()->SetPosition(pos - delta);
}

UIButton::UIButton(const char* texturePath)
{
	// Setup SpriteComponent.
	SDL_Texture* texture = AssetManager::Get()->LoadTexture(texturePath);
	spriteComponent = AddComponent<SpriteComponent>();
	spriteComponent->SetTexture(texture);
	spriteComponent->SetSortOrder(100);
	Vector2D size = spriteComponent->GetScaledSize();
	// Setup ColliderComponent.
	colliderComponent = AddComponent<ColliderComponent>();
	colliderComponent->SetBounds(SDL_Rect{ 0, 0, (int)size.x, (int)size.y });
}

void UIButton::Update(float deltaTime)
{
	GameObject::Update(deltaTime);

	Vector2D pos;
	SDL_Point point;
	SDL_Rect bounds;
	if (Input::IsMouseKeyDown(1, pos))
	{
		point = SDL_Point{ (int)pos.x, (int)pos.y };
		bounds = colliderComponent->GetBounds();
		if (SDL_PointInRect(&point, &bounds))
			isMouseDown = true;
	}
	else if (isMouseDown && Input::IsMouseKeyUp(1, pos))
	{
		isMouseDown = false;
		point = SDL_Point{ (int)pos.x, (int)pos.y };
		bounds = colliderComponent->GetBounds();
		if (SDL_PointInRect(&point, &bounds))
		{
			if (onButtonClicked)
				onButtonClicked();
		}
	}
}

HUDCanvas::HUDCanvas()
{
	windowSize = GalagaApplication::Get()->GetWindowSize();
	// Setup Menu Button.
	menuButton = new UIButton("Game/Assets/UI/menu.png");
	menuButton->GetComponent<SpriteComponent>()->SetScale(0.8f);
	Vector2D size = menuButton->GetComponent<SpriteComponent>()->GetScaledSize();
	menuButton->GetTranform()->SetPosition(Vector2D(windowSize.x - size.x, 0.f));
	menuButton->SetClickListener(std::bind(&HUDCanvas::OnMenuButton_Clicked, this));
	childObjects.push_back(menuButton);
	// Setup Score Text.
	scoreText = new UIText("Score: ", 36);
	childObjects.push_back(scoreText);
	// Setup Health Text.
	healthText = new UIText("Health: ", 36);
	healthText->SetPivot(Vector2D(0.5f, 0.f));
	healthText->SetPos(Vector2D(windowSize.x / 2.f, 0.f));
	childObjects.push_back(healthText);
	// Setup Stage Text.
	stageText = new UIText("Stage: ", 36);
	stageText->SetPivot(Vector2D(1.f, 0.f));
	stageText->SetPos(Vector2D(windowSize.x - 200.f, 0.f));
	childObjects.push_back(stageText);
	// Setup GameOver Text.
	gameOverText = new UIText("Game Over", 50);
	gameOverText->SetPivot(Vector2D(0.5f, 0.5f));
	gameOverText->SetPos(Vector2D(windowSize.x / 2.f, windowSize.y / 2.f));
	gameOverText->SetActive(false);
	childObjects.push_back(gameOverText);
}

void HUDCanvas::SetScoreText(int score)
{
	std::string text = "Score: " + std::to_string(score);
	scoreText->SetText(text.c_str());
}

void HUDCanvas::SetHealthText(int health)
{
	std::string text = "Health: " + std::to_string(health);
	healthText->SetText(text.c_str());
}

void HUDCanvas::SetStageText(int stage, int maxStage)
{
	std::string text = "Stage: " + std::to_string(stage) + "/" + std::to_string(maxStage);
	stageText->SetText(text.c_str());
}

void HUDCanvas::ShowGameOverText()
{
	gameOverText->SetActive(true);
}

void HUDCanvas::ShowYouWinText()
{
	gameOverText->SetText("You Win!!!");
	gameOverText->SetActive(true);
}

void HUDCanvas::OnMenuButton_Clicked()
{
	std::cout << "kpav!" << std::endl;
	scoreText->SetText("This is another Score Mazafaka!!!");
}
