#include <stdio.h>

#include <stdlib.h>
#include <string.h>

#define OPTION_STR_SIZE 256

struct option {
	void (*exec)(struct option* this);
	char* (*get_name)(struct option* this);
	char* (*get_name_short)(struct option* this);
	char* (*get_description)(struct option* this);
	struct option* (*set_name)(
			struct option* this, const char* name);
	struct option* (*set_name_short)(
			struct option* this, const char* name_short);
	struct option* (*set_description)(
			struct option* this, const char* description);
	struct option* (*set_exec_func)(
			struct option* this, void (*option_exec_func)(void));
	
	char name[OPTION_STR_SIZE];
	char name_short[OPTION_STR_SIZE];
	char description[OPTION_STR_SIZE];
	void (*exec_func)(void);
};

static void this_exec(struct option* this)
{
	if (this->exec_func == NULL) return;
	this->exec_func();
}

static char* this_get_name(struct option* this)
{
	if (this == NULL) return NULL;
	return this->name;
}

static char* this_get_name_short(struct option* this)
{
	if (this == NULL) return NULL;
	return this->name_short;
}

static char* this_get_description(struct option* this)
{
	if (this == NULL) return NULL;
	return this->description;
}

static struct option* this_set_name(struct option* this, const char* name)
{
	if (this == NULL) return NULL;
	strcpy(this->name, name);
	return this;
}

static struct option* this_set_name_short(
		struct option* this, const char* name_short)
{
	if (this == NULL) return NULL;
	strcpy(this->name_short, name_short);
	return this;
}

static struct option* this_set_description(
		struct option* this, const char* description)
{
	if (this == NULL) return NULL;
	strcpy(this->description, description);
	return this;
}

static struct option* this_set_exec_func(
		struct option* this, void (*exec_func)(void))
{
	if (this == NULL) return NULL;
	this->exec_func = exec_func;
	return this;
}

struct option* new_option(const char* name)
{
	if (strlen(name) >= OPTION_STR_SIZE) return NULL;

	struct option* tmp = (struct option*)malloc(sizeof(struct option));
	strcpy(tmp->name, name);
	tmp->exec_func = NULL;

	tmp->exec = this_exec;
	tmp->get_name = this_get_name;
	tmp->get_name_short = this_get_name_short;
	tmp->get_description = this_get_description;
	tmp->set_name = this_set_name;
	tmp->set_name_short = this_set_name_short;
	tmp->set_description = this_set_description;
	tmp->set_exec_func = this_set_exec_func;
	return tmp;
}

void delete_option(struct option* option_info)
{
	if (option_info == NULL) return;
	free(option_info);
	option_info = NULL;
}
