# Notes on Building Marlin firmware for TRONXY X5SA PRO

## Mac

The following steps were required under macOS beyond those documented in the `README.md` file.

- Install arm-none-eabi-gcc with homebrew

`brew install armmbed/formulae/arm-none-eabi-gcc\`

- Included the changes to `buildroot/share/PlatformIO/scripts/marlin.py` as defined by madmaxed at <https://github.com/madmaxed/F4xx-SIM480x320/commit/62a904a3e3873170ca7e0e6ffa5f2bfb0a762b7d>


## Linux
- sudo apt install python3-pip
- pip install -U platformio


## Windows
- 'choco install python'
- 'pip install -U platformio'


## All Platforms

- Made corrections to the `~/.platformio/packages/framework-arduinoststm32/libraries/SrcWrapper/src/stm32/interrupt.cpp` file according to FAQ section 3 from the `README.md` file. (The path to the interrupt.cpp file changed slightly per platform but the error message tells you where it is located.)
- pio run -e tronxy_stm32f446
