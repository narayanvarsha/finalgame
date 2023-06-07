#include <Adafruit_CircuitPlayground.h>
#include <AsyncDelay.h>

#define BUTTON_A A7
#define BUTTON_B A4
int LEVEL_DELAY=1000;

int currentLevel = 1;
int sequenceLength = 1;
int sequence[10];
int playerIndex = 0;

void setup() {
  CircuitPlayground.begin();
  randomSeed(analogRead(0));
}

void loop() {
  if (currentLevel > 10) {
    // Game completed
    CircuitPlayground.clearPixels();
    CircuitPlayground.playTone(440, 1000); // Play a sound to indicate game completion
    delay(2000);
    resetGame();
  }

  if (playerIndex == sequenceLength) {
    // Player completed the sequence for the current level
    playerIndex = 0;
    delay(LEVEL_DELAY);
    nextLevel();
  }

  checkButtons();
}

void resetGame() {
  currentLevel = 1;
  sequenceLength = 1;
  playerIndex = 0;
}

void nextLevel() {
  sequenceLength++;
  generateSequence();
  playSequence();
}

void generateSequence() {
  for (int i = 0; i < sequenceLength; i++) {
    sequence[i] = random(2); // Generate random sequence of 0s (pink) and 1s (blue)
  }
}

void playSequence() {
  for (int i = 0; i < sequenceLength; i++) {
    if (sequence[i] == 0) {
      CircuitPlayground.setPixelColor(i, 255, 0, 255); // Pink
    } else {
      CircuitPlayground.setPixelColor(i, 0, 0, 255); // Blue
    }
    delay(500);
    CircuitPlayground.clearPixels();
    delay(100);
  }
}

void checkButtons() {
  if (CircuitPlayground.leftButton()) {
    handleButtonPress(0); // Pink button
  } else if (CircuitPlayground.rightButton()) {
    handleButtonPress(1); // Blue button
  }
}

void handleButtonPress(int color) {
  if (sequence[playerIndex] == color) {
    // Correct button pressed
    CircuitPlayground.playTone(880, 100); // Play a sound to indicate correct answer
    CircuitPlayground.setPixelColor(playerIndex, color == 0 ? 255 : 0, 0, color == 0 ? 255 : 0); // Light up the corresponding LED
    playerIndex++;
  } else {
    // Incorrect button pressed
    CircuitPlayground.playTone(220, 500); // Play a sound to indicate wrong answer
    resetGame();
  }
}
