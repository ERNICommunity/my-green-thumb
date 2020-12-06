# my-green-thumb

## Status
![example workflow name](https://github.com/ERNICommunity/my-green-thumb/workflows/build-app_arm-gcc/badge.svg)
![example workflow name](https://github.com/ERNICommunity/my-green-thumb/workflows/buildNtest-core_linux-gcc/badge.svg)

## Getting Started

### Prerequisites

- [git](https://git-scm.com/downloads)
- [Docker Desktop](https://www.docker.com/get-started)
- [Visual Studio Code](https://code.visualstudio.com/)
  - Add Extension `ms-vscode-remote.remote-containers`

### Installation

- Get the repo:
  ```ssh
  git clone --recursive https://github.com/ERNICommunity/my-green-thumb
  ```
- Start `Docker Desktop`
- Open the project folder in VS Code.  
  Press `ctrl+shift+p` to open the command palette and enter `Remote-Containers: Reopen in Container`.

### Build

- Open the internal terminal in VS Code
  Press `ctrl+shift+p` to open the command palette and enter `Toggle Integrated Terminal`.
- Build the app or the tests with the scripts in the tools folder:
  ```ssh
  ./tools/build_app.sh
  ```

### Flash the image

- Use the Micro USB cable to connect the **USB STLink** port on the STM DevKit to your computer.
- In File Explorer, find the binary files that you created in the previous section.
- Copy the binary file.
- In File Explorer, find the STM Devkit that's connected to your computer. The device appears as a drive on your system with the drive label **DIS_L4IOT**.
- Paste the binary file into the root folder of the STM Devkit. Flashing starts automatically and completes in a few seconds.

    > Note: During the flashing process, a LED rapidly toggles between red and green on the STM DevKit.

### Debugging

- Get [openODC](http://openocd.org/getting-openocd/)
- Start OpenODC (Replace MY_IP_ADDRESS with your actual IP): 
  ```
  cd path_to_openocd_folder
  openocd -f scripts/interface/stlink.cfg -f scripts/board/stm32l4discovery.cfg -c "gdb_port 3333" -c "telnet_port 4444" -c "bindto MY_IP_ADDRESS" -c "init; reset init; halt"
  ```
- Open `.vscode/launch.json` file
- Change go to the 'cortex-debug' configuration an change the IP-address under `"gdbTarget": "MY_IP_ADDRESS:3333"` to your IP-address

At moment an autoconfiguration of the IP-address isn't possible.

## Wiki

[Go to wiki](https://github.com/ERNICommunity/my-green-thumb/wiki/Software-Requirements-Specification)

## TODO

- Useing of proper Namespaces
- Top Level Class Smartpot
- Make WaterRegulator / MoistureSensor / WaterValve configurable
- Interface documentation