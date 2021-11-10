//***************************************
// Universidad del Valle de Guatemala
// Electrónica Digital 2
// Proyecto 1 - Sensor de Temperatura
// Nombre: Alessandro Paiz
// Carné: 19572
//***************************************

//****************************************
// Librerías
//****************************************
#include <Arduino.h>

//****************************************
// Defincion de Pines
//****************************************
#define pinLM35 35

//****************************************
// Prototipo de Funciones
//****************************************
void EMAADC(void);
void RecibirValor(void);

//****************************************
// Variables Globales
//****************************************
// Variables ADC
int adcRaw = 0;
double adcFiltradoT = 0;
double alpha = 0.09;
float celsius = 0.0;

String sensorb1 = ""; // Guardar valor obtenido cuando se pulso el boton en Tiva C

int estadob1 = 0;
//****************************************
// ISRs
//****************************************

//****************************************
// Configuracion
//****************************************
void setup()
{
  Serial.begin(115200);
  Serial2.begin(115200);
}
//****************************************
// Loop Principal
//****************************************
void loop()
{
  RecibirValor();
}
//****************************************
// Funciones
//****************************************
void EMAADC(void)
{
  adcRaw = analogReadMilliVolts(pinLM35);
  adcFiltradoT = (alpha * adcRaw) + ((1.0 - alpha) * adcFiltradoT);
  celsius = (adcFiltradoT / 10.0);
  Serial2.println(celsius);
  Serial.print("Temperatura: ");
  Serial.println(celsius);
}

