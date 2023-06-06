#include <Adafruit_CircuitPlayground.h>
#include <AsyncDelay.h>
int right=5;
int left=4;
int level=1;
int length=1;
int sequence[10];
int playerindex=0;

void setup()
{
  Serial.begin(9600);
  CircuitPlayground.begin();
}

void loop()
{
  if(level>10)
  {
    CircuitPlayground.clearPixels();
    CircuitPlayground.playTone(440,1000);
    delay(2000);
    restart();
  }
  if (playerindex==length)
  {
    playerindex=0;
    delay(2000);
    nextlevel();
  }
  check();
}
void nextlevel()
{
  length++;
  lights();

}
void buttonpart(int color)
{
  if(sequence[playerindex]==color)
  {
    CircuitPlayground.playTone(880,100);
    CircuitPlayground.setPixelColor(playerindex, color == 0 ? 255 : 0, 0, color == 0 ? 255 : 0); // Light up the corresponding LED
    playerindex++;
  }
  else
  {
    // Incorrect button pressed
    CircuitPlayground.playTone(220, 500); // Play a sound to indicate wrong answer
    restart();    
  }
}
void lights()
{
   CircuitPlayground.clearPixels();
    for(int i=1;i<=length;i++)
    {
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
void check()
{
    if (CircuitPlayground.leftButton()) {
    handleButtonPress(0); // Pink button
  } else if (CircuitPlayground.rightButton()) {
    handleButtonPress(1); // Blue button
  }
}
void restart()
{
  level=1;
  length=1;
  playerindex=0;
}