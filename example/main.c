#include <stdio.h>
#include "../include/bliss.h"

int main() {
	struct bliss_app* app = new_bliss_app("example-app");
	printf("app: %p\n", app);
	printf("help: %p\n", app->print_help);

	delete_bliss_app(app);
	return 0;
}
