EESchema Schematic File Version 4
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
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
L MCU_Module:Arduino_Nano_v3.x A0
U 1 1 5C565154
P 3900 3550
F 0 "A0" H 3900 2464 50  0000 C CNN
F 1 "Arduino_Nano_v3.x" H 3900 2373 50  0000 C CNN
F 2 "Module:Arduino_Nano" H 4050 2600 50  0001 L CNN
F 3 "http://www.mouser.com/pdfdocs/Gravitech_Arduino_Nano3_0.pdf" H 3900 2550 50  0001 C CNN
	1    3900 3550
	1    0    0    -1  
$EndComp
NoConn ~ 4400 3850
NoConn ~ 4400 3750
NoConn ~ 4400 3650
NoConn ~ 4400 3550
NoConn ~ 4400 3350
NoConn ~ 4400 3050
NoConn ~ 4400 2950
NoConn ~ 4400 4150
NoConn ~ 4400 4250
NoConn ~ 4000 2550
Wire Wire Line
	4000 4550 3900 4550
$Comp
L Device:CP C0
U 1 1 5C566386
P 1450 3550
F 0 "C0" H 1568 3596 50  0000 L CNN
F 1 "100uF 35V" H 1568 3505 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D13.0mm_P5.00mm" H 1488 3400 50  0001 C CNN
F 3 "~" H 1450 3550 50  0001 C CNN
	1    1450 3550
	1    0    0    -1  
$EndComp
$Comp
L Connector:Jack-DC J0
U 1 1 5C5663F1
P 800 3500
F 0 "J0" H 855 3825 50  0000 C CNN
F 1 "Power" H 855 3734 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 850 3460 50  0001 C CNN
F 3 "~" H 850 3460 50  0001 C CNN
	1    800  3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	1100 3400 1450 3400
Wire Wire Line
	1100 3600 1100 3700
Wire Wire Line
	1100 3700 1450 3700
Wire Wire Line
	1450 3400 1450 2400
Wire Wire Line
	3800 2400 3800 2550
Connection ~ 1450 3400
Wire Wire Line
	1450 3700 1450 4550
Connection ~ 1450 3700
Connection ~ 3900 4550
NoConn ~ 3400 2950
NoConn ~ 3400 3050
NoConn ~ 3400 3450
NoConn ~ 3400 3550
NoConn ~ 3400 3650
NoConn ~ 3400 3750
NoConn ~ 3400 3850
NoConn ~ 3400 3950
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 5C569346
P 2950 2400
F 0 "#FLG0101" H 2950 2475 50  0001 C CNN
F 1 "PWR_FLAG" H 2950 2574 50  0000 C CNN
F 2 "" H 2950 2400 50  0001 C CNN
F 3 "~" H 2950 2400 50  0001 C CNN
	1    2950 2400
	1    0    0    -1  
$EndComp
Connection ~ 2950 2400
Wire Wire Line
	2950 2400 3800 2400
$Comp
L Connector:Conn_01x03_Male J1
U 1 1 5C56A054
P 1900 2850
F 0 "J1" H 2006 3128 50  0000 C CNN
F 1 "Neopixel_12" H 2006 3037 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 1900 2850 50  0001 C CNN
F 3 "~" H 1900 2850 50  0001 C CNN
	1    1900 2850
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x03_Male J2
U 1 1 5C56A3CE
P 1900 3400
F 0 "J2" H 2006 3678 50  0000 C CNN
F 1 "Neopixel_24" H 2006 3587 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 1900 3400 50  0001 C CNN
F 3 "~" H 1900 3400 50  0001 C CNN
	1    1900 3400
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x03_Male J3
U 1 1 5C56A3F2
P 1900 3900
F 0 "J3" H 2006 4178 50  0000 C CNN
F 1 "Neopixel_60" H 2006 4087 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 1900 3900 50  0001 C CNN
F 3 "~" H 1900 3900 50  0001 C CNN
	1    1900 3900
	1    0    0    -1  
$EndComp
Connection ~ 2850 4550
Wire Wire Line
	1450 2400 2950 2400
Wire Wire Line
	1450 4550 2850 4550
Wire Wire Line
	2850 4550 3200 4550
$Comp
L Device:R R0
U 1 1 5C573D74
P 2400 2950
F 0 "R0" V 2300 3000 50  0000 R CNN
F 1 "300" V 2300 2850 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 2330 2950 50  0001 C CNN
F 3 "~" H 2400 2950 50  0001 C CNN
	1    2400 2950
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R1
U 1 1 5C573ED2
P 2400 3500
F 0 "R1" V 2300 3500 50  0000 C CNN
F 1 "300" V 2300 3350 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 2330 3500 50  0001 C CNN
F 3 "~" H 2400 3500 50  0001 C CNN
	1    2400 3500
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R2
U 1 1 5C573FE0
P 2400 4000
F 0 "R2" V 2300 4000 50  0000 C CNN
F 1 "300" V 2300 3850 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 2330 4000 50  0001 C CNN
F 3 "~" H 2400 4000 50  0001 C CNN
	1    2400 4000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3100 3500 2550 3500
Wire Wire Line
	2550 2950 3250 2950
Wire Wire Line
	2100 2950 2250 2950
Wire Wire Line
	2100 3500 2250 3500
Wire Wire Line
	2100 4000 2250 4000
Wire Wire Line
	2100 3900 2850 3900
Wire Wire Line
	3250 2950 3250 3150
Wire Wire Line
	3400 3150 3250 3150
Wire Wire Line
	3400 3250 3100 3250
Wire Wire Line
	3100 3250 3100 3500
Wire Wire Line
	3400 3350 3200 3350
Wire Wire Line
	3200 3350 3200 4000
Wire Wire Line
	2550 4000 3200 4000
NoConn ~ 3400 4050
NoConn ~ 3400 4150
NoConn ~ 3400 4250
$Comp
L chronodot:Chronodot U0
U 1 1 5C58C2A9
P 5700 3500
F 0 "U0" H 5700 3014 50  0000 C CNN
F 1 "Chronodot" H 5700 2923 50  0000 C CNN
F 2 "Logos:chronodot" H 5700 2900 50  0001 C CNN
F 3 "https://www.adafruit.com/product/255" H 5970 3550 50  0001 C CNN
	1    5700 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4400 4050 4900 4050
Wire Wire Line
	4900 4050 4900 3300
Wire Wire Line
	4900 3300 5200 3300
Wire Wire Line
	4400 3950 4800 3950
Wire Wire Line
	4800 3950 4800 3400
Wire Wire Line
	4800 3400 5200 3400
NoConn ~ 5200 3700
NoConn ~ 6200 3600
NoConn ~ 6200 3300
Wire Wire Line
	5600 3100 5600 2400
Wire Wire Line
	5600 2400 4100 2400
NoConn ~ 5700 3100
Wire Wire Line
	4000 4550 5700 4550
Wire Wire Line
	5700 4550 5700 3900
Connection ~ 4000 4550
Wire Wire Line
	4100 2550 4100 2400
Wire Wire Line
	2950 2400 2950 2850
Wire Wire Line
	2100 2850 2950 2850
Connection ~ 2950 2850
Wire Wire Line
	2950 2850 2950 3400
Connection ~ 2950 3400
Wire Wire Line
	2850 3900 2950 3900
Wire Wire Line
	2950 3400 2950 3900
Wire Wire Line
	2100 3400 2950 3400
Wire Wire Line
	2100 2750 2850 2750
Wire Wire Line
	2850 2750 2850 3300
Wire Wire Line
	2100 3300 2850 3300
Connection ~ 2850 3300
Wire Wire Line
	2850 3300 2850 3800
Wire Wire Line
	2100 3800 2850 3800
Connection ~ 2850 3800
Wire Wire Line
	2850 3800 2850 4550
$Comp
L power:GND #PWR0101
U 1 1 5C593C8A
P 3200 4550
F 0 "#PWR0101" H 3200 4300 50  0001 C CNN
F 1 "GND" H 3205 4377 50  0000 C CNN
F 2 "" H 3200 4550 50  0001 C CNN
F 3 "" H 3200 4550 50  0001 C CNN
	1    3200 4550
	1    0    0    -1  
$EndComp
Connection ~ 3200 4550
Wire Wire Line
	3200 4550 3900 4550
$Comp
L power:PWR_FLAG #FLG0102
U 1 1 5C5695F3
P 2850 4550
F 0 "#FLG0102" H 2850 4625 50  0001 C CNN
F 1 "PWR_FLAG" H 2850 4723 50  0000 C CNN
F 2 "" H 2850 4550 50  0001 C CNN
F 3 "~" H 2850 4550 50  0001 C CNN
	1    2850 4550
	-1   0    0    1   
$EndComp
$EndSCHEMATC
