/*
 * RDA5807M FM Radio Sketch control using BLE
 * Repo App: https://github.com/satujamsaja/blefm
 * http://satujamsaja.blogspot.co.id
 * 
 */

#include <Wire.h>
#include <radio.h>
#include <RDA5807M.h>
#include <RDSParser.h>
#include <SoftwareSerial.h>

// Radio frequency presets.
RADIO_FREQ preset[] = {
  8780,
  8860,
  8940,
  9100,
  9140,
  9180,
  9300,
  9330,
  9410,
  9490,
  9530,
  9610,
  9690,
  9730,
  9850,
  9930,
  10000,
  10120,
  10200,
  10280,
  10320,
  10360,
  10440,
  10520,
  10600,
  10690,
  
};

RDA5807M radio;
RDSParser rds;
SoftwareSerial ble(7,8);

int pid = 17;
int vol;
char cmd;

void setup() {
  Serial.begin(9600);
  ble.begin(9600);
  radio.init();
  radio.setBandFrequency(RADIO_BAND_FM, preset[pid]);
  radio.setMono(false);
  radio.setMute(false);
  radio.setVolume(8);
  radio.attachReceiveRDS(RDS_process);
  rds.attachServicenNameCallback(DisplayServiceName);
}

void loop() {
  
  if (ble.available() > 0) {
      cmd = ble.read();
      switch(cmd) {
        case 'm':
          radio.setMute(!radio.getMute());
          break;
        case 's':
          radio.setMono(!radio.getMono());
          Serial.flush();
          break;
        case 'b':
          radio.setBassBoost(!radio.getBassBoost());
          Serial.flush();
          break;
        case '+':
          vol = radio.getVolume();
          if (vol < 15) {
            radio.setVolume(++vol);      
          }
          Serial.flush();
          break;
        case '-':
          vol = radio.getVolume();
          if (vol > 0) {
            radio.setVolume(--vol);
          }
          Serial.flush();
          break;
        case '>':
          if(pid < (sizeof(preset) / sizeof(RADIO_FREQ)) - 1) {
            pid++;
            radio.setFrequency(preset[pid]);  
          }
          Serial.flush();
          break;
        case '<':
          if(pid > 0) {
            pid--;
            radio.setFrequency(preset[pid]); 
          }
          Serial.flush();
          break;
        case 'i':
          radioInfo();
          Serial.flush();
          break; 
        case 'r':
          radio.term();
          delay(3000);
          radio.init();
          Serial.flush();
          break;    
    }
  }

  // Check RDS.
  radio.checkRDS();

  // Send update to app.
  sendUpdate();
}

// Display radio info on serial monitor.
void radioInfo() {
    char s[12];
    radio.formatFrequency(s, sizeof(s));
    Serial.print("Station:"); Serial.println(s);
    Serial.print("Radio:"); radio.debugRadioInfo();
    Serial.print("Audio:"); radio.debugAudioInfo();
}

// Display RDS name in serial monitor.
void DisplayServiceName(char *name) {
  Serial.print("RDS:");
  Serial.println(name);
}

// Process RDS data.
void RDS_process(uint16_t block1, uint16_t block2, uint16_t block3, uint16_t block4) {
  rds.processData(block1, block2, block3, block4);
}

// Send update to app.
void sendUpdate() {
  char s[12];
  boolean mode;
  
  delay(500);
  radio.formatFrequency(s, sizeof(s));
  // Add debugging to serial monitor
  mode = radio.debugAudio();
  Serial.println(mode);
  ble.print(String(s) + "/" + mode + "/" + radio.getVolume());
  Serial.println(String(s) + "/" + mode + "/" + radio.getVolume());
}

