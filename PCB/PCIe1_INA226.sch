EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 7
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
L Device:R_Shunt R?
U 1 1 618700B8
P 2050 1300
AR Path="/618700B8" Ref="R?"  Part="1" 
AR Path="/6183E367/618700B8" Ref="R?"  Part="1" 
AR Path="/6183E367/61863742/618700B8" Ref="R8"  Part="1" 
AR Path="/618BA1E0/618700B8" Ref="R10"  Part="1" 
F 0 "R10" V 1825 1300 50  0000 C CNN
F 1 "10mR" V 1916 1300 50  0000 C CNN
F 2 "Resistor_SMD:R_Shunt_Vishay_WSK2512_6332Metric_T2.66mm" V 1980 1300 50  0001 C CNN
F 3 "~" H 2050 1300 50  0001 C CNN
	1    2050 1300
	0    1    1    0   
$EndComp
$Comp
L Device:R_Shunt R?
U 1 1 618700BE
P 2050 2900
AR Path="/618700BE" Ref="R?"  Part="1" 
AR Path="/6183E367/618700BE" Ref="R?"  Part="1" 
AR Path="/6183E367/61863742/618700BE" Ref="R9"  Part="1" 
AR Path="/618BA1E0/618700BE" Ref="R11"  Part="1" 
F 0 "R11" V 1825 2900 50  0000 C CNN
F 1 "25mR" V 1916 2900 50  0000 C CNN
F 2 "Resistor_SMD:R_Shunt_Vishay_WSK2512_6332Metric_T2.66mm" V 1980 2900 50  0001 C CNN
F 3 "~" H 2050 2900 50  0001 C CNN
	1    2050 2900
	0    1    1    0   
$EndComp
$Comp
L Device:R_Shunt R?
U 1 1 618700C4
P 2050 4550
AR Path="/618700C4" Ref="R?"  Part="1" 
AR Path="/6183E367/618700C4" Ref="R?"  Part="1" 
AR Path="/6183E367/61863742/618700C4" Ref="R10"  Part="1" 
AR Path="/618BA1E0/618700C4" Ref="R12"  Part="1" 
F 0 "R12" V 1825 4550 50  0000 C CNN
F 1 "25mR" V 1916 4550 50  0000 C CNN
F 2 "Resistor_SMD:R_Shunt_Vishay_WSK2512_6332Metric_T2.66mm" V 1980 4550 50  0001 C CNN
F 3 "~" H 2050 4550 50  0001 C CNN
	1    2050 4550
	0    1    1    0   
$EndComp
$Comp
L m_pex_sensor-rescue:INA226-Analog_ADC U?
U 1 1 618700CA
P 3850 1400
AR Path="/618700CA" Ref="U?"  Part="1" 
AR Path="/6183E367/618700CA" Ref="U?"  Part="1" 
AR Path="/6183E367/61863742/618700CA" Ref="U6"  Part="1" 
AR Path="/618BA1E0/618700CA" Ref="U6"  Part="1" 
F 0 "U6" H 3600 1950 50  0000 C CNN
F 1 "INA226" H 3600 1850 50  0000 C CNN
F 2 "Package_SO:MSOP-10_3x3mm_P0.5mm" H 3900 1500 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/ina226.pdf" H 4200 1300 50  0001 C CNN
	1    3850 1400
	1    0    0    -1  
$EndComp
$Comp
L m_pex_sensor-rescue:INA226-Analog_ADC U?
U 1 1 618700D0
P 3850 3050
AR Path="/618700D0" Ref="U?"  Part="1" 
AR Path="/6183E367/618700D0" Ref="U?"  Part="1" 
AR Path="/6183E367/61863742/618700D0" Ref="U7"  Part="1" 
AR Path="/618BA1E0/618700D0" Ref="U7"  Part="1" 
F 0 "U7" H 3600 3600 50  0000 C CNN
F 1 "INA226" H 3600 3500 50  0000 C CNN
F 2 "Package_SO:MSOP-10_3x3mm_P0.5mm" H 3900 3150 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/ina226.pdf" H 4200 2950 50  0001 C CNN
	1    3850 3050
	1    0    0    -1  
$EndComp
$Comp
L m_pex_sensor-rescue:INA226-Analog_ADC U?
U 1 1 618700D6
P 3850 4700
AR Path="/618700D6" Ref="U?"  Part="1" 
AR Path="/6183E367/618700D6" Ref="U?"  Part="1" 
AR Path="/6183E367/61863742/618700D6" Ref="U8"  Part="1" 
AR Path="/618BA1E0/618700D6" Ref="U8"  Part="1" 
F 0 "U8" H 3600 5250 50  0000 C CNN
F 1 "INA226" H 3600 5150 50  0000 C CNN
F 2 "Package_SO:MSOP-10_3x3mm_P0.5mm" H 3900 4800 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/ina226.pdf" H 4200 4600 50  0001 C CNN
	1    3850 4700
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR?
U 1 1 618700E2
P 3850 800
AR Path="/618700E2" Ref="#PWR?"  Part="1" 
AR Path="/6183E367/618700E2" Ref="#PWR?"  Part="1" 
AR Path="/6183E367/61863742/618700E2" Ref="#PWR0131"  Part="1" 
AR Path="/618BA1E0/618700E2" Ref="#PWR0131"  Part="1" 
F 0 "#PWR0131" H 3850 650 50  0001 C CNN
F 1 "VCC" H 3867 973 50  0000 C CNN
F 2 "" H 3850 800 50  0001 C CNN
F 3 "" H 3850 800 50  0001 C CNN
	1    3850 800 
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 618700E8
P 4150 850
AR Path="/618700E8" Ref="C?"  Part="1" 
AR Path="/6183E367/618700E8" Ref="C?"  Part="1" 
AR Path="/6183E367/61863742/618700E8" Ref="C6"  Part="1" 
AR Path="/618BA1E0/618700E8" Ref="C6"  Part="1" 
F 0 "C6" V 3898 850 50  0000 C CNN
F 1 "100nF" V 3989 850 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4188 700 50  0001 C CNN
F 3 "~" H 4150 850 50  0001 C CNN
	1    4150 850 
	0    1    1    0   
