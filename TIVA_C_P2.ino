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


//****************************************
// Defincion de Pines
//****************************************

//Botones
#define b1   PF_4    // B1 se utiliza para solicitar dato del sensor conectado al ESP32
#define b2   PF_0    // B2 se utiliza para guardar el dato recibido en la memoria SD

#define LCD_RST PD_0
#define LCD_CS PD_1
#define LCD_RS PD_2
#define LCD_WR PD_3
#define LCD_RD PE_1
#define NOTE_C4_1 260

int DPINS[] = {PB_0, PB_1, PB_2, PB_3, PB_4, PB_5, PB_6, PB_7};
//***************************************************************************************************************************************
// Functions Prototypes
//***************************************************************************************************************************************
void LCD_Init(void);
void LCD_CMD(uint8_t cmd);
void LCD_DATA(uint8_t data);
void SetWindows(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
void LCD_Clear(unsigned int c);
void H_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c);
void V_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c);
void Rect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int c);
void FillRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int c);
void LCD_Print(String text, int x, int y, int fontSize, int color, int background);

void LCD_Bitmap(unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned char bitmap[]);
void LCD_Sprite(int x, int y, int width, int height, unsigned char bitmap[], int columns, int index, char flip, char offset);

void sensor(void); // Función recibir valor del otro microcontrolador si existe
void UART(void);    //Función de comunicación USART con computadora
void RecibirDatoyEnviar(void); // Funcion para recibir valor del ESP32 al pulsar boton
void EscribirSD (void);
void SonidoB1 (void);
void SonidoB2 (void);
