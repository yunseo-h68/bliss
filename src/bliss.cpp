#include <iostream>
#include <cstring>
#include <string>
#include "bliss.h"

static std::string parse_option_name(const char* str) {
	int i = 0;
	std::string name = "";
	while (str[i] == '-') i++;
	for (int j = 0; str[i+j] != '\0'; j++) {
		name += str[i+j];
	}
	return name;
}

int bliss_run(BlissApp* app, int argc, char* argv[]) {
	int check = 0;
	if (argc == 1) {
		app->Exec();
	}

	for (int i = 1; i < argc; i++) {
		std::string name;
		if (strlen(argv[i]) >= 2 && argv[i][0] == '-') {
			name = parse_option_name(argv[i]);
			BlissOption* option_tmp = NULL;

			if (argv[i][1] != '-') {
				option_tmp = app->GetOptionByNameShort(name);
			} else if (argv[i][2] != '-') {
				option_tmp = app->GetOptionByName(name);
			}
			if (option_tmp == NULL) {
				std::cout << "NOT FOUND OPTION: " << argv[i] << "\n";
				continue;
			}
			option_tmp->Exec();
			check = 1;
			continue;
		}
		BlissCommand* subcommand_tmp = app->GetSubcommandByName(argv[i]);
		if (subcommand_tmp == NULL) {
			std::cout << "NOT FOUND SUBCOMMAND: " << argv[i] << "\n";
			if (!check && i == argc - 1) {
				return -1;
			}
			continue;
		}
		check = 1;
		subcommand_tmp -> Exec();
	}
	
	delete app;

	return 0;
}
