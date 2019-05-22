
/*
  Snake.ino
  Fisher Bricker

 */


#include <MeggyJrSimple.h> 

struct Point
{
  int x;
  int y;
};

Point s1 = {3,0};
Point s2 = {2,0};
Point s3 = {1,0};
Point s4 = {0,0};
Point snakeArray[64] = {s1,s2,s3,s4};

//snakeArray[0].x
//snakeArray[0].y

int appleX;
int appleY;
boolean gotApple =false;
int dir;
int eat;
int eatLights;
int marker;

void setup() {
  MeggyJrSimpleSetup();
  snakeArray[0].x=3;
  snakeArray[0].y=0;
  appleX= random(8);
  appleY= random(8);
  eat=1;
  marker=4;
  eatLights=1;
}

void loop() {
 UpdateSnake();
 MovementPlayer();
 Loop();
 DrawSnake();
 AppleSpawn();
 MarkerUpdate();
 
 DisplaySlate();
 delay(150);
 ClearSlate();
 
 

 ApplesEaten();
}


void MovementPlayer() {
  CheckButtonsDown();
  if (Button_Up)
  {
    dir=90;
  }
  if (Button_Down)
  {
    dir=270;
  }
  if (Button_Left)
  {
    dir=180;
  }
  if (Button_Right)
  {
    dir=0;
  }
  if (dir==0)
  {
    snakeArray[0].x++;
  }
  if (dir==90)
  {
    snakeArray[0].y++;
  }  
  if (dir==180)
  {
    snakeArray[0].x--;
  }  
  if (dir==270)
  {
    snakeArray[0].y--;
  }
  for (int i=0;i<marker;i++)
  {
    if (snakeArray[0].x==snakeArray[i].x && snakeArray[0].y==snakeArray[i].y)
    {
      
    }
}

void Loop() {
 if (snakeArray[0].x==8)
    {
      snakeArray[0].x=0;
    }
    if (snakeArray[0].x == -1)
    {
      snakeArray[0].x=7;
    }
    if (snakeArray[0].y==8)
    {
      snakeArray[0].y=0;
    }
    if (snakeArray[0].y == -1)
    {
      snakeArray[0].y=7;
    }
}


void AppleSpawn() {
  if (appleX==snakeArray[0].x && appleY==snakeArray[0].y)
  {
    gotApple=true;
    eatLights*=2;
    eat++;
  }
  if (gotApple==true)
  {
    appleX=random(8);
    appleY=random(8);
//    for (int i=0;i<marker;i++)
//    {
//      if (appleX==snakeArray[i].x && appleY==snakeArray[i].y)
//      {
//        
//      }
//    }
    gotApple=false;
  }
  DrawPx(appleX,appleY,Red);
}

void ApplesEaten() {
  if (eatLights==256)
  {
    eatLights=0;
    Tone_Start(18150,50);    
  }
  SetAuxLEDs(eatLights-1);
}

void DrawSnake() {
  for (int i=1;i<marker;i++)
  {
    DrawPx(snakeArray[i].x,snakeArray[i].y,Blue);
  }
  DrawPx(snakeArray[0].x,snakeArray[0].y,Green);
}

void MarkerUpdate() {
  if (eat==2)
  {
    marker++;
    eat=1;
  }
}

void UpdateSnake() {
  for (int i=marker-1;i>0;i--)
  {
    snakeArray[i].x=snakeArray[i-1].x;
    snakeArray[i].y=snakeArray[i-1].y;
  }
}