$EndComp
$Comp
L Device:C C?
U 1 1 618700EE
P 4150 2500
AR Path="/618700EE" Ref="C?"  Part="1" 
AR Path="/6183E367/618700EE" Ref="C?"  Part="1" 
AR Path="/6183E367/61863742/618700EE" Ref="C7"  Part="1" 
AR Path="/618BA1E0/618700EE" Ref="C7"  Part="1" 
F 0 "C7" V 3898 2500 50  0000 C CNN
F 1 "100nF" V 3989 2500 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4188 2350 50  0001 C CNN
F 3 "~" H 4150 2500 50  0001 C CNN
	1    4150 2500
	0    1    1    0   
$EndComp
$Comp
L Device:C C?
U 1 1 618700F4
P 4150 4150
AR Path="/618700F4" Ref="C?"  Part="1" 
AR Path="/6183E367/618700F4" Ref="C?"  Part="1" 
AR Path="/6183E367/61863742/618700F4" Ref="C8"  Part="1" 
AR Path="/618BA1E0/618700F4" Ref="C8"  Part="1" 
F 0 "C8" V 3898 4150 50  0000 C CNN
F 1 "100nF" V 3989 4150 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4188 4000 50  0001 C CNN
F 3 "~" H 4150 4150 50  0001 C CNN
	1    4150 4150
	0    1    1    0   
$EndComp
$Comp
L power:VCC #PWR?
U 1 1 618700FA
P 5900 1400
AR Path="/618700FA" Ref="#PWR?"  Part="1" 
AR Path="/6183E367/618700FA" Ref="#PWR?"  Part="1" 
AR Path="/6183E367/61863742/618700FA" Ref="#PWR0132"  Part="1" 
AR Path="/618BA1E0/618700FA" Ref="#PWR0132"  Part="1" 
F 0 "#PWR0132" H 5900 1250 50  0001 C CNN
F 1 "VCC" H 5917 1573 50  0000 C CNN
F 2 "" H 5900 1400 50  0001 C CNN
F 3 "" H 5900 1400 50  0001 C CNN
	1    5900 1400
	1    0    0    -1  
$EndComp
Connection ~ 5900 1400
$Comp
L power:GNDA #PWR?
U 1 1 61870102
P 3850 1950
AR Path="/61870102" Ref="#PWR?"  Part="1" 
AR Path="/6183E367/61870102" Ref="#PWR?"  Part="1" 
AR Path="/6183E367/61863742/61870102" Ref="#PWR0133"  Part="1" 
AR Path="/618BA1E0/61870102" Ref="#PWR0133"  Part="1" 
F 0 "#PWR0133" H 3850 1700 50  0001 C CNN
F 1 "GNDA" H 3854 1795 50  0000 C CNN
F 2 "" H 3850 1950 50  0001 C CNN
F 3 "" H 3850 1950 50  0001 C CNN
	1    3850 1950
	1    0    0    -1  
$EndComp
$Comp
L power:GNDA #PWR?
U 1 1 61870108
P 3850 3600
AR Path="/61870108" Ref="#PWR?"  Part="1" 
AR Path="/6183E367/61870108" Ref="#PWR?"  Part="1" 
AR Path="/6183E367/61863742/61870108" Ref="#PWR0134"  Part="1" 
AR Path="/618BA1E0/61870108" Ref="#PWR0134"  Part="1" 
F 0 "#PWR0134" H 3850 3350 50  0001 C CNN
F 1 "GNDA" H 3854 3445 50  0000 C CNN
F 2 "" H 3850 3600 50  0001 C CNN
F 3 "" H 3850 3600 50  0001 C CNN
	1    3850 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	3850 800  3850 850 
Wire Wire Line
	4000 850  3850 850 
Connection ~ 3850 850 
Wire Wire Line
	3850 850  3850 900 
Wire Wire Line
	3850 1900 3850 1950
$Comp
L power:GNDA #PWR?
U 1 1 61870113
P 4400 850
AR Path="/61870113" Ref="#PWR?"  Part="1" 
AR Path="/6183E367/61870113" Ref="#PWR?"  Part="1" 
AR Path="/6183E367/61863742/61870113" Ref="#PWR0135"  Part="1" 
AR Path="/618BA1E0/61870113" Ref="#PWR0135"  Part="1" 
F 0 "#PWR0135" H 4400 600 50  0001 C CNN
F 1 "GNDA" H 4404 695 50  0000 C CNN
F 2 "" H 4400 850 50  0001 C CNN
F 3 "" H 4400 850 50  0001 C CNN
	1    4400 850 
	0    -1   -1   0   
$EndComp
$Comp
L power:VCC #PWR?
U 1 1 6187011A
P 3850 2450
AR Path="/6187011A" Ref="#PWR?"  Part="1" 
AR Path="/6183E367/6187011A" Ref="#PWR?"  Part="1" 
AR Path="/6183E367/61863742/6187011A" Ref="#PWR0136"  Part="1" 
AR Path="/618BA1E0/6187011A" Ref="#PWR0136"  Part="1" 
F 0 "#PWR0136" H 3850 2300 50  0001 C CNN
F 1 "VCC" H 3867 2623 50  0000 C CNN
F 2 "" H 3850 2450 50  0001 C CNN
F 3 "" H 3850 2450 50  0001 C CNN
	1    3850 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	3850 2450 3850 2500
Wire Wire Line
	4000 2500 3850 2500
Connection ~ 3850 2500
Wire Wire Line
	3850 2500 3850 2550
$Comp
L power:GNDA #PWR?
U 1 1 61870124
P 4400 2500
AR Path="/61870124" Ref="#PWR?"  Part="1" 
AR Path="/6183E367/61870124" Ref="#PWR?"  Part="1" 
AR Path="/6183E367/61863742/61870124" Ref="#PWR0137"  Part="1" 
AR Path="/618BA1E0/61870124" Ref="#PWR0137"  Part="1" 
F 0 "#PWR0137" H 4400 2250 50  0001 C CNN
F 1 "GNDA" H 4404 2345 50  0000 C CNN
F 2 "" H 4400 2500 50  0001 C CNN
F 3 "" H 4400 2500 50  0001 C CNN
	1    4400 2500
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4300 2500 4400 2500
Wire Wire Line
	3850 3550 3850 3600
