#ifndef BLISS_VERSION_H
#define BLISS_VERSION_H

struct version_info {
	int release;
	int major;
	int minor;
};

void version_print(const char* name, struct version_info version);
void version_parse(struct version_info *version, const char* version_str);

#endif
