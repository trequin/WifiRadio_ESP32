#include <WiFi.h>
#include <TFT_eSPI.h>  // TFT library for TTGO
#include <Audio.h>     // See my repository at github "https://github.com/schreibfaul1/ESP32-audioI2S"
#include <Preferences.h>

#define I2S_DOUT      25
#define I2S_BCLK      27
#define I2S_LRC       26

Preferences pref;
TFT_eSPI tft = TFT_eSPI();  // Create TFT object for TTGO
Audio audio;

String ssid =     "<enter wifi ssid here>";
String password = "<enter password here>";

String stations[] = {
        "https://stream.treevine.life/BossHogg",
        "https://stream.treevine.life/TreeVineLife",
        "https://stream.treevine.life/Zona-Sur",
        "https://stream.treevine.life/Bike_Wit_Me_Radio",
        "https://stream.treevine.life/noise",
};

uint8_t max_volume   = 21;
uint8_t max_stations = 0;   // will be set later
uint8_t cur_station  = 0;   // current station (nr)
uint8_t cur_volume   = 0;   // will be set from stored preferences

// GUI buttons structure
struct _btns {
    uint16_t x;
    uint16_t y;
    uint16_t w;
    uint16_t h;
    uint8_t  action;
    uint8_t  status;
};
typedef _btns btns;
btns btn[4];

enum action { VOLUME_UP=0, VOLUME_DOWN=1, STATION_UP=2, STATION_DOWN=3 };
enum status { RELEASED=0, PRESSED=1 };

void draw_button(btns b) {
    uint16_t color = TFT_BLACK;
    uint8_t r = 4, o = r*3;
    if(b.status == RELEASED) color = TFT_YELLOW;
    if(b.status == PRESSED)  color = TFT_GREEN;
    tft.drawRoundRect(b.x, b.y, b.w, b.h, r, color);
}

void write_stationNr(uint8_t nr) {
    tft.fillRect(80, 250, 80, 60, TFT_BLACK);
    tft.setTextDatum(MC_DATUM);
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    tft.drawString(String(nr), 120, 280, 4);
}

void write_volume(uint8_t vol) {
    tft.fillRect(320, 250, 80, 60, TFT_BLACK);
    tft.setTextDatum(MC_DATUM);
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    tft.drawString(String(vol), 360, 280, 4);
}

void write_stationName(String sName) {
    tft.fillRect(0, 0, 240, 40, TFT_BLACK);
    tft.setTextDatum(MC_DATUM);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawString(sName, 120, 20, 2);
}

void write_streamTitle(String sTitle) {
    tft.fillRect(0, 50, 240, 60, TFT_BLACK);
    tft.setTextDatum(MC_DATUM);
    tft.setTextColor(TFT_CYAN, TFT_BLACK);
    tft.drawString(sTitle, 120, 80, 2);
}

void setup() {
    Serial.begin(115200);
    max_stations = sizeof(stations) / sizeof(stations[0]);

    // Initialize Preferences
    pref.begin("WebRadio", false);
    if(pref.getShort("volume", 1000) == 1000) {
        pref.putShort("volume", 10);
        pref.putShort("station", 0);
    } else {
        cur_station = pref.getShort("station");
        cur_volume = pref.getShort("volume");
    }

    // Initialize WiFi
    WiFi.begin(ssid.c_str(), password.c_str());
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("WiFi connected!");

    // Initialize TFT
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);

    // Initialize Audio
    audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
    audio.setVolume(cur_volume);
    audio.connecttohost(stations[cur_station].c_str());

    // Draw initial GUI
    for(uint8_t i = 0; i < 4; i++) draw_button(btn[i]);
    write_volume(cur_volume);
    write_stationNr(cur_station);
}

void loop() {
    audio.loop();
}

// Audio event handlers
void audio_info(const char *info) {
    Serial.print("audio_info: "); Serial.println(info);
}

void audio_showstation(const char *info) {
    write_stationName(String(info));
}

void audio_showstreamtitle(const char *info) {
    write_streamTitle(String(info));
}
