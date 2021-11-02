PLEASE REFER TO THE APPLICATION NOTE FOR THIS MODULE FOR MORE INFORMATION

r_flash_rx
=================

Document Number 
---------------
r01an2184eu0110

Version
-------
v1.10

Overview
--------
A simple Application Program Interface (API) has been created to allow users of flash based RX600, RX200 and RX100 Series
devices to easily integrate reprogramming abilities into their applications using User Mode programming. User Mode programming 
is the term used to describe a Renesas MCU's ability to reprogram its own internal flash memory while running in its 
normal operational mode. 

Features
--------
* Data and Code Flash Erase
* Data and Code Flash Blank Check
* Data and Code Flash Write
* Supports background operations (BGO) on ROM and data flash.
* RX100 Code Flash access window protection
* RX100 Code Flash swap section support
* RX600 and RX200 ROM lock bit support

Supported MCUs
--------------
* RX110 Group
* RX111 Group
* RX113 Group
* RX610 Group
* RX621, RX62N Group
* RX62T Group
* RX62G Group
* RX630 Group
* RX631, RX63N Group 
* RX63T Group
* RX210 Group
* RX21A Group
* RX220 Group


Boards Tested On
----------------
* RSKRX110
* RSKRX111
* RSKRX113
* RSKRX610
* RSK+RX62N
* RSKRX62T
* YRDKRX62N
* RSKRX630
* RSK+RX63N
* YRDKRX63N
* RSKRX62G
* RSKRX63T_64PIN
* RSKRX63T_144PIN
* RSKRX210
* RSKRX210B
* HSBRX21AP
* RSKRX220


Limitations
-----------
* This code is not re-entrant but does protect against multiple concurrent function calls.
* During ROM operations neither the ROM or DF can be accessed. If using ROM BGO then make sure code runs from RAM.
* During DF operations the DF cannot be accessed but ROM can be accessed normally.

Peripherals Used Directly
-------------------------
* Flash Control Unit (FCU) - RX600 and RX200 only


Required Packages
-----------------
* r_bsp      V2.70

How to add to your project
--------------------------
* Add the r_flash_rx and r_config folders to your project.
* Add a project include path for the 'r_flash_rx' directory. 
* Add a project include path for the 'r_flash_rx\src' directory.
* Add a project include path for the 'r_flash_rx\src\targets' directory.

For RX100 MCU's:
* Add a project include path for the 'r_flash_rx\src\non_fcu\rx100' directory.
* Copy the reference configuration file 'r_flash_rx100_config_reference.h' to your project and rename it 
  r_flash_rx_config.h.

For RX200  and RX600 MCU's:
* Add a project include path for the 'r_flash_rx\src\fcu' directory.
* Copy the reference configuration file 'r_flash_config_reference.h' to your project and rename it 
  r_flash_rx_config.h.

* Configure middleware for your system through just copied r_flash_rx_config.h.
* Add a #include for r_flash_api_rx_if.h to any source files that need to use the Flash API.
* (The following steps are only required if you are programming or erasing ROM. If you are only operating on data 
  flash, then these steps can be ignored. These steps are discussed with more detail in the app note.)
* Make a ROM section named 'PFRAM'.
* Make a RAM section named 'RPFRAM'.
* Configure your linker such that code allocated in the 'FRAM' section will actually be executed in RAM. (see app note)
* After reset, make sure the Flash API code is copied from ROM to RAM. This can be done by calling the 
  R_FlashCodeCopy() function.


* Add a project include path for the 'r_config' directory.
* Open "r_config\r_flash_rx_config.h" file and configure the driver for your 
  project.
* Add a #include for r_flash_rx_if.h to any source files that need to use the 
  API functions.

Toolchain(s) Used
-----------------
* Renesas RX v2.01.00


File Structure
--------------
r_flash_rx
|   readme.txt
|   r_flash_rx_if.h
|
+---doc
|       r01an2184eu0110_rx.pdf
|
+---ref
|       r_flash_rx_config_reference.h
|
+---src
    +-- r_flash_rx.c
    +-- r_flash_rx.h
    |
    +-- targets
        |
        |--rx21a
             |
             |-- r_flash_api_rx21a.h
        |
        |--rx62g
             |
             |-- r_flash_api_rx62g.h
        |
        |--rx62n
             |
             |-- r_flash_api_rx62n.h
        |
        |--rx62t
             |
             |-- r_flash_api_rx62t.h
        |
        |--rx63n
             |
             |-- r_flash_api_rx63n.h
        |
        |--rx63t
             |
             |-- r_flash_api_rx63t.h
        |
        |--rx110
             |
             |-- r_flash_api_rx110.h
        |
        |--rx111
             |
             |-- r_flash_api_rx111.h
        |
        |--rx113
             |
             |-- r_flash_api_rx113.h
        |
        |--rx210
             |
             |-- r_flash_api_rx210.h
        |
        |--rx220
             |
             |-- r_flash_api_rx220.h
        |
        |--rx610
             |
             |-- r_flash_api_rx610.h
        |
        |--rx630
             |
             |-- r_flash_api_rx630.h
 
    |
    +-- fcu
         |--r_flash_fcu_64m_rx.c
         |
         |--r_flash_fcu_64m_if.h
         |
         |--r_flash_fcu_rx.c
         |
         |--r_flash_fcu_if.h
    |
    +-- non_fcu\rx100
         |
         |--r_codeflash_extra_rx100.c
         |
         |--r_codeflash_extra_rx100.h
         |
         |--r_codeflash_rx100.c
         |
         |--r_codeflash_rx100.h
         |
         |--r_dataflash_rx100.c
         |
         |--r_dataflash_rx100.h
         |
         |--r_flash_common_rx100.h 
         |
         |--r_flash_rx100_rx.c
         |
         |--r_flash_rx100_if.h
         | 
         |--r_flash_utils.c        |
    
r_config
    r_flash_rx_config.h

