EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 7
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Mechanical:MountingHole H1
U 1 1 5CA46FDA
P 950 6750
F 0 "H1" H 1050 6796 50  0000 L CNN
F 1 "MountingHole" H 1050 6705 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.5mm" H 950 6750 50  0001 C CNN
F 3 "~" H 950 6750 50  0001 C CNN
	1    950  6750
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H2
U 1 1 5CA470F2
P 950 7000
F 0 "H2" H 1050 7046 50  0000 L CNN
F 1 "MountingHole" H 1050 6955 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.5mm" H 950 7000 50  0001 C CNN
F 3 "~" H 950 7000 50  0001 C CNN
	1    950  7000
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H3
U 1 1 5CA4712C
P 950 7250
F 0 "H3" H 1050 7296 50  0000 L CNN
F 1 "MountingHole" H 1050 7205 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.5mm" H 950 7250 50  0001 C CNN
F 3 "~" H 950 7250 50  0001 C CNN
	1    950  7250
	1    0    0    -1  
$EndComp
$Sheet
S -15200 15000 11750 9700
U 618BA1D7
F0 "sheet618BA1D2" 404
F1 "PCIe2_INA226.sch" 50
$EndSheet
Wire Notes Line
	-19300 -750 -19300 36200
Wire Notes Line
	-19300 36200 -750 36200
Wire Notes Line
	-750 -650 -19250 -650
Wire Notes Line
	-19250 -650 -19250 -600
Wire Notes Line
	-750 36200 -750 -650
$Sheet
S -15050 4400 11700 8600
U 618BA1DE
F0 "sheet618BA1D3" 404
F1 "12V_Supp_INA226.sch" 50
$EndSheet
$Sheet
S -15500 25950 11750 8500
U 618BA1E0
F0 "sheet618BA1D4" 404
F1 "PCIe1_INA226.sch" 50
$EndSheet
Text Notes -19200 -900 0    50   ~ 0
INA226
Text Notes -19550 -1000 0    602  ~ 0
INA226 Measurement IC's\n
$Sheet
S 1150 12250 16450 11300
U 618BA1E4
F0 "PCIe_Slots" 405
F1 "PCIe_Slots.sch" 405
$EndSheet
Text Notes 200  -300 0    404  ~ 0
Input / Output\n
Text GLabel 1900 3250 0    50   Input ~ 0
12V
Wire Wire Line
	2050 3250 1900 3250
Text GLabel 4750 1850 2    50   Input ~ 0
3V3_VCC
$Comp
L power:VCC #PWR?
U 1 1 618BA1FD
P 4650 1850
AR Path="/6183E367/618BA1FD" Ref="#PWR?"  Part="1" 
AR Path="/618BA1FD" Ref="#PWR0101"  Part="1" 
F 0 "#PWR0101" H 4650 1700 50  0001 C CNN
F 1 "VCC" H 4665 2023 50  0000 C CNN
F 2 "" H 4650 1850 50  0001 C CNN
F 3 "" H 4650 1850 50  0001 C CNN
	1    4650 1850
	1    0    0    -1  
$EndComp
$Sheet
S 13250 200  9650 8000
U 618FDF23
F0 "STM32 F745" 404
F1 "STM32 F745_VET6.sch" 50
$EndSheet
Wire Wire Line
	3650 4500 3550 4500
Wire Wire Line
	3550 4500 3550 4600
Wire Wire Line
	3550 4700 3650 4700
Wire Wire Line
	3650 4600 3550 4600
Connection ~ 3550 4600
Wire Wire Line
	3550 4600 3550 4700
Wire Wire Line
	3550 4600 3450 4600
Text GLabel 3450 4800 0    50   Input ~ 0
Sense1
Wire Wire Line
	3650 4900 3550 4900
Wire Wire Line
	3550 4900 3550 5000
Wire Wire Line
	3550 5100 3650 5100
Wire Wire Line
	3650 5200 3550 5200
Wire Wire Line
	3550 5200 3550 5100
Connection ~ 3550 5100
Text GLabel 3450 5000 0    50   Input ~ 0
Sense0
Text GLabel 3450 4600 0    50   Input ~ 0
Supp1_12V_OUT
Wire Wire Line
	5700 4500 5600 4500
Wire Wire Line
	5600 4500 5600 4600
