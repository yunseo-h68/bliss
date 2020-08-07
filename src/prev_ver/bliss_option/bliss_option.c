//test
#include <stdio.h>

#include <stdlib.h>
#include "../core/option/option.h"

struct bliss_option {
	struct bliss_option* (*set_name)(struct bliss_option* this, const char* name);
	struct bliss_option* (*set_name_short)(struct bliss_option* this, const char* name_short);
	struct bliss_option* (*set_description)(struct bliss_option* this, const char* description);
	struct bliss_option* (*set_exec_func)(
			struct bliss_option* this,
			void (*option_exec_func)(void));
	struct option* (*get_option)(struct bliss_option* this);
	struct option* this_option;
};

static struct option* this_get_option(struct bliss_option* this)
{
	if (this == NULL) return NULL;
	return this->this_option;
}

static struct bliss_option* this_set_name(struct bliss_option* this, const char* name)
{
	if (this == NULL) return NULL;
	this->this_option->set_name(this->this_option, name);
	return this;
}

static struct bliss_option* this_set_name_short(struct bliss_option* this, const char* name_short)
{
	if (this == NULL) return NULL;
	this->this_option->set_name_short(this->this_option, name_short);
	return this;
}

static struct bliss_option* this_set_description(struct bliss_option* this, const char* description)
{
	if (this == NULL) return NULL;
	this->this_option->set_description(this->this_option, description);
	return this;
}

static struct bliss_option* this_set_exec_func(struct bliss_option* this, void (*option_exec_func)(void))
{
	if (this == NULL) return NULL;
	this->this_option->set_exec_func(this->this_option, option_exec_func);
	return this;
}

struct bliss_option* new_bliss_option(const char* name)
{
	struct bliss_option* tmp = (struct bliss_option*)malloc(sizeof(struct bliss_option));
	tmp->get_option = this_get_option;
	tmp->set_name = this_set_name;
	tmp->set_name_short = this_set_name_short;
	tmp->set_description = this_set_description;
	tmp->set_exec_func = this_set_exec_func;
	tmp->this_option = new_option(name);
	return tmp;
}

void delete_bliss_option(struct bliss_option* bliss_option_info)
{
	if (bliss_option_info == NULL) return;
	if (bliss_option_info->this_option != NULL) {
		delete_option(bliss_option_info->this_option);
	}
	free(bliss_option_info);
	bliss_option_info = NULL;
}
