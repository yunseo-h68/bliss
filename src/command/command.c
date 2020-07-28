#include <stdlib.h>
#include <string.h>
#include "../option/option.h"

#define COMMAND_STR_SIZE 256

struct command {
	int is_subcommand;
	int subcommands_count;
	int options_count;
	char name[COMMAND_STR_SIZE];
	char description[COMMAND_STR_SIZE];
	char usage[COMMAND_STR_SIZE];
	struct command** subcommands;
	struct option** options;
	void (*exec_func)(void);

	void (*exec)(struct command* this);
	char* (*get_name)(struct command* this);
	char* (*get_description)(struct command* this);
	char* (*get_usage)(struct command* this);
	int (*get_options_count)(struct command* this);
	int (*get_subcommands_count)(struct command* this);
	struct option* (*get_option_by_index)(struct command* this, int index);
	struct option* (*get_option)(struct command* this, const char* option_name);
	struct command* (*get_subcommand_by_index)(struct command* this, int index);
	struct command* (*get_subcommand)(struct command* this, const char* subcommand_name);
	struct command* (*set_name)(struct command* this, const char* name);
	struct command* (*set_description)(struct command* this, const char* description);
	struct command* (*set_usage)(struct command* this, const char* usage);
	struct command* (*add_subcommand)(struct command* this, struct command* subcommand);
	struct command* (*delete_subcommand)(struct command* this, const char* subcommand_name);
	struct command* (*add_option)(struct command* this, struct option* option_info);
	struct command* (*delete_option)(struct command* this, const char* option_name);
};

static void this_exec(struct command* this)
{
	this->exec_func();
}

static char* this_get_name(struct command* this)
{
	return this->name;
}

static char* this_get_description(struct command* this)
{
	return this->description;
}

static char* this_get_usage(struct command* this)
{
	return this->usage;
}

static int this_get_options_count(struct command* this)
{
	return this->options_count;
}

static int this_get_subcommands_count(struct command* this)
{
	return this->subcommands_count;
}

static struct option* this_get_option_by_index(struct command* this, int index)
{
	return this->options[index];
}

static struct option* this_get_option(struct command* this, const char* option_name)
{
	int i;

	for (i = 0; i < this->options_count; i++) {
		if (!strcmp(this->options[i]->get_name(this->options[i]), option_name))
			return this->options[i];
	}

	return NULL;
}

static struct command* this_get_subcommand_by_index(struct command* this, int index)
{
	return this->subcommands[index];
}

static struct command* this_get_subcommand(struct command* this, const char* subcommand_name)
{
	int i;

	for (i = 0; i < this->subcommands_count; i++) {
		if (!strcmp(this->subcommands[i]->name, subcommand_name))
			return this->subcommands[i];
	}

	return NULL;
}

static struct command* this_set_name(struct command* this, const char* name)
{
	if (strlen(name) > COMMAND_STR_SIZE - 1) return NULL;
	strcpy(this->name, name);
	return this;
}

static struct command* this_set_description(struct command* this, const char* description)
{
	if (strlen(description) > COMMAND_STR_SIZE - 1) return NULL;
	strcpy(this->description, description);
	return this;
}

static struct command* this_set_usage(struct command* this, const char* usage)
{
	if (strlen(usage) > COMMAND_STR_SIZE - 1) return NULL;
	strcpy(this->usage, usage);
	return this;
}

static struct command* this_add_subcommand(struct command* this, struct command* subcommand)
{
	if (this->subcommands[this->subcommands_count]->is_subcommand != 1) {
		this->subcommands[this->subcommands_count] = subcommand;
		this->subcommands[this->subcommands_count]->is_subcommand = 1;
		(this->subcommands_count)++;
		return this;
	}
	return NULL;
}

static struct command* this_delete_subcommand(struct command* this, const char* subcommand_name)
{
	int i;

	for (i = 0; i < this->subcommands_count; i++) {
		if (!strcmp(this->subcommands[i]->name, subcommand_name)) {
			free(this->subcommands[i]);
			(this->subcommands_count)--;
			break;
		}
	}
	
	return this;
}

static struct command* this_add_option(struct command* this, struct option* option_info)
{
	this->options[this->options_count] = option_info;
	(this->options_count)++;
	return this;
}

static struct command* this_delete_option(struct command* this, const char* option_name)
{
	int i ;

	for (i = 0; i < this->options_count; i++) {
		if (!strcmp(this->options[i]->get_name(this->options[i]), option_name)) {
			delete_option(this->options[i]);
			break;
		}
	}

	return this;
}

struct command* new_command(const char* name)
{
	struct command* tmp = (struct command*)malloc(sizeof(struct command));
	tmp->is_subcommand = 0;
	strcpy(tmp->name, name);
	tmp->exec = this_exec;
	tmp->get_name = this_get_name;
	tmp->get_description = this_get_description;
	tmp->get_usage = this_get_usage;

	tmp->get_options_count = this_get_options_count;
	tmp->get_subcommands_count = this_get_subcommands_count;
	tmp->get_option_by_index = this_get_option_by_index;
	tmp->get_option = this_get_option;
	tmp->get_subcommand_by_index = this_get_subcommand_by_index;
	tmp->get_subcommand = this_get_subcommand;
	tmp->set_name = this_set_name;
	tmp->set_description = this_set_description;
	tmp->set_usage = this_set_usage;
	tmp->add_subcommand = this_add_subcommand;
	tmp->delete_subcommand = this_delete_subcommand;
	tmp->add_option = this_add_option;
	tmp->delete_option = this_delete_option;
	return tmp;
}

void delete_command(struct command* command_info)
{
	int i, j;
	for (i = 0; i < command_info->options_count; i++) {
		delete_option(command_info->options[i]);
	}
	for (i = 0; i < command_info->subcommands_count; i++) {
		for (j = 0; j < command_info->subcommands[i]->options_count; j++) {
			delete_option(command_info->subcommands[i]->options[j]);
		}
		free(command_info->subcommands[i]);
	}
	free(command_info);
}
