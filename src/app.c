#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "option/option.h"
#include "command/command.h"
#include "version/version.h"

struct bliss_app {
	struct command* this_command;
	struct bliss_version* this_version;

	void (*exec)(struct bliss_app* this);
	char* (*get_name)(struct bliss_app* this);
	char* (*get_description)(struct bliss_app* this);
	char* (*get_usage)(struct bliss_app* this);
	struct bliss_version* (*get_version)(struct bliss_app* this);
	struct bliss_app* (*add_subcommand)(struct bliss_app* this, struct bliss_app* subcommand);
	struct bliss_app* (*add_option)(struct bliss_app* this, struct bliss_option* option_info);
};

struct bliss_option {
	struct option* this_option;

	struct bliss_option* (*set_name)(struct bliss_option* this, const char* name);
	struct bliss_option* (*set_name_short)(struct bliss_option* this, const char* name_short);
	struct bliss_option* (*set_exec_func)(
			struct bliss_option* this, 
			void (*option_exec_func)(void));
};

struct bliss_version {
	struct version* this_version;

	char* (*to_string)(struct bliss_version* this);
	int (*release)(struct bliss_version* thiis);
	int (*major)(struct bliss_version* this);
	int (*minor)(struct bliss_version* this);
};

struct bliss_app* new_bliss_app(const char* name, const char* version_string)
{
	struct bliss_app* = (struct bliss_app*)malloc(sizeof(bliss_app));
	bliss_app -> command = new_command(name);

	struct option* option_tmp = new_option("help");
	option_tmp->set_name_short(option_tmp, "h")
		->set_description(option_tmp, "Display this information");

	bliss_app->command->add_option(this, help_option);
	return tmp;
}

struct command* print_help(struct bliss_app* this)
{
	int i, j;
	struct option* option_tmp;
	struct command* subcommand_tmp;

	printf("%s | %s\n\n", this->get_name(this), this->get_description(this));
	printf("Option:\n");
	for (i = 0; i < this->get_options_count; i++) {
		option_tmp = this->get_option_by_index(this, i);
		printf("\t-%s --%s : %s\n", 
				option_tmp->get_name_short(this),
				option_tmp->get_name(this),
				option_tmp->get_description(this));
	}
	printf("\nSubcommands:\n");
	for (i = 0; i < this->get_subcommands_count(this); i++) {
		subcommand_tmp = this->get_subcommand_by_index(this, i);
		printf("\t%s : %s\n", 
				subcommand_tmp->get_name,
				subcommand_tmp->get_description);
	}
}
