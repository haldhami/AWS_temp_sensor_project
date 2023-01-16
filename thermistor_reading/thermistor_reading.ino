// the value of the series resistor
#define SERIESRESISTOR 10000
// What pin to connect the first sensor to
#define THERMISTORPIN_IN A0
// Define pin for second thermistor
// #define THERMISTORPIN_OUT A1
// resistance at 25 degrees C
#define THERMISTORNOMINAL 10000
// temp. for nominal resistance (almost always 25 C)
#define TEMPERATURENOMINAL 25
// The beta coefficient of the thermistor (usually 3000-4000)
#define BCOEFFICIENT 3800
// The number of samples to average over (max is 255 for memory reasons)
#define NUMSAMPLES 255

float r_in[NUMSAMPLES];
float r_out[NUMSAMPLES];

void setup(void) {
  Serial.begin(9600);
}

void loop(void) {
  uint8_t i;
  float avg_r_in;
  float avg_r_out;

  // take N samples in a row, with a slight delay
  for (i = 0; i < NUMSAMPLES; i++) {
    r_in[i] = analogRead(THERMISTORPIN_IN);
    // r_out[i] = analogRead(THERMISTORPIN_OUT);
    delay(10);
  }

  // average all the samples out
  avg_r_in = 0;
  avg_r_out = 0;
  for (i = 0; i < NUMSAMPLES; i++) {
    avg_r_in += r_in[i];
    // avg_r_out += r_out[i];
  }
  avg_r_in /= NUMSAMPLES;
  // avg_r_out /= NUMSAMPLES;

  // convert the value to resistance
  avg_r_in = (1023 / avg_r_in) - 1;      // (1023/ADC - 1)
  avg_r_in = SERIESRESISTOR / avg_r_in;  // 10K / (1023/ADC - 1)

  // avg_r_out = (1023 / avg_r_out) - 1;
  // avg_r_out = SERIESRESISTOR / avg_r_out;

  float temp_in;
  float temp_out;

  temp_in = avg_r_in / THERMISTORNOMINAL;           // (R/Ro)
  temp_in = log(temp_in);                        // ln(R/Ro)
  temp_in /= BCOEFFICIENT;                         // 1/B * ln(R/Ro)
  temp_in += 1.0 / (TEMPERATURENOMINAL + 273.15);  // + (1/To)
  temp_in = 1.0 / temp_in;                       // Invert
  temp_in -= 273.15;                               // convert absolute temp to C

  // temp_out = avg_r_out / THERMISTORNOMINAL;
  // temp_out = log(temp_out);
  // temp_out /= BCOEFFICIENT;
  // temp_out += 1.0 / (TEMPERATURENOMINAL + 273.15);
  // temp_out = 1.0 / temp_out;
  // temp_out -= 273.15;

  Serial.println(temp_in);

  delay(5000);
}