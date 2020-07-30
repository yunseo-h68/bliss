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

static struct bliss_app* this_set_version(struct bliss_app* this, const char* version_string)
{
	this->this_version->set_version(this->this_version, version_string);
	return this;
}

static struct bliss_app* this_add_subcommand(struct bliss_app* this, struct bliss_app* subcommand)
{
	this->this_command->add_subcommand(this->this_command, subcommand->this_command);
	return this;
}

static struct bliss_app* this_add_option(struct bliss_app* this, struct bliss_option* option)
{
	this->this_command->add_option(this->this_command, option->get_option(option));
	return this;
}

struct bliss_app* new_bliss_app(const char* name)
{
	struct bliss_app* tmp = NULL;
	struct bliss_option* help_option = NULL;
	
	tmp = (struct bliss_app*)malloc(sizeof(struct bliss_app));
	tmp->this_command = new_command(name);

	help_option = new_bliss_option("help");
	help_option
		->set_name_short(help_option, "h")
		->set_description(help_option, "Display this information");

	this_add_option(tmp, help_option);
	tmp->print_help = this_print_help;
	tmp->get_name = this_get_name;
	tmp->get_description = this_get_description;
	tmp->get_usage = this_get_usage;
	tmp->get_version = this_get_version;
	tmp->set_version = this_set_version;
	tmp->add_subcommand = this_add_subcommand;
	tmp->add_option = this_add_option;

	return tmp;
}

void delete_bliss_app(struct bliss_app* bliss_app_info)
{
	delete_command(bliss_app_info->this_command);
	delete_bliss_version(bliss_app_info->this_version);
	free(bliss_app_info);
}
