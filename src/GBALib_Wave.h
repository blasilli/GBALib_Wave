/*
  GBALib_Wave.h - Wawe Management Library
  Copyright (c) 2024 Graziano Blasilli.
*/


#ifndef GBALib_Wave_h
#define GBALib_Wave_h

#include <Arduino.h>

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

class WaveRepeatingSync {
  private:
    uint8_t pin;
    int amplitude;
    int onTime;
    int offTime;
    bool log;
    const char* waveName;

    void syncWrite();

  public:
    /**
     * Constructor to initialize the WaveRepeatingSync object.
     * 
     * @param pin  The pin number to which the LED or device is connected.
     */
    WaveRepeatingSync(uint8_t pin);

    /**
     * Constructor to initialize the WaveRepeatingSync object.
     * 
     * @param pin  The pin number to which the LED or device is connected.
     * @param log  Wheter log the parameters before sending signal to the pin.
     */
    WaveRepeatingSync(uint8_t pin, bool log);

    /**
     * Set the name of the wave, to be logged when generating.
     * 
     * @param name  The name of the wave.
     */
    void setName(const char* name);

    /**
     * Set the amplitude of the wave.
     * 
     * @param amp  The amplitude value (0 to 255 for PWM).
     */
    void setAmplitude(int amp);

    /**
     * Set the on and off times of the wave.
     * 
     * @param onTime  The duration in milliseconds for which the wave is on.
     * @param offTime The duration in milliseconds for which the wave is off.
     */
    void setTiming(int onTime, int offTime);

    /**
     * Log the current amplitude, on time, and off time to the Serial Monitor.
     */
    void logDetails();

    /**
    * Start the wave generation by turning on the pin for the specified on time and off time.
    * 
    * @param repetitions  The number of times to repeat the wave generation.
    */
    void generate(int repetitions = 1);

    /**
    * Generate the wave repeatedly for the specified duration in milliseconds.
    * 
    * @param duration  The total duration in milliseconds to generate the wave.
    */
    void generateForMillisec(unsigned long duration);

};

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

class WaveSingleSync {
  private:
    uint8_t pin;
    int amplitude;
    int onTime;
    int offTime;
    bool log;
    const char* waveName;
    bool hasGenerated;

    void syncWrite();

  public:
    /**
     * Constructor to initialize the WaveSingleSync object.
     * 
     * @param pin  The pin number to which the LED or device is connected.
     */
    WaveSingleSync(uint8_t pin);

    /**
     * Constructor to initialize the WaveSingleSync object.
     * 
     * @param pin  The pin number to which the LED or device is connected.
     * @param log  Wheter log the parameters before sending signal to the pin.
     */
    WaveSingleSync(uint8_t pin, bool log);

    /**
     * Set the name of the wave, to be logged when generating.
     * 
     * @param name  The name of the wave.
     */
    void setName(const char* name);

    /**
     * Set the amplitude of the wave.
     * 
     * @param amp  The amplitude value (0 to 255 for PWM).
     */
    void setAmplitude(int amp);

    /**
     * Set the on and off times of the wave.
     * 
     * @param onTime  The duration in milliseconds for which the wave is on.
     * @param offTime The duration in milliseconds for which the wave is off.
     */
    void setTiming(int onTime, int offTime);

    /**
     * Log the current amplitude, on time, and off time to the Serial Monitor.
     */
    void logDetails();

    /**
    * Start the wave generation by turning on the pin for the specified on time and off time.
    * 
    * @param repetitions  The number of times to repeat the wave generation.
    */
    void generate(int repetitions = 1);

    /**
    * Generate the wave repeatedly for the specified duration in milliseconds.
    * 
    * @param duration  The total duration in milliseconds to generate the wave.
    */
    void generateForMillisec(unsigned long duration);

};




#endif