$Comp
L power:VCC #PWR?
U 1 1 6187012C
P 3850 4100
AR Path="/6187012C" Ref="#PWR?"  Part="1" 
AR Path="/6183E367/6187012C" Ref="#PWR?"  Part="1" 
AR Path="/6183E367/61863742/6187012C" Ref="#PWR0138"  Part="1" 
AR Path="/618BA1E0/6187012C" Ref="#PWR0138"  Part="1" 
F 0 "#PWR0138" H 3850 3950 50  0001 C CNN
F 1 "VCC" H 3867 4273 50  0000 C CNN
F 2 "" H 3850 4100 50  0001 C CNN
F 3 "" H 3850 4100 50  0001 C CNN
	1    3850 4100
	1    0    0    -1  
$EndComp
$Comp
L power:GNDA #PWR?
U 1 1 61870132
P 4400 4150
AR Path="/61870132" Ref="#PWR?"  Part="1" 
AR Path="/6183E367/61870132" Ref="#PWR?"  Part="1" 
AR Path="/6183E367/61863742/61870132" Ref="#PWR0139"  Part="1" 
AR Path="/618BA1E0/61870132" Ref="#PWR0139"  Part="1" 
F 0 "#PWR0139" H 4400 3900 50  0001 C CNN
F 1 "GNDA" H 4404 3995 50  0000 C CNN
F 2 "" H 4400 4150 50  0001 C CNN
F 3 "" H 4400 4150 50  0001 C CNN
	1    4400 4150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3850 4100 3850 4150
Wire Wire Line
	4000 4150 3850 4150
Connection ~ 3850 4150
Wire Wire Line
	3850 4150 3850 4200
Wire Wire Line
	4300 4150 4400 4150
$Comp
L power:GNDA #PWR?
U 1 1 6187013D
P 3850 5250
AR Path="/6187013D" Ref="#PWR?"  Part="1" 
AR Path="/6183E367/6187013D" Ref="#PWR?"  Part="1" 
AR Path="/6183E367/61863742/6187013D" Ref="#PWR0140"  Part="1" 
AR Path="/618BA1E0/6187013D" Ref="#PWR0140"  Part="1" 
F 0 "#PWR0140" H 3850 5000 50  0001 C CNN
F 1 "GNDA" H 3854 5095 50  0000 C CNN
F 2 "" H 3850 5250 50  0001 C CNN
F 3 "" H 3850 5250 50  0001 C CNN
	1    3850 5250
	1    0    0    -1  
$EndComp
Wire Wire Line
	3850 5200 3850 5250
Wire Wire Line
	3450 1500 2150 1500
Wire Wire Line
	2150 1500 2150 1450
Wire Wire Line
	1950 1600 1950 1450
Wire Wire Line
	3450 1100 3350 1100
Wire Wire Line
	4250 1500 4700 1500
Wire Wire Line
	4800 1400 4250 1400
Wire Wire Line
	4800 4700 4250 4700
Wire Wire Line
	4700 4800 4250 4800
Wire Wire Line
	3450 3150 2150 3150
Wire Wire Line
	2150 3150 2150 3050
Wire Wire Line
	1950 3250 1950 3050
Wire Wire Line
	3450 2750 3350 2750
Wire Wire Line
	3450 4800 2150 4800
Wire Wire Line
	2150 4800 2150 4700
Wire Wire Line
	1950 4900 1950 4700
Wire Wire Line
	3450 4400 3350 4400
Text Notes 2000 1750 0    50   ~ 0
12V
Text Notes 2000 3400 0    50   ~ 0
3.3A (aux)
Text Notes 2000 5050 0    50   ~ 0
3.3V
Wire Wire Line
	4250 3050 4800 3050
Wire Wire Line
	4250 3150 4700 3150
Connection ~ 4700 3150
Wire Wire Line
	4700 3150 4700 4800
Wire Wire Line
	2250 1300 2350 1300
Wire Wire Line
	2350 1300 2350 1000
Wire Wire Line
	2350 1000 1400 1000
Wire Wire Line
	1850 1300 1750 1300
Wire Wire Line
	1750 1300 1750 1100
Wire Wire Line
	1750 1100 1400 1100
Wire Wire Line
	2250 2900 2350 2900
Wire Wire Line
	2350 2900 2350 2600
Wire Wire Line
	1850 2900 1750 2900
Wire Wire Line
	2250 4550 2350 4550
Wire Wire Line
	2350 4550 2350 4250
Wire Wire Line
	2350 4250 1400 4250
Wire Wire Line
	1850 4550 1750 4550
Wire Wire Line
	1750 4550 1750 4350
Wire Wire Line
	1750 4350 1400 4350
Wire Wire Line
	1950 1600 3450 1600
Wire Wire Line
	3350 1100 3350 900 
Wire Wire Line
	3350 900  1750 900 
Wire Wire Line
	1750 900  1750 1100
Connection ~ 1750 1100
Wire Wire Line
	3350 2750 3350 2500
Wire Wire Line
	3350 2500 1750 2500
Wire Wire Line
	3350 4400 3350 4150
Wire Wire Line
	3350 4150 1750 4150
Wire Wire Line
	1750 4150 1750 4350
Connection ~ 1750 4350
Wire Wire Line
	1950 3250 3450 3250
Wire Wire Line
	1950 4900 3450 4900
Text Label 4500 1500 0    50   ~ 0
SCL
Text Label 4500 1400 0    50   ~ 0
SDA
Text Label 4500 3050 0    50   ~ 0
SDA
Text Label 4500 4700 0    50   ~ 0
SDA
Wire Wire Line
	5900 1900 5900 1400
Connection ~ 4800 3050
Wire Wire Line
	4800 3050 4800 4700
