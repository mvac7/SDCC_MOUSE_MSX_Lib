# Mouse MSX SDCC Library (fR3eL Project)

```
Author: Ramones
        adapted to SDCC by Andrear
        new versions by mvac7 [mvac7303b@gmail.com]
Architecture: MSX
Format: C Object (SDCC .rel)
Programming language: C and Z80 assembler
```



## Description

This project is an Open Source library with basic functions for reading mouse controller of MSX computers.

Use them for developing MSX applications using Small Device C Compiler (SDCC).

This library allows the use of mouse control on first generation MSX computers, since the GTPAD function of the BIOS does not support it.

It can be used for developing ROM applications such as MSX-DOS.

The source code includes an application to test or learn how to use the library.

This library is part of the [MSX fR3eL Project](https://github.com/mvac7/SDCC_MSX_fR3eL).

Enjoy it!



## Requirements

* Small Device C Compiler (SDCC) v3.9 http://sdcc.sourceforge.net/
* Hex2bin v2.5 http://hex2bin.sourceforge.net/ 




## History of versions:
```
   v1.0 (2007) First version (by Ramones)
   v1.1 (2011) Adapted to SDCC (by Andrear)
   v1.2 (08/08/2012) Commented button control code. Use the STRIG function from the SDCC JOYSTICK Library.
                     Commented the code that calls the GTPAD function of the BIOS, so that it works in MSX-DOS.
   v1.3 (24/01/2016) The CheckMouse function performs the complete check and returns the resulting value.
   v1.4 (11/12/2020) Converted to C language. Coordinates are passed to C variables instead of fixed positions in memory.
```


## Functions

* char **CheckMouse**() - Check if there is a mouse connected to any of the ports.
* void **MouseRead**() - Mouse reading.



## Variables

* Mouse_port [char] - value of mouse port (0 - nothing; 1 - port A; 2 - port B)
* Mouse_X [signed char] - value of X-axis of the mouse
* Mouse_Y [signed char] - value of Y-axis of the mouse 



## Acknowledgments
  
I want to give a special thanks to all those who freely share their knowledge with the MSX developer community.

* Ramones > [MSXblog](https://www.msxblog.es/tutoriales-de-programacion-en-ensamblador-ramones/) [MSXbanzai](http://msxbanzai.tni.nl/dev/faq.html)
* Andrear > [Blog](http://andrear.altervista.org/home/msxsoftware.php)
* Avelino Herrera > [WEB](http://msx.atlantes.org/index_es.html)
* Nerlaska > [Blog](http://albertodehoyonebot.blogspot.com.es)
* Marq/Lieves!Tuore > [Marq](http://www.kameli.net/marq/) [Lieves!Tuore](http://www.kameli.net/lt/)
* [Fubukimaru](https://github.com/Fubukimaru) > [Blog](http://www.gamerachan.org/fubu/)
* Sapphire/Z80ST > [WEB](http://z80st.auic.es/)
* Fernando García > [youTube](https://www.youtube.com/user/bitvision)
* Eric Boez > [gitHub](https://github.com/ericb59)
* MSX Assembly Page > [WEB](http://map.grauw.nl/resources/msxbios.php)
* Portar MSX Tech Doc > [WEB](http://nocash.emubase.de/portar.htm)
* MSX Resource Center > [WEB](http://www.msx.org/)
* Karoshi MSX Community (RIP 2007-2020)
* BlueMSX emulator >> [WEB](http://www.bluemsx.com/)
* OpenMSX emulator >> [WEB](http://openmsx.sourceforge.net/)
* Meisei emulator >> ?
