# About the Nemesis-Mod project...
It started off as me just wanting to play with an Arduino while repurposing some old .NET Gadgeteer hardware I had laying around the house. It turned into quite a bit more than that over the months that I worked on it. Hopefully the source code will help someone interested in replicating the success I had with my project with their own. Happy coding!

| Branch | Status |
| ------ | -------------|
| master | [![Build status](https://ci.appveyor.com/api/projects/status/i8yxeyigt2mpq8k4/branch/master?svg=true)](https://ci.appveyor.com/project/winnster/nemesis-mod/branch/master) |
| latest | [![Build status](https://ci.appveyor.com/api/projects/status/i8yxeyigt2mpq8k4?svg=true)](https://ci.appveyor.com/project/winnster/nemesis-mod) |

## Hardware Requirements
These are the boards and hardware being used by the project.
- [Nerf Rival Nemesis MXVII-10K](https://shop.hasbro.com/en-us/product/nerf-rival-nemesis-mxvii-10-k-blue:04E71588-5056-9047-F5B8-940FC9A5A209)
- [Adafruit Feather M4 Express (ATSAMD51)](https://www.adafruit.com/product/3857)
- [Adafruit Feather nRF52840 Express](https://www.adafruit.com/product/4062)
- [Adafruit FeatherWing Proto - Prototyping Add-on](https://www.adafruit.com/product/2884)
- [Adafruit I2C Non-Volatile FRAM Breakout](https://www.adafruit.com/product/1895)
- [Tactile Switch Button (12mm square, 6mm tall)](https://www.adafruit.com/product/1119)
- [Pololu Dual G2 High-Power Motor Driver 18v18 Shield for Arduino](https://www.pololu.com/product/2515)
- [Pololu G2 High-Power Motor Driver 18v17](https://www.pololu.com/product/2991)
- [Pololu 5V, 500mA Step-Down Voltage Regulator](https://www.pololu.com/product/2843)
- [MaxAmps LiPo 3250 3S 11.1v Battery Pack](https://www.maxamps.com/lipo-3250-3s-11-1v-battery-pack)

## Development Environment
This is the development environment setup that is currently being used to write the code included within this repository.

### Toolset
Below are the software which must be installed to compile the source code.
- Visual Studio Code
  - C/C++ extension
- MinGW (with msys-base-bin package)

### Toolset (optional)
The below are the optional tools that could be used as a replacement for the Makefile support.
- Arduino Extension for Visual Studio Code
- Arduino Board Manager Packages
  - Adafruit SAMD Boards (1.6.5)
  - Adafruit nRF52 Boards (0.21.0)

### Dependencies
Below are the dependencies that are being used by the project and must be installed using the Arduino IDE Library Manager.
- [Adafruit FRAM I2C](https://github.com/adafruit/Adafruit_FRAM_I2C)
- [DualG2HighPowerMotorShield](https://github.com/pololu/dual-g2-high-power-motor-shield)
