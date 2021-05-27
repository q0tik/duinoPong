#include <U8g2lib.h>

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ SCL, /* data=*/ SDA);

int xB = 62, yB = 14, vxB = 2, vyB = 2;
int xP = 15, yP = 5;
int xI = 111, yI = 5;
int ft = 0;

void setup() {
  pinMode(3, INPUT);
  pinMode(6, INPUT);
  u8g2.begin();
  u8g2.setFontPosTop();
  //Serial.begin(9600);
}

void loop() {
  //u8g2.clearBuffer();
  drawBall();
  drawPlayer();
  drawBot();
  if (ft == 3) {
    drawBot();
    ft = 0;
  }
  ft++;
  delay(1);
}

void drawBall() {
  int a = xB,b = yB;

  if ((vxB < 0 && xB <= 16 && xB >= xP && yB >= (yP - 1) && yB <= (yP + 12)) || (vxB > 0 && xB >= 109 && xB <= xI && yB >= (yI - 1) && yB <= (yI + 12))) {
    vxB = -vxB;
    if ((yB >= (yP - 1) && yB <= (yP + 4) && vyB > 0) || (yB >= (yI - 1) && yB <= (yI + 4) && vyB > 0) || (yB <= (yP + 12) && yB > (yP + 8) && vyB < 0) || (yB <= (yI + 12) && yB >= (yI + 8) && vyB < 0)) {
      vyB = -vyB;
    }
  }
  
  if ((vyB < 0 && yB <= 0) || (vyB > 0 && yB >= 30)) {
    vyB = -vyB;
  }
  
  xB += vxB;
  yB += vyB;

  if ((xB <= 10)|| (xB >= 120 )) {
    start(); 
  }

  //errase old ball
  u8g2.setDrawColor(0);
  u8g2.drawPixel(a, b);
  u8g2.drawPixel(a + 1, b);
  u8g2.drawPixel(a, b + 1);
  u8g2.drawPixel(a + 1, b + 1);
  //draw new ball
  u8g2.setDrawColor(1);
  u8g2.drawPixel(xB, yB);
  u8g2.drawPixel(xB + 1, yB);
  u8g2.drawPixel(xB, yB + 1);
  u8g2.drawPixel(xB + 1, yB + 1);
  u8g2.sendBuffer();
}

void drawPlayer() {
  int sY = yP;
  
  int up = digitalRead(3);
  int down = digitalRead(6);
  //Serial.println("up" + String(up) + "\ndown" + String(down));

  if (up == HIGH && yP > 0) {
    yP--;
  } else if (down == HIGH && yP < 20) {
    yP++;
  }

  if (sY < yP) {
    u8g2.setDrawColor(0);
    u8g2.drawPixel(xP, sY);
  } else if (sY > yP) {
    u8g2.setDrawColor(0);
    u8g2.drawPixel(xP, sY + 11);
  }
  u8g2.setDrawColor(1);
  for(int i = 0; i < 12; i++) {
    u8g2.drawPixel(xP, yP + i);
  }
  u8g2.sendBuffer();
}

void drawBot() {
  int sY = yI;
  
  //Serial.println("up" + String(up) + "\ndown" + String(down));

  if (yB < (yI + 5) && yI > 0) {
    yI--;
  } else if (yB >= (yI + 5) && yI < 20) {
    yI++;
  }

  if (sY < yI) {
    u8g2.setDrawColor(0);
    u8g2.drawPixel(xI, sY);
  } else if (sY > yI) {
    u8g2.setDrawColor(0);
    u8g2.drawPixel(xI, sY + 11);
  }
  u8g2.setDrawColor(1);
  for(int i = 0; i < 12; i++) {
    u8g2.drawPixel(xI, yI + i);
  }
  u8g2.sendBuffer();
}

void start() {
    xP = 15;
    yP = 5;
    xI = 111; 
    yI = 5;
    xB = random(60, 66); 
    yB = random(13, 17);
  
    vxB = random(0, 2) == 0 ? 2 : -2;
    vyB = random(0, 2) == 0 ? 2 : -2;
    u8g2.clearBuffer();
}
