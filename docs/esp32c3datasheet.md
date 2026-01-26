Product Overview
ESP32-C3 series of SoCs is an ultra-low-power and highly-integrated MCU-based solution that supports 2.4
GHz Wi-Fi and Bluetooth® Low Energy (Bluetooth LE). The block diagram of ESP32-C3 is shown below.
Espressif’s ESP32-C3 Wi-Fi + Bluetooth® Low Energy SoC
Core System
RISC-V
32-bit
Microprocessor
Cache
JTAG
SPI0/1
SRAM
ROM
Peripherals 
I2C
⚙
SPI2 
TWAI®
GDMA 
⚙
LED PWM
I2S
RMT
Wireless MAC and 
Baseband
Wi-Fi MAC 
Wi-Fi 
Baseband
Bluetooth LE 
Link Controller
Bluetooth LE 
Baseband
GPIO
RF
2.4 GHz Balun + Switch
2.4 GHz Transmitter
2.4 GHz Receiver
RF Synthesizer
RTC
RTC 
Memory
PMU
RTC GPIO
UART
eFuse 
Controller
RTC Super Watchdog Timer
DIG ADC 
Controller
RTC Watchdog Timer
Brownout Detector
Security
SHA
⚙
AES
⚙
RSA
⚙
RNG
USB Serial/
JTAG
General-purpose Timers
System Timer
Temperature 
Sensor
Main System Watchdog Timers
HMAC
⚙
Digital 
Signature
⚙
Secure 
Boot
Modules having power in specific power modes:
Active
Active and Modem-sleep
All modes
Active, Modem-sleep, and Light-sleep;
⚙
⚙
Flash 
Encryption
optional in Light-sleep
Figure 1: Block Diagram of ESP32C3
Solution Highlights
• Acomplete WiFi subsystem that complies
with IEEE 802.11b/g/n protocol and supports
Station mode, SoftAP mode, SoftAP + Station
mode, and promiscuous mode
• ABluetooth LE subsystem that supports
features of Bluetooth 5 and Bluetooth mesh
• 32bit RISCV singlecore processor with a
four-stage pipeline that operates at up to 160
MHz
• Stateof theart power and RF performance
Espressif Systems
• Storage capacities ensured by 400 KB of
SRAM (16 KB for cache) and 384 KB of ROM on
the chip, and SPI, Dual SPI, Quad SPI, and QPI
interfaces that allow connection to external flash
• Reliable security features ensured by– Cryptographic hardware accelerators that
support AES-128/256, Hash, RSA, HMAC,
digital signature and secure boot– Random number generator– Permission control on accessing internal
2
Submit Documentation Feedback
ESP32-C3 Series Datasheet v1.4
memory, external memory, and peripherals– External memory encryption and decryption
Features
WiFi
• IEEE 802.11 b/g/n-compliant
• Supports 20 MHz, 40 MHz bandwidth in 2.4
GHz band
• 1T1R mode with data rate up to 150 Mbps
• Wi-Fi Multimedia (WMM)
• TX/RX A-MPDU, TX/RX A-MSDU
• Immediate Block ACK
• Fragmentation and defragmentation
• Transmit opportunity (TXOP)
• Automatic Beacon monitoring (hardware TSF)
• 4×virtual Wi-Fi interfaces
• Simultaneous support for Infrastructure BSS in
Station mode, SoftAP mode, Station + SoftAP
mode, and promiscuous mode
Note that when ESP32-C3 scans in Station mode,
the SoftAP channel will change along with the
Station channel
• Antenna diversity
• 802.11mc FTM
Bluetooth
• Bluetooth LE: Bluetooth 5, Bluetooth mesh
• High power mode (21 dBm)
• Speed: 125 Kbps, 500 Kbps, 1 Mbps, 2 Mbps
• Advertising extensions
• Multiple advertisement sets
• Channel selection algorithm #2
• Internal co-existence mechanism between Wi-Fi
and Bluetooth to share the same antenna
Espressif Systems
• Rich set of peripheral interfaces and GPIOs,
ideal for various scenarios and complex
applications
CPUand Memory
• 32-bit RISC-V single-core processor, up to 160
MHz
• CoreMark® score:– 1core at 160 MHz: 407.22 CoreMark; 2.55
CoreMark/MHz
• 384 KBROM
• 400 KBSRAM(16 KBfor cache)
• 8KBSRAMinRTC
• Embedded flash (see details in Chapter 1
ESP32-C3 Series Comparison)
• SPI, Dual SPI, Quad SPI, and QPI interfaces that
allow connection to multiple external flash
• Access to flash accelerated by cache
• Supports flash in-Circuit Programming (ICP)
Advanced Peripheral Interfaces
• 22or 16 programmable GPIOs
• Digital interfaces:– 3×SPI– 2×UART– 1×I2C– 1×I2S– Remote control peripheral, with 2 transmit
channels and 2 receive channels– LEDPWMcontroller, with up to 6 channels– Full-speed USB Serial/JTAG controller– General DMA controller (GDMA), with 3
transmit channels and 3 receive channels– 1×TWAI® controller compatible with ISO
11898-1 (CAN Specification 2.0)
• Analog interfaces:
3
Submit Documentation Feedback
ESP32-C3 Series Datasheet v1.4
– 2×12-bit SAR ADCs, up to 6 channels
Security– 1×temperature sensor
• Timers:– 2×54-bit general-purpose timers– 3×digital watchdog timers– 1×analog watchdog timer– 1×52-bit system timer
Low Power Management
• Power Management Unit with four power modes
Applications (A Nonexhaustive List)
• Secure boot
• Flash encryption
• 4096-bit OTP, up to 1792 bits for use
• Cryptographic hardware acceleration:– AES-128/256 (FIPS PUB 197)
• Permission Control
• SHAAccelerator (FIPS PUB 180-4)
• RSAAccelerator
• Random Number Generator (RNG)
• HMAC
• Digital signature
With ultra-low power consumption, ESP32-C3 is an ideal choice for IoT devices in the following areas:
• Smart Home– Light control– Smart button– Smart plug– Indoor positioning
• Industrial Automation– Industrial robot– Mesh network– Human machine interface (HMI)– Industrial field bus
• Health Care– Health monitor– Baby monitor
• Consumer Electronics– Smart watch and bracelet– Over-the-top (OTT) devices
Espressif Systems– Wi-Fi speaker– Logger toys and proximity sensing toys
• Smart Agriculture– Smart greenhouse– Smart irrigation– Agriculture robot
• Retail and Catering– POSmachines– Service robot
• Audio Device– Internet music players– Live streaming devices– Internet radio players
• Generic Low-power IoT Sensor Hubs
• Generic Low-power IoT Data Loggers
4
Submit Documentation Feedback
ESP32-C3 Series Datasheet v1.4
Contents
Contents
ProductOverview 2
SolutionHighlights 2
Features 3
Applications 4
1 ESP32C3SeriesComparison 9
1.1 ESP32-C3SeriesNomenclature 9
1.2 Comparison 9
2PinDefinition 10
2.1 PinLayout 10
2.2 PinDescription 11
2.3 PowerScheme 13
2.4 StrappingPins 14
3 FunctionalDescription 17
3.1 CPUandMemory 17
3.1.1 CPU 17
3.1.2 InternalMemory 17
3.1.3 ExternalFlash 17
3.1.4 AddressMappingStructure 18
3.1.5 Cache 18
3.2 SystemClocks 19
3.2.1 CPUClock 19
3.2.2 RTCClock 19
3.3 AnalogPeripherals 19
3.3.1 Analog-to-DigitalConverter(ADC) 19
3.3.2 TemperatureSensor 20
3.4 DigitalPeripherals 20
3.4.1 GeneralPurposeInput/Output Interface(GPIO) 20
3.4.2 SerialPeripheral Interface(SPI) 22
3.4.3 UniversalAsynchronousReceiverTransmitter(UART) 23
3.4.4 I2CInterface 23
3.4.5 I2SInterface 24
3.4.6 RemoteControlPeripheral 24
3.4.7 LEDPWMController 24
3.4.8 GeneralDMAController 24
3.4.9 USBSerial/JTAGController 25
3.4.10TWAI®Controller 25
3.5 RadioandWi-Fi 25
3.5.1 2.4GHzReceiver 26
3.5.2 2.4GHzTransmitter 26
3.5.3 ClockGenerator 26
EspressifSystems 5
SubmitDocumentationFeedback
ESP32-C3SeriesDatasheetv1.4
Contents
3.5.4 Wi-Fi Radio and Baseband
3.5.5 Wi-Fi MAC
3.5.6 Networking Features
3.6 Bluetooth LE
3.6.1 Bluetooth LE Radio and PHY
3.6.2 Bluetooth LE Link Layer Controller
3.7 LowPower Management
3.8 Timers
3.8.1 General Purpose Timers
3.8.2 System Timer
3.8.3 Watchdog Timers
3.9 Cryptographic Hardware Accelerators
3.10 Physical Security Features
3.11 Peripheral Pin Configurations
4 Electrical Characteristics
4.1 Absolute Maximum Ratings
4.2 Recommended Operating Conditions
4.3 VDD_SPI Output Characteristics
4.4 DCCharacteristics (3.3 V, 25 °C)
4.5 ADCCharacteristics
4.6 Current Consumption
4.6.1 RF Current Consumption in Active Mode
4.6.2 Current Consumption in Other Modes
4.7 Reliability
4.8 Wi-Fi Radio
4.8.1 Wi-Fi RF Transmitter (TX) Specifications
4.8.2 Wi-Fi RF Receiver (RX) Specifications
4.9 Bluetooth LE Radio
4.9.1 Bluetooth LE RF Transmitter (TX) Specifications
4.9.2 Bluetooth LE RF Receiver (RX) Specifications
5 Package Information
6 Related Documentation and Resources
Revision History
Espressif Systems
26
27
27
27
27
27
28
28
28
29
29
30
30
30
33
33
33
33
34
34
35
35
35
36
36
37
37
39
39
40
43
44
45
6
Submit Documentation Feedback
ESP32-C3 Series Datasheet v1.4
ListofTables
ListofTables
1 ESP32-C3SeriesComparison 9
2 PinDescription 11
3 DescriptionofESP32-C3Power-upandResetTimingParameters 14
4 StrappingPins 15
5 ParameterDescriptionsofSetupandHoldTimesfortheStrappingPins 16
6 IOMUXPinFunctions 20
7 Power-UpGlitchesonPins 22
8 MappingofSPISignalsandChipPins 23
9 ConnectionBetweenESP32-C3andExternalFlash 23
10 PeripheralPinConfigurations 30
11 AbsoluteMaximumRatings 33
12 RecommendedOperatingConditions 33
13 VDD_SPIOutputCharacteristics 33
14 DCCharacteristics(3.3V,25°C) 34
15 ADCCharacteristics 34
16 ADCCalibrationResults 35
17 CurrentConsumptionDependingonRFModes 35
18 CurrentConsumptioninModem-sleepMode 35
19 CurrentConsumptioninLow-PowerModes 36
20 ReliabilityQualifications 36
21 Wi-FiFrequency 36
22 TXPowerwithSpectralMaskandEVMMeeting802.11Standards 37
23 TXEVMTest 37
24 RXSensitivity 37
25 MaximumRXLevel 38
26 RXAdjacentChannelRejection 38
27 BluetoothLEFrequency 39
28 TransmitterCharacteristics-BluetoothLE1Mbps 39
29 TransmitterCharacteristics-BluetoothLE2Mbps 39
30 TransmitterCharacteristics-BluetoothLE125Kbps 40
31 TransmitterCharacteristics-BluetoothLE500Kbps 40
32 ReceiverCharacteristics-BluetoothLE1Mbps 41
33 ReceiverCharacteristics-BluetoothLE2Mbps 41
34 ReceiverCharacteristics-BluetoothLE125Kbps 42
35 ReceiverCharacteristics-BluetoothLE500Kbps 42
EspressifSystems 7
SubmitDocumentationFeedback
ESP32-C3SeriesDatasheetv1.4
List of Figures
List of Figures
1
2
3
4
5
6
7
8
9
Block Diagram of ESP32-C3
ESP32-C3 Series Nomenclature
ESP32-C3 Pin Layout (Top View, Excluding ESP32-C3FH4AZ)
ESP32-C3FH4AZ Pin Layout (Top View)
ESP32-C3 Power Scheme
ESP32-C3 Power-up and Reset Timing
Setup and Hold Times for the Strapping Pins
Address Mapping Structure
QFN32 (5×5 mm) Package
Espressif Systems
2
9
10
11
13
14
15
18
43
8
Submit Documentation Feedback
ESP32-C3 Series Datasheet v1.4
1 ESP32-C3 Series Comparison
1. ESP32C3 Series Comparison
1.1 ESP32C3 Series Nomenclature
ESP32-C3
F
H
x
AZ
Other Identification Code 
Flash 
Flash temperature
H: High temperature
N: Normal temperature
Flash
Chip series
Figure 2: ESP32C3 Series Nomenclature
1.2 Comparison
Ordering Code
Table 1: ESP32C3 Series Comparison
Embedded Flash
Ambient Temperature (°C)
ESP32-C31
—–40 ∼ 105
Package (mm)
GPIO No.
QFN32 (5*5)
ESP32-C3FN4
4 MB–40 ∼ 85
22
QFN32 (5*5)
ESP32-C3FH4
4 MB–40 ∼ 105
22
QFN32 (5*5)
ESP32-C3FH4AZ2
4 MB
22–40 ∼ 105
1 ESP32-C3 requires an external SPI flash.
QFN32 (5*5)
16
2 For ESP32-C3FH4AZ, SPI0/SPI1 pins for flash connection are not bonded. For details, see Note 7
under Table 2 Pin Description.
Espressif Systems
9
Submit Documentation Feedback
ESP32-C3 Series Datasheet v1.4
2 PinDefinition
2. Pin Definition
2.1 Pin Layout
LNA_IN
VDD3P3
VDD3P3
XTAL_32K_P
1
2
3
4
VDDA
32
VDDA
31
XTAL_P
30
XTAL_N
29
U0TXD
28
U0RXD
27
GPIO19
26
GPIO18
25
XTAL_32K_N
GPIO2
CHIP_EN
GPIO3
5
6
7
8
ESP32-C3
9
MTMS
10
MTDI
11
VDD3P3_RTC
12
MTCK
13
MTDO
14
GPIO8
33 GND
15
GPIO9
16
GPIO10
24
23
22
21
20
19
18
17
Figure 3: ESP32C3 Pin Layout (Top View, Excluding ESP32C3FH4AZ)
Espressif Systems
10
Submit Documentation Feedback
SPIQ
SPID
SPICLK
SPICS0
SPIWP
SPIHD
VDD_SPI
VDD3P3_CPU
ESP32-C3 Series Datasheet v1.4
2 PinDefinition
1
2
3
4
5
6
7
8 17
18
19
20
21
22
23
24
9
10
11
12
13
14
15
16
27
28
29
30
31
32
26
25 GPIO10
GPIO9
GPIO8
MTDO
MTCK
VDD3P3_RTC
MTDI
MTMS
GPIO3
CHIP_EN
GPIO2
XTAL_32K_N
XTAL_32K_P
VDD3P3
VDD3P3
LNA_IN
VDDA
VDDA
XTAL_P
XTAL_N
U0TXD
U0RXD
GPIO19
GPIO18
NC
NC
NC
NC
NC
VDD_SPI
VDD3P3_CPU
ESP32-C3FH4AZ
33 GND
NC
Figure4:ESP32C3FH4AZPinLayout(TopView)
2.2 PinDescription
Table2:PinDescription
Name No. Type PowerDomain Function
LNA_IN 1 I/O — RFinputandoutput
VDD3P3 2 PA — Analogpowersupply
VDD3P3 3 PA — Analogpowersupply
XTAL_32K_P 4 I/O/T VDD3P3_RTC GPIO0, ADC1_CH0, XTAL_32K_P
XTAL_32K_N 5 I/O/T VDD3P3_RTC GPIO1, ADC1_CH1, XTAL_32K_N
GPIO2 6 I/O/T VDD3P3_RTC GPIO2, ADC1_CH2, FSPIQ
CHIP_EN 7 I VDD3P3_RTC
High:on,enablesthechip.
Low:off,thechippowersoff.
Note:Donot leavetheCHIP_ENpinfloating.
EspressifSystems 11
SubmitDocumentationFeedback
ESP32-C3SeriesDatasheetv1.4
2 PinDefinition
Name No. Type PowerDomain Function
GPIO3 8 I/O/T VDD3P3_RTC GPIO3, ADC1_CH3
MTMS 9 I/O/T VDD3P3_RTC GPIO4, ADC1_CH4, FSPIHD, MTMS
MTDI 10 I/O/T VDD3P3_RTC GPIO5, ADC2_CH0, FSPIWP, MTDI
VDD3P3_RTC 11 PD — InputpowersupplyforRTC
MTCK 12 I/O/T VDD3P3_CPU GPIO6, FSPICLK, MTCK
MTDO 13 I/O/T VDD3P3_CPU GPIO7, FSPID, MTDO
GPIO8 14 I/O/T VDD3P3_CPU GPIO8
GPIO9 15 I/O/T VDD3P3_CPU GPIO9
GPIO10 16 I/O/T VDD3P3_CPU GPIO10, FSPICS0
VDD3P3_CPU 17 PD — InputpowersupplyforCPUIO
VDD_SPI 18 I/O/T/PD VDD3P3_CPU GPIO11, outputpowersupplyforflash6
SPIHD 19 I/O/T VDD3P3_CPU GPIO12, SPIHD
SPIWP 20 I/O/T VDD3P3_CPU GPIO13, SPIWP
SPICS0 21 I/O/T VDD3P3_CPU GPIO14, SPICS0
SPICLK 22 I/O/T VDD3P3_CPU GPIO15, SPICLK
SPID 23 I/O/T VDD3P3_CPU GPIO16, SPID
SPIQ
7
24 I/O/T VDD3P3_CPU GPIO17, SPIQ
GPIO18 25 I/O/T VDD3P3_CPU GPIO18, USB_D
GPIO19 26 I/O/T VDD3P3_CPU GPIO19, USB_D+
U0RXD 27 I/O/T VDD3P3_CPU GPIO20, U0RXD
U0TXD 28 I/O/T VDD3P3_CPU GPIO21, U0TXD
XTAL_N 29 — — Externalcrystaloutput
XTAL_P 30 — — Externalcrystal input
VDDA 31 PA — Analogpowersupply
VDDA 32 PA — Analogpowersupply
GND 33 G — Ground
1PA:analogpowersupply;PD:powersupplyforRTCIO; I: input;O:output;T:highimpedance.
2PinfunctionsinboldfontarethedefaultpinfunctionsinSPIbootmode.
3PortsofembeddedflashcorrespondtopinsofESP32-C3FN4andESP32-C3FH4asfollows:
•CS#=SPICS0
•IO0/DI=SPID
•IO1/DO=SPIQ
•CLK=SPICLK
•IO2/WP#=SPIWP
•IO3/HOLD#=SPIHD
Thesepinsarenotrecommendedforotheruses.
4ForthedataportconnectionbetweenESP32-C3andexternal flashpleaserefertoSection3.4.2SerialPeripheral
Interface(SPI).
5Thepinfunctioninthistablerefersonlytosomefixedsettingsanddonotcoverallcasesforsignalsthatcanbe
inputandoutput throughtheGPIOmatrix. FormoreinformationontheGPIOmatrix,pleaserefer toChapter IO
MUXandGPIOMatrix(GPIO, IO_MUX) inESP32-C3TechnicalReferenceManual.
6BydefaultVDD_SPI isthepowersupplypinforembeddedflashorexternal flash. ItcanonlybeusedasGPIO11
onlywhenthechipisconnectedtoanexternal flash,andthisflashispoweredbyanexternalpowersupply.
7ForESP32-C3FH4AZ,pinswithintheframe(namelypin19∼pin24)arenotbonded,andarelabelledas”not
connected”.
EspressifSystems 12
SubmitDocumentationFeedback
ESP32-C3SeriesDatasheetv1.4
2 PinDefinition
2.3 Power Scheme
ESP32-C3 has four input power pins:
• VDDA1
• VDDA2
• VDD3P3_RTC
• VDD3P3_CPU
And one input/output power pin:
• VDD_SPI
VDDA1 and VDDA2 are the input power supply for the analog domain.
When working as an output power supply, VDD_SPI can be powered by VDD3P3_CPU via RSPI (nominal 3.3 V).
VDD_SPI can be powered off via software to minimize the current leakage of flash in Deep-sleep mode.
RTC IO is powered from VDD3P3_RTC.
The RTC domain is powered from Low Power Voltage Regulator, which is powered from VDD3P3_RTC.
The Digital System domain is powered from Digital System Voltage Regulator, which is powered from
VDD3P3_CPU and VDD3P3_RTC at the same time.
Digital IO is powered from VDD3P3_CPU.
The power scheme diagram is shown in Figure 5.
Figure 5: ESP32C3 Power Scheme
Espressif Systems
13
Submit Documentation Feedback
ESP32-C3 Series Datasheet v1.4
2 PinDefinition
Notes on CHIP_EN:
Figure 6 shows the power-up and reset timing of ESP32-C3. Details about the parameters are listed in Table
3.
t 0
2.8 V
VDDA, 
VDD3P3,
VDD3P3_RTC,
VDD3P3_CPU
t 1
VIL_nRST
CHIP_EN
Figure 6: ESP32C3 Powerup and Reset Timing
Table 3: Description of ESP32C3 Powerup and Reset Timing Parameters
Parameter
Min
Description (µs)
t0
Time between bringing up the VDDA, VDD3P3, VDD3P3_RTC, and
VDD3P3_CPU rails, and activating CHIP_EN
50
t1
Duration of CHIP_EN signal level < VIL_nRST (refer to its value in
Table 14) to reset the chip
2.4 Strapping Pins
ESP32-C3 has three strapping pins:
• GPIO2
• GPIO8
• GPIO9
50
Software can read the values of GPIO2, GPIO8 and GPIO9 from GPIO_STRAPPING field in GPIO_STRAP_REG
register. For register description, please refer to Section GPIO Matrix Register Summary in
ESP32-C3 Technical Reference Manual.
During the chip’s system reset, the latches of the strapping pins sample the voltage level as strapping bits of ”0”
or ”1”, and hold these bits until the chip is powered down or shut down.
Types of system reset include:
• power-on reset
• RTCwatchdog reset
• brownout reset
• analog super watchdog reset
• crystal clock glitch detection reset
Espressif Systems
14
Submit Documentation Feedback
ESP32-C3 Series Datasheet v1.4
2 PinDefinition
Bydefault,GPIO9isconnectedtotheinternalweakpull-upresistor. IfGPIO9isnotconnectedorconnectedto
anexternalhigh-impedancecircuit,thelatchedbitvaluewillbe”1”
Tochangethestrappingbitvalues,youcanapplytheexternalpull-down/pull-upresistances,orusethehost
MCU’sGPIOstocontrol thevoltagelevelof thesepinswhenpoweringonESP32-C3.
Afterreset,thestrappingpinsworkasnormal-functionpins.
Table4listsdetailedbootingconfigurationsof thestrappingpins.
Table4:StrappingPins
BootingMode1
Pin Default SPIBoot DownloadBoot
GPIO2 N/A 1 1
GPIO8 N/A Don’tcare 1
GPIO9 Internalweak
pull-up 1 0
Enabling/DisablingROMMessagesPrintinSPIBootMode
Pin Default Functionality
GPIO8 N/A
WhenthevalueofeFusefieldEFUSE_UART_PRINT_CONTROLis
0(default),print isenabledandnotcontrolledbyGPIO8.
1, ifGPIO8is0,print isenabled; ifGPIO8is1, it isdisabled.
2, ifGPIO8is0,print isdisabled; ifGPIO8is1, it isenabled.
3,print isdisabledandnotcontrolledbyGPIO8.
1ThestrappingcombinationofGPIO8=0andGPIO9=0isinvalidandwill triggerunexpectedbe
havior.
Figure7showsthesetupandholdtimesforthestrappingpinsbeforeandaftertheCHIP_ENsignalgoeshigh.
DetailsabouttheparametersarelistedinTable5.
CHIP_EN
t 1 t 0
Strapping pin
VIL_nRST
VIH
Figure7:SetupandHoldTimesfortheStrappingPins
EspressifSystems 15
SubmitDocumentationFeedback
ESP32-C3SeriesDatasheetv1.4
2 PinDefinition
Table 5: Parameter Descriptions of Setup and Hold Times for the Strapping Pins
Min
Description (ms)
Setup time before CHIP_EN goes from low to high
t1
Parameter
t0
Hold time after CHIP_EN goes high
0
3
Espressif Systems
16
Submit Documentation Feedback
ESP32-C3 Series Datasheet v1.4
3 Functional Description
3. Functional Description
This chapter describes the functions of ESP32-C3.
3.1 CPUandMemory
3.1.1 CPU
ESP32-C3 has a low-power 32-bit RISC-V single-core microprocessor with the following features:
• four-stage pipeline that supports a clock frequency of up to 160 MHz
• RV32IMC ISA
• 32-bit multiplier and 32-bit divider
• upto 32 vectored interrupts at seven priority levels
• upto 8 hardware breakpoints/watchpoints
• upto 16 PMPregions
• JTAG for debugging
For more information, please refer to Chapter ESP-RISC-V CPU in ESP32-C3 Technical Reference Manual.
3.1.2 Internal Memory
ESP32-C3’s internal memory includes:
• 384 KBof ROM: for booting and core functions.
• 400 KBof onchip SRAM: for data and instructions, running at a configurable frequency of up to 160
MHz. Of the 400 KB SRAM, 16 KB is configured for cache.
• RTCFASTmemory: 8 KBof SRAMthat can be accessed by the main CPU. It can retain data in
Deep-sleep mode.
• 4Kbit of eFuse: 1792 bits are reserved for your data, such as encryption key and device ID.
• Embedded flash : See details in Chapter 1 ESP32-C3 Series Comparison.
For more information, please refer to Chapter System and Memory in ESP32-C3 Technical Reference
Manual.
3.1.3 External Flash
ESP32-C3 supports SPI, Dual SPI, Quad SPI, and QPI interfaces that allow connection to multiple external
flash.
CPU’s instruction memory space and read-only data memory space can map into external flash of ESP32-C3,
whose size can be 16 MB at most. ESP32-C3 supports hardware encryption/decryption based on XTS-AES to
protect developers’ programs and data in flash.
Through high-speed caches, ESP32-C3 can support at a time up to:
• 8MBof instruction memory space which can map into flash as individual blocks of 64 KB. 8-bit, 16-bit and
32-bit reads are supported.
• 8MBofdata memory space which can map into flash as individual blocks of 64 KB. 8-bit, 16-bit and
32-bit reads are supported.
Espressif Systems
17
Submit Documentation Feedback
ESP32-C3 Series Datasheet v1.4
3 Functional Description
Note:
After ESP32-C3 is initialized, software can customize the mapping of external flash into the CPU address space.
For more information, please refer to Chapter System and Memory in ESP32-C3 Technical Reference
Manual.
3.1.4 Address Mapping Structure
Figure 8: Address Mapping Structure
Note:
The memory space with gray background is not available for use.
3.1.5 Cache
ESP32-C3 has an eight-way set associative cache. This cache is read-only and has the following features:
• size: 16 KB
• block size: 32 bytes
• pre-load function
• lock function
Espressif Systems
18
Submit Documentation Feedback
ESP32-C3 Series Datasheet v1.4
3 Functional Description
• critical word first and early restart
3.2 System Clocks
For more information, please refer to Chapter Reset and Clock in ESP32-C3 Technical Reference Manual.
3.2.1 CPU Clock
The CPU clock has three possible sources:
• external main crystal clock
• fast RC oscillator (typically about 17.5 MHz, and adjustable)
• PLL clock
The application can select the clock source from the three clocks above. The selected clock source drives the
CPU clock directly, or after division, depending on the application. Once the CPU is reset, the default clock
source would be the external main crystal clock divided by 2.
Note:
ESP32-C3 is unable to operate without an external main crystal clock.
3.2.2 RTC Clock
The RTC slow clock is used for RTC counter, RTC watchdog and low-power controller. It has three possible
sources:
• external low-speed (32 kHz) crystal clock
• internal slow RC oscillator (typically about 136 kHz, and adjustable)
• internal fast RC oscillator divided clock (derived from the fast RC oscillator divided by 256)
The RTC fast clock is used for RTC peripherals and sensor controllers. It has two possible sources:
• external main crystal clock divided by 2
• internal fast RC oscillator divide-by-N clock (typically about 17.5 MHz, and adjustable)
3.3 Analog Peripherals
For more information, please refer to Chapter On-Chip Sensors and Analog Signal Processing in ESP32-C3
Technical Reference Manual.
3.3.1 AnalogtoDigital Converter (ADC)
ESP32-C3 integrates two 12-bit SAR ADCs.
• ADC1supports measurements on 5 channels, and is factory-calibrated.
• ADC2supports measurements on 1 channel, and is not factory-calibrated.
Espressif Systems
19
Submit Documentation Feedback
ESP32-C3 Series Datasheet v1.4
3 Functional Description
Note:
ADC2 of some chip revisions is not operable. For details, please refer to ESP32-C3 Series SoC Errata.
For ADC characteristics, please refer to Table 15.
For GPIOs assigned to ADC, please refer to Table 10.
3.3.2 Temperature Sensor
The temperature sensor generates a voltage that varies with temperature. The voltage is internally converted via
an ADC into a digital value.
The temperature sensor has a range of–40 °C to 125 °C. It is designed primarily to sense the temperature
changes inside the chip. The temperature value depends on factors like microcontroller clock frequency or I/O
load. Generally, the chip’s internal temperature is higher than the operating ambient temperature.
3.4 Digital Peripherals
3.4.1 General Purpose Input / Output Interface (GPIO)
ESP32-C3 has 22 or 16 GPIO pins which can be assigned various functions by configuring corresponding
registers. Besides digital signals, some GPIOs can be also used for analog functions, such as ADC.
All GPIOs have selectable internal pull-up or pull-down, or can be set to high impedance. When these GPIOs are
configured as an input, the input value can be read by software through the register. Input GPIOs can also be set
to generate edge-triggered or level-triggered CPU interrupts. All digital IO pins are bi-directional, non-inverting
and tristate, including input and output buffers with tristate control. These pins can be multiplexed with other
functions, such as the UART, SPI, etc. For low-power operations, the GPIOs can be set to holding state.
The IO MUX and the GPIO matrix are used to route signals from peripherals to GPIO pins. Together they provide
highly configurable I/O. Using GPIO Matrix, peripheral input signals can be configured from any IO pins while
peripheral output signals can be configured to any IO pins. Table 6 shows the IO MUX functions of each
pin.
Table 6: IO MUX Pin Functions
Name No.
Function 0
Function 1
Function 2
XTAL_32K_P
4
GPIO0
GPIO0
Reset
Notes
—
0
XTAL_32K_N
5
GPIO1
GPIO1
—
R
0
GPIO2
6
GPIO2
GPIO2
FSPIQ
R
1
GPIO3
8
GPIO3
GPIO3
—
R
1
MTMS
9
MTMS
GPIO4
FSPIHD
R
1
MTDI
10
MTDI
GPIO5
FSPIWP
R
1
MTCK
12
MTCK
GPIO6
FSPICLK
R
1*
MTDO
13
MTDO
GPIO7
FSPID
G
1
GPIO8
14
GPIO8
GPIO8
—
G
1
GPIO9
15
GPIO9
GPIO9
—
—
3
GPIO10
16
GPIO10
—
GPIO10
Espressif Systems
FSPICS0
20
Submit Documentation Feedback
1
G
ESP32-C3 Series Datasheet v1.4
3 Functional Description
Name No.
Function 0
Function 1
Function 2
VDD_SPI
1
18
GPIO11
GPIO11
Reset
Notes
—
0
SPIHD
19
SPIHD
GPIO12
—
—
3
SPIWP
20
SPIWP
GPIO13
—
—
3
SPICS0
21
SPICS0
GPIO14
—
—
3
SPICLK
22
SPICLK
GPIO15
—
—
3
SPID
23
SPID
GPIO16
—
—
3
SPIQ
24
SPIQ
GPIO17
—
—
3
GPIO18
25
GPIO18
GPIO18
—
—
0
GPIO19
26
GPIO19
GPIO19
—
USB, G
0*
U0RXD
27
U0RXD
GPIO20
—
USB
3
U0TXD
28
U0TXD
G
GPIO21
—
4
—
1 ForESP32-C3FH4AZ,pinswithintheframe(namelypin19∼pin24)arenotbonded, andarelabelled
as ”not connected”.
Reset
The default configuration of each pin after reset:
• 0- input disabled, in high impedance state (IE = 0)
• 1- input enabled, in high impedance state (IE = 1)
• 2- input enabled, pull-down resistor enabled (IE = 1, WPD = 1)
• 3- input enabled, pull-up resistor enabled (IE = 1, WPU = 1)
• 4-output enabled, pull-up resistor enabled (OE = 1, WPU = 1)
• 0*- input disabled, pull-up resistor enabled (IE = 0, WPU = 0, USB_WPU = 1). See details in Notes
• 1*- When the value of eFuse bit EFUSE_DIS_PAD_JTAG is
0, input enabled, pull-up resistor enabled (IE = 1, WPU = 1)
1, input enabled, in high impedance state (IE = 1)
Werecommend pulling high or low GPIO pins in high impedance state to avoid unnecessary power
consumption. You may add pull-up and pull-down resistors in your PCB design referring to Table 14, or enable
internal pull-up and pull-down resistors during software initialization.
Notes
• R-These pins have analog functions.
• USB-GPIO18 and GPIO19 are USB pins. The pull-up value of a USB pin is controlled by the pin’s pull-up
value together with USB pull-up value. If any of the two pull-up values is 1, the pin’s pull-up resistor will be
enabled. The pull-up resistors of USB pins are controlled by USB_SERIAL_JTAG_DP_PULLUP bit.
• G-These pins have glitches during power-up. See details in Table 7.
Espressif Systems
21
Submit Documentation Feedback
ESP32-C3 Series Datasheet v1.4
3 Functional Description
Table 7: PowerUp Glitches on Pins
Pin
Glitch1
Typical Time Period
(ns)
MTCK
Low-level glitch
MTDO
Low-level glitch
5
5
GPIO10
Low-level glitch
5
U0RXD
Low-level glitch
5
GPIO18
High-level glitch
50000
1 Low-level glitch: the pin is at a low level output status during the
time period;
High-level glitch: the pin is at a high level output status during the
time period;
Pull-down glitch: the pin is at an internal weak pulled-down status
during the time period;
Pull-up glitch: the pin is at an internal weak pulled-up status during
the time period.
Please refer to Table 14 for detailed parameters about low/high
level and pull-down/up.
For more information, please refer to Chapter IO MUX and GPIO Matrix (GPIO, IO_MUX) in ESP32-C3 Technical
Reference Manual.
3.4.2 Serial Peripheral Interface (SPI)
ESP32-C3 features three SPI interfaces (SPI0, SPI1, and SPI2). SPI0 and SPI1 can be configured to operate in
SPI memory mode, while SPI2 can be configured to operate in general-purpose SPI modes.
• SPI Memory mode
In SPI memory mode, SPI0 and SPI1 interface with SPI memory. Data are transferred in unit of byte. Up to
four-line STR reads and writes are supported. The clock frequency is configurable to a maximum of 120
MHz in STR mode.
• SPI2 Generalpurpose SPI (GPSPI) mode
When SPI2 acts as a general-purpose SPI, it can operate in master and slave modes. SPI2 supports
two-line full-duplex communication and single-/two-/four-line half-duplex communication in both master
and slave modes. The host’s clock frequency is configurable. Data are transferred in unit of byte. The clock
polarity (CPOL) and phase (CPHA) are also configurable. The SPI2 interface can connect to GDMA.– In master mode, the clock frequency is 80 MHz at most, and the four modes of SPI transfer format are
supported.– In slave mode, the clock frequency is 60 MHz at most, and the four modes of SPI transfer format are
also supported.
The mapping between SPI bus signals and GPIO pins is shown in Table 8:
Espressif Systems
22
Submit Documentation Feedback
ESP32-C3 Series Datasheet v1.4
3 Functional Description
Table 8: Mapping of SPI Signals and Chip Pins
FullDuplex
HalfDuplex
Chip Pin Signal
SPI Signal
SPI Signal
Pin Function
FSPI Signals
MOSI
MOSI
D
MISO
(MISO)
Q
FSPID
FSPIQ
CS
CS
CS
FSPICS0 ~ 5
CLK
CLK
CLK
FSPICLK
—
—
WP
FSPIWP
—
—
HD
FSPIHD
In most cases, the data port connection between ESP32-C3 and external flash is as follows:
Table 9: Connection Between ESP32C3 and External Flash
External Flash Data Port
Chip Pin
SPI SingleLine Mode
SPI TwoLine Mode
SPID (SPID)
DI
IO0
SPI FourLine Mode
SPIQ (SPIQ)
DO
IO1
IO0
IO1
SPIWP (SPIWP)
WP#
—
IO2
SPIHD (SPIHD)
HOLD#
—
For GPIOs assigned to SPI, please refer to Table 10.
IO3
For more information, please refer to Chapter SPI Controller (SPI) in ESP32-C3 Technical Reference
Manual.
3.4.3 Universal Asynchronous Receiver Transmitter (UART)
ESP32-C3 has two UART interfaces, i.e. UART0 and UART1, which support IrDA and asynchronous
communication (RS232 and RS485) at a speed of up to 5 Mbps. The UART controller provides hardware flow
control (CTS and RTS signals) and software flow control (XON and XOFF). Both UART interfaces connect to
GDMAvia UHCI0, and can be accessed by the GDMA controller or directly by the CPU.
For GPIOs assigned to UART, please refer to Table 10.
For more information, please refer to Chapter UART Controller (UART) in ESP32-C3 Technical Reference
Manual.
3.4.4 I2C Interface
ESP32-C3 has an I2C bus interface which is used for I2C master mode or slave mode, depending on your
configuration. The I2C interface supports:
• standard mode (100 Kbit/s)
• fast mode (400 Kbit/s)
• upto 800 Kbit/s (constrained by SCL and SDA pull-up strength)
• 7-bit and 10-bit addressing mode
• double addressing mode
• 7-bit broadcast address
Espressif Systems
23
Submit Documentation Feedback
ESP32-C3 Series Datasheet v1.4
3 Functional Description
You can configure instruction registers to control the I2C interface for more flexibility.
For GPIOs assigned to I2C, please refer to Table 10.
For more information, please refer to Chapter I2C Controller (I2C) in ESP32-C3 Technical Reference
Manual.
3.4.5 I2S Interface
ESP32-C3 includes a standard I2S interface. This interface can operate as a master or a slave in full-duplex
mode or half-duplex mode, and can be configured for 8-bit, 16-bit, 24-bit, or 32-bit serial communication. BCK
clock frequency, from 10 kHz up to 40 MHz, is supported.
The I2S interface connects to the GDMA controller. The interface supports TDM PCM, TDM MSB alignment,
TDM standard, and PDM standard.
For GPIOs assigned to I2S, please refer to Table 10.
For more information, please refer to Chapter I2S Controller (I2S) in ESP32-C3 Technical Reference Manual.
3.4.6 Remote Control Peripheral
The Remote Control Peripheral (RMT) supports two channels of infrared remote transmission and two channels
of infrared remote reception. By controlling pulse waveform through software, it supports various infrared and
other single wire protocols. All four channels share a 192 × 32-bit memory block to store transmit or receive
waveform.
For GPIOs assigned to the Remote Control Peripheral, please refer to Table 10.
For more information, please refer to Chapter Remote Control Peripheral (RMT) in ESP32-C3 Technical Reference
Manual.
3.4.7 LED PWMController
The LED PWMcontroller can generate independent digital waveform on six channels. The LED PWM
controller:
• can generate digital waveform with configurable periods and duty cycle. The accuracy of duty cycle can be
up to 18 bits.
• has multiple clock sources, including APB clock and external main crystal clock.
• can operate when the CPU is in Light-sleep mode.
• supports gradual increase or decrease of duty cycle, which is useful for the LED RGB color-gradient
generator.
For GPIOs assigned to LED PWM, please refer to Table 10.
For more information, please refer to Chapter LED PWM Controller (LEDC) in ESP32-C3 Technical Reference
Manual.
3.4.8 General DMA Controller
ESP32-C3 has a general DMA controller (GDMA) with six independent channels, i.e. three transmit channels and
three receive channels. These six channels are shared by peripherals with DMA feature. The GDMA controller
implements a fixed-priority scheme among these channels, whose priority can be configured.
The GDMA controller controls data transfer using linked lists. It allows peripheral-to-memory and
memory-to-memory data transfer at a high speed. All channels can access internal RAM.
Espressif Systems
24
Submit Documentation Feedback
ESP32-C3 Series Datasheet v1.4
3 Functional Description
Peripherals on ESP32-C3 with DMA feature are SPI2, UHCI0, I2S, AES, SHA, and ADC.
For more information, please refer to Chapter GDMA Controller (GDMA) in ESP32-C3 Technical Reference
Manual.
3.4.9 USB Serial/JTAG Controller
ESP32-C3 integrates a USB Serial/JTAG controller. This controller has the following features:
• CDC-ACMvirtual serial port and JTAG adapter functionality
• USB2.0 full speed compliant, capable of up to 12 Mbit/s transfer speed (Note that this controller does not
support the faster 480 Mbit/s high-speed transfer mode)
• programming embedded/external flash
• CPUdebugging with compact JTAG instructions
• afull-speed USB PHY integrated in the chip
For GPIOs assigned to USB Serial/JTAG, please refer to Table 10.
For more information, please refer to Chapter USB Serial/JTAG Controller (USB_SERIAL_JTAG) in ESP32-C3
Technical Reference Manual.
3.4.10 TWAI® Controller
ESP32-C3 has a TWAI® controller with the following features:
• compatible with ISO 11898-1 protocol (CAN Specification 2.0)
• standard frame format (11-bit ID) and extended frame format (29-bit ID)
• bit rates from 1 Kbit/s to 1 Mbit/s
• multiple modes of operation: Normal, Listen Only, and Self-Test (no acknowledgment required)
• 64-byte receive FIFO
• acceptance filter (single and dual filter modes)
• error detection and handling: error counters, configurable error interrupt threshold, error code capture,
arbitration lost capture
For GPIOs assigned to TWAI, please refer to Table 10.
For more information, please refer to Chapter Two-wire Automotive Interface (TWAI) in ESP32-C3 Technical
Reference Manual.
3.5 Radio and WiFi
ESP32-C3 radio consists of the following blocks:
• 2.4 GHz receiver
• 2.4 GHz transmitter
• bias and regulators
• balun and transmit-receive switch
• clock generator
Espressif Systems
25
Submit Documentation Feedback
ESP32-C3 Series Datasheet v1.4
3 Functional Description
3.5.1 2.4 GHz Receiver
The 2.4 GHz receiver demodulates the 2.4 GHz RF signal to quadrature baseband signals and converts them to
the digital domain with two high-resolution, high-speed ADCs. To adapt to varying signal channel conditions,
ESP32-C3 integrates RF filters, Automatic Gain Control (AGC), DC offset cancelation circuits, and baseband
filters.
3.5.2 2.4 GHz Transmitter
The 2.4 GHz transmitter modulates the quadrature baseband signals to the 2.4 GHz RF signal, and drives the
antenna with a high-powered CMOS power amplifier. The use of digital calibration further improves the linearity of
the power amplifier.
Additional calibrations are integrated to cancel any radio imperfections, such as:
• carrier leakage
• I/Q amplitude/phase matching
• baseband nonlinearities
• RFnonlinearities
• antenna matching
These built-in calibration routines reduce the cost, time, and specialized equipment required for product
testing.
3.5.3 Clock Generator
The clock generator produces quadrature clock signals of 2.4 GHz for both the receiver and the transmitter. All
components of the clock generator are integrated into the chip, including inductors, varactors, filters, regulators
and dividers.
The clock generator has built-in calibration and self-test circuits. Quadrature clock phases and phase noise are
optimized on chip with patented calibration algorithms which ensure the best performance of the receiver and the
transmitter.
3.5.4 WiFi Radio and Baseband
ESP32-C3 Wi-Fi radio and baseband support the following features:
• 802.11b/g/n
• 802.11n MCS0-7 that supports 20 MHz and 40 MHz bandwidth
• 802.11n MCS32
• 802.11n 0.4 µs guard interval
• data rate up to 150 Mbps
• RXSTBC(single spatial stream)
• adjustable transmitting power
• antenna diversity
ESP32-C3 supports antenna diversity with an external RF switch. This switch is controlled by one or more
GPIOs, and used to select the best antenna to minimize the effects of channel imperfections.
Espressif Systems
26
Submit Documentation Feedback
ESP32-C3 Series Datasheet v1.4
3 Functional Description
3.5.5 WiFi MAC
ESP32-C3 implements the full 802.11 b/g/n Wi-Fi MAC protocol. It supports the Basic Service Set (BSS) STA
and SoftAP operations under the Distributed Control Function (DCF). Power management is handled
automatically with minimal host interaction to minimize the active duty period.
ESP32-C3 Wi-Fi MAC applies the following low-level protocol functions automatically:
• 4×virtual Wi-Fi interfaces
• infrastructure BSS in Station mode, SoftAP mode, Station + SoftAP mode, and promiscuous mode
• RTSprotection, CTS protection, Immediate Block ACK
• fragmentation and defragmentation
• TX/RX A-MPDU, TX/RX A-MSDU
• transmit opportunity (TXOP)
• Wi-Fi multimedia (WMM)
• GCMP, CCMP, TKIP, WAPI, WEP, BIP, WPA2-PSK/WPA2-Enterprise, and WPA3-PSK/WPA3-Enterprise
• automatic beacon monitoring (hardware TSF)
• 802.11mc FTM
3.5.6 Networking Features
Espressif provides libraries for TCP/IP networking, ESP-WIFI-MESH networking, and other networking protocols
over Wi-Fi. TLS 1.0, 1.1 and 1.2 is also supported.
3.6 Bluetooth LE
ESP32-C3 includes a Bluetooth Low Energy subsystem that integrates a hardware link layer controller, an
RF/modem block and a feature-rich software protocol stack. It supports the core features of Bluetooth 5 and
Bluetooth mesh.
3.6.1 Bluetooth LE Radio and PHY
Bluetooth Low Energy radio and PHY in ESP32-C3 support:
• 1MbpsPHY
• 2MbpsPHYfor higher data rates
• coded PHY for longer range (125 Kbps and 500 Kbps)
• HWListen before talk (LBT)
3.6.2 Bluetooth LE Link Layer Controller
Bluetooth Low Energy Link Layer Controller in ESP32-C3 supports:
• LEadvertising extensions, to enhance broadcasting capacity and broadcast more intelligent data
• multiple advertisement sets
• simultaneous advertising and scanning
• multiple connections in simultaneous central and peripheral roles
• adaptive frequency hopping and channel assessment
Espressif Systems
27
Submit Documentation Feedback
ESP32-C3 Series Datasheet v1.4
3 Functional Description
• LEchannel selection algorithm #2
• connection parameter update
• high duty cycle non-connectable advertising
• LEprivacy 1.2
• LEdata packet length extension
• link layer extended scanner filter policies
• low duty cycle directed advertising
• link layer encryption
• LEPing
3.7 LowPower Management
With the use of advanced power-management technologies, ESP32-C3 can switch between different power
modes.
• Active mode: CPU and chip radio are powered on. The chip can receive, transmit, or listen.
• Modem-sleep mode: The CPU is operational and the clock speed can be reduced. Wi-Fi base band,
Bluetooth LE base band, and radio are disabled, but Wi-Fi and Bluetooth LE connection can remain active.
• Light-sleep mode: The CPU is paused. Any wake-up events (MAC, host, RTC timer, or external interrupts)
will wake up the chip. Wi-Fi and Bluetooth LE connection can remain active.
• Deep-sleep mode: CPU and most peripherals are powered down. Only the RTC memory is powered on.
Wi-Fi connection data are stored in the RTC memory. The RTC timer or the RTC GPIOs can wake up the
chip from the Deep-sleep mode.
For power consumption in different power modes, please refer to Section 4.6.
3.8 Timers
3.8.1 General Purpose Timers
ESP32-C3 is embedded with two 54-bit general-purpose timers, which are based on 16-bit prescalers and
54-bit auto-reload-capable up/down-timers.
The timers’ features are summarized as follows:
• a16-bit clock prescaler, from 1 to 65536
• a54-bit time-base counter programmable to be incrementing or decrementing
• able to read real-time value of the time-base counter
• halting and resuming the time-base counter
• programmable alarm generation
• level interrupt generation
For more information, please refer to Chapter Timer Group (TIMG) in ESP32-C3 Technical Reference
Manual.
Espressif Systems
28
Submit Documentation Feedback
ESP32-C3 Series Datasheet v1.4
3 Functional Description
3.8.2 System Timer
ESP32-C3 integrates a 52-bit system timer, which has two 52-bit counters and three comparators. The system
timer has the following features:
• counters with a fixed clock frequency of 16 MHz
• three types of independent interrupts generated according to alarm value
• two alarm modes: target mode and period mode
• 52-bit target alarm value and 26-bit periodic alarm value
• automatic reload of counter value
• counters can be stalled if the CPU is stalled or in OCD mode
For more information, please refer to Chapter System Timer (SYSTIMER) in ESP32-C3 Technical Reference
Manual.
3.8.3 Watchdog Timers
For more information, please refer to Chapter Watchdog Timers (WDT) in ESP32-C3 Technical Reference
Manual.
Digital Watchdog Timers
ESP32-C3 contains three digital watchdog timers: one in each of the two timer groups (called Main System
Watchdog Timers, or MWDT) and one in the RTC module (called the RTC Watchdog Timer, or RWDT).
During the flash boot process, RWDT and the MWDT in timer group 0 (TIMG0) are enabled automatically in order
to detect and recover from booting errors.
Digital watchdog timers have the following features:
• four stages, each with a programmable timeout value. Each stage can be configured, enabled and
disabled separately
• interrupt, CPU reset, or core reset for MWDT upon expiry of each stage; interrupt, CPU reset, core reset, or
system reset for RWDT upon expiry of each stage
• 32-bit expiry counter
• write protection, to prevent RWDT and MWDT configuration from being altered inadvertently
• flash boot protection
If the boot process from an SPI flash does not complete within a predetermined period of time, the
watchdog will reboot the entire main system.
Analog Watchdog Timer
ESP32-C3 also has one analog watchdog timer: RTC super watchdog timer (SWD). It is an ultra-low-power
circuit in analog domain that helps to prevent the system from operating in a sub-optimal state and resets the
system if required.
SWDhas the following features:
• Ultra-low power
• Interrupt to indicate that the SWD timeout period is close to expiring
Espressif Systems
29
Submit Documentation Feedback
ESP32-C3 Series Datasheet v1.4
3 Functional Description
• Various dedicated methods for software to feed SWD, which enables SWD to monitor the working state of
the whole operating system
3.9 Cryptographic Hardware Accelerators
ESP32-C3 is equipped with hardware accelerators of general algorithms, such as AES-128/AES-256 (FIPS PUB
197), ECB/CBC/OFB/CFB/CTR (NIST SP 800-38A), SHA1/SHA224/SHA256 (FIPS PUB 180-4), and RSA3072.
The chip also supports independent arithmetic, such as Big Integer Multiplication and Big Integer Modular
Multiplication. The maximum operation length for RSA and Big Integer Modular Multiplication is 3072 bits. The
maximum factor length for Big Integer Multiplication is 1536 bits.
3.10 Physical Security Features
• Transparent external flash encryption (AES-XTS algorithm) with software inaccessible key prevents
unauthorized readout of your application code or data.
• Secure boot feature uses a hardware root of trust to ensure only signed firmware (with RSA-PSS signature)
can be booted.
• HMACmodule can use a software inaccessible MAC key to generate MAC signatures for identity
verification and other purposes.
• Digital Signature module can use a software inaccessible secure key to generate RSA signatures for identity
verification.
• World Controller provides two running environments for software. All hardware and software resources are
sorted to two groups, and placed in either secure or general world. The secure world cannot be accessed
by hardware in the general world, thus establishing a security boundary.
3.11 Peripheral Pin Configurations
Table 10: Peripheral Pin Configurations
Interface
Signal
Pin
Function
ADC
ADC1_CH0
ADC1_CH1
XTAL_32K_P
XTAL_32K_N
ADC1_CH2
GPIO2
ADC1_CH3
GPIO3
ADC1_CH4
MTMS
ADC2_CH0
MTDI
JTAG
MTDI
Two 12-bit SAR ADCs
MTDI
MTCK
MTCK
MTMS
MTMS
MTDO
MTDO
JTAG for software debugging
Espressif Systems
30
Submit Documentation Feedback
ESP32-C3 Series Datasheet v1.4
3 Functional Description
Interface
Signal
Pin
Function
UART
I2C
U0RXD_in
U0CTS_in
U0DSR_in
U0TXD_out
U0RTS_out
U0DTR_out
U1RXD_in
U1CTS_in
U1DSR_in
U1TXD_out
U1RTS_out
U1DTR_out
Any GPIO pins Two UART channels with hardware flow control
and GDMA
I2CEXT0_SCL_in
I2CEXT0_SDA_in
I2CEXT1_SCL_in
I2CEXT1_SDA_in
I2CEXT0_SCL_out
I2CEXT0_SDA_out
I2CEXT1_SCL_out
I2CEXT1_SDA_out
LED PWM
Any GPIO pins One I2C channel in slave or master mode
ledc_ls_sig_out0~5
I2S
Any GPIO pins Six independent PWM channels
I2S0O_BCK_in
I2S_MCLK_in
I2SO_WS_in
I2SI_SD_in
I2SI_BCK_in
I2SI_WS_in
I2SO_BCK_out
I2S_MCLK_out
I2SO_WS_out
I2SO_SD_out
I2SI_BCK_out
I2SI_WS_out
I2SO_SD1_out
Any GPIO pins Stereo input and output from/to the audiocodec
Remote Control
Peripheral
SPI0/1
RMT_SIG_IN0~1
RMT_SIG_OUT0~1
Any GPIO pins Two channels for an IR transceiver of various
waveforms
SPICLK_out_mux
SPICS0_out
SPICLK
SPICS0
SPICS1_out
Any GPIO pins
SPID_in/_out
SPID
SPIQ_in/_out
SPIQ
SPIWP_in/_out
SPIWP
SPIHD_in/_out
SPIHD
Support Standard SPI, Dual SPI, Quad SPI, and
QPI that allow connection to external flash
Espressif Systems
31
Submit Documentation Feedback
ESP32-C3 Series Datasheet v1.4
3 Functional Description
Interface
Signal
Pin
Function
SPI2
FSPICLK_in/_out_mux Any GPIO pins
FSPICS0_in/_out
FSPICS1~5_out
FSPID_in/_out
FSPIQ_in/_out
FSPIWP_in/_out
FSPIHD_in/_out
USB Serial/JTAG USB_D+
• Master mode and slave mode of SPI, Dual
SPI, Quad SPI, and QPI
• Connection to external flash, RAM, and
other SPI devices
• Four modes of SPI transfer format
• Configurable SPI frequency
• 64-byte FIFO or GDMA buffer
GPIO19
USB_D
GPIO18
TWAI
twai_rx
USB-to-serial converter, and USB-to-JTAG
converter
Any GPIO pins Compatible with ISO 11898-1 protocol
twai_tx
twai_bus_off_on
twai_clkout
Espressif Systems
32
Submit Documentation Feedback
ESP32-C3 Series Datasheet v1.4
4 Electrical Characteristics
4. Electrical Characteristics
4.1 Absolute Maximum Ratings
Stresses beyond the absolute maximum ratings listed in the table below may cause permanent damage to the
device. These are stress ratings only, and do not refer to the functional operation of the device.
Table 11: Absolute Maximum Ratings
Symbol
Parameter Min
VDDA, VDD3P3, VDD3P3_RTC,
VDD3P3_CPU, VDD_SPI
Voltage applied to power supply pins
per power domain
Max Unit–0.3
TSTORE
Storage temperature
3.6
V–40
4.2 Recommended Operating Conditions
Table 12: Recommended Operating Conditions
Symbol
150
°C
Parameter Min Typ
Max Unit
VDDA, VDD3P3
VDD3P3_RTC
VDD_SPI (working as
input power supply)1
Voltage applied to power supply pins per
power domain
—
3.0
3.3
3.6
V
3.0
VDD3P3_CPU2,3
Voltage applied to power supply pin
3.0
3.3
3.6
V
3.3
IV DD4
Current delivered by external power supply
0.5
3.6
V
— — A
ESP32-C3
TA
Operating ambient
temperature
ESP32-C3FN4
105–40
—
85
°C
ESP32-C3FH4
105
1 For more information, please refer to Section 2.3 Power Scheme.
2 When VDD_SPI is used to drive peripherals, VDD3P3_CPU should comply with the peripherals’ speci
fications. For more information, please refer to Table 13.
3 To write eFuse, VDD3P3_CPU should not be higher than 3.3 V.
4 If you use a single power supply, the recommended output current is 500 mA or more.
4.3 VDD_SPI Output Characteristics
Table 13: VDD_SPI Output Characteristics
Symbol
Parameter
RSPI
On-resistance in 3.3 V mode
Typ
Unit
7.5
Espressif Systems
33
Submit Documentation Feedback
Ω
ESP32-C3 Series Datasheet v1.4
4 ElectricalCharacteristics
Note:
Inreal-lifeapplications,whenVDD_SPIworks in3.3Voutputmode, VDD3P3_CPUmaybeaffectedbyRSPI. For
example,whenVDD3P3_CPUisusedtodrivea3.3Vflash, itshouldcomplywiththefollowingspecifications:
VDD3P3_CPU>VDD_flash_min+I_flash_max*RSPI
Amongwhich,VDD_flash_ministheminimumoperatingvoltageof theflash,andI_flash_maxthemaximumcurrent.
Formoreinformation,pleaserefertosection2.3PowerScheme.
4.4 DCCharacteristics(3.3V,25°C)
Table14:DCCharacteristics(3.3V,25°C)
Symbol Parameter Min Typ Max Unit
CIN Pincapacitance — 2 — pF
VIH High-level inputvoltage 0.75×VDD1 — VDD1+0.3 V
VIL Low-level inputvoltage–0.3 — 0.25×VDD1 V
IIH High-level inputcurrent — — 50 nA
IIL Low-level inputcurrent — — 50 nA
VOH2 High-leveloutputvoltage 0.8×VDD1 — — V
VOL2 Low-leveloutputvoltage — — 0.1×VDD1 V
IOH
High-levelsourcecurrent (VDD1=3.3V,
VOH>=2.64V,PAD_DRIVER=3) — 40 — mA
IOL
Low-levelsinkcurrent (VDD1=3.3V,VOL=
0.495V,PAD_DRIVER=3) — 28 — mA
RPU Pull-upresistor — 45 — kΩ
RPD Pull-downresistor — 45 — kΩ
VIH_nRST Chipresetreleasevoltage 0.75×VDD1 — VDD1+0.3 V
VIL_nRST Chipresetvoltage–0.3 — 0.25×VDD1 V
1VDDistheI/Ovoltageforaparticularpowerdomainofpins.
2VOHandVOLaremeasuredusinghigh-impedanceload.
4.5 ADCCharacteristics
Table15:ADCCharacteristics
Symbol Parameter Min Max Unit
DNL(Differentialnonlinearity)1
ADCconnectedtoanexternal–7 7 LSB 100nFcapacitor;DCsignal input;
INL(Integralnonlinearity) ambienttemperatureat25°C;–12 12 LSB Wi-Fioff
Samplingrate — — 100 kSPS2
1TogetbetterDNLresults,youcansamplemultipletimesandapplyafilter,orcalculatetheaveragevalue.
2kSPSmeanskilosamples-per-second.
EspressifSystems 34
SubmitDocumentationFeedback
ESP32-C3SeriesDatasheetv1.4
4 Electrical Characteristics
The calibrated ADC results after hardware calibration + software calibration are shown in Table 16. For higher
accuracy, you may implement your own calibration methods.
Table 16: ADC Calibration Results
Parameter
Description Min Max
ATTEN0, effective measurement range of 0 ~ 750
Unit–10
ATTEN1, effective measurement range of 0 ~ 1050
Total error–10
10
10
mV
mV
ATTEN2, effective measurement range of 0 ~ 1300–10
ATTEN3, effective measurement range of 0 ~ 2500
10
mV–35
4.6 Current Consumption
35
mV
The current consumption measurements are taken with a 3.3 V supply at 25 °C of ambient temperature at the RF
port. All transmitters’ measurements are based on a 100% duty cycle.
4.6.1 RF Current Consumption in Active Mode
Table 17: Current Consumption Depending on RF Modes
Work mode
Description
802.11b, 1 Mbps, @21 dBm
Peak (mA)
802.11g, 54 Mbps, @19 dBm
TX
Active (RF working)
335
285
802.11n, HT20, MCS7, @18.5 dBm
276
802.11n, HT40, MCS7, @18.5 dBm
278
802.11b/g/n, HT20
RX
84
802.11n, HT40
87
4.6.2 Current Consumption in Other Modes
Table 18: Current Consumption in Modemsleep Mode
CPUFrequency
(MHz)
Mode
Typ
Description
All Peripherals Clocks
Disabled (mA)
All Peripherals Clocks
Enabled (mA)1
CPU is running
160
Modem-sleep2,3
23
28
CPU is idle
16
21
CPU is running
80
17
22
CPU is idle
13
18
1 In practice, the current consumption might be different depending on which peripherals are enabled.
2 In Modem-sleep mode, Wi-Fi is clock gated.
3 In Modem-sleep mode, the consumption might be higher when accessing flash. For a flash rated at 80
Mbit/s, in SPI 2-line mode the consumption is 10 mA.
Espressif Systems
35
Submit Documentation Feedback
ESP32-C3 Series Datasheet v1.4
4 ElectricalCharacteristics
Table19:CurrentConsumptioninLowPowerModes
Mode Description Typ(µA)
Light-sleep VDD_SPIandWi-Fiarepowereddown,andallGPIOsarehigh-impedance 130
Deep-sleep RTCtimer+RTCmemory 5
Poweroff CHIP_ENissettolowlevel,thechipispoweredoff 1
4.7 Reliability
Table20:ReliabilityQualifications
TestItem TestConditions TestStandard
HTOL(HighTemperature
OperatingLife) 125°C,1000hours JESD22-A108
ESD(Electro-Static
DischargeSensitivity)
HBM(HumanBodyMode)1±2000V JS-001
CDM(ChargeDeviceMode)2±1000V JS-002
Latchup Currenttrigger±200mA JESD78 Voltagetrigger1.5×VDDmax
Preconditioning
Bake24hours@125°C
Moisturesoak(level3:192hours@30°C,60%RH)
IRreflowsolder:260+0°C,20seconds,threetimes
J-STD-020,JESD47,
JESD22-A113
TCT(TemperatureCycling
Test)–65°C/150°C,500cycles JESD22-A104
uHAST(Highly
AcceleratedStressTest,
unbiased)
130°C,85%RH,96hours JESD22-A118
HTSL(HighTemperature
StorageLife) 150°C,1000hours JESD22-A103
LTSL(LowTemperature
StorageLife)–40°C,1000hours JESD22-A119
1JEDECdocumentJEP155statesthat500VHBMallowssafemanufacturingwithastandardESDcontrolprocess.
2JEDECdocumentJEP157statesthat250VCDMallowssafemanufacturingwithastandardESDcontrolprocess.
4.8 WiFiRadio
Table21:WiFiFrequency
Min Typ Max
Parameter (MHz) (MHz) (MHz)
Centerfrequencyofoperatingchannel 2412 — 2484
EspressifSystems 36
SubmitDocumentationFeedback
ESP32-C3SeriesDatasheetv1.4
4 ElectricalCharacteristics
4.8.1 WiFiRFTransmitter(TX)Specifications
Table22:TXPowerwithSpectralMaskandEVMMeeting802.11Standards
Min Typ Max
Rate (dBm) (dBm) (dBm)
802.11b,1Mbps — 21.0 —
802.11b,11Mbps — 21.0 —
802.11g,6Mbps — 21.0 —
802.11g,54Mbps — 19.0 —
802.11n,HT20,MCS0 — 20.0 —
802.11n,HT20,MCS7 — 18.5 —
802.11n,HT40,MCS0 — 20.0 —
802.11n,HT40,MCS7 — 18.5 —
Table23:TXEVMTest
Min Typ SL1
Rate (dB) (dB) (dB)
802.11b,1Mbps,@21dBm —–24.5–10
802.11b,11Mbps,@21dBm —–25.0–10
802.11g,6Mbps,@21dBm —–23.0–5
802.11g,54Mbps,@19dBm —–27.5–25
802.11n,HT20,MCS0,@20dBm —–22.5–5
802.11n,HT20,MCS7,@18.5dBm —–29.0–27
802.11n,HT40,MCS0,@20dBm —–22.5–5
802.11n,HT40,MCS7,@18.5dBm —–28.0–27
1SLstandsforstandardlimitvalue.
4.8.2 WiFiRFReceiver(RX)Specifications
Table24:RXSensitivity
Min Typ Max
Rate (dBm) (dBm) (dBm)
802.11b,1Mbps —–98.4 —
802.11b,2Mbps —–96.0 —
802.11b,5.5Mbps —–93.0 —
802.11b,11Mbps —–88.6 —
802.11g,6Mbps —–93.8 —
802.11g,9Mbps —–92.2 —
802.11g,12Mbps —–91.0 —
802.11g,18Mbps —–88.4 —
802.11g,24Mbps —–85.8 —
802.11g,36Mbps —–82.0 —
Cont’donnextpage
EspressifSystems 37
SubmitDocumentationFeedback
ESP32-C3SeriesDatasheetv1.4
4 ElectricalCharacteristics
Table24–cont’dfrompreviouspage
Min Typ Max
Rate (dBm) (dBm) (dBm)
802.11g,48Mbps —–78.0 —
802.11g,54Mbps —–76.6 —
802.11n,HT20,MCS0 —–93.6 —
802.11n,HT20,MCS1 —–90.8 —
802.11n,HT20,MCS2 —–88.4 —
802.11n,HT20,MCS3 —–85.0 —
802.11n,HT20,MCS4 —–81.8 —
802.11n,HT20,MCS5 —–77.8 —
802.11n,HT20,MCS6 —–76.0 —
802.11n,HT20,MCS7 —–74.8 —
802.11n,HT40,MCS0 —–90.0 —
802.11n,HT40,MCS1 —–88.0 —
802.11n,HT40,MCS2 —–85.2 —
802.11n,HT40,MCS3 —–82.0 —
802.11n,HT40,MCS4 —–78.8 —
802.11n,HT40,MCS5 —–74.6 —
802.11n,HT40,MCS6 —–73.0 —
802.11n,HT40,MCS7 —–71.4 —
Table25:MaximumRXLevel
Min Typ Max
Rate (dBm) (dBm) (dBm)
802.11b,1Mbps — 5 —
802.11b,11Mbps — 5 —
802.11g,6Mbps — 5 —
802.11g,54Mbps — 0 —
802.11n,HT20,MCS0 — 5 —
802.11n,HT20,MCS7 — 0 —
802.11n,HT40,MCS0 — 5 —
802.11n,HT40,MCS7 — 0 —
Table26:RXAdjacentChannelRejection
Min Typ Max
Rate (dB) (dB) (dB)
802.11b,1Mbps — 35 —
802.11b,11Mbps — 35 —
802.11g,6Mbps — 31 —
802.11g,54Mbps — 20 —
802.11n,HT20,MCS0 — 31 —
Cont’donnextpage
EspressifSystems 38
SubmitDocumentationFeedback
ESP32-C3SeriesDatasheetv1.4
4 ElectricalCharacteristics
Table26–cont’dfrompreviouspage
Min Typ Max
Rate (dB) (dB) (dB)
802.11n,HT20,MCS7 — 16 —
802.11n,HT40,MCS0 — 25 —
802.11n,HT40,MCS7 — 11 —
4.9 BluetoothLERadio
Table27:BluetoothLEFrequency
Min Typ Max Parameter (MHz) (MHz) (MHz)
Centerfrequencyofoperatingchannel 2402 — 2480
4.9.1 BluetoothLERFTransmitter(TX)Specifications
Table28:TransmitterCharacteristics BluetoothLE1Mbps
Parameter Description Min Typ Max Unit
RFtransmitpower RFpowercontrol range–24.00 0 21.00 dBm
Gaincontrolstep — 3.00 — dB
Carrierfrequencyoffsetanddrift
Max|fn|n=0,1,2,..k — 17.00 — kHz
Max|f0−fn| — 1.75 — kHz
Max|fn−fn−5| — 1.46 — kHz
|f1−f0| — 0.80 — kHz
Modulationcharacteristics
∆f1avg — 250.00 — kHz
Min∆f2max (for at least
99.9%ofall∆f2max) — 190.00 — kHz
∆f2avg/∆f1avg — 0.83 — —
In-bandspuriousemissions
±2MHzoffset —–37.62 — dBm
±3MHzoffset —–41.95 — dBm
>±3MHzoffset —–44.48 — dBm
Table29:TransmitterCharacteristics BluetoothLE2Mbps
Parameter Description Min Typ Max Unit
RFtransmitpower RFpowercontrol range–24.00 0 21.00 dBm
Gaincontrolstep — 3.00 — dB
Carrierfrequencyoffsetanddrift
Max|fn|n=0,1,2,..k — 20.80 — kHz
Max|f0−fn| — 1.30 — kHz
Max|fn−fn−5| — 1.33 — kHz
|f1−f0| — 0.70 — kHz
Modulationcharacteristics
∆f1avg — 498.00 — kHz
Cont’donnextpage
EspressifSystems 39
SubmitDocumentationFeedback
ESP32-C3SeriesDatasheetv1.4
4 ElectricalCharacteristics
Table29–cont’dfrompreviouspage
Parameter Description Min Typ Max Unit
Min∆f2max (for at least
99.9%ofall∆f2max) — 430.00 — kHz
∆f2avg/∆f1avg — 0.93 — —
In-bandspuriousemissions
±4MHzoffset —–43.55 — dBm
±5MHzoffset —–45.26 — dBm
>±5MHzoffset —–45.26 — dBm
Table30:TransmitterCharacteristics BluetoothLE125Kbps
Parameter Description Min Typ Max Unit
RFtransmitpower RFpowercontrol range–24.00 0 21.00 dBm
Gaincontrolstep — 3.00 — dB
Carrierfrequencyoffsetanddrift
Max|fn|n=0,1,2,..k — 17.50 — kHz
Max|f0−fn| — 0.45 — kHz
|fn−fn−3| — 0.70 — kHz
|f0−f3| — 0.30 — kHz
Modulationcharacteristics
∆f1avg — 250.00 — kHz
Min∆f1max (for at least
99.9%ofall∆f2max) — 235.00 — kHz
In-bandspuriousemissions
±2MHzoffset —–37.90 — dBm
±3MHzoffset —–41.00 — dBm
>±3MHzoffset —–42.50 — dBm
Table31:TransmitterCharacteristics BluetoothLE500Kbps
Parameter Description Min Typ Max Unit
RFtransmitpower RFpowercontrol range–24.00 0 21.00 dBm
Gaincontrolstep — 3.00 — dB
Carrierfrequencyoffsetanddrift
Max|fn|n=0,1,2,..k — 17.00 — kHz
Max|f0−fn| — 0.88 — kHz
|fn−fn−3| — 1.00 — kHz
|f0−f3| — 0.20 — kHz
Modulationcharacteristics
∆f2avg — 208.00 — kHz
Min∆f2max (for at least
99.9%ofall∆f2max) — 190.00 — kHz
In-bandspuriousemissions
±2MHzoffset —–37.90 — dBm
±3MHzoffset —–41.30 — dBm
>±3MHzoffset —–42.80 — dBm
4.9.2 BluetoothLERFReceiver(RX)Specifications
EspressifSystems 40
SubmitDocumentationFeedback
ESP32-C3SeriesDatasheetv1.4
4 Electrical Characteristics
Table 32: Receiver Characteristics Bluetooth LE 1 Mbps
Parameter
Description
Min T
Sensitivity @30.8% PER
—
yp Max
Unit
—–97 — dBm
Maximum received signal @30.8% PER —
—
5
Co-channel C/I
—
—
— dBm
8
F =F0+1MHz
—–3
— dB
F =F0–1MHz
— dB
—–4
F =F0+2MHz
—–31 — dB
Adjacent channel selectivity C/I
Image frequency
— dB
—–29 — dB
F =F0–2MHz
F =F0+3MHz
F =F0–3MHz
—–33 — dB
—–27 — dB
F ≥F0+4MHz
F ≤F0–4MHz
—–29 — dB
—–38 — dB
—
Adjacent channel to image frequency
F =Fimage + 1 MHz
—–29 — dB
—–41 — dB
F =Fimage– 1 MHz
—–33 — dB
30 MHz ~2000 MHz
—–5
2003 MHz ~ 2399 MHz
Out-of-band blocking performance
Intermodulation
— dBm
—–18 — dBm
2484 MHz ~ 2997 MHz
3000 MHz ~ 12.75 GHz
—–15 — dBm
—–5
—
— dBm
—–30 — dBm
Table 33: Receiver Characteristics Bluetooth LE 2 Mbps
Parameter
Description
Min T
Sensitivity @30.8% PER
—
yp Max
Unit
—–93 — dBm
Maximum received signal @30.8% PER —
—
3
Co-channel C/I
—
— dBm
— 10 — dB
F =F0+2MHz
—–7
F =F0–2MHz
— dB
—–7
F =F0+4MHz
—–26 — dB
Adjacent channel selectivity C/I
Image frequency
— dB
—–28 — dB
F =F0–4MHz
F =F0+6MHz
F =F0–6MHz
—–26 — dB
—–27 — dB
F ≥F0+8MHz
F ≤F0–8MHz
—–29 — dB
—–28 — dB
—
Adjacent channel to image frequency
F =Fimage + 2 MHz
—–28 — dB
—–26 — dB
F =Fimage– 2 MHz
—–7
30 MHz ~2000 MHz
—–5
— dB
2003 MHz ~ 2399 MHz
Out-of-band blocking performance
Intermodulation
— dBm
—–19 — dBm
2484 MHz ~ 2997 MHz
3000 MHz ~ 12.75 GHz
—–16 — dBm
—–5
—
— dBm
—–29 — dBm
Espressif Systems
41
Submit Documentation Feedback
ESP32-C3 Series Datasheet v1.4
4 Electrical Characteristics
Table 34: Receiver Characteristics Bluetooth LE 125 Kbps
Parameter
Description
Min T
yp Max
Sensitivity @30.8% PER
—
Unit
—–105
Maximum received signal @30.8% PER —
—
— dBm
5
Co-channel C/I
—
—
— dBm
3
F =F0+1MHz
—–6
— dB
F =F0–1MHz
— dB
—–6
F =F0+2MHz
—–43 — dB
Adjacent channel selectivity C/I
Image frequency
— dB
—–33 — dB
F =F0–2MHz
F =F0+3MHz
F =F0–3MHz
—–37 — dB
—–47 — dB
F ≥F0+4MHz
F ≤F0–4MHz
—–40 — dB
—–50 — dB
—
Adjacent channel to image frequency
F =Fimage + 1 MHz
—–40 — dB
—–50 — dB
F =Fimage– 1 MHz
—–37 — dB
Table 35: Receiver Characteristics Bluetooth LE 500 Kbps
Parameter
Description
Min T
yp Max
Sensitivity @30.8% PER
—
Unit
—–100
Maximum received signal @30.8% PER —
—
— dBm
5
Co-channel C/I
—
—
— dBm
3
F =F0+1MHz
—–2
— dB
F =F0–1MHz
— dB
—–3
F =F0+2MHz
—–33 — dB
Adjacent channel selectivity C/I
Image frequency
— dB
—–32 — dB
F =F0–2MHz
F =F0+3MHz
F =F0–3MHz
—–23 — dB
—–40 — dB
F ≥F0+4MHz
F ≤F0–4MHz
—–34 — dB
—–44 — dB
—
Adjacent channel to image frequency
F =Fimage + 1 MHz
—–34 — dB
—–46 — dB
F =Fimage– 1 MHz
—–23 — dB
Espressif Systems
42
Submit Documentation Feedback
ESP32-C3 Series Datasheet v1.4
5 PackageInformation
5. PackageInformation
Figure9:QFN32(5×5mm)Package
Note:
• Thesourcefileof recommendedPCBlandpatternisprovidedforyour reference. YoucanviewitwithAutodesk
Viewer;
• ForreferencePCBlayout,pleaserefertoESP32-C3HardwareDesignGuidelines;
• For informationabouttape,reel,andproductmarking,pleaserefertoEspressifChipPackagingInformation.
EspressifSystems 43
SubmitDocumentationFeedback
ESP32-C3SeriesDatasheetv1.4
6 Related Documentation and Resources
6. Related Documentation and Resources
Related Documentation
• ESP32-C3TechnicalReferenceManual–DetailedinformationonhowtousetheESP32-C3memoryandperipherals.
• ESP32-C3HardwareDesignGuidelines– GuidelinesonhowtointegratetheESP32-C3intoyourhardwareproduct.
• ESP32-C3 Series SoC Errata– Descriptions of known errors in ESP32-C3 series of SoCs.
• Certificates
https://espressif.com/en/support/documents/certificate