#ifndef TYPEDEFS_H
#define TYPEDEFS_H

enum class Space
{
	Relative,
	World
};

constexpr int targetScreenWidth = 1920;
constexpr int targetScreenHeight = 1080;
constexpr float targetAspectRatio = targetScreenWidth / (float)targetScreenHeight;

#endif // !TYPEDEFS_H

