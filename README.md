v1 is broken and required some bodge wires to work. I have not updated the schematic and PCB to correct my mistakes. It also has some deficencies in the dimming circuit resulint in a quiet, but audible whine.

v2 is in progress and will fix many issues and make the clock easier to update. It wil be using an RP2040.

Features
- Automatic time seting using GPS
- User sets their time zone using dip switches
- Tubes dim with ambient light
- Day light savings time will be controlled using a +/-1 switch 
- Plenty of test points for testing and hacking
- USB C for power and data

The goal of this is to be a program once project so the end user will never need to plug it into a computer. But if they do, the RP2040 will make firmware updates easy
