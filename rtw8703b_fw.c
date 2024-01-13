// SPDX-License-Identifier: GPL-2.0
/* Copyright Fiona Klute <fiona.klute@gmx.de> */
#include <stdio.h>
#include "drv_types.h"
#include "hal8703b_fw.h"


int write_fw_file(const char *name, const u8 *data, const u32 len)
{
	FILE *f = fopen(name, "w");
	if (f == NULL)
	{
		fprintf(stderr, "Could not open %s!\n", name);
		return -1;
	}

	size_t written = fwrite(data, sizeof(u8), len, f);
	int ret = fclose(f);

	if (written != len || ret != 0)
	{
		fprintf(stderr,
			"Write to %s failed, %zd bytes written.\n",
			name, written);
		return -2;
	}

	printf("%s: %u bytes\n", name, len);
	return 0;
}


#define WRITE_FW_CHECKED(KIND)					\
	do {							\
		int ret = write_fw_file(			\
			"rtw8703b_fw_" #KIND ".bin",		\
			array_mp_8703b_fw_ ## KIND,		\
			array_length_mp_8703b_fw_ ## KIND);	\
		if (ret	!= 0)					\
			return 1;				\
	} while (0)


int main()
{
	WRITE_FW_CHECKED(ap);
	WRITE_FW_CHECKED(nic);
	WRITE_FW_CHECKED(wowlan);

	return 0;
}
