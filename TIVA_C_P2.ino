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

extern uint8_t fondo[];
extern uint8_t clima[];
extern uint8_t lluvia[];
extern uint8_t SignoCelsius[];
extern uint8_t sollluvia[];
extern uint8_t solnubeviento[];

//***************************************************************************************************************************************
// Variables Globales
//***************************************************************************************************************************************
String sensorT = "";
int estadob1 = 0;
int buzzerPin = PF_1;

int SB1[] = {
   NOTE_E4,NOTE_D4};
   
int DuracionS1[] = {
  4, 4};

int SB2[] = {
   NOTE_C4_1,NOTE_F4};
   
int DuracionS2[] = {
  4, 4};


//***************************************************************************************************************************************
// Inicialización
//***************************************************************************************************************************************
void setup() {
  SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
  Serial.begin(115200);
  Serial2.begin(115200);
  GPIOPadConfigSet(GPIO_PORTB_BASE, 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7, GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD_WPU);
  Serial.println("Inicio");
  LCD_Init();
  LCD_Clear(0xFFFF);
  FillRect(0, 0, 320, 240, 0x765E);
  FillRect(4, 5, 20, 4, 0xFFFF);
  FillRect(4, 13, 20, 4, 0xFFFF);
  FillRect(4, 21, 20, 4, 0xFFFF);
  FillRect(0, 140, 340, 1, 0xFFFF);
  
  String text1 = "Chiquimula, Guatemala";
  LCD_Print(text1, 120, 50, 1, 0xFFFF, 0x765E);

//  String text2 = "27.5"; 
  
  LCD_Bitmap(40, 65, 64, 64, clima);
  
  LCD_Bitmap(30, 150, 32, 32, lluvia);

  String Lunes = "Lun";
  LCD_Print(Lunes, 33, 190, 1, 0xFFFF, 0x765E);
  
  LCD_Bitmap(90, 145, 32, 32, sollluvia);

  String Martes = "Mar";
  LCD_Print(Martes, 96, 190, 1, 0xFFFF, 0x765E);

  
  LCD_Bitmap(155, 145, 32, 32, solnubeviento);

  String Miercoles = "Mie";
  LCD_Print(Miercoles, 155, 190, 1, 0xFFFF, 0x765E);
  
  LCD_Bitmap(210, 145, 32, 32, sollluvia);

  String Jueves = "Jue";
  LCD_Print(Jueves, 215, 190, 1, 0xFFFF, 0x765E);
  
  LCD_Bitmap(270, 150, 32, 32, lluvia);

  String Viernes = "Vie";
  LCD_Print(Viernes, 275, 190, 1, 0xFFFF, 0x765E);

  String Indicador = "Parcialmente nublado";
  LCD_Print(Indicador, 120, 120, 1, 0xFFFF, 0x765E);

  SPI.setModule(0);
    // Estamos Inicializando la tarjeta SD
  if (!SD.begin(PA_3)) {
    Serial.println("initialization failed!");
    return;
  }
  
  pinMode(PA_3, OUTPUT);
  pinMode(b1, INPUT_PULLUP);
  pinMode(b2, INPUT_PULLUP);

}
