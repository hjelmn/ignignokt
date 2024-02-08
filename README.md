This project contains all the files from my recreation of the Ignignokt LED sign. Included in this repository are the current Kicad files.

The board is roughly based on the data available at:

https://hackaday.io/project/183827-reverse-engineering-the-mooninite-led-panels/details

with minor modifications (there could be errors-- if you find some please post a PR with the fix):

 - Added a barrel power input to support an external power supply. Added a circuit to disable the batter if an external power supply is connected. This circuit uses a P-channel MOSFET which closes the Batt+ when a voltage is detected on Vcc.
 - Added a battery pack connector and pads to solder on a battery.

TODO:

 - Code for the microcontroller.
 - Err

The current version of the board costs roughly $85 to produce with LEDs from China and parts sourced from the US.

To use this project download kicad and open the project.

The license for all of these files is GPLv3.