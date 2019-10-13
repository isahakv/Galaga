#include "GalagaApplication.h"

int main()
{
	GalagaApplication* app = GalagaApplication::Get();
	app->Init(800, 600, false);

	return app->Run();
}
