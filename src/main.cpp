#include <Arduino.h>
#include <ADC_Read.h>
#include "FILTER.h"

ADC adc_ldr;

FILTER butter;
FILTER iir_hpf;
FILTER mov_avg;

const byte ADC_PIN = 25;
float input_reading = 0;
float out_signals[3];
double start_time;
float fs = 5000;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  float b_butter[3] = {0.0055, 0.0111, 0.0055};
  float a_butter[3] = {1, -1.7786, 0.8008};

  float b_iir_hpf[3] = {1, -2, 1};
  float a_iir_hpf[3] = {1, -1.8630, 0.8677};

  float b_mov_avg[4] = {0.25, 0.25, 0.25, 0.25};
  float a_mov_avg[1] = {1};

  butter.setup(b_butter, a_butter, 3, 3);
  iir_hpf.setup(b_iir_hpf, a_iir_hpf, 3, 3);
  mov_avg.setup(b_mov_avg, a_mov_avg, 4, 1);
  
  adc_ldr.begin(ADC_PIN, 12, 3.3F);
  start_time = micros();
  //input_reading = 1;

  
}

void loop() {
 
 if(micros() - start_time >= fs)
 {
  input_reading = adc_ldr.readVoltage();
  out_signals[0] = butter.filter(input_reading);
  out_signals[1] = iir_hpf.filter(input_reading);
  out_signals[2] = mov_avg.filter(input_reading);

  Serial.printf("%f,%f,%f,%f \n", input_reading, out_signals[0], out_signals[1], out_signals[2]);
 }
}