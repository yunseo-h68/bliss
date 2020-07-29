#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "command/command.h"
#include "bliss_option/bliss_option.h"
#include "bliss_version/bliss_version.h"

struct bliss_app {
	struct command* this_command;
	struct bliss_version* this_version;

	void (*exec)(struct bliss_app* this);
	void (*print_help)(struct bliss_app* this);
	char* (*get_name)(struct bliss_app* this);
	char* (*get_description)(struct bliss_app* this);
	char* (*get_usage)(struct bliss_app* this);
	struct bliss_version* (*get_version)(struct bliss_app* this);
	struct bliss_app* (*set_version)(struct bliss_app* this, const char* version_string);
	struct bliss_app* (*add_subcommand)(struct bliss_app* this, struct bliss_app* subcommand);
	struct bliss_app* (*add_option)(struct bliss_app* this, struct bliss_option* option);
};

static void this_print_help(struct bliss_app* this)
{
	this->this_command->print_help(this->this_command);
}

static char* this_get_name(struct bliss_app* this)
{
	return this->this_command->get_name(this->this_command);
}

static char* this_get_description(struct bliss_app* this)
{
	return this->this_command->get_description(this->this_command);
}

static char* this_get_usage(struct bliss_app* this)
{
	return this->this_command->get_usage(this->this_command);
}

static struct bliss_version* this_get_version(struct bliss_app* this)
{
	return this->this_version;
}

static struct bliss_app* set_version(struct bliss_app* this, const char* version_string)
{
	this->this_version->set_version(this->this_version, version_string);
	return this;
}

static struct bliss_app* add_subcommand(struct bliss_app* this, struct bliss_app* subcommand)
{
}

struct bliss_app* new_bliss_app(const char* name)
{
	struct bliss_app* tmp = (struct bliss_app*)malloc(sizeof(struct bliss_app));
	tmp->this_command = new_command(name);

	struct bliss_option* help_option = new_bliss_option("help");
	help_option
		->set_name_short(help_option, "h")
		->set_description(help_option, "Display this information");

	//tmp->this_command->add_option(tmp->this_command, help_option);
	tmp->print_help = this_print_help;

	return tmp;
}
