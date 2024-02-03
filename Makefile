# SPDX-License-Identifier: GPL-2.0
# Copyright Fiona Klute <fiona.klute@gmx.de>

firmware_install = rtw8703b_fw.bin \
	rtw8703b_wow_fw.bin
firmware_files = rtw8703b_ap_fw.bin \
	$(firmware_install)

all: $(firmware_files)

install: $(firmware_install)
	sudo mkdir -p /lib/firmware/rtw88/
	sudo install -m 644 $(firmware_install) /lib/firmware/rtw88/

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
