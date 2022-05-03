#include <Arduino.h>
#include <ADC_Read.h>
#include "FILTER.h"

ADC adc_ldr;

FILTER butter;
FILTER iir_hpf;
FILTER mov_avg;

const byte ADC_PIN = 25;
float input_reading = 0;
float input_volts, out;
int i=0;
const int max_samples = 5000;
float signal_readings[max_samples];



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  float b_butter[3] = {0.0055, 0.0111, 0.0055};
  float a_butter[3] = {1, -1.7786, 0.8008};
  int order_butter = 0;

  float b_iir_hpf[3] = {0.0055, 0.0111, 0.0055};
  float a_iir_hpf[3] = {1, -1.8630, 0.8677};
  int order_iir_hpf = 0;

  float b_mov_avg[4] = {0.0055, 0.0111, 0.0055, 0.005};
  float a_mov_avg[4] = {1, -1.8630, 0.8677, 0.005};
  int order_mov_avg = 3;

 // butter.setup(b_butter, a_butter, order_butter);
 // iir_hpf.setup(b_iir_hpf, a_iir_hpf, order_iir_hpf);
  mov_avg.setup(b_mov_avg, a_mov_avg, order_mov_avg, 4, 4);


  //pinMode(adc_1, INPUT);
  //Serial.write(13);
  
  adc_ldr.begin(ADC_PIN, 12, 3.3F);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  input_reading = adc_ldr.readRaw();
  //Serial.write(to_string(input_reading));
  //out = mov_avg.filter(input_reading);
  Serial.println(mov_avg.filter(input_reading));
  //Serial.print("HOLA");
  Serial.println(input_reading);
}