#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "command/command.h"
#include "option/option.h"
#include "bliss_option/bliss_option.h"
#include "bliss_version/bliss_version.h"

#define BLISS_APP_STR_SIZE 1024

struct bliss_app {
	int (*exec)(struct bliss_app* this, int argc, char* argv[]);
	void (*print_help)(struct bliss_app* this);
	char* (*get_name)(struct bliss_app* this);
	char* (*get_description)(struct bliss_app* this);
	char* (*get_usage)(struct bliss_app* this);
	struct bliss_version* (*get_version)(struct bliss_app* this);
	struct bliss_app* (*set_name)(struct bliss_app* this, const char* name);
	struct bliss_app* (*set_description)(struct bliss_app* this, const char* description);
	struct bliss_app* (*set_usage)(struct bliss_app* this, const char* usage);
	struct bliss_app* (*set_version)(struct bliss_app* this, const char* version_string);
	struct bliss_app* (*set_subcommand_exec)(struct bliss_app* this, void (*subcommand_exec_func)(void));
	struct bliss_app* (*add_subcommand)(struct bliss_app* this, struct bliss_app* subcommand);
	struct bliss_app* (*add_option)(struct bliss_app* this, struct bliss_option* option);

	struct command* this_command;
	struct bliss_version* this_version;
};

static char* parse_option_name(const char* string, char* name)
{
	int i = 0, j = 0;
	while(string[i] == '-') i++;
	for(j = 0; string[i+j] != '\0'; j++) {
		name[j] = string[i+j];
	}
	name[j] = '\0';
}

static void this_print_help(struct bliss_app* this)
{
	if (this->this_version && strlen(this->this_version->to_string(this->this_version))>0) {
		printf("Version %s\n\n", this->this_version->to_string(this->this_version));
	}
	this->this_command->print_help(this->this_command);
}

static int this_exec(struct bliss_app* this, int argc, char* argv[])
{
	int i, j;
	char option_name_tmp[OPTION_STR_SIZE];
	struct option* option_tmp = NULL;
	struct command* subcommand_tmp = NULL;

	if (argc == 1) {
		this_print_help(this);
		return 0;
	}
	for (i = 1; i < argc; i++) {
		if (argv[i][0] == '-') {
			parse_option_name(argv[i], option_name_tmp);
			option_tmp = this->this_command->get_option(this->this_command, option_name_tmp);
			if (option_tmp != NULL) {
				option_tmp->exec(option_tmp);
			}
		} else {
			subcommand_tmp = this->this_command->get_subcommand(this->this_command, argv[i]);
			if (subcommand_tmp != NULL) {
				subcommand_tmp -> exec(subcommand_tmp);
			} else if (i == argc -1) {
				printf("%s is not found\n", argv[i]);
				return 0;
			}
			break;
		}
	}

	return 0;
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

static struct bliss_app* this_set_name(struct bliss_app* this, const char* name)
{
	this->this_command->set_name(this->this_command, name);
	return this;
}

static struct bliss_app* this_set_description(struct bliss_app* this, const char* description)
{
	this->this_command->set_description(this->this_command, description);
	return this;
}

static struct bliss_app* this_set_usage(struct bliss_app* this, const char* usage)
{
	this->this_command->set_usage(this->this_command, usage);
	return this;
}

static struct bliss_app* this_set_version(struct bliss_app* this, const char* version_string)
{
	this->this_version->set_version(this->this_version, version_string);
	return this;
}

static struct bliss_app* this_set_exec(struct bliss_app* this, int (*exec_func)(struct bliss_app* this, int argc, char* argv[]))
{
	this->exec = exec_func;
	return this;
}

static struct bliss_app* this_add_subcommand(struct bliss_app* this, struct bliss_app* subcommand)
{
	char usage_buffer[BLISS_APP_STR_SIZE];
	sprintf(usage_buffer, "%s [subcommands]",
			this->this_command->get_name(this->this_command));
	if (this->this_command->get_options_count(this->this_command) > 0) {
		sprintf(usage_buffer, "%s [options] [subcommands]",
				this->this_command->get_name(this->this_command));
	}
	this_set_usage(this, usage_buffer);
	this->this_command->add_subcommand(this->this_command, subcommand->this_command);
	return this;
}

static struct bliss_app* this_add_option(struct bliss_app* this, struct bliss_option* option)
{
	char usage_buffer[BLISS_APP_STR_SIZE];
	sprintf(usage_buffer, "%s [options]",
			this->this_command->get_name(this->this_command));
	if (this->this_command->get_subcommands_count(this->this_command) > 0) {
		sprintf(usage_buffer, "%s [options] [subcommands]", 
				this->this_command->get_name(this->this_command));
	}
	this_set_usage(this, usage_buffer);
	this->this_command->add_option(this->this_command, option->get_option(option));
	return this;
}

struct bliss_app* new_bliss_app(const char* name)
{
	struct bliss_app* tmp = NULL;
	struct bliss_option* help_option = NULL;
	
	tmp = (struct bliss_app*)malloc(sizeof(struct bliss_app));
	tmp->this_command = new_command(name);
	this_set_usage(tmp, name);
	tmp->this_version = new_bliss_version("0.0.0");
	
	tmp->exec = this_exec;
	tmp->print_help = this_print_help;
	tmp->get_name = this_get_name;
	tmp->get_description = this_get_description;
	tmp->get_usage = this_get_usage;
	tmp->get_version = this_get_version;
	tmp->set_name = this_set_name;
	tmp->set_description = this_set_description;
	tmp->set_usage = this_set_usage;
	tmp->set_version = this_set_version;
	tmp->add_subcommand = this_add_subcommand;
	tmp->add_option = this_add_option;

	return tmp;
}

void delete_bliss_app(struct bliss_app* bliss_app_info)
{
	if (bliss_app_info == NULL) return;
	if (bliss_app_info->this_command != NULL) {
		delete_command(bliss_app_info->this_command);
	}
	if (bliss_app_info->this_version != NULL) {
		delete_bliss_version(bliss_app_info->this_version);
	}
	free(bliss_app_info);
}
