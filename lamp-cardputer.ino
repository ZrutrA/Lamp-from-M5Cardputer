#include <M5Cardputer.h>

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 135

uint16_t colors[] = {TFT_RED, TFT_GREEN, TFT_BLUE, TFT_YELLOW, TFT_CYAN, TFT_MAGENTA, TFT_WHITE};
const char* colorNames[] = {"RED", "GREEN", "BLUE", "YELLOW", "CYAN", "MAGENTA", "WHITE"};
int currentColor = 0;
int brightnessLevels[] = {255, 191, 127, 63};
const char* brightnessNames[] = {"100%", "75%", "50%", "25%"};
int currentBrightness = 0;
bool lightOn = false;

void setup() {
    auto cfg = M5.config();
    M5Cardputer.begin(cfg);
    M5Cardputer.Display.setRotation(1);
    M5Cardputer.Display.setTextSize(2);
    M5Cardputer.Display.setTextColor(TFT_WHITE, TFT_BLACK);
    M5Cardputer.Display.fillScreen(TFT_BLACK);
    showSelectionScreen();
}

void loop() {
    M5Cardputer.update();
    if (M5Cardputer.Keyboard.isKeyPressed('/')) { // Right
        currentColor = (currentColor + 1) % 7;
        if (!lightOn) {
            showSelectionScreen();
        } else {
            applySettings();
        }
        delay(200); // Debounce delay
    }
    if (M5Cardputer.Keyboard.isKeyPressed(',')) { // Left
        currentColor = (currentColor + 6) % 7; // To emulate -1 mod 7
        if (!lightOn) {
            showSelectionScreen();
        } else {
            applySettings();
        }
        delay(200); // Debounce delay
    }
    if (M5Cardputer.Keyboard.isKeyPressed('.')) { // Down
        currentBrightness = (currentBrightness + 1) % 4;
        if (!lightOn) {
            showSelectionScreen();
        } else {
            applySettings();
        }
        delay(200); // Debounce delay
    }
    if (M5Cardputer.Keyboard.isKeyPressed(';')) { // Up
        currentBrightness = (currentBrightness + 3) % 4; // To emulate -1 mod 4
        if (!lightOn) {
            showSelectionScreen();
        } else {
            applySettings();
        }
        delay(200); // Debounce delay
    }
    if (M5Cardputer.Keyboard.isKeyPressed(KEY_ENTER)) { // Enter key
        lightOn = true;
        applySettings();
        delay(200); // Debounce delay
    }
    if (M5Cardputer.Keyboard.isKeyPressed(KEY_BACKSPACE)) { // Backspace key
        lightOn = false;
        showSelectionScreen();
        delay(200); // Debounce delay
    }
}

void showSelectionScreen() {
    M5Cardputer.Display.fillScreen(TFT_BLACK);
    M5Cardputer.Display.setCursor(10, 10);
    M5Cardputer.Display.print("Color: ");
    M5Cardputer.Display.setTextColor(colors[currentColor], TFT_BLACK);
    M5Cardputer.Display.print(colorNames[currentColor]);
    M5Cardputer.Display.setTextColor(TFT_WHITE, TFT_BLACK);

    M5Cardputer.Display.setCursor(10, 50);
    M5Cardputer.Display.print("Brightness: ");
    M5Cardputer.Display.print(brightnessNames[currentBrightness]);

    M5Cardputer.Display.display();
}

void applySettings() {
    uint16_t color = colors[currentColor];
    int brightness = brightnessLevels[currentBrightness];
    
    // Set brightness
    M5Cardputer.Display.setBrightness(brightness);
    
    // Fill screen with the selected color
    M5Cardputer.Display.fillScreen(color);
    M5Cardputer.Display.display();
}
