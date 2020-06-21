**ATTITUDE HEADING REFERENCE SYSTEM**

**-With STM32F411E discovery board**

Table of Contents

[1 Introduction 3](#_Toc481000721)

[2 Description 3](#description)

[3 Environment Setup 3](#environment-setup)

[3.1 OpenOCD 3](#openocd)

[3.2 GCC Tool chain 4](#gcc-tool-chain)

[3.3 STM32cube Library 4](#stm32cube-library)

[3.4 Mavlink Library 5](#mavlink-library)

[3.5 QGroundControl 6](#qgroundcontrol)

[4 Code Generation and Compilation 6](#_Toc481000729)

[5 Software upload 7](#software-upload)

[6 Demonstration 8](#demonstration)

[6.1 Hardware setup 8](#hardware-setup)

[6.2 Qgroundcontrol setup 8](#qgroundcontrol-setup)

[6.3 Demo 9](#demo)

Introduction
============

The purpose of the project is to auto generate Codes from AADL models of
an Attitude Heading Reference System and demonstrate the implementation
of FreeRTOS targets on ST Discovery kit using Ocarina tool and
PolyORB-HI-C middleware. This document also specifies the steps required
to integrate the generated code with STMCube Library, FreeRTOS, Mavlink
and the steps required to link and generate the binary files for
implementing on the STM32F411E Discovery Board.

![http://www.st.com/st-web-ui/static/active/en/fragment/product\_related/rpn\_information/board\_photo/stm32f411e-disco.jpg](./imgs/image1.jpeg){width="2.0758081802274715in"
height="3.2334711286089237in"}![](./imgs/image2.png){width="2.8396227034120733in"
height="2.0685990813648294in"}

Figure 1 STM32F411E Discovery board

Description
===========

+-----------------------------------+-----------------------------------+
| -   ahrs-system.aadl              | -   top hierarchy AADL model to   |
|                                   |     implement the Attitude        |
|                                   |     Heading Reference             |
|                                   |     System(AHRS)                  |

+===================================+===================================+
| -   ahrs-hardware.aadl            | -   AADL model for hardware       |
|                                   |     specificities. Hardware       |
|                                   |     architecture of STM32F411E    |
|                                   |     Discovery kit is used.        |
+-----------------------------------+-----------------------------------+
| -   ahrs-software.aadl            | -   AADL model for the software   |
|                                   |     components                    |
+-----------------------------------+-----------------------------------+
| -   ahrs-subprograms.aadl         | -   AADL model for the            |
|                                   |     subprograms to link           |
|                                   |     userdefined subroutines with  |
|                                   |     AADL model.                   |
+-----------------------------------+-----------------------------------+
| -   ahrs-data\_types.aadl         | -   AADL model for the            |
|                                   |     declaration of data types     |
+-----------------------------------+-----------------------------------+
| -   threads.cpp                   | -   contains userdefined          |
|                                   |     subroutines                   |
+-----------------------------------+-----------------------------------+
| -   userdefined.mk                | -   configuration for Compiler    |
|                                   |     Linker Flags, FreeRTOS        |
|                                   |     components, userdefined       |
|                                   |     sources, path for STM32Cube   |
|                                   |     libraries and path for        |
|                                   |     Mavlink headerss              |
+-----------------------------------+-----------------------------------+
| -   LinkerScript.ld               | -   used by linker                |
+-----------------------------------+-----------------------------------+
| -   stlink-v2.cfg                 | -   ST-link configuration file    |
|                                   |     used by openocd               |
+-----------------------------------+-----------------------------------+
| -   stm32f4discovery.cfg          | -   stm32f4 discovery kit         |
|                                   |     configuration file used by    |
|                                   |     openocd                       |
+-----------------------------------+-----------------------------------+
| -   /include                      | -   contains user defined         |
|                                   |     libraries                     |
+-----------------------------------+-----------------------------------+
| -   /src                          | -   stm32f4 discovery kit         |
|                                   |     configuration file used by    |
|                                   |     openocd                       |
+-----------------------------------+-----------------------------------+

Environment Setup
=================

It is assumed that Ocarina and PolyORB-HI-C are installed in the host
machine

OpenOCD
-------

The OpenOCD is used to download the binaries from host machine to the
STM32f4 discovery board via USB ST-LINK interface . The OpenOCD 0.9.0
can be installed from the following location:

<http://sourceforge.net/projects/openocd/files/openocd/0.9.0/openocd-0.9.0.tar.bz2/download>

Once the tar is downloaded and extracted the following commands are
executed to install the application:

1.  \$ cd openocd-0.9.0

2.  \$ ./Configure

3.  \$ make

4.  \$ sudo make install

Once successfully installed, check the installation summary at the
terminal that the support for ST-Link is enabled. Build dependencies are
as follows.

-   make

-   libtool

-   pkg-config

-   libusb-1.0

While here, copy contrib/99-openocd.rules in /etc/udev/rules.d/ and add
users needing to flash the card into the plugdev group if required.

GCC Tool chain
--------------

GCC tool chain is required for cross compilation of the source code to
generate binaries for execution on the STM32 board. Recommended version
of the cross-compilation chain is gcc-4.9.3. It can be downloaded from
the link below. Export the PATH of arm-none-eabi\* binaries.

<https://launchpadlibrarian.net/218827486/gcc-arm-none-eabi-4_9-2015q3-20150921-linux.tar.bz2>.

The tool chain can also be downloaded using apt-get using commands on
the link:
<https://launchpad.net/~terry.guo/+archive/ubuntu/gcc-arm-embedded>

STM32cube Library
-----------------

The STM32CUBE can be downloaded from the link:
<http://www.st.com/web/en/catalog/tools/PF259243>. It contains the HAL
drivers, Board support packages and a copy of FreeRTOS with the
necessary bits for the specific CPU. After download required directory
perform the following.

1.  ![](./imgs/image3.png){width="5.75625in"
    height="2.4430555555555555in"}Define the macros 'STM32F411xE' and
    'USE\_HAL\_DRIVER' in the STM32cube libraires
    STM32Cube\_FW\_F4\_V1.15.0\\Drivers\\CMSIS\\Device\\ST\\STM32F4xx\\
    Include\\stm32f4xx.h

2.  This step enables the libraries for STM32411xE board. Support for
    different version of STM32F4 boards can be enabled respectively.

3.  Specifiy the path of STM32cube libraries in userdefined.mk file. Set
    the path for \"STM32LIB\". For example. 'STM32LIB = \$(HOME)/
    local/STM32Cube\_FW\_F4\_V1.15.0'

The sensor scaling logic implemented in the STM Cube Library cannot be
used with the EKF algorithm. The scaling provided by the STM Cube
library needs to be commented in the STMCube code.

Following are the files that are required to be modified:

4.  ![](./imgs/image4.png){width="6.768055555555556in"
    height="0.7515594925634296in"}The file
    STM32Cube\_FW\_F4\_V1.15.0/Drivers/BSP/Components/l3gd20/l3gd20.c.
    Function void L3GD20\_ReadXYZAngRate(float \*pfData) needs to be
    updated to remove the sensitivity multiplication.

5.  ![](./imgs/image5.png){width="6.776388888888889in"
    height="0.8416666666666667in"}The file
    STM32Cube\_FW\_F4\_V1.15.0/Drivers/BSP/Components/lsm303dlhc/lsm303dlhc.c :
    Function : void LSM303DLHC\_AccReadXYZ(int16\_t\* pData) needs to be
    modified to remove the sensitivity multiplication.

Mavlink Library
---------------

MAVLink is a protocol used for interfacing between ground control and
drones. In the sample application, the MAVLINK communication is
established between the qgroundcontrol application on PC and STM32, via
a UART interface. To download and generate MAVLINK header files for
C-lanugage use the following:

*\$ git clone* <https://github.com/mavlink/mavlink/>*.*

*\$ cd mavlink*

*\$ python mavgenerate.py*

![C:\\Aa\_MS\_EMS\\12\_Integrated Team
Project\\reports\\mavlinkgenerator.png](./imgs/image6.png){width="3.0966885389326335in"
height="1.610883639545057in"}

Figure 2 mavlink generator GUI

A MAVLink Generator GUI opens up, Do the following

-   Select the xml file, Browse to
    mavlink/message\_definitions/v1.0/common.xml.

-   Select the output directory. Browse to the desired location(here
    say: /mavlink/mavlink\_headers

-   Select the 'C' as the language option.

-   Select the protocol version 1.0

-   Click Generate button.

It generates header files contains messages structures, code to encode
and decode the messages. It is header only and does not require
compilation. Set the mavlink header path in userdefined.mk as below

-   Specifiy the path of generated mavlink headers in userdefined.mk
    file. Set the path for \"MAVLINK\_HEADERS\". For example.
    ' MAVLINK\_HEADERS=\$(HOME)/ local/ mavlink/mavlink-headers'

QGroundControl
--------------

QGroundControl provides full ground station support and configuration
for the drone Flight Stacks. QGroundControl also provides flight support
for any MAVLink capable vehicle. It is used in this project for
demonstration purposes. Any other equivalent ground station with MAVLink
protocol support can be used. QGround Control can be downloaded from the
link: <http://qgroundcontrol.org/downloads>

The Qgroundcontrol application can be started with the script
'qgroundcontrol-start.sh' and with commands

*\$ cd qgroundcontrol*

*\$ cd ./ qgroundcontrol-start.sh*

Code Generation and Compilation
===============================

![](./imgs/image7.png){width="5.786840551181102in"
height="2.7906977252843395in"}

The C code can be generated and complied for the AADL models with
Ocarina. All can be done with the single command is as follows.

*\$ cd ahrs\_discovery*

*\$ make build\_c*

The build\_c rule generates the c-code in folder
/sbc\_32f411ediscovery\_rtos/software. A copy of PolyORB-HI-C runtime is
provided in /sbc\_32f411ediscovery\_rtos/polyorb-hi-c. On successful
compilation, the generated binary- **'software.elf'** is found in
/sbc\_32f411ediscovery\_rtos/software/software.elf.

Alternaively, Its also possible to compile pregenerated sources is as
follows.

*\$ cd ahrs\_discovery*

*\$ cd sbc\_32f411ediscovery\_rtos/software/*

*\$ make all*

Software upload
===============

The generated binary can be uploaded on to the STM32F411e board through
ST-Link using openocd is as follows.

1.  Connect the STM32F4 discovery board to the host machine. Use an USB
    type A to mini-B cable to connect the USB ST-Link interface of
    discovery board with usb port of the host machine.

2.  Make sure the jumpers at 'cn3' ST-LINK is placed

3.  Use th following commands to upload the binary in the discovery
    board

*\$ cd ahrs\_discovery*

*\$ openocd -f stlink-v2.cfg -c \"set WORKAREASIZE 0x2000\" -f
stm32f4discovery.cfg -c \"program
sbc\_32f411ediscovery\_rtos/software/software.elf verify reset exit\"*

![](./imgs/image8.png){width="6.065972222222222in"
height="4.694444444444445in"}A successful loading operation looks as
below.

After uploading the binaries, preliminarily it is expected that the leds
LD3, LD4, LD5, LD6 blinks and LD7 glows as defined at the application.

Demonstration
=============

Hardware setup
--------------

1.  Connect the STM32F4 discovery board to the host machine. Use an USB
    type A to mini-B cable to connect the USB ST-Link interface of
    discovery board with usb port of the host machine. This powers the
    Discovery board.

2.  ![](./imgs/image9.jpeg){width="5.065972222222222in"
    height="3.0909722222222222in"}Establish the Serial link. Use an FTDI
    cable to connect the Discovery board's serial link with the host
    machine. Serial interface configuration of discovery board is as
    below.

  **P1 Port Pin**     **Function**   **Connection**
  ------------------- -------------- ---------------------------------------------
  PA2                 USART2\_TX     Connected to Rx of FTDI cable on host side.
  PA3                 USART2\_RX     Connected to Tx of FTDI cable on host side.
  Baud Rate: 115200

Qgroundcontrol setup
--------------------

The Qgroundcontrol application needs to be configured to receive the
mavlink messages at the serial port.

1.  Start the qgroundcontrol application as mentioned in section 3.5

2.  Go to 'Preferences -\>Comm Links', the 'comm Links Settings' window
    is appears

3.  Add a serial connection. In the the create New link Configuration
    (WIP) window enter the configurations such as name(could be any
    name), type (select serial), serial port(choose the serial port
    connected to discovery board) and BaudRate(115200).

4.  ![](./imgs/image10.png){width="6.05in"
    height="3.301388888888889in"}Enable the serial link with connect
    button.

Demo
----

1.  Set up the hardware as per section 6.1

2.  Upload the generated binaries in the discovery board as per section
    5

3.  Set up the qgroundcontrol application as per section 6.2

4.  Press and release the reset push button on the board. It is expected
    for The leds LD3, LD4,LD5, LD6 to blink and LD7 to glow. This
    represents the application executing on the discovery board. At the
    same time the Qgroundcontrol detects the serial connection and looks
    as below.

    ![](./imgs/image11.png){width="5.328856080489939in"
    height="3.047169728783902in"}

5.  ![](./imgs/image12.png){width="5.160377296587926in"
    height="3.565563210848644in"}To view the mavink messages open the
    Analyze window by 'Widgets -\> Analyze'. The Analyze window displays
    the data received using mavlink messages at the serial interface.
    The typical analyze window with 'rollspeed' 'pitchspeed' and
    'yawspeed' selection is as given below.

This demonstrates the implementation of Attitude Heading References
System on FreeRTOS targets using Ocarina and PolyORB-HI-C middlewares.
