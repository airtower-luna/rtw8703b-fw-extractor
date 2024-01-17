# SPDX-License-Identifier: GPL-2.0
# Copyright Fiona Klute <fiona.klute@gmx.de>

firmware_files = rtw8703b_ap_fw.bin \
	rtw8703b_fw.bin \
	rtw8703b_wow_fw.bin

all: $(firmware_files)

%.o: %.c
	gcc -fPIC -DCONFIG_RTL8703B -c -o $@ $<

rtw8703b_fw: rtw8703b_fw.o hal8703b_fw.o
	gcc -DCONFIG_RTL8703B -o $@ $^

$(firmware_files): rtw8703b_fw
	./rtw8703b_fw

clean:
	rm -f *.o
	rm -f rtw8703b_fw
	rm -f *.bin

.PHONY: all clean
