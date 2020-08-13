#include "example_app.h"

int main(int argc, char* argv[]) {
	BlissApp* exampleApp = CreateApp();
	return bliss_run(exampleApp, argc, argv);
}
