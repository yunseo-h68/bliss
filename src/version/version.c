#include <math.h>
#include "../util/util.h"

struct version {
	int release;
	int major;
	int minor;
	char* str;

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
}

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

static int get_release(struct version* this)
{
	return this->release;
}

static int get_major(struct version* this)
{
	return this->major;
}

static int get_minor(struct version* this)
{
	return this->minor;
}

static char* get_string(struct version* this)
{
	this->str = version_to_string(this);
	return this->str;
}

static struct version* set_release(struct version* this, int release)
{
	this->release = release;
	return this;
}

static struct version* set_major(struct version* this, int major)
{
	this->major = major;
	return this;
}

static struct version* set_minor(struct version* this, int minor)
{
	this->minor = minor;
	return this;
}

static struct version* set_version_from_str(struct version* this, const char* str)
{
	version_parse(this, str);
	return this;
}

static struct version* up_release(struct version* this)
{
	(this->release)++;
	return this;
}

static struct version* up_major(struct version* this)
{
	(this->major)++;
	return this;
}

static struct version* up_minor(struct version* this)
{
	(this->minor)++;
	return this;
}

struct version* new_version()
{
	struct version* tmp = (struct *version)malloc(sizeof(struct version));
	tmp->get_release = get_release;
	tmp->get_major = get_major;
	tmp->get_minor = get_minor;
	tmp->get_string = get_string;
	tmp->set_release = set_release;
	tmp->set_major = set_major;
	tmp->set_minor = set_minor;
	tmp->set_version_from_str = set_version_from_str;
	tmp->up_release = up_release;
	tmp->up_major = up_major;
	tmp->up_minor = up_minor;
	return tmp;
}

void delete_version(struct version* version_info)
{
	if (version_info->str != NULL)
		free(version_info->str);
	if (version_info != NULL)
		free(version_info);
}
