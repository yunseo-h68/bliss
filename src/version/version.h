#ifndef BLISS_VERSION_H
#define BLISS_VERSION_H

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
};

struct version* new_version();
void delete_version(struct version* version_info);

#endif
