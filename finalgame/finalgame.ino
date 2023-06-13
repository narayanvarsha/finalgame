#include <Adafruit_CircuitPlayground.h>
#include <AsyncDelay.h>
int rightpin=5;
int leftpin=4;
int level=1;
int sequence[11];
int playerindex=1;
int pink=1;
int blue=0;


void setup()
{
  Serial.begin(9600);
  CircuitPlayground.begin();
  attachInterrupt(digitalPinToInterrupt(leftpin),leftpart,FALLING); //attaching interrupts
  attachInterrupt(digitalPinToInterrupt(rightpin),rightpart,FALLING);
}

void loop()
{
  if(level>=10)
  {
    CircuitPlayground.clearPixels();
    CircuitPlayground.playTone(440,1000); //indicates the game is complete
    delay(2000);
    restartgame();
  }
  if (playerindex==level) //makes sure the player finished the current level amd can move on
  {
    playerindex=1;
    delay(1000);
    nextlevel();
  }
}


void nextlevel()
{
  display();
  Serial.print("Level "); //changes to the next level 
  Serial.println(level);
  level++;
}
void buttonpart(int color)
{
  if(sequence[playerindex]==color)
  {
    //Correct button pressed
    CircuitPlayground.playTone(880,100); //play sound to indicate correct answer
    playerindex++;
  }
  else
  {
    // Incorrect button pressed
    CircuitPlayground.playTone(220, 500); // Play a sound to indicate wrong answer
    restartgame();    
  }
}
void display() 
{
  //function to play the random lights for the game
    for(int i=1;i<=level;i++)
    {
      int LED_num=random(10);
      if(LED_num%2==0)
      {
        CircuitPlayground.setPixelColor(LED_num,255,0,255); //pink
        sequence[i]=pink;
      }
      else
      {
        CircuitPlayground.setPixelColor(LED_num,0,0,255); //blue
        sequence[i]=blue;
      }
    delay(500);
    CircuitPlayground.clearPixels();
    delay(100);
    }
    CircuitPlayground.clearPixels();
}


void restartgame()
{
  level=1; //this function runs when the player eiter finishes the game or looses a level.
  playerindex=1;
}
void leftpart()
{
    buttonpart(pink); //left button interrupt
}
void rightpart()
{
    buttonpart(blue); //right button interrupt
}