Wire Wire Line
	4700 1500 4700 1700
Wire Wire Line
	4800 1400 4800 1500
Connection ~ 4800 1500
Wire Wire Line
	4800 1500 4800 3050
Wire Wire Line
	4800 1500 5100 1500
Connection ~ 4700 1700
Wire Wire Line
	4700 1700 4700 3150
$Comp
L Device:R R?
U 1 1 618701F1
P 5100 1650
AR Path="/618701F1" Ref="R?"  Part="1" 
AR Path="/6183E367/618701F1" Ref="R?"  Part="1" 
AR Path="/6183E367/61863742/618701F1" Ref="R11"  Part="1" 
AR Path="/618BA1E0/618701F1" Ref="R13"  Part="1" 
F 0 "R13" H 5170 1696 50  0000 L CNN
F 1 "4.7k" H 5170 1605 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 5030 1650 50  0001 C CNN
F 3 "~" H 5100 1650 50  0001 C CNN
	1    5100 1650
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 618701F7
P 5450 1550
AR Path="/618701F7" Ref="R?"  Part="1" 
AR Path="/6183E367/618701F7" Ref="R?"  Part="1" 
AR Path="/6183E367/61863742/618701F7" Ref="R12"  Part="1" 
AR Path="/618BA1E0/618701F7" Ref="R14"  Part="1" 
F 0 "R14" H 5520 1596 50  0000 L CNN
F 1 "4.7k" H 5520 1505 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 5380 1550 50  0001 C CNN
F 3 "~" H 5450 1550 50  0001 C CNN
	1    5450 1550
	1    0    0    -1  
$EndComp
Connection ~ 5100 1500
Wire Wire Line
	5450 1700 4700 1700
Wire Wire Line
	5100 1900 5100 1800
Wire Wire Line
	5100 1500 6500 1500
Wire Wire Line
	5450 1400 5900 1400
Text GLabel 1400 1000 0    50   Input ~ 0
PCIe1_12V_OUT
Wire Wire Line
	1750 2500 1750 2700
Wire Wire Line
	1750 2900 1750 2700
Connection ~ 1750 2700
Wire Wire Line
	1750 2700 1400 2700
Wire Wire Line
	2350 2600 1400 2600
Text GLabel 1400 2600 0    50   Input ~ 0
PCIe1_3AUX_OUT
Text GLabel 1400 4250 0    50   Input ~ 0
PCIe1_3V3_OUT
Wire Wire Line
	5100 1900 5900 1900
Wire Wire Line
	5450 1700 6500 1700
Text GLabel 6500 1500 2    50   Input ~ 0
PCIe1_SDA
Text GLabel 6500 1700 2    50   Input ~ 0
PCIe1_SCL
Text GLabel 1400 4350 0    50   Input ~ 0
3V3_PCIe
Text GLabel 1400 2700 0    50   Input ~ 0
3V3_PCIe
Text GLabel 1400 1100 0    50   Input ~ 0
12V
$Comp
L Jumper:SolderJumper_2_Open JP?
U 1 1 62C67220
P 10150 1050
AR Path="/618BA1D7/62C67220" Ref="JP?"  Part="1" 
AR Path="/618BA1E0/62C67220" Ref="JP53"  Part="1" 
F 0 "JP53" H 10150 1255 50  0000 C CNN
F 1 "SolderJumper_2_Open" H 10150 1164 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_RoundedPad1.0x1.5mm" H 10150 1050 50  0001 C CNN
F 3 "~" H 10150 1050 50  0001 C CNN
	1    10150 1050
	1    0    0    -1  
$EndComp
$Comp
L Jumper:SolderJumper_2_Open JP?
U 1 1 62C67226
P 10150 1400
AR Path="/618BA1D7/62C67226" Ref="JP?"  Part="1" 
AR Path="/618BA1E0/62C67226" Ref="JP54"  Part="1" 
F 0 "JP54" H 10150 1605 50  0000 C CNN
F 1 "SolderJumper_2_Open" H 10150 1514 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_RoundedPad1.0x1.5mm" H 10150 1400 50  0001 C CNN
F 3 "~" H 10150 1400 50  0001 C CNN
	1    10150 1400
	1    0    0    -1  
$EndComp
$Comp
L Jumper:SolderJumper_2_Open JP?
U 1 1 62C6722C
P 10150 1750
AR Path="/618BA1D7/62C6722C" Ref="JP?"  Part="1" 
AR Path="/618BA1E0/62C6722C" Ref="JP55"  Part="1" 
F 0 "JP55" H 10150 1955 50  0000 C CNN
F 1 "SolderJumper_2_Open" H 10150 1864 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_RoundedPad1.0x1.5mm" H 10150 1750 50  0001 C CNN
F 3 "~" H 10150 1750 50  0001 C CNN
	1    10150 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	10000 1400 10000 1750
Wire Wire Line
	10000 1050 10000 1200
Connection ~ 10000 1400
Connection ~ 10000 1200
Wire Wire Line
	10000 1200 10000 1400
$Comp
L power:GNDA #PWR?
U 1 1 62C67237
P 10300 1050
AR Path="/62C67237" Ref="#PWR?"  Part="1" 
AR Path="/6183E367/62C67237" Ref="#PWR?"  Part="1" 
AR Path="/6183E367/618A2E14/62C67237" Ref="#PWR?"  Part="1" 
AR Path="/618BA1DE/62C67237" Ref="#PWR?"  Part="1" 
AR Path="/618BA1D7/62C67237" Ref="#PWR?"  Part="1" 
AR Path="/618BA1E0/62C67237" Ref="#PWR0127"  Part="1" 
F 0 "#PWR0127" H 10300 800 50  0001 C CNN
F 1 "GNDA" H 10304 895 50  0000 C CNN
F 2 "" H 10300 1050 50  0001 C CNN
F 3 "" H 10300 1050 50  0001 C CNN
	1    10300 1050
	0    -1   -1   0   
