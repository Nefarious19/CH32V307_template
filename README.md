# CH32V307VCT6 FreeRTOS example (on CH32V307-EVT board)

This repository contains CH32V307VCT6 RISC-V microcontroller FreeRTOS template project.
This simple project demonstrates how to use latest FreeRTOS kernel (with small modifications for QingKeV4 CPU) with mentioned MCU.

I took some code and ideas from: https://blog.imi.moe/freertos-on-ch32v307/

I'm thanking author for shared knowledge, code and inspiration.

This repo also contains code that was written by Nanjing Qinheng Microelectronics Co., Ltd.
I did not found any info about license.

# Code description

Firmware in this repo:
- initializes clock to 144MHz using HSE and PLL
- initializes PC0 as output and is using this pin to blink with an onboard LED
- print PC0 GPIO state to serial output
- uses FreeRTOS task to blink

# How to build

This code can be build and flashed on any modern linux computer. I used Ubuntu 22.04 on Ryzen 5900X based PC. With some modifications, it can be also build and flashed on windows.

### Prerequisites

Minimal cmake version 3.10 is required for build process.

### Clone this repo

```bash
git clone https://github.com/Nefarious19/CH32V307_template.git --recursive

cd CH32V307_template

git submodule update --init --recursive
```

### Download toolchain

Go to directory above this repo and download toolchain

```bash
wget http://file.mounriver.com/tools/MRS_Toolchain_Linux_x64_V1.90.tar.xz
```
### Decompress toolchain

Use **tar** to decompress toolchain

```bash
tar -xvf MRS_Toolchain_Linux_x64_V1.90.tar.xz
```
### Change folder name

Change folder name

```bash
mv MRS_Toolchain_Linux_x64_V1.90 riscv_toolchain
```

Optionally, you can remove downloaded archive

```bash
rm MRS_Toolchain_Linux_x64_V1.90.tar.xz
```

### Build

Go back to repo root directory

```bash
cd CH32V307_template
```
Create build directory

```bash
mkdir build
```
Go to build dir

```bash
cd build
```

#### Release build

Invoke

```bash
cmake -DCMAKE_BUILD_TYPE=Release ../

make
```

#### Debug build

Invoke

```bash
cmake -DCMAKE_BUILD_TYPE=Debug ../

make
```

### Flashing

I assume you are using WCH link. If so, be sure you have properly configured it.

Go to downloaded toolchain directory

#### Before flashing test your connection to target


```bash
cd riscv_toolchain/beforeinstall

./start.sh
```

```bash
cd riscv_toolchain/OpenOCD/bin

./openocd -f ./wch-riscv.cfg
```

You should see output as below

```
Open On-Chip Debugger 0.11.0+dev-02415-gfad123a16-dirty (2023-10-11-14:01)
Licensed under GNU GPL v2
For bug reports, read
	http://openocd.org/doc/doxygen/bugs.html
Info : only one transport option; autoselect 'sdi'
Warn : Transport "sdi" was already selected
Ready for Remote Connections
Info : Listening on port 6666 for tcl connections
Info : Listening on port 4444 for telnet connections
Info : WCH-LinkE  mode:RV version 2.11 
Info : wlink_init ok
Info : clock speed 6000 kHz
Info : [wch_riscv.cpu.0] datacount=2 progbufsize=8
Info : [wch_riscv.cpu.0] Examined RISC-V core; found 1 harts
Info : [wch_riscv.cpu.0]  XLEN=32, misa=0x40901125
[wch_riscv.cpu.0] Target successfully examined.
Info : starting gdb server for wch_riscv.cpu.0 on 3333
Info : Listening on port 3333 for gdb connections
```

#### Flashing target

Go to build directory

```bash
cd CH32V307_template/build
```

and invoke 

```bash
make flash_mcu
```

You should see output as below

```
[  6%] Built target freertos_kernel_port
[ 26%] Built target freertos_kernel
[100%] Built target ch32v307_template.elf
Open On-Chip Debugger 0.11.0+dev-02415-gfad123a16-dirty (2023-10-11-14:01)
Licensed under GNU GPL v2
For bug reports, read
	http://openocd.org/doc/doxygen/bugs.html
Info : only one transport option; autoselect 'sdi'
Warn : Transport "sdi" was already selected
Ready for Remote Connections
Info : WCH-LinkE  mode:RV version 2.11 
Info : wlink_init ok
Info : clock speed 6000 kHz
Info : [wch_riscv.cpu.0] datacount=2 progbufsize=8
Info : [wch_riscv.cpu.0] Examined RISC-V core; found 1 harts
Info : [wch_riscv.cpu.0]  XLEN=32, misa=0x40901125
[wch_riscv.cpu.0] Target successfully examined.
Info : starting gdb server for wch_riscv.cpu.0 on 3333
Info : Listening on port 3333 for gdb connections
** Programming Started **
Info : device id = 0x7bbe759e
Info : flash size = 288kbytes
Info : ROM 256 kbytes RAM 64 kbytes
** Programming Finished **
** Verify Started **
** Verified OK **
** Resetting Target **
shutdown command invoked
[100%] Built target flash_mcu
```