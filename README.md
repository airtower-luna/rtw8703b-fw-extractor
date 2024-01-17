# RTL8723CS/RTL8703B firmware extractor

The [vendor `8723cs` driver in megi's tree that's commonly used on the
Pinephone
today](https://xff.cz/git/linux/tree/drivers/staging/rtl8723cs?h=orange-pi-6.7&id=f45c45abc5325682d06cb51c06aba1f817fba462)
contains its firmware as huge byte arrays, which doesn't work nicely
with the modern Linux firmware infrastructure. The code in this
repository compiles them into a binary which writes them to disk as
binary files.

The files `hal8703b_fw.h` and `hal8703b_fw.c` have been [copied
verbatim from the vendor
driver](https://xff.cz/git/linux/tree/drivers/staging/rtl8723cs/hal/rtl8703b?h=orange-pi-6.7&id=f45c45abc5325682d06cb51c06aba1f817fba462).
`drv_types.h` is a compatibility header that defines types and macros
used in the former files, and `rtw8703b_fw.c` is the tool that takes
the arrays and writes them to disk.

## Naming

RTL8723CS is the name of the combined wifi/bluetooth chip in the
Pinephone, according to the vendor code the wifi component is called
RTL8703B. I'm using the `rtw` prefix for this tool because it matches
the `rtw88` based driver I'm experimenting with.

## Usage

Assuming you have `make` and GCC, calling `make` should be all that's
needed:

```
$ make
gcc -fPIC -DCONFIG_RTL8703B -c -o rtw8703b_fw.o rtw8703b_fw.c
gcc -fPIC -DCONFIG_RTL8703B -c -o hal8703b_fw.o hal8703b_fw.c
gcc -DCONFIG_RTL8703B -o rtw8703b_fw rtw8703b_fw.o hal8703b_fw.o
./rtw8703b_fw
rtw8703b_ap_fw.bin: 19994 bytes
rtw8703b_fw.bin: 20290 bytes
rtw8703b_wow_fw.bin: 23074 bytes
```

The resulting `*.bin` files are the firmware binaries. For use with
[my experimental `rtw88_8703b`/`rtw88_8723cs`
driver](https://github.com/airtower-luna/linux/tree/rtw88_8723cs/drivers/net/wireless/realtek/rtw88)
place them in `/lib/firmware/rtw88/`.
