#!/bin/bash
# Command-line build of cutcutgo-bl for PIC32MK1024MCF100 (no MPLAB X needed).
# Mirrors the settings in cutcutgo_bl.X/nbproject/configurations.xml.
# Usage (Git Bash):  ./build.sh      ->  build/cutcutgo_bl_pic32mk1024mcf100.hex
# Override tool locations with XC32_DIR / DFP_DIR if yours differ.
set -euo pipefail

XC32_DIR="${XC32_DIR:-/c/Program Files/Microchip/xc32/v5.10}"
DFP_DIR="${DFP_DIR:-/c/Program Files/Microchip/MPLABX/v6.20/packs/Microchip/PIC32MK-MC_DFP/1.11.151}"
CC="$XC32_DIR/bin/xc32-gcc"
BIN2HEX="$XC32_DIR/bin/xc32-bin2hex"

ROOT="$(cd "$(dirname "$0")" && pwd)"
PRJ="$ROOT/cutcutgo_bl.X"
CFG="src/config/pic32mk_mcf100"
NAME="cutcutgo_bl_pic32mk1024mcf100"
OUT="$ROOT/build"
mkdir -p "$OUT/obj"

COMMON=(-mprocessor=32MK1024MCF100 "-mdfp=$DFP_DIR")
CFLAGS=("${COMMON[@]}" -g -O2 -fno-common -ffunction-sections -fdata-sections
        -I"$PRJ/src" -I"$PRJ/$CFG" -Werror-implicit-function-declaration)

SRCS=(
  $CFG/driver/memory/src/drv_memory_nvm.c
  $CFG/driver/memory/src/drv_memory.c
  $CFG/driver/usb/usbfs/src/drv_usbfs.c
  $CFG/driver/usb/usbfs/src/drv_usbfs_device.c
  $CFG/peripheral/clk/plib_clk.c
  $CFG/peripheral/evic/plib_evic.c
  $CFG/peripheral/gpio/plib_gpio.c
  $CFG/peripheral/nvm/plib_nvm.c
  $CFG/stdio/xc32_monitor.c
  $CFG/system/int/src/sys_int.c
  $CFG/usb/src/usb_device_msd.c
  $CFG/usb/src/usb_device.c
  $CFG/initialization.c
  $CFG/interrupts.c
  $CFG/exceptions.c
  $CFG/usb_device_init_data.c
  $CFG/tasks.c
  src/main.c src/app.c src/buttons.c src/led.c src/reset.c src/fat32.c
)

OBJS=()
cd "$PRJ"
for s in "${SRCS[@]}"; do
  o="$OUT/obj/$(echo "$s" | tr '/' '_' ).o"
  echo "CC  $s"
  "$CC" "${CFLAGS[@]}" -c "$s" -o "$o"
  OBJS+=("$o")
done

# Note: xc32-gcc -mdfp links the device's interrupt vector offset (OFFxxx)
# initialisation automatically; the linker's "Optional file
# vector_offset_init.o not found" message is harmless.
ELF="$OUT/$NAME.elf"
echo "LD  $ELF"
"$CC" "${COMMON[@]}" -o "$ELF" "${OBJS[@]}" \
  -Wl,--script="$PRJ/$CFG/p32MK1024MCF100.ld" \
  -Wl,--defsym=_min_heap_size=512,--gc-sections,-Map="$OUT/cutcutgo_bl.map"
"$BIN2HEX" "$ELF"
echo "HEX ${ELF%.elf}.hex"
