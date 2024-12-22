# jLink 

![GitHub Release](https://img.shields.io/github/v/release/Watchdog0x/jLink)
![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)

jLink is a command-line utility for controlling your Jabra headset.

 <img src="src/image.png"/>

## Features
    - Basic Control: Manage basic functions of your Jabra headset.
    - Device Discovery: Search for new devices and manage connections.
    - Paired Devices: View the list of paired devices.
    - Battery Status: Check the battery status of your headset

## Tested Devices:

- jabra Link 380 with Jabra Evolve2 85

## Navigation
- S: Move down
- W: Move up
- Enter: Select or switch the option

## Installation

#### 1. Using curl
```bash
curl -so- https://raw.githubusercontent.com/Watchdog0x/jLink/main/install.sh | sudo bash
```

#### 2. Using wget
```bash
wget -qO- https://raw.githubusercontent.com/Watchdog0x/jLink/main/install.sh | sudo bash
```

## TODO

    - Code Cleanup: Improve the current codebase, which is in need of refactoring.
    - Device Switching: Add support for switching between multiple connected devices.
    - Headset Settings: Implement features for configuring advanced headset settings.
    - Sound Control: Integrate with PipeWire for precise sound management.
    - Daemon Service: Create a background service using IPC shared memory for seamless operation

## Contributing

Contributions are welcome! Here are some ways you can help:
Refactor and clean up the code.
Implement new features from the TODO list.
Report bugs or suggest enhancements via the issue tracke