#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../option/option.h"

#define COMMAND_STR_SIZE 256

struct command {
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
	struct command* (*set_exec_func)(
			struct command* this, 
			void (*command_exec_func)(struct command* this));
	struct command* (*add_subcommand)(struct command* this, struct command* subcommand);
	struct command* (*delete_subcommand)(struct command* this, const char* subcommand_name);
	struct command* (*add_option)(struct command* this, struct option* option_info);
	struct command* (*delete_option)(struct command* this, const char* option_name);
	void (*print_help)(struct command* this);	
	
	int is_subcommand;
	int subcommands_count;
	int options_count;
	char name[COMMAND_STR_SIZE];
	char description[COMMAND_STR_SIZE];
	char usage[COMMAND_STR_SIZE];
	struct command** subcommands;
	struct option** options;
	void (*exec_func)(struct command* this);
};

static void this_exec(struct command* this)
{
	this->exec_func(this);
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
	
	if (this->options_count == 0) return NULL;
	for (i = 0; i < this->options_count; i++) {
		if (
				!strcmp(this->options[i]->get_name(this->options[i]), option_name) ||
				!strcmp(this->options[i]->get_name_short(this->options[i]), option_name)
			) {
			return this->options[i];
		}
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

static struct command* this_set_exec_func(
		struct command* this, 
		void (*command_exec_func)(struct command* this))
{
	this->exec_func = command_exec_func;
	return this;
}

static struct command* this_add_subcommand(struct command* this, struct command* subcommand)
{
	if (this->subcommands[this->subcommands_count]->is_subcommand != 1) {
		if (this->subcommands == NULL) {
			this->subcommands = (struct command**)malloc(sizeof(struct command));
		} else {
			this->subcommands = (struct command**)realloc(
					this->subcommands,
					sizeof(struct command) * (this->subcommands_count + 1));
		}
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
	if (this_get_option(this, option_info->get_name(option_info)) == NULL) {
		if (this->options == NULL) {
			this->options = (struct option**)malloc(sizeof(struct option));
		} else {
			this->options = (struct option**)realloc(
					this->options,
					sizeof(struct option) * (this->options_count + 1));
		}
		this->options[this->options_count] = option_info;
		(this->options_count)++;
		return this;
	}
	return NULL;
}

static struct command* this_delete_option(struct command* this, const char* option_name)
{
	int i ;

	for (i = 0; i < this->options_count; i++) {
		if (
				!strcmp(this->options[i]->get_name(this->options[i]), option_name) ||
				!strcmp(this->options[i]->get_name_short(this->options[i]), option_name)
			) {
			delete_option(this->options[i]);
			break;
		}
	}

	return this;
}

static void this_print_help(struct command* this)
{
	int i;
	struct option* option_tmp;
	struct command* subcommand_tmp;

	if (strlen(this->name) > 0) printf("%s", this->name);
	if (strlen(this->description)>0) printf(" | %s", this->description);
	printf("\n\n");

	if (strlen(this->usage) > 0) printf("Usage:\n\t%s\n\n", this->usage);
	
	if (this->options_count > 0) {
		printf("Options:\n");
		for (i = 0; i < this->options_count; i++) {
			option_tmp = this_get_option_by_index(this, i);
			printf("\t");
			if (strlen(option_tmp->get_name_short(option_tmp)) > 0) {
				printf("-%s ", option_tmp -> get_name_short(option_tmp));
			}
			if (strlen(option_tmp->get_name(option_tmp)) > 0) {
				printf("--%s ", option_tmp->get_name(option_tmp));
			}
			if (strlen(option_tmp->get_description(option_tmp)) > 0) {
				printf(": %s", option_tmp->get_description(option_tmp));
			}
			printf("\n");
		}
	}
	if (!(this->is_subcommand)) {
		if (this->subcommands_count > 0) {
			printf("\nSubcommands:\n");
			for (i = 0; i < this->subcommands_count; i++) {
				subcommand_tmp = this_get_subcommand_by_index(this, i);
				if (strlen(subcommand_tmp->name) > 0) {
					printf("%s ", subcommand_tmp->name);
				}
				if (strlen(subcommand_tmp->description) > 0) {
					printf(": %s", subcommand_tmp->description);
				}
				printf("\n");
			}
		}
	}
	
}


struct command* new_command(const char* name)
{
	struct command* tmp = (struct command*)malloc(sizeof(struct command));
	tmp->is_subcommand = 0;
	tmp->subcommands_count = 0;
	tmp->options_count = 0;
	tmp->options = NULL;

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
	tmp->print_help = this_print_help;

	tmp->exec_func = this_print_help;
	return tmp;
}

void delete_command(struct command* command_info)
{
	int i, j;

	if (command_info == NULL) return;

	for (i = 0; i < command_info->options_count; i++) {
		if (command_info->options[i] != NULL) {
			delete_option(command_info->options[i]);
		}
	}
	if (command_info->options != NULL) {
		free(command_info->options);
		command_info->options = NULL;
	}
	for (i = 0; i < command_info->subcommands_count; i++) {
		for (j = 0; j < command_info->subcommands[i]->options_count; j++) {
			if (command_info->subcommands[i]->options[j] != NULL) {
				delete_option(command_info->subcommands[i]->options[j]);
			}
		}
		if (command_info->subcommands[i]->options != NULL) {
			free(command_info->subcommands[i]->options);
			command_info->subcommands[i]->options = NULL;
		}
		if (command_info->subcommands[i] != NULL) {
			free(command_info->subcommands[i]);
			command_info->subcommands[i] = NULL;
		}
	}
	if (command_info->subcommands != NULL) {
		free(command_info->subcommands);
		command_info->subcommands = NULL;
	}
	free(command_info);
	command_info = NULL;
}