This is just one of many other Intel 8080 emulation programs for linux.  As you might guess, I didn't write it because the others are trash, (I expect they are as good or better), but rather I just simply wanted to do it.  After getting CP/M up and running I started to remember what it was like to use a computer back in the day.  It's amazing that back then how we thought of it as this fantastic productivity tool and today my only thought is how did we get anything done.

I had intentions to do (actually started as) a Zilog Z80 emulation.  But, after getting the base Intel instructions running and getting CP/M up and running I more or less lost interest in the whole thing.

A couple things of interest:

I have a throttle in the instruction fetch function (no idea how accurate it is) but normally leave it disabled.  (I have no patience.)

The emulator is fully capable of running as an Intel 8080 or a Zilog Z80 (if the instruction set is ever completed).

Processor emulation mode can be changed on the fly.

Intel 8080 and Zilog Z80 flags are generated per the processor manual.  The main differences being the DAA instruction and the parity flag.
  
With CP/M running disks may be mounted and dismounted through the embedded command processor activated by pressing the 'F1' key.