Wire Wire Line
	5600 4700 5700 4700
Wire Wire Line
	5700 4600 5600 4600
Connection ~ 5600 4600
Wire Wire Line
	5600 4600 5600 4700
Wire Wire Line
	5600 4600 5500 4600
Wire Wire Line
	5700 4800 5600 4800
Text GLabel 5500 4800 0    50   Input ~ 0
Sense1
Wire Wire Line
	5700 4900 5600 4900
Wire Wire Line
	5600 4900 5600 5000
Wire Wire Line
	5600 5100 5700 5100
Wire Wire Line
	5700 5200 5600 5200
Wire Wire Line
	5600 5200 5600 5100
Connection ~ 5600 5100
Wire Wire Line
	5700 5000 5600 5000
Text GLabel 5500 5000 0    50   Input ~ 0
Sense0
Text GLabel 5500 4600 0    50   Input ~ 0
Supp2_12V_OUT
$Comp
L power:GNDD #PWR0144
U 1 1 61CCC1F3
P 4400 1750
F 0 "#PWR0144" H 4400 1500 50  0001 C CNN
F 1 "GNDD" H 4404 1595 50  0000 C CNN
F 2 "" H 4400 1750 50  0001 C CNN
F 3 "" H 4400 1750 50  0001 C CNN
	1    4400 1750
	-1   0    0    1   
$EndComp
$Comp
L Mechanical:MountingHole H4
U 1 1 61A5C235
P 1850 6750
F 0 "H4" H 1950 6796 50  0000 L CNN
F 1 "MountingHole" H 1950 6705 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.5mm" H 1850 6750 50  0001 C CNN
F 3 "~" H 1850 6750 50  0001 C CNN
	1    1850 6750
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H5
U 1 1 61A5C23B
P 1850 7000
F 0 "H5" H 1950 7046 50  0000 L CNN
F 1 "MountingHole" H 1950 6955 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.5mm" H 1850 7000 50  0001 C CNN
F 3 "~" H 1850 7000 50  0001 C CNN
	1    1850 7000
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H6
U 1 1 61A5C241
P 1850 7250
F 0 "H6" H 1950 7296 50  0000 L CNN
F 1 "MountingHole" H 1950 7205 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.5mm" H 1850 7250 50  0001 C CNN
F 3 "~" H 1850 7250 50  0001 C CNN
	1    1850 7250
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 2500 5650 2500
Wire Wire Line
	5750 2300 5650 2300
Text GLabel 5650 2300 0    50   Input ~ 0
TX+
Text GLabel 5650 2500 0    50   Input ~ 0
TX-
Wire Wire Line
	6550 3000 6650 3000
Text GLabel 6650 3000 2    50   Input ~ 0
RX+
Text GLabel 6550 2800 2    50   Input ~ 0
RX-
Wire Wire Line
	3900 1750 3950 1750
$Comp
L power:GNDA #PWR0106
U 1 1 61C4DBA0
P 4200 1750
F 0 "#PWR0106" H 4200 1500 50  0001 C CNN
F 1 "GNDA" H 4205 1577 50  0000 C CNN
F 2 "" H 4200 1750 50  0001 C CNN
F 3 "" H 4200 1750 50  0001 C CNN
	1    4200 1750
	-1   0    0    1   
$EndComp
Connection ~ 4200 1750
Wire Wire Line
	4200 1750 4400 1750
$Comp
L power:VDD #PWR0112
U 1 1 61C7033B
P 4700 1850
F 0 "#PWR0112" H 4700 1700 50  0001 C CNN
F 1 "VDD" H 4715 2023 50  0000 C CNN
F 2 "" H 4700 1850 50  0001 C CNN
F 3 "" H 4700 1850 50  0001 C CNN
	1    4700 1850
	-1   0    0    1   
$EndComp
$Comp
L power:GNDPWR #PWR0121
U 1 1 61CEEF05
P 1800 3350
F 0 "#PWR0121" H 1800 3150 50  0001 C CNN
F 1 "GNDPWR" H 1805 3195 50  0000 C CNN
F 2 "" H 1800 3300 50  0001 C CNN
F 3 "" H 1800 3300 50  0001 C CNN
	1    1800 3350
	1    0    0    -1  
