// SPDX-License-Identifier: GPL-2.0
/* Copyright Fiona Klute <fiona.klute@gmx.de> */
#include <linux/types.h>

typedef __u32 u32;
typedef __u8 u8;

#define LOAD_FW_HEADER_FROM_DRIVER
#define CONFIG_AP_WOWLAN
#define CONFIG_WOWLAN

/* defined in rtl8723cs hal/phydm/phydm_types.h */
#define ODM_AP	0x01
#define ODM_CE	0x04
#define ODM_WIN	0x08

/* Set to 0x04 in rtl8723cs Makefile, but I want to extract all
 * available firmware, so I'm using a bitwise OR of all the types
 * defined above. */
#define DM_ODM_SUPPORT_TYPE 0x0d
