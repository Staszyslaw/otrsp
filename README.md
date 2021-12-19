# OTRSP controller

## Requirements
#### Debian based:
``sudo apt install git build-essential cmake qtbase5-dev``

#### Arch based
``sudo pacman -S git base-devel cmake qt5-tools``

## Building from source
```console
$ git clone git@github.com:Staszyslaw/otrsp.git
$ cd otrsp
$ mkdir Release
$ cmake -S . -B Release -D CMAKE_BUILD_TYPE=Release
$ cmake --build Release
$ cd Release && ./otrsp
```

## Configuration
Configuration for this app is stored in config.json file generated on first run.<br />
Config is stored in the same directory as the app.
In the same directory there will be created windowpos file, which contains saved position of the window so it can be restored on next run.
In case of any problems you can delete any of the files and the app will be configured again.
##### Default configuration:
```json
{
  "autoConnect": "false", // "true" or "false" - auto connect to serial on startup
  "stayOnTop": "false", // "true" or "false" - stay on top of all windows
  "buttons": { // buttons configuration
    "button1": { // button1 configuration
      "action": "AUX11", // action to be sent to controller. 
                         //Termination character is added automatically
      "text": "Button 1" // text to be displayed on button
    },
    "button2": { // button2 configuration
      "action": "AUX12", // same as above
      "text": "Button 2" // same as above
    },
    "button3": { // ...
      "action": "AUX13",
      "text": "Button 3"
    },
    "button4": {
      "action": "AUX14",
      "text": "Button 4"
    },
    "button5": {
      "action": "AUX15",
      "text": "Button 5"
    },
    "button6": {
      "action": "AUX16",
      "text": "Button 6"
    },
    "button7": {
      "action": "AUX17",
      "text": "Button 7"
    },
    "button8": {
      "action": "AUX18",
      "text": "Button 8"
    }
  },
  "serial": { // serial port configuration
    "baudrate": "9600", // baudrate (9600, 19200, 38400, 57600, 115200)
    "port": "ttyUSB0" // port name (ttyUSB0, ttyS0, ttyAMA0, etc.)
                      //No need to add "/dev/" prefix
  }
}
```

## Libraries used
- [Qt](https://www.qt.io/)
- [RS232](https://gitlab.com/Teuniz/RS-232/-/tree/master)
- [miniconf](https://github.com/c-w-m/miniconf/)

## License
This software is licensed under the terms of the GNU General Public License version 3.
Full license text is available at https://www.gnu.org/licenses/gpl-3.0.html