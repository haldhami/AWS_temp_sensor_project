// the value of the series resistor
// #define SERIESRESISTOR 10000
// What pin to connect the first sensor to
#define THERMISTORPIN_IN A0
// Define pin for second thermistor
#define THERMISTORPIN_OUT A1
// resistance at 25 degrees C
#define THERMISTORNOMINAL 10000
// temp. for nominal resistance (almost always 25 C)
#define TEMPERATURENOMINAL 25
// The beta coefficient of the thermistor (taken from spec sheet)
#define BCOEFFICIENT1 4150
#define BCOEFFICIENT2 4100
// The number of samples to average over (max is 255 for memory reasons)
#define NUMSAMPLES 200

float r[NUMSAMPLES][2];
// float r_out[NUMSAMPLES];

void setup(void) {
  Serial.begin(9600);
}

void loop(void) {
  uint8_t i;
  float temp_in;
  float temp_out;

  // take N samples in a row, over the course of a minute
  for (i = 0; i < NUMSAMPLES; i++) {
    r[i][0] = analogRead(THERMISTORPIN_IN);
    r[i][1] = analogRead(THERMISTORPIN_OUT);
    delay(300);
  }
  

  // average all the samples out
  temp_in = 0;
  temp_out = 0;
  for (i = 0; i < NUMSAMPLES; i++) {
    temp_in += r[i][0];
    temp_out += r[i][1];
  }
  temp_in /= NUMSAMPLES;
  temp_out /= NUMSAMPLES;

  // convert the value to resistance
  temp_in = (1023 / temp_in) - 1;      // (1023/ADC - 1)
  temp_in = THERMISTORNOMINAL / temp_in;  // 10K / (1023/ADC - 1)

  temp_out = (1023 / temp_out) - 1;
  temp_out = THERMISTORNOMINAL / temp_out;



  temp_in = temp_in / THERMISTORNOMINAL;           // (R/Ro)
  temp_in = log(temp_in);                        // ln(R/Ro)
  temp_in /= BCOEFFICIENT1;                         // 1/B * ln(R/Ro)
  temp_in += 1.0 / (TEMPERATURENOMINAL + 273.15);  // + (1/To)
  temp_in = 1.0 / temp_in;                       // Invert
  temp_in -= 273.15;                               // convert absolute temp to C

  temp_out = temp_out / THERMISTORNOMINAL;
  temp_out = log(temp_out);
  temp_out /= BCOEFFICIENT2;
  temp_out += 1.0 / (TEMPERATURENOMINAL + 273.15);
  temp_out = 1.0 / temp_out;
  temp_out -= 273.15;

  Serial.print(temp_in);
  Serial.print(F(","));
  Serial.println(temp_out);

  // delay(5000);
}
