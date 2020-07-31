#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../util/util.h"

struct version {
	int (*get_release)(struct version* this);
	int (*get_major)(struct version* this);
	int (*get_minor)(struct version* this);
	char* (*get_string)(struct version* this);
	struct version* (*set_release)(struct version* this, int release);
	struct version* (*set_major)(struct version* this, int major);
	struct version* (*set_minor)(struct version* this, int minor);
	struct version* (*set_version_from_str)(struct version* this, const char* str);
	struct version* (*up_release)(struct version* this);
	struct version* (*up_major)(struct version* this);
	struct version* (*up_minor)(struct version* this);
	
	int release;
	int major;
	int minor;
	char* str;
};

static int version_parse_number(int* version_num, const char* version_str, int start, int finish)
{
	int i = 0, j = 0;
	long double version_temp = 0;

	for (i = start; i < finish; i++) {
		if ('0' > version_str[i] || '9' < version_str[i])
			continue;
		version_temp += (version_str[i] - '0') / pow(10, j);
		j++;
	}
	*version_num = version_temp * pow(10, j - 1);
	return i;
}

static void version_parse(struct version* version_info, const char* str)
{
	int finish = 0;
	int start = 0;
	int i = 0;
	int *version_nums[3] = {&(version_info->release), &(version_info->major), &(version_info->minor)};

	for (i = 0; i < 3; i++) {
		while (str[finish+1] != '.' && str[finish+1]) 
			finish++;
		start = version_parse_number(version_nums[i], str, start, finish);
		finish++;
	}
}

static char* version_to_string(struct version* version_info)
{
	int version_size = 
		get_digit_number(version_info->release) + 
		get_digit_number(version_info->major) + 
		get_digit_number(version_info->minor) + 4;
	char *version_str = (char*)malloc(sizeof(char) * version_size);
	sprintf(version_str, "%d.%d.%d", version_info->release, version_info->major, version_info->minor);
	return version_str;
}

static int this_get_release(struct version* this)
{
	return this->release;
}

static int this_get_major(struct version* this)
{
	return this->major;
}

static int this_get_minor(struct version* this)
{
	return this->minor;
}

static char* this_get_string(struct version* this)
{
	this->str = version_to_string(this);
	return this->str;
}

static struct version* this_set_release(struct version* this, int release)
{
	this->release = release;
	return this;
}

static struct version* this_set_major(struct version* this, int major)
{
	this->major = major;
	return this;
}

static struct version* this_set_minor(struct version* this, int minor)
{
	this->minor = minor;
	return this;
}

static struct version* this_set_version_from_str(struct version* this, const char* str)
{
	version_parse(this, str);
	return this;
}

static struct version* this_up_release(struct version* this)
{
	(this->release)++;
	return this;
}

static struct version* this_up_major(struct version* this)
{
	(this->major)++;
	return this;
}

static struct version* this_up_minor(struct version* this)
{
	(this->minor)++;
	return this;
}

struct version* new_version()
{
	struct version* tmp = (struct version*)malloc(sizeof(struct version));
	tmp->str = NULL;
	tmp->get_release = this_get_release;
	tmp->get_major = this_get_major;
	tmp->get_minor = this_get_minor;
	tmp->get_string = this_get_string;
	tmp->set_release = this_set_release;
	tmp->set_major = this_set_major;
	tmp->set_minor = this_set_minor;
	tmp->set_version_from_str = this_set_version_from_str;
	tmp->up_release = this_up_release;
	tmp->up_major = this_up_major;
	tmp->up_minor = this_up_minor;
	return tmp;
}

void delete_version(struct version* version_info)
{
	if (version_info == NULL) return;
	if (version_info->str != NULL && strlen(version_info->str) > 0) {
		free(version_info->str);
		version_info->str = NULL;
	}

	free(version_info);
	version_info = NULL;
}
