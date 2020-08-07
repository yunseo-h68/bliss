#ifndef BLISS_BLISS_VERSION_H
#define BLISS_BLISS_VERSION_H

struct bliss_version {
	char* (*to_string)(struct bliss_version* this);
	int (*release)(struct bliss_version* this);
	int (*major)(struct bliss_version* this);
	int (*minor)(struct bliss_version* this);
	struct bliss_version* (*set_version)(
			struct bliss_version* this, 
			const char* version_string);
};

struct bliss_version* new_bliss_version(const char* version_string);
void delete_bliss_version(struct bliss_version* bliss_version_info);

#endif
