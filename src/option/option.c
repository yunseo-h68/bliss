#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "option.h"

struct option {
	char name[OPTION_STR_SIZE];
	char name_short[OPTION_STR_SIZE];
	char description[OPTION_STR_SIZE];
	void (*exec_func)(void);

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
};

static void exec(struct option* this)
{
	this->exec_func();
}

static char* get_name(struct option* this)
{
	return this->name;
}

static char* get_name_short(struct option* this)
{
	return this->name_short;
}

static char* get_description(struct option* this)
{
	return this->description;
}

static struct option* set_name(struct option* this, const char* name)
{
	strcpy(this->name, name);
	return this;
}

static struct option* set_name_short(
		struct option* this, const char* name_short)
{
	strcpy(this->name_short, name_short);
	return this;
}

static struct option* set_description(
		struct option* this, const char* description)
{
	strcpy(this->description, description);
	return this;
}

static struct option* set_exec_func(
		struct option* this, void (*exec_func)(void))
{
	this->exec_func = exec_func;
	return this;
}

struct option* new_option(const char* name)
{
	struct option* tmp = (struct *option)malloc(sizeof(struct option));
	strcpy(tmp->name, name);
	tmp->exec = exec;
	tmp->get_name = get_name;
	tmp->get_name_short = get_name_short;
	tmp->get_description = get_description;
	tmp->set_name = set_name;
	tmp->set_name_short = set_name_short;
	tmp->set_description = set_description;
	tmp->set_exec_func = set_exec_func;
	return tmp;
}