$EndComp
$Comp
L power:VCC #PWR?
U 1 1 62C6723D
P 10350 1400
AR Path="/62C6723D" Ref="#PWR?"  Part="1" 
AR Path="/6183E367/62C6723D" Ref="#PWR?"  Part="1" 
AR Path="/6183E367/618A2E14/62C6723D" Ref="#PWR?"  Part="1" 
AR Path="/618BA1DE/62C6723D" Ref="#PWR?"  Part="1" 
AR Path="/618BA1D7/62C6723D" Ref="#PWR?"  Part="1" 
AR Path="/618BA1E0/62C6723D" Ref="#PWR0128"  Part="1" 
F 0 "#PWR0128" H 10350 1250 50  0001 C CNN
F 1 "VCC" H 10367 1573 50  0000 C CNN
F 2 "" H 10350 1400 50  0001 C CNN
F 3 "" H 10350 1400 50  0001 C CNN
	1    10350 1400
	0    1    1    0   
$EndComp
Wire Wire Line
	10350 1400 10300 1400
$Comp
L Jumper:SolderJumper_2_Open JP?
U 1 1 62C67244
P 9000 1600
AR Path="/618BA1D7/62C67244" Ref="JP?"  Part="1" 
AR Path="/618BA1E0/62C67244" Ref="JP47"  Part="1" 
F 0 "JP47" H 9000 1805 50  0000 C CNN
F 1 "SolderJumper_2_Open" H 9000 1714 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_RoundedPad1.0x1.5mm" H 9000 1600 50  0001 C CNN
F 3 "~" H 9000 1600 50  0001 C CNN
	1    9000 1600
	1    0    0    -1  
$EndComp
$Comp
L Jumper:SolderJumper_2_Open JP?
U 1 1 62C6724A
P 9000 1950
AR Path="/618BA1D7/62C6724A" Ref="JP?"  Part="1" 
AR Path="/618BA1E0/62C6724A" Ref="JP48"  Part="1" 
F 0 "JP48" H 9000 2155 50  0000 C CNN
F 1 "SolderJumper_2_Open" H 9000 2064 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_RoundedPad1.0x1.5mm" H 9000 1950 50  0001 C CNN
F 3 "~" H 9000 1950 50  0001 C CNN
	1    9000 1950
	1    0    0    -1  
$EndComp
$Comp
L Jumper:SolderJumper_2_Open JP?
U 1 1 62C67250
P 9000 2300
AR Path="/618BA1D7/62C67250" Ref="JP?"  Part="1" 
AR Path="/618BA1E0/62C67250" Ref="JP49"  Part="1" 
F 0 "JP49" H 9000 2505 50  0000 C CNN
F 1 "SolderJumper_2_Open" H 9000 2414 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_RoundedPad1.0x1.5mm" H 9000 2300 50  0001 C CNN
F 3 "~" H 9000 2300 50  0001 C CNN
	1    9000 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	8850 1950 8850 2300
Connection ~ 8850 1950
$Comp
L power:GNDA #PWR?
U 1 1 62C67258
P 9150 1600
AR Path="/62C67258" Ref="#PWR?"  Part="1" 
AR Path="/6183E367/62C67258" Ref="#PWR?"  Part="1" 
AR Path="/6183E367/618A2E14/62C67258" Ref="#PWR?"  Part="1" 
AR Path="/618BA1DE/62C67258" Ref="#PWR?"  Part="1" 
AR Path="/618BA1D7/62C67258" Ref="#PWR?"  Part="1" 
AR Path="/618BA1E0/62C67258" Ref="#PWR0130"  Part="1" 
F 0 "#PWR0130" H 9150 1350 50  0001 C CNN
F 1 "GNDA" H 9154 1445 50  0000 C CNN
F 2 "" H 9150 1600 50  0001 C CNN
F 3 "" H 9150 1600 50  0001 C CNN
	1    9150 1600
	0    -1   -1   0   
$EndComp
$Comp
L power:VCC #PWR?
U 1 1 62C6725E
P 9200 1950
AR Path="/62C6725E" Ref="#PWR?"  Part="1" 
AR Path="/6183E367/62C6725E" Ref="#PWR?"  Part="1" 
AR Path="/6183E367/618A2E14/62C6725E" Ref="#PWR?"  Part="1" 
AR Path="/618BA1DE/62C6725E" Ref="#PWR?"  Part="1" 
AR Path="/618BA1D7/62C6725E" Ref="#PWR?"  Part="1" 
AR Path="/618BA1E0/62C6725E" Ref="#PWR0142"  Part="1" 
F 0 "#PWR0142" H 9200 1800 50  0001 C CNN
F 1 "VCC" H 9217 2123 50  0000 C CNN
F 2 "" H 9200 1950 50  0001 C CNN
F 3 "" H 9200 1950 50  0001 C CNN
	1    9200 1950
	0    1    1    0   
$EndComp
Wire Wire Line
	9200 1950 9150 1950
Wire Wire Line
	8850 1600 8850 1950
Wire Wire Line
	8500 1300 8500 1950
Wire Wire Line
	8500 1950 8850 1950
Wire Notes Line
	11100 700  11100 2900
Wire Notes Line
	11100 2900 8350 2900
Wire Notes Line
	8350 2900 8350 700 
Wire Notes Line
	8350 700  11100 700 
Text Notes 8350 700  0    50   ~ 0
I2C Address Selection\n
Text Label 8450 1200 0    50   ~ 0
A1_pcie1_12V
Text Label 8450 1300 0    50   ~ 0
A0_pcie1_12V
Wire Wire Line
	6600 1200 10000 1200
$Comp
L Jumper:SolderJumper_2_Open JP?
U 1 1 62C67270
P 10150 3600
AR Path="/618BA1D7/62C67270" Ref="JP?"  Part="1" 
AR Path="/618BA1E0/62C67270" Ref="JP56"  Part="1" 
F 0 "JP56" H 10150 3805 50  0000 C CNN
F 1 "SolderJumper_2_Open" H 10150 3714 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_RoundedPad1.0x1.5mm" H 10150 3600 50  0001 C CNN
F 3 "~" H 10150 3600 50  0001 C CNN
	1    10150 3600
	1    0    0    -1  