$EndComp
Text GLabel 2050 3150 0    50   Input ~ 0
3V3_PCIe
$Comp
L power:GNDPWR #PWR0122
U 1 1 61C428E9
P 3350 5100
F 0 "#PWR0122" H 3350 4900 50  0001 C CNN
F 1 "GNDPWR" H 3354 4946 50  0000 C CNN
F 2 "" H 3350 5050 50  0001 C CNN
F 3 "" H 3350 5050 50  0001 C CNN
	1    3350 5100
	1    0    0    -1  
$EndComp
Wire Wire Line
	3350 5100 3550 5100
Wire Wire Line
	5400 5100 5600 5100
$Comp
L power:GNDPWR #PWR0125
U 1 1 61C44592
P 5400 5100
F 0 "#PWR0125" H 5400 4900 50  0001 C CNN
F 1 "GNDPWR" H 5404 4946 50  0000 C CNN
F 2 "" H 5400 5050 50  0001 C CNN
F 3 "" H 5400 5050 50  0001 C CNN
	1    5400 5100
	1    0    0    -1  
$EndComp
Wire Wire Line
	3650 4800 3550 4800
Wire Wire Line
	3650 5000 3550 5000
Connection ~ 3550 5000
Wire Wire Line
	3550 5000 3550 5100
Wire Wire Line
	3550 4900 3550 4800
Connection ~ 3550 4900
Wire Wire Line
	5600 4900 5600 4800
Connection ~ 5600 4900
Connection ~ 5600 5000
Wire Wire Line
	5600 5000 5600 5100
Wire Notes Line
	3450 4800 3550 4800
Wire Notes Line
	3450 5000 3550 5000
Wire Notes Line
	5500 4800 5600 4800
Wire Notes Line
	5600 5000 5500 5000
Wire Wire Line
	6650 2400 6600 2400
Text GLabel 5600 2900 0    50   Input ~ 0
IX_PIN4_PIN5
Wire Wire Line
	5600 2900 5650 2900
$Sheet
S 400  -9100 11450 7150
U 61B3F2E9
F0 "Ethernet / PHY" 404
F1 "Ethernet.sch" 50
$EndSheet
Text GLabel 3900 2250 2    50   Input ~ 0
PCIe1_SCL
Text GLabel 3900 2150 2    50   Input ~ 0
PCIe1_SDA
Text GLabel 3900 2450 2    50   Input ~ 0
PCIe2_SCL
Text GLabel 3900 2350 2    50   Input ~ 0
PCIe2_SDA
Text GLabel 3900 2050 2    50   Input ~ 0
Supp_12V_SCL
Text GLabel 3900 1950 2    50   Input ~ 0
Supp_12V_SDA
$Comp
L Connector:Conn_01x08_Male J1
U 1 1 61FD7FB3
P 3700 2050
F 0 "J1" H 3808 2531 50  0000 C CNN
F 1 "Conn_01x08_Male" H 3808 2440 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x08_P2.54mm_Vertical" H 3700 2050 50  0001 C CNN
F 3 "~" H 3700 2050 50  0001 C CNN
	1    3700 2050
	1    0    0    -1  
$EndComp
Connection ~ 4700 1850
Wire Wire Line
	4700 1850 4750 1850
Connection ~ 4650 1850
Wire Wire Line
	4650 1850 4550 1850
Wire Wire Line
	4700 1850 4650 1850
Wire Wire Line
	4250 -300 4250 700 
Wire Wire Line
	4000 1200 3950 1200
Wire Wire Line
	4400 1200 4300 1200
$Comp
L Device:R R?
U 1 1 620252AB
P 4150 1200
AR Path="/618BA1E4/620252AB" Ref="R?"  Part="1" 
AR Path="/620252AB" Ref="R21"  Part="1" 
F 0 "R21" H 4220 1246 50  0000 L CNN
F 1 "1k" H 4220 1155 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 4080 1200 50  0001 C CNN
F 3 "~" H 4150 1200 50  0001 C CNN
	1    4150 1200
	0    1    1    0   
$EndComp
$Comp
L Device:LED D?
U 1 1 620252B1
P 4550 1200
AR Path="/618BA1E4/620252B1" Ref="D?"  Part="1" 
AR Path="/620252B1" Ref="D7"  Part="1" 
F 0 "D7" V 4589 1280 50  0000 L CNN
F 1 "LED" V 4498 1280 50  0000 L CNN
F 2 "LED_SMD:LED_0805_2012Metric_Castellated" H 4550 1200 50  0001 C CNN
F 3 "~" H 4550 1200 50  0001 C CNN
	1    4550 1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	4550 1850 4550 1300
Wire Wire Line
	4550 1300 4700 1300
Wire Wire Line
	4700 1300 4700 1200
Connection ~ 4550 1850
Wire Wire Line
	4550 1850 3900 1850
Wire Wire Line
	3950 1750 3950 1200
Connection ~ 3950 1750
Wire Wire Line
	3950 1750 4200 1750
$Comp
L PCIe-Power-Measurement-Board_dummy-rescue:430450800-MOLEX_8POL_ATXSUPP J4
U 1 1 62031159
P 3650 4500
F 0 "J4" H 4178 4203 60  0000 L CNN
F 1 "430450800" H 4178 4097 60  0000 L CNN
F 2 "Connector_Molex:Molex_Mini-Fit_Jr_5569-08A2_2x04_P4.20mm_Horizontal" H 4050 4040 60  0001 C CNN
F 3 "" H 3650 4500 60  0000 C CNN
	1    3650 4500
	1    0    0    -1  
$EndComp
$Comp
L PCIe-Power-Measurement-Board_dummy-rescue:430450800-MOLEX_8POL_ATXSUPP J5
U 1 1 620359A2
P 5700 4500
F 0 "J5" H 6228 4203 60  0000 L CNN
F 1 "430450800" H 6228 4097 60  0000 L CNN
F 2 "Connector_Molex:Molex_Mini-Fit_Jr_5569-08A2_2x04_P4.20mm_Horizontal" H 6100 4040 60  0001 C CNN
F 3 "" H 5700 4500 60  0000 C CNN
	1    5700 4500
	1    0    0    -1  
$EndComp
Connection ~ 6600 2400
Wire Wire Line
	6600 2400 6550 2400
Wire Wire Line
	5750 2900 5650 2900
Connection ~ 5650 2900
Wire Wire Line
	1800 3350 2050 3350
$Comp
L PCIe-Power-Measurement-Board_dummy-rescue:IX61G-A-10P-IX61G-A-10P J3
U 1 1 6274DA8D
P 6150 2800
F 0 "J3" H 6150 3667 50  0000 C CNN
F 1 "IX61G-A-10P" H 6150 3576 50  0000 C CNN
F 2 "HRS_IX61G-A-10P" H 6150 2800 50  0001 L BNN
F 3 "" H 6150 2800 50  0001 L BNN
F 4 "Good" H 6150 2800 50  0001 L BNN "AVAILABILITY"
F 5 "IX Series 10 Position A Key Vertical Right Angle Surface Mount Male Plug" H 6150 2800 50  0001 L BNN "DESCRIPTION"
F 6 "Hirose Electric" H 6150 2800 50  0001 L BNN "MF"
F 7 "3.24 USD" H 6150 2800 50  0001 L BNN "PRICE"
F 8 "None" H 6150 2800 50  0001 L BNN "PACKAGE"
F 9 "IX61G-A-10P" H 6150 2800 50  0001 L BNN "MP"
	1    6150 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 3100 5750 3100
Wire Wire Line
	5650 2900 5650 3100
Wire Wire Line
	6600 2200 6550 2200
Wire Wire Line
	6600 2200 6600 2400
$Comp
L Connector_Generic:Conn_01x03 J6
U 1 1 626ABEA4
P 2250 3250
F 0 "J6" H 2330 3292 50  0000 L CNN
F 1 "MR60PW-M" H 2330 3201 50  0000 L CNN
F 2 "XT60PW-M_horizontal:AMASS_MR60PW-M" H 2250 3250 50  0001 C CNN
F 3 "~" H 2250 3250 50  0001 C CNN
	1    2250 3250
	1    0    0    -1  
$EndComp
$Comp
L PCIe-Power-Measurement-Board_dummy-rescue:IX60G-B-10P-IX60G-B-10P J2
U 1 1 6282818B
P 7800 2600
F 0 "J2" H 7800 3167 50  0000 C CNN
F 1 "IX60G-B-10P" H 7800 3076 50  0000 C CNN
F 2 "HIROSE_IX60G-B-10P" H 7800 2600 50  0001 L BNN
F 3 "" H 7800 2600 50  0001 L BNN
F 4 "6.1 mm" H 7800 2600 50  0001 L BNN "MAXIMUM_PACKAGE_HEIGHT"
F 5 "Hirose" H 7800 2600 50  0001 L BNN "MF"
F 6 "20200430" H 7800 2600 50  0001 L BNN "PARTREV"
F 7 "Manufacturer Recommendations" H 7800 2600 50  0001 L BNN "STANDARD"
	1    7800 2600
	1    0    0    -1  
$EndComp
$Comp
L Device:Jumper JP20
U 1 1 62B22478
P 1950 900
F 0 "JP20" H 1950 1164 50  0000 C CNN
F 1 "Jumper" H 1950 1073 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x02_P2.54mm_Vertical" H 1950 900 50  0001 C CNN
F 3 "~" H 1950 900 50  0001 C CNN
	1    1950 900 
	1    0    0    -1  
$EndComp
Text GLabel 1650 900  0    50   Input ~ 0
Supp_12V_SDA
$Comp
L Device:Jumper JP24
U 1 1 62B2F584
P 1950 1300
F 0 "JP24" H 1950 1564 50  0000 C CNN
F 1 "Jumper" H 1950 1473 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x02_P2.54mm_Vertical" H 1950 1300 50  0001 C CNN
F 3 "~" H 1950 1300 50  0001 C CNN
	1    1950 1300
	1    0    0    -1  
$EndComp
Text GLabel 2250 1300 2    50   Input ~ 0
PCIe2_SDA
Text GLabel 1650 1300 0    50   Input ~ 0
Supp_12V_SDA
Text GLabel 2250 900  2    50   Input ~ 0
PCIe1_SDA
$Comp
L Device:Jumper JP28
U 1 1 62B3F417
P 1950 1700
F 0 "JP28" H 1950 1964 50  0000 C CNN
F 1 "Jumper" H 1950 1873 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x02_P2.54mm_Vertical" H 1950 1700 50  0001 C CNN
F 3 "~" H 1950 1700 50  0001 C CNN
	1    1950 1700
	1    0    0    -1  
$EndComp
Text GLabel 1650 1700 0    50   Input ~ 0
Supp_12V_SCL
$Comp
L Device:Jumper JP32
U 1 1 62B3F420
P 1950 2100
F 0 "JP32" H 1950 2364 50  0000 C CNN
F 1 "Jumper" H 1950 2273 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x02_P2.54mm_Vertical" H 1950 2100 50  0001 C CNN
F 3 "~" H 1950 2100 50  0001 C CNN
	1    1950 2100
	1    0    0    -1  
$EndComp
Text GLabel 2250 2100 2    50   Input ~ 0
PCIe2_SCL
Text GLabel 1650 2100 0    50   Input ~ 0
Supp_12V_SCL
Text GLabel 2250 1700 2    50   Input ~ 0
PCIe1_SCL
$Comp
L Device:Jumper JP36
U 1 1 62B4C2DA
P 1950 2500
F 0 "JP36" H 1950 2764 50  0000 C CNN
F 1 "Jumper" H 1950 2673 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x02_P2.54mm_Vertical" H 1950 2500 50  0001 C CNN
F 3 "~" H 1950 2500 50  0001 C CNN
	1    1950 2500
	1    0    0    -1  
$EndComp
Text GLabel 1650 2500 0    50   Input ~ 0
PCIe2_SCL
$Comp
L Device:Jumper JP40
U 1 1 62B4C2E1
P 1950 2900
F 0 "JP40" H 1950 3164 50  0000 C CNN
F 1 "Jumper" H 1950 3073 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x02_P2.54mm_Vertical" H 1950 2900 50  0001 C CNN
F 3 "~" H 1950 2900 50  0001 C CNN
	1    1950 2900
	1    0    0    -1  
$EndComp
Text GLabel 2250 2900 2    50   Input ~ 0
PCIe2_SDA
Text GLabel 1650 2900 0    50   Input ~ 0
PCIe1_SDA
Text GLabel 2250 2500 2    50   Input ~ 0
PCIe1_SCL
$EndSCHEMATC
