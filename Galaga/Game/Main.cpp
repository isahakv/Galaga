#include "GalagaApplication.h"

int main()
{
	GalagaApplication* app = GalagaApplication::Get();
	//app->Init(800, 600, false);
	app->Init(1680, 1050, false);

	return app->Run();
}
