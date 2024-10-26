/*
  GBALib_Wave.h - Wawe Management Library
  Copyright (c) 2024 Graziano Blasilli.
*/


#include "GBALib_Wave.h"


/* **************************************************************************************
**************************************************************************************
**************************************************************************************
**************************************************************************************/

/* **************************************************************************************
**************************************************************************************
**************************************************************************************
**************************************************************************************
 _    _                ______                      _   _             _____                  
| |  | |               | ___ \                    | | (_)           /  ___|                 
| |  | | __ ___   _____| |_/ /___ _ __   ___  __ _| |_ _ _ __   __ _\ `--. _   _ _ __   ___ 
| |/\| |/ _` \ \ / / _ \    // _ \ '_ \ / _ \/ _` | __| | '_ \ / _` |`--. \ | | | '_ \ / __|
\  /\  / (_| |\ V /  __/ |\ \  __/ |_) |  __/ (_| | |_| | | | | (_| /\__/ / |_| | | | | (__ 
 \/  \/ \__,_| \_/ \___\_| \_\___| .__/ \___|\__,_|\__|_|_| |_|\__, \____/ \__, |_| |_|\___|
                                 | |                            __/ |       __/ |           
                                 |_|                           |___/       |___/  

**************************************************************************************
**************************************************************************************
**************************************************************************************
************************************************************************************** */   

// Constructor to initialize the pwm pin
WaveRepeatingSync::WaveRepeatingSync(uint8_t pin) {
  this->pin = pin;
  pinMode(this->pin, OUTPUT);
  this->amplitude = 0;
  this->onTime = 0;
  this->offTime = 0;
  this->log = false;
}

// Constructor to initialize the pwm pin
WaveRepeatingSync::WaveRepeatingSync(uint8_t pin, bool log) {
  this->pin = pin;
  pinMode(this->pin, OUTPUT);
  this->amplitude = 0;
  this->onTime = 0;
  this->offTime = 0;
  this->log = log;
}

// Set the name of the wave
void WaveRepeatingSync::setName(const char* name) {
  this->waveName = name;
}

// Set the amplitude value
void WaveRepeatingSync::setAmplitude(int amp) {
  this->amplitude = constrain(amp, 0, 255);
}

// Set the on and off times
void WaveRepeatingSync::setTiming(int onTime, int offTime) {
  this->onTime = onTime;
  this->offTime = offTime;
}

// Log the current wave name, amplitude, onTime, and offTime values to the Serial Monitor
void WaveRepeatingSync::logDetails() {
  Serial.print("[WaveRepeatingSync] ");
  Serial.print("(");
  Serial.print(this->waveName);
  Serial.print(") ");
  Serial.print("Amplitude: ");
  Serial.print(this->amplitude);
  Serial.print(", On Time: ");
  Serial.print(this->onTime);
  Serial.print(" ms, Off Time: ");
  Serial.print(this->offTime);
  Serial.println(" ms");
}

// Generate multiple
void WaveRepeatingSync::generate(int repetitions = 1) {
  if(this->log) this->logDetails();
  for (int i = 0; i < repetitions; i++) {
    this->syncWrite();
  }
}

// Generate the wave repeatedly for the specified duration in milliseconds.
void WaveRepeatingSync::generateForMillisec(unsigned long duration) {
  unsigned long startTime = millis();  // Record the start time
  // Continue generating the wave until the elapsed time exceeds the duration
  while (millis() - startTime < duration) {
    generate();
  }
  // Ensure the wave is turned off at the end of the duration
  analogWrite(this->pin, 0);
}

void WaveRepeatingSync::syncWrite() {
  analogWrite(this->pin, this->amplitude);
  delay(this->onTime);
  analogWrite(this->pin, 0);
  delay(this->offTime);
}

/* **************************************************************************************
**************************************************************************************
**************************************************************************************
**************************************************************************************
 _    _                 _____ _             _      _____                  
| |  | |               /  ___(_)           | |    /  ___|                 
| |  | | __ ___   _____\ `--. _ _ __   __ _| | ___\ `--. _   _ _ __   ___ 
| |/\| |/ _` \ \ / / _ \`--. \ | '_ \ / _` | |/ _ \`--. \ | | | '_ \ / __|
\  /\  / (_| |\ V /  __/\__/ / | | | | (_| | |  __/\__/ / |_| | | | | (__ 
 \/  \/ \__,_| \_/ \___\____/|_|_| |_|\__, |_|\___\____/ \__, |_| |_|\___|
                                       __/ |              __/ | 

**************************************************************************************
**************************************************************************************
**************************************************************************************
************************************************************************************** */  

// Constructor to initialize the pwm pin
WaveSingleSync::WaveSingleSync(uint8_t pin) {
  this->pin = pin;
  pinMode(this->pin, OUTPUT);
  this->amplitude = 0;
  this->onTime = 0;
  this->offTime = 0;
  this->log = false;
  this->hasGenerated = false;
}

// Constructor to initialize the pwm pin
WaveSingleSync::WaveSingleSync(uint8_t pin, bool log) {
  this->pin = pin;
  pinMode(this->pin, OUTPUT);
  this->amplitude = 0;
  this->onTime = 0;
  this->offTime = 0;
  this->log = log;
}

// Set the name of the wave
void WaveSingleSync::setName(const char* name) {
  this->waveName = name;
}

// Set the amplitude value
void WaveSingleSync::setAmplitude(int amp) {
  this->amplitude = constrain(amp, 0, 255);
}

// Set the on and off times
void WaveSingleSync::setTiming(int onTime, int offTime) {
  this->onTime = onTime;
  this->offTime = offTime;
}

// Log the current wave name, amplitude, onTime, and offTime values to the Serial Monitor
void WaveSingleSync::logDetails() {
  Serial.print("[WaveSingleSync] ");
  Serial.print("(");
  Serial.print(this->waveName);
  Serial.print(") ");
  Serial.print("Amplitude: ");
  Serial.print(this->amplitude);
  Serial.print(", On Time: ");
  Serial.print(this->onTime);
  Serial.print(" ms, Off Time: ");
  Serial.print(this->offTime);
  Serial.println(" ms");
}


// Generate multiple
void WaveSingleSync::generate(int repetitions = 1) {
  if (this->hasGenerated) {
    return;
  }
  if(this->log) this->logDetails();
  for (int i = 0; i < repetitions; i++) {
    this->syncWrite();
    this->hasGenerated = true;
  }
}

// Generate the wave repeatedly for the specified duration in milliseconds.
void WaveSingleSync::generateForMillisec(unsigned long duration) {
  if (this->hasGenerated) {
    return;
  }
  unsigned long startTime = millis();  // Record the start time
  // Continue generating the wave until the elapsed time exceeds the duration

  if(this->log) this->logDetails();

  while (millis() - startTime < duration) {
    this->syncWrite();
  }
  // Ensure the wave is turned off at the end of the duration
  analogWrite(this->pin, 0);
  this->hasGenerated = true;
}

void WaveSingleSync::syncWrite() {
  analogWrite(this->pin, this->amplitude);
  delay(this->onTime);
  analogWrite(this->pin, 0);
  delay(this->offTime);
}

