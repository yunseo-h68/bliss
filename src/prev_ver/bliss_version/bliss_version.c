#include <stdlib.h>
#include "../core/version/version.h"

struct bliss_version {
	char* (*to_string)(struct bliss_version* this);
	int (*release)(struct bliss_version* this);
	int (*major)(struct bliss_version* this);
	int (*minor)(struct bliss_version* this);
	struct bliss_version* (*set_version)(
			struct bliss_version* this, 
			const char* version_string);
	
	struct version* this_version;
};

static char* this_to_string(struct bliss_version* this)
{
	return this->this_version->get_string(this->this_version);
}

static int this_release(struct bliss_version* this)
{
	return this->this_version->get_release(this->this_version);
}

static int this_major(struct bliss_version* this)
{
	return this->this_version->get_major(this->this_version);
}

static int this_minor(struct bliss_version* this)
{
	return this->this_version->get_minor(this->this_version);
}

static struct bliss_version* this_set_version(struct bliss_version* this, const char* version_string)
{
	this->this_version->set_version_from_str(this->this_version, version_string);
	return this;
}

struct bliss_version* new_bliss_version(const char* version_string)
{
	struct bliss_version* tmp = (struct bliss_version*)malloc(sizeof(struct bliss_version));
	tmp->this_version = new_version();
	tmp->this_version->set_version_from_str(tmp->this_version, version_string);
	
	tmp->to_string = this_to_string;
	tmp->release = this_release;
	tmp->major = this_major;
	tmp->minor = this_minor;
	tmp->set_version = this_set_version;
	
	return tmp;
}

void delete_bliss_version(struct bliss_version* bliss_version_info)
{
	if (bliss_version_info->this_version != NULL) {
		delete_version(bliss_version_info->this_version);
	}
	free(bliss_version_info);
	bliss_version_info = NULL;
}
