#ifndef GALAGAAPPLICATION_H
#define GALAGAAPPLICATION_H

#include "../Engine/Core/Platform/Application.h"

class GalagaApplication : public Application
{
private:
	GalagaApplication();
	~GalagaApplication();

public:
	static GalagaApplication* Get();
	virtual void Init(int width, int height, bool isFullScreen) override;

private:
	static GalagaApplication* instance;
};

#endif // !GALAGAAPPLICATION_H
