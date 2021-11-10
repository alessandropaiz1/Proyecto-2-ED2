//***************************************************************************************************************************************
/* Universidad del Valle de Guatemala
   Electrónica Digital 2
   Proyecto 1 - Sensor de Temperatura
   Nombre: Alessandro Paiz
   Carné: 19572
*/
//***************************************************************************************************************************************

//***************************************************************************************************************************************
// Librerías
//***************************************************************************************************************************************

#include <Arduino.h>

#include <SPI.h>
#include <SD.h>

File archivo;

#include <stdint.h>
#include <stdbool.h>
#include <TM4C123GH6PM.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/rom_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"

#include "bitmaps.h"
#include "font.h"
#include "lcd_registers.h"
#include "pitches.h"


