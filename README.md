# NAA-Measurement-Carrier-System
This project includes the hardware and software solution of a carrier system for network attached accelerators (NAA). It is intended to be placed in a server rack and replace the common CPU-based carrier systems for hardware accelerators. It was developed as part of a master thesis at the Fraunhofer Institute HHI in the ESG group.


## Overview
This project focuses on making the use of NAAs more energy efficient and to measure their application-specific power consumption during operation. For this purpose, a system was designed and realized which consists of several PCBs and the implementation of microcontroller software. The complete project is explained in detail in the written version of the [master thesis](Doku/MasterThesis_NAA_Mess_TrägerSystem_PaulMamatis.pdf)
.
![Overview](Doku/images/Gesamt_uebersicht_english.svg)




## Code
The code section contains all the C code for the microcontroller including third party libraries, the code I wrote is [here](Code/C/source). The Python code was written to evaluate the measurement system and its deviation. The bash scripts are implemented for a remote access to the system over network. 

## PCB
Contains the KiCad files for the PCB designs of the carrier module.

## Use
This repository is for application purposes and represents my latest work. 