$EndComp
$Comp
L Jumper:SolderJumper_2_Open JP?
U 1 1 62C67276
P 10150 3950
AR Path="/618BA1D7/62C67276" Ref="JP?"  Part="1" 
AR Path="/618BA1E0/62C67276" Ref="JP57"  Part="1" 
F 0 "JP57" H 10150 4155 50  0000 C CNN
F 1 "SolderJumper_2_Open" H 10150 4064 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_RoundedPad1.0x1.5mm" H 10150 3950 50  0001 C CNN
F 3 "~" H 10150 3950 50  0001 C CNN
	1    10150 3950
	1    0    0    -1  
$EndComp
$Comp
L Jumper:SolderJumper_2_Open JP?
U 1 1 62C6727C
P 10150 4300
AR Path="/618BA1D7/62C6727C" Ref="JP?"  Part="1" 
AR Path="/618BA1E0/62C6727C" Ref="JP58"  Part="1" 
F 0 "JP58" H 10150 4505 50  0000 C CNN
F 1 "SolderJumper_2_Open" H 10150 4414 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_RoundedPad1.0x1.5mm" H 10150 4300 50  0001 C CNN
F 3 "~" H 10150 4300 50  0001 C CNN
	1    10150 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	10000 3950 10000 4300
Wire Wire Line
	10000 3600 10000 3750
Connection ~ 10000 3950
Connection ~ 10000 3750
Wire Wire Line
	10000 3750 10000 3950
$Comp
L power:GNDA #PWR?
U 1 1 62C67287
P 10300 3600
AR Path="/62C67287" Ref="#PWR?"  Part="1" 
AR Path="/6183E367/62C67287" Ref="#PWR?"  Part="1" 
AR Path="/6183E367/618A2E14/62C67287" Ref="#PWR?"  Part="1" 
AR Path="/618BA1DE/62C67287" Ref="#PWR?"  Part="1" 
AR Path="/618BA1D7/62C67287" Ref="#PWR?"  Part="1" 
AR Path="/618BA1E0/62C67287" Ref="#PWR0165"  Part="1" 
F 0 "#PWR0165" H 10300 3350 50  0001 C CNN
F 1 "GNDA" H 10304 3445 50  0000 C CNN
F 2 "" H 10300 3600 50  0001 C CNN
F 3 "" H 10300 3600 50  0001 C CNN
	1    10300 3600
	0    -1   -1   0   
$EndComp
$Comp
L power:VCC #PWR?
U 1 1 62C6728D
P 10350 3950
AR Path="/62C6728D" Ref="#PWR?"  Part="1" 
AR Path="/6183E367/62C6728D" Ref="#PWR?"  Part="1" 
AR Path="/6183E367/618A2E14/62C6728D" Ref="#PWR?"  Part="1" 
AR Path="/618BA1DE/62C6728D" Ref="#PWR?"  Part="1" 
AR Path="/618BA1D7/62C6728D" Ref="#PWR?"  Part="1" 
AR Path="/618BA1E0/62C6728D" Ref="#PWR0166"  Part="1" 
F 0 "#PWR0166" H 10350 3800 50  0001 C CNN
F 1 "VCC" H 10367 4123 50  0000 C CNN
F 2 "" H 10350 3950 50  0001 C CNN
F 3 "" H 10350 3950 50  0001 C CNN
	1    10350 3950
	0    1    1    0   
$EndComp
Wire Wire Line
	10350 3950 10300 3950
$Comp
L Jumper:SolderJumper_2_Open JP?
U 1 1 62C67294
P 9000 4150
AR Path="/618BA1D7/62C67294" Ref="JP?"  Part="1" 
AR Path="/618BA1E0/62C67294" Ref="JP50"  Part="1" 
F 0 "JP50" H 9000 4355 50  0000 C CNN
F 1 "SolderJumper_2_Open" H 9000 4264 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_RoundedPad1.0x1.5mm" H 9000 4150 50  0001 C CNN
F 3 "~" H 9000 4150 50  0001 C CNN
	1    9000 4150
	1    0    0    -1  
$EndComp
$Comp
L Jumper:SolderJumper_2_Open JP?
U 1 1 62C6729A
P 9000 4500
AR Path="/618BA1D7/62C6729A" Ref="JP?"  Part="1" 
AR Path="/618BA1E0/62C6729A" Ref="JP51"  Part="1" 
F 0 "JP51" H 9000 4705 50  0000 C CNN
F 1 "SolderJumper_2_Open" H 9000 4614 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_RoundedPad1.0x1.5mm" H 9000 4500 50  0001 C CNN
F 3 "~" H 9000 4500 50  0001 C CNN
	1    9000 4500
	1    0    0    -1  
$EndComp
$Comp
L Jumper:SolderJumper_2_Open JP?
U 1 1 62C672A0
P 9000 4850
AR Path="/618BA1D7/62C672A0" Ref="JP?"  Part="1" 
AR Path="/618BA1E0/62C672A0" Ref="JP52"  Part="1" 
F 0 "JP52" H 9000 5055 50  0000 C CNN
F 1 "SolderJumper_2_Open" H 9000 4964 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_RoundedPad1.0x1.5mm" H 9000 4850 50  0001 C CNN
F 3 "~" H 9000 4850 50  0001 C CNN
	1    9000 4850
	1    0    0    -1  
$EndComp
Wire Wire Line
	8850 4500 8850 4850
Connection ~ 8850 4500
$Comp
L power:GNDA #PWR?
U 1 1 62C672A8
P 9150 4150
AR Path="/62C672A8" Ref="#PWR?"  Part="1" 
AR Path="/6183E367/62C672A8" Ref="#PWR?"  Part="1" 
AR Path="/6183E367/618A2E14/62C672A8" Ref="#PWR?"  Part="1" 
AR Path="/618BA1DE/62C672A8" Ref="#PWR?"  Part="1" 
AR Path="/618BA1D7/62C672A8" Ref="#PWR?"  Part="1" 
AR Path="/618BA1E0/62C672A8" Ref="#PWR0167"  Part="1" 
F 0 "#PWR0167" H 9150 3900 50  0001 C CNN
F 1 "GNDA" H 9154 3995 50  0000 C CNN
F 2 "" H 9150 4150 50  0001 C CNN
F 3 "" H 9150 4150 50  0001 C CNN
	1    9150 4150
	0    -1   -1   0   
