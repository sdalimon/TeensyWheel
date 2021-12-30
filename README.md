# TeensyWheel
A replacement PCB for the Flashfire ForceWheel WH2304-V gaming wheel

I bought the Flashfire ForceWheel WH2304-V because it was low cost, but found the button configuration annoying.  There are a lot of bottons, but many of them are shared with other functions (like the paddles and gearshift).  Some of this was configurable, but it had to be done each time the unit was plugged in.

I knew a Teensy can act as a joystick so looked into using one as a replacement controller.  It didn't turn out that hard.  Most of the time was spent measuring the button and mounting hole locations on the original PCB to be sure the replecement would fit.
A bit of code later and now all buttons are indiviually mapped to joystick inputs.  

It works well, but I haven't used it a lot since I am having trouble with the button mapping in American Truck Simulator to make them all work. They all show up and work in the Windows control panel.

The software does not implement the vibration or USB host features.

Sorry there isn't a BOM, but most of the parts were scavanged off the original PCB.
