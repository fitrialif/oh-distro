# pavlo irobot 2012

# use config.h
USE_CONFIG_H = yes

# MCU
MCU = atxmega32a4u
#MCU = atxmega32a4

# Clock Speed
F_CPU = 32000000

# Programmer settings
OVERRIDE_AVRDUDE_PROGRAMMER = yes
AVRDUDE_PROGRAMMER = avrispmkII
AVRDUDE_PORT = usb

# Fuse settings
AVRDUDE_FUSES =
# If you wish to override the default fuse settings
# determined in main Makefile, change them here
# and then uncomment OVERRIDE_AVRDUDE_FUSES
# See XMega A series datasheet (Atmel doc8077) section 4.16

# Fuse byte 0: JTAG User ID
# If a custom JTAG User ID is required, uncomment
# and set it here
#AVRDUDE_FUSES += -U fuse0:w:0x00:m

# Fuse byte 1: Watchdog
# Set WDPER and WDWPER
# See datasheet sections 4.16.2, 11.7.1, and 11.7.2
# for more information
AVRDUDE_FUSES += -U fuse1:w:0x77:m

# Fuse byte 2: Reset configuration
# Spike detector, reset vector location, and BOD
# in power down configuration
# See datasheet section 4.16.3 for more information
AVRDUDE_FUSES += -U fuse2:w:0xBF:m

# There is no fuse byte 3.....

# Fuse byte 4: Start-up configuration
# See datasheet section 4.16.4
# Configures external reset disable, start-up time,
# watchdog timer lock, and jtag disable
AVRDUDE_FUSES += -U fuse4:w:0xF7:m

# Fuse byte 5
# See datasheet section 4.16.5
# Configures BOD operation in active mode,
# EEPROM preserved through chip erase, and
# BOD detection leven
AVRDUDE_FUSES += -U fuse5:w:0xE1:m

# Lock byte
# See datasheet section 4.16.6
# Lock bits for boot loader, application,
# and application table sections via internal
# SPM commands and external programming interface
#AVRDUDE_FUSES += -U lock:w:0xBF:m

# Write user sig row (256 bytes max)
# Uncomment to initialize user sig row with custom data
##AVRDUDE_USERSIG = -U usersig:w:0x01,0x02,0x03:m
##AVRDUDE_USERSIG = -U usersig:w:filename
#AVRDUDE_USERSIG = -U usersig:w:...:m

# Uncomment to override default fuse configurations
# from main Makefile
OVERRIDE_AVRDUDE_FUSES = yes

# XBoot settings

# AVR1008 fixes
# Really only applicable to XMEGA 256a3 rev A and B devices
#USE_AVR1008_EEPROM = yes

# Entry
USE_ENTER_DELAY = yes
USE_ENTER_UART = yes

# Exit
#LOCK_SPM_ON_EXIT = yes

# Communication
USE_LED = yes
USE_UART = yes
USE_UART_EN_PINS = yes
#USE_UART_EN_PIN = yes

# General Options
#USE_WATCHDOG = yes

# Bootloader Features
ENABLE_BLOCK_SUPPORT = yes
ENABLE_FLASH_BYTE_SUPPORT = yes
ENABLE_EEPROM_BYTE_SUPPORT = yes
ENABLE_LOCK_BITS = yes
ENABLE_FUSE_BITS = yes
ENABLE_FLASH_ERASE_WRITE = yes
ENABLE_CRC_SUPPORT = yes

# ENTER_DELAY
ENTER_BLINK_COUNT     = 127
ENTER_BLINK_WAIT      = 80000
#blink count must not exceed 127
#blink wait is 32bit
#32MHz, 50,000=72msec
#32MHz, 90,000=132msec
#32MHz, 160,000=236msec (30sec total)
#32MHz, 80,000=118msec (15sec total)

# ENTER_UART
ENTER_UART_NEED_SYNC = yes
ENTER_UART_NEED_SUPER_SYNC = yes
ENTER_UART_SUPER_SYNC_COUNT = 10

# LED
LED_PORT_NAME         = C
LED_PIN               = 7
LED_INV               = 0

# UART
# Select BAUD rate, port name, and UART number
#UART_BAUD_RATE        = 115200
UART_BAUD_RATE        = 38400
UART_PORT_NAME        = D
UART_NUMBER           = 0
#UART_RX_PUEN          = yes

# UART RS485 Enable Output
UART_EN_PIN1_PORT_NAME = D
UART_EN_PIN1           = 0
UART_EN_PIN2_PORT_NAME = D
UART_EN_PIN2           = 1
UART_EN_PIN_INV        = 0

#below this is unused, but needs to be defined
WATCHDOG_TIMEOUT      = WDT_PER_1KCLK_gc
# I2C
I2C_DEVICE_PORT       = C
I2C_ADDRESS           = 0x10
# FIFO
FIFO_DATA_PORT_NAME   = C
FIFO_CTL_PORT_NAME    = D
FIFO_RXF_N_bm         = (1<<3)
FIFO_TXE_N_bm         = (1<<2)
FIFO_RD_N_bm          = (1<<1)
FIFO_WR_N_bm          = (1<<0)