$EndComp
$Comp
L power:VCC #PWR?
U 1 1 62C672AE
P 9200 4500
AR Path="/62C672AE" Ref="#PWR?"  Part="1" 
AR Path="/6183E367/62C672AE" Ref="#PWR?"  Part="1" 
AR Path="/6183E367/618A2E14/62C672AE" Ref="#PWR?"  Part="1" 
AR Path="/618BA1DE/62C672AE" Ref="#PWR?"  Part="1" 
AR Path="/618BA1D7/62C672AE" Ref="#PWR?"  Part="1" 
AR Path="/618BA1E0/62C672AE" Ref="#PWR0168"  Part="1" 
F 0 "#PWR0168" H 9200 4350 50  0001 C CNN
F 1 "VCC" H 9217 4673 50  0000 C CNN
F 2 "" H 9200 4500 50  0001 C CNN
F 3 "" H 9200 4500 50  0001 C CNN
	1    9200 4500
	0    1    1    0   
$EndComp
Wire Wire Line
	9200 4500 9150 4500
Wire Wire Line
	8850 4150 8850 4500
Wire Wire Line
	8500 3850 8500 4500
Wire Wire Line
	8500 4500 8850 4500
Wire Notes Line
	11100 3250 11100 5450
Wire Notes Line
	11100 5450 8350 5450
Wire Notes Line
	8350 5450 8350 3250
Wire Notes Line
	8350 3250 11100 3250
Text Notes 8350 3250 0    50   ~ 0
I2C Address Selection\n
Text Label 8450 3750 0    50   ~ 0
A1_pcie1_3V3AUX
Text Label 8450 3850 0    50   ~ 0
A0_pcie1_3V3AUX
Wire Wire Line
	6600 3750 10000 3750
Wire Wire Line
	6500 1300 8500 1300
Wire Wire Line
	6500 3850 8500 3850
Text GLabel 9150 2300 2    50   Input ~ 0
PCIe1_SDA
Text GLabel 10300 1750 2    50   Input ~ 0
PCIe1_SDA
Text GLabel 9150 4850 2    50   Input ~ 0
PCIe1_SDA
Text GLabel 10300 4300 2    50   Input ~ 0
PCIe1_SDA
$Comp
L Jumper:SolderJumper_2_Open JP?
U 1 1 62C75100
P 6950 4500
AR Path="/618BA1D7/62C75100" Ref="JP?"  Part="1" 
AR Path="/618BA1E0/62C75100" Ref="JP44"  Part="1" 
F 0 "JP44" H 6950 4705 50  0000 C CNN
F 1 "SolderJumper_2_Open" H 6950 4614 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_RoundedPad1.0x1.5mm" H 6950 4500 50  0001 C CNN
F 3 "~" H 6950 4500 50  0001 C CNN
	1    6950 4500
	1    0    0    -1  
$EndComp
$Comp
L Jumper:SolderJumper_2_Open JP?
U 1 1 62C75106
P 6950 4850
AR Path="/618BA1D7/62C75106" Ref="JP?"  Part="1" 
AR Path="/618BA1E0/62C75106" Ref="JP45"  Part="1" 
F 0 "JP45" H 6950 5055 50  0000 C CNN
F 1 "SolderJumper_2_Open" H 6950 4964 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_RoundedPad1.0x1.5mm" H 6950 4850 50  0001 C CNN
F 3 "~" H 6950 4850 50  0001 C CNN
	1    6950 4850
	1    0    0    -1  
$EndComp
$Comp
L Jumper:SolderJumper_2_Open JP?
U 1 1 62C7510C
P 6950 5200
AR Path="/618BA1D7/62C7510C" Ref="JP?"  Part="1" 
AR Path="/618BA1E0/62C7510C" Ref="JP46"  Part="1" 
F 0 "JP46" H 6950 5405 50  0000 C CNN
F 1 "SolderJumper_2_Open" H 6950 5314 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_RoundedPad1.0x1.5mm" H 6950 5200 50  0001 C CNN
F 3 "~" H 6950 5200 50  0001 C CNN
	1    6950 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	6800 4850 6800 5200
Wire Wire Line
	6800 4500 6800 4650
Connection ~ 6800 4850
Connection ~ 6800 4650
Wire Wire Line
	6800 4650 6800 4850
$Comp
L power:GNDA #PWR?
U 1 1 62C75117
P 7100 4500
AR Path="/62C75117" Ref="#PWR?"  Part="1" 
AR Path="/6183E367/62C75117" Ref="#PWR?"  Part="1" 
AR Path="/6183E367/618A2E14/62C75117" Ref="#PWR?"  Part="1" 
AR Path="/618BA1DE/62C75117" Ref="#PWR?"  Part="1" 
AR Path="/618BA1D7/62C75117" Ref="#PWR?"  Part="1" 
AR Path="/618BA1E0/62C75117" Ref="#PWR0169"  Part="1" 
F 0 "#PWR0169" H 7100 4250 50  0001 C CNN
F 1 "GNDA" H 7104 4345 50  0000 C CNN
F 2 "" H 7100 4500 50  0001 C CNN
F 3 "" H 7100 4500 50  0001 C CNN
	1    7100 4500
	0    -1   -1   0   
$EndComp
$Comp
L power:VCC #PWR?
U 1 1 62C7511D
P 7150 4850
AR Path="/62C7511D" Ref="#PWR?"  Part="1" 
AR Path="/6183E367/62C7511D" Ref="#PWR?"  Part="1" 
AR Path="/6183E367/618A2E14/62C7511D" Ref="#PWR?"  Part="1" 
AR Path="/618BA1DE/62C7511D" Ref="#PWR?"  Part="1" 
AR Path="/618BA1D7/62C7511D" Ref="#PWR?"  Part="1" 
AR Path="/618BA1E0/62C7511D" Ref="#PWR0170"  Part="1" 
F 0 "#PWR0170" H 7150 4700 50  0001 C CNN
F 1 "VCC" H 7167 5023 50  0000 C CNN
F 2 "" H 7150 4850 50  0001 C CNN
F 3 "" H 7150 4850 50  0001 C CNN
	1    7150 4850
	0    1    1    0   
$EndComp
Wire Wire Line
	7150 4850 7100 4850
$Comp
L Jumper:SolderJumper_2_Open JP?
U 1 1 62C75124
P 5800 5050
AR Path="/618BA1D7/62C75124" Ref="JP?"  Part="1" 
AR Path="/618BA1E0/62C75124" Ref="JP41"  Part="1" 
F 0 "JP41" H 5800 5255 50  0000 C CNN
F 1 "SolderJumper_2_Open" H 5800 5164 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_RoundedPad1.0x1.5mm" H 5800 5050 50  0001 C CNN
F 3 "~" H 5800 5050 50  0001 C CNN
	1    5800 5050
	1    0    0    -1  
$EndComp
$Comp
L Jumper:SolderJumper_2_Open JP?
U 1 1 62C7512A
P 5800 5400
AR Path="/618BA1D7/62C7512A" Ref="JP?"  Part="1" 
AR Path="/618BA1E0/62C7512A" Ref="JP42"  Part="1" 
F 0 "JP42" H 5800 5605 50  0000 C CNN
F 1 "SolderJumper_2_Open" H 5800 5514 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_RoundedPad1.0x1.5mm" H 5800 5400 50  0001 C CNN
F 3 "~" H 5800 5400 50  0001 C CNN
	1    5800 5400
	1    0    0    -1  
$EndComp
$Comp
L Jumper:SolderJumper_2_Open JP?
U 1 1 62C75130
P 5800 5750
AR Path="/618BA1D7/62C75130" Ref="JP?"  Part="1" 
AR Path="/618BA1E0/62C75130" Ref="JP43"  Part="1" 
F 0 "JP43" H 5800 5955 50  0000 C CNN
F 1 "SolderJumper_2_Open" H 5800 5864 50  0000 C CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_RoundedPad1.0x1.5mm" H 5800 5750 50  0001 C CNN
F 3 "~" H 5800 5750 50  0001 C CNN
	1    5800 5750
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 5400 5650 5750
Connection ~ 5650 5400
$Comp
L power:GNDA #PWR?
U 1 1 62C75138
P 5950 5050
AR Path="/62C75138" Ref="#PWR?"  Part="1" 
AR Path="/6183E367/62C75138" Ref="#PWR?"  Part="1" 
AR Path="/6183E367/618A2E14/62C75138" Ref="#PWR?"  Part="1" 
AR Path="/618BA1DE/62C75138" Ref="#PWR?"  Part="1" 
AR Path="/618BA1D7/62C75138" Ref="#PWR?"  Part="1" 
AR Path="/618BA1E0/62C75138" Ref="#PWR0171"  Part="1" 
F 0 "#PWR0171" H 5950 4800 50  0001 C CNN
F 1 "GNDA" H 5954 4895 50  0000 C CNN
F 2 "" H 5950 5050 50  0001 C CNN
F 3 "" H 5950 5050 50  0001 C CNN
	1    5950 5050
	0    -1   -1   0   
$EndComp
$Comp
L power:VCC #PWR?
U 1 1 62C7513E
P 6000 5400
AR Path="/62C7513E" Ref="#PWR?"  Part="1" 
AR Path="/6183E367/62C7513E" Ref="#PWR?"  Part="1" 
AR Path="/6183E367/618A2E14/62C7513E" Ref="#PWR?"  Part="1" 
AR Path="/618BA1DE/62C7513E" Ref="#PWR?"  Part="1" 
AR Path="/618BA1D7/62C7513E" Ref="#PWR?"  Part="1" 
AR Path="/618BA1E0/62C7513E" Ref="#PWR0172"  Part="1" 
F 0 "#PWR0172" H 6000 5250 50  0001 C CNN
F 1 "VCC" H 6017 5573 50  0000 C CNN
F 2 "" H 6000 5400 50  0001 C CNN
F 3 "" H 6000 5400 50  0001 C CNN
	1    6000 5400
	0    1    1    0   
$EndComp
Wire Wire Line
	6000 5400 5950 5400
Wire Wire Line
	5650 5050 5650 5400
Wire Wire Line
	5300 4750 5300 5400
Wire Wire Line
	5300 5400 5650 5400
Wire Notes Line
	7900 4150 7900 6350
Wire Notes Line
	7900 6350 5150 6350
Wire Notes Line
	5150 4150 7900 4150
Text Notes 5150 4150 0    50   ~ 0
I2C Address Selection\n
Text Label 5250 4650 0    50   ~ 0
A1_pcie1_3V3
Text Label 5250 4750 0    50   ~ 0
A0_pcie1_3V3
Wire Wire Line
	5000 4750 5300 4750
Wire Wire Line
	5100 4650 6800 4650
Text GLabel 5950 5750 2    50   Input ~ 0
PCIe1_SDA
Text GLabel 7100 5200 2    50   Input ~ 0
PCIe1_SDA
Wire Notes Line
	5150 6350 5150 4150
Connection ~ 5450 1700
Wire Wire Line
	4300 850  4400 850 
Wire Wire Line
	4250 1100 6600 1100
Wire Wire Line
	6600 1100 6600 1200
Wire Wire Line
	4250 1200 6500 1200
Wire Wire Line
	6500 1200 6500 1300
Wire Wire Line
	4250 2750 6600 2750
Wire Wire Line
	6600 2750 6600 3750
Wire Wire Line
	4250 2850 6500 2850
Wire Wire Line
	6500 2850 6500 3850
Wire Wire Line
	4250 4400 5100 4400
Wire Wire Line
	5100 4400 5100 4650
Wire Wire Line
	4250 4500 5000 4500
Wire Wire Line
	5000 4500 5000 4750
$EndSCHEMATC
