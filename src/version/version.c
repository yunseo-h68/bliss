#include <stdio.h>
#include <math.h>
#include "version.h"

static int version_parse_number(int* version_num, const char* version_str, int start, int finish)
{
	int i = 0, j = 0;
	long double version_temp = 0;

	for (i = start; i < finish; i++) {
		if ('0' > version[i] || '9' < version_str[i])
			continue;
		version_temp += (version_str[i] - '0') / pow(10, j);
		j++;
	}
	*version_num = version_temp * pow(10, j - 1);
	return i;
}

void version_print(const char* name, struct version_info version)
{
	printf("%s version %d.%d.%d\n",
			name,
			version.release,
			version.major,
			version.minor
		  );
}

void version_parse(struct version_info* version, const char* version_str)
{
	int i = 0;
	int j = 0;

	while (version_str[i++] != '.' && version_str[i]);
	j = version_parse_number(&(version->release), version_str, j, i);
	i++;

	while (version_str[i++] != '.' && version_str[i]);
	j = version_parse_number(&(version->major), version_str, j, i);
	i++;

	while (version_str[i++] != '.' && version_str[i]);
	j = version_parse_number(&(version->minor), version_str, j, i);

	if (version->release == 0 &&
			version->major == 0 &&
			version->minor == 0) {
		version->minor++;
	}
}
