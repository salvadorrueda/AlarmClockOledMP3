
/***********************************************************/
//Demo for the RTC module by Catalex
//Hardware: RTC *1
//Board:  Arduino UNO R3
//IDE:     Arduino-1.0
//Function:  Set time and get the time from RTC chip(DS1307) and display
//              it on the serial monitor.
//Store: http://www.aliexpress.com/store/1199788
//          http://www.dx.com/
/***************************************************************/
//* RTC module attached to I2C bus as follows:
//**[RTC] - [Arduino UNO R3]
//**SCL - A5
//**SDA - A4
//**VCC - 5V
/**********************************************************/


#include <Wire.h>
#include "DS1307.h"


DS1307 clock;//define a object of DS1307 class






/***********************************************************/
//Demo for the Serial MP3 Player by Catalex
//Hardware: Serial MP3 Player *1
//Board:  Arduino UNO R3
//IDE:      Arduino-1.0
//Function:  To play the first song in the micro sd card.
//Store: http://www.aliexpress.com/store/1199788
//          http://www.dx.com/
#include <SoftwareSerial.h>


#define ARDUINO_RX 5//should connect to TX of the Serial MP3 Player module
#define ARDUINO_TX 6//connect to RX of the module
SoftwareSerial mySerial(ARDUINO_RX, ARDUINO_TX);


static int8_t Send_buf[8] = {0} ;


 
/************Command byte**************************/
#define CMD_NEXT_SONG 0X01
#define CMD_PREV_SONG 0X02
#define CMD_PLAY_W_INDEX 0X03
#define CMD_VOLUME_UP 0X04
#define CMD_VOLUME_DOWN 0X05
#define CMD_SET_VOLUME 0X06
#define CMD_SINGLE_CYCLE_PLAY 0X08
#define CMD_SEL_DEV 0X09
  #define DEV_TF 0X02
#define CMD_SLEEP_MODE 0X0A
#define CMD_WAKE_UP 0X0B
#define CMD_RESET 0X0C
#define CMD_PLAY 0X0D
#define CMD_PAUSE 0X0E
#define CMD_PLAY_FOLDER_FILE 0X0F
#define CMD_STOP_PLAY 0X16
#define CMD_FOLDER_CYCLE 0X17
#define CMD_SET_SINGLE_CYCLE 0X19
  #define SINGLE_CYCLE_ON 0X00
  #define SINGLE_CYCLE_OFF 0X01
#define CMD_SET_DAC 0X1A
  #define DAC_ON  0X00
  #define DAC_OFF 0X01
#define CMD_PLAY_W_VOL 0X22


#define CMD_SHUFFLE_PLAY 0x18




void sendCommand(int8_t command, int16_t dat)
{
  char c;
  delay(20);
  Send_buf[0] = 0x7e; //starting byte
  Send_buf[1] = 0xff; //version
  Send_buf[2] = 0x06; //the number of bytes of the command without starting byte and ending byte
  Send_buf[3] = command; //
  Send_buf[4] = 0x01;//0x00 = no feedback, 0x01 = feedback
  Send_buf[5] = (int8_t)(dat >> 8);//datah
  Send_buf[6] = (int8_t)(dat); //datal
  Send_buf[7] = 0xef; //ending byte
  for(uint8_t i=0; i<8; i++)//
  {
    mySerial.write(Send_buf[i]);
   // Serial.print(Send_buf[i],HEX);
  }
  /*
  delay(20);
  while( mySerial.available() )
    {
     c = mySerial.read();
     Serial.print(c,HEX);
    }
 */
}






/*********************************************************************
This is an example for our Monochrome OLEDs based on SSD1306 drivers


  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98


This example is for a 128x64 size display using I2C to communicate
3 pins are required to interface (2 I2C and one reset)


Adafruit invests time and resources providing this open source code,
please support Adafruit and open-source hardware by purchasing
products from Adafruit!


Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/


#include <SPI.h>
//#include <Wire.h>  // RTC alredy included
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);


#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2




#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };


#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif


void setup()   {                


  //////////////////////////// MP3 /////////////////
    mySerial.begin(9600);
    delay(500);//Wait chip initialization is complete
    sendCommand(CMD_SEL_DEV, DEV_TF);//select the TF card  
    delay(200);//wait for 200ms
//    sendCommand(CMD_PLAY_W_VOL, 0X0F01);//play the first song with volume 15 class




  //////////////////////////// MP3 /////////////////


  Serial.begin(9600);


  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  // init done
 
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(2000);


  // Clear the buffer.
  display.clearDisplay();
/*
  // draw a single pixel
  display.drawPixel(10, 10, WHITE);
  // Show the display buffer on the hardware.
  // NOTE: You _must_ call display after making any drawing commands
  // to make them visible on the display hardware!
  display.display();
  delay(2000);
  display.clearDisplay();


  // draw many lines
  testdrawline();
  display.display();
  delay(2000);
  display.clearDisplay();


  // draw rectangles
  testdrawrect();
  display.display();
  delay(2000);
  display.clearDisplay();


  // draw multiple rectangles
  testfillrect();
  display.display();
  delay(2000);
  display.clearDisplay();


  // draw mulitple circles
  testdrawcircle();
  display.display();
  delay(2000);
  display.clearDisplay();


  // draw a white circle, 10 pixel radius
  display.fillCircle(display.width()/2, display.height()/2, 10, WHITE);
  display.display();
  delay(2000);
  display.clearDisplay();


  testdrawroundrect();
  delay(2000);
  display.clearDisplay();


  testfillroundrect();
  delay(2000);
  display.clearDisplay();


  testdrawtriangle();
  delay(2000);
  display.clearDisplay();
   
  testfilltriangle();
  delay(2000);
  display.clearDisplay();


  // draw the first ~12 characters in the font
  testdrawchar();
  display.display();
  delay(2000);
  display.clearDisplay();


  // draw scrolling text
  testscrolltext();
  delay(2000);
  display.clearDisplay();


  // text display tests
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Hello, world!");
  display.setTextColor(BLACK, WHITE); // 'inverted' text
  display.println(3.141592);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.print("0x"); display.println(0xDEADBEEF, HEX);
  display.display();
  delay(2000);


  // miniature bitmap display
  display.clearDisplay();
  display.drawBitmap(30, 16,  logo16_glcd_bmp, 16, 16, 1);
  display.display();


  // invert the display
  display.invertDisplay(true);
  delay(1000);
  display.invertDisplay(false);
  delay(1000);


  // draw a bitmap icon and 'animate' movement
//  testdrawbitmap(logo16_glcd_bmp, LOGO16_GLCD_HEIGHT, LOGO16_GLCD_WIDTH);
*/
}






int hora,minutos, ahora=7, aminutos=0;
boolean alarma = true;
char c; //


void loop() {
  //    printTime();
  display.clearDisplay();    
     clock.getTime();
    //Serial.print(clock.hour, DEC);
  display.setCursor(0,0);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  hora=clock.hour;
  minutos=clock.minute;
  //display.print(clock.hour, DEC);
  display.print(hora);
      display.print(":");
  display.print(minutos);
 //    display.print(clock.minute, DEC);
    display.print(":");
    display.print(clock.second, DEC);
    display.print("    ");
    //display.print(clock.month, DEC);
    display.println(" ");
   
   display.println("ALARM ");
  display.print(ahora);
      display.print(":");
  display.print(aminutos);
 
  display.display();
  delay(2000);
 
 if(hora==ahora&&minutos==aminutos&&alarma){
 // ALARM
  sendCommand(CMD_PLAY_W_VOL, 0X0F01);//play the first song with volume 15 class
  display.println ("WAKE UP");
  display.display();
  delay(2000);
  alarma = false;
 }






/************Command byte**************************/
/*
#define CMD_NEXT_SONG 0X01
#define CMD_PREV_SONG 0X02
#define CMD_PLAY_W_INDEX 0X03
#define CMD_VOLUME_UP 0X04
#define CMD_VOLUME_DOWN 0X05
#define CMD_SET_VOLUME 0X06
#define CMD_SINGLE_CYCLE_PLAY 0X08
#define CMD_SEL_DEV 0X09
  #define DEV_TF 0X02
#define CMD_SLEEP_MODE 0X0A
#define CMD_WAKE_UP 0X0B
#define CMD_RESET 0X0C
#define CMD_PLAY 0X0D
#define CMD_PAUSE 0X0E
#define CMD_PLAY_FOLDER_FILE 0X0F
#define CMD_STOP_PLAY 0X16
#define CMD_FOLDER_CYCLE 0X17
#define CMD_SET_SINGLE_CYCLE 0X19
  #define SINGLE_CYCLE_ON 0X00
  #define SINGLE_CYCLE_OFF 0X01
#define CMD_SET_DAC 0X1A
  #define DAC_ON  0X00
  #define DAC_OFF 0X01
#define CMD_PLAY_W_VOL 0X22


#define CMD_SHUFFLE_PLAY 0x18
*/
 
   #define CMD  0X0
 
 if( Serial.available() )
    {
    c = Serial.read();
    switch (c) {
    case '?':
          Serial.println("HELP  ");
          Serial.println(" S > Shuffle Play ");
          Serial.println(" P > Play ");
          Serial.println(" p > Pause");
          Serial.println(" n > Next");
          Serial.println(" u > Volume UP");
          Serial.println(" d > Volume DOWN");
          Serial.println(" c > Command");
      break;
      
      case 'c':
       int8_t ic;
          Serial.println("Command");
          ic = Serial.read();
      delay(20);
  Send_buf[0] = 0x7e; //starting byte
  Send_buf[1] = 0xff; //version
  Send_buf[2] = 0x06; //the number of bytes of the command without starting byte and ending byte
  //Send_buf[3] = command; //
  Send_buf[3] = (int8_t)(ic); //
  Send_buf[4] = 0x01;//0x00 = no feedback, 0x01 = feedback
  Send_buf[5] = 0x00; //(int8_t)(dat >> 8);//datah
  Send_buf[6] = 0x00; //(int8_t)(dat); //datal
  Send_buf[7] = 0xef; //ending byte
  for(uint8_t i=0; i<8; i++)//
  {
    mySerial.write(Send_buf[i]);
      Serial.print(Send_buf[i],HEX);


 
  while( mySerial.available() )
    {
     c = mySerial.read();
     Serial.print(c,HEX);
    }
 
}
    
      
      
      
      break;
      case 'T':
           Serial.println("Testing");         
 
   Send_buf[0] = 0x7e; //starting byte
  Send_buf[1] = 0xff; //version
  Send_buf[2] = 0x06; //the number of bytes of the command without starting byte and ending byte
  Send_buf[3] = 0x01; //
  Send_buf[4] = 0x01;//0x00 = no feedback, 0x01 = feedback
  Send_buf[5] = 0x00;//datah
  Send_buf[6] = 0x00; //datal
  Send_buf[7] = 0xef; //ending byte


 
 for(uint8_t i=0; i<8; i++)//
  {
    mySerial.write(Send_buf[i]);
  }
          break;
          
      
      case 'S':
          Serial.println("Shuffle Play");          
             sendCommand(CMD_SHUFFLE_PLAY, 0x0200);
         // sendCommand(CMD_FOLDER_CYCLE,0x0200);
         // sendCommand(CMD_PLAY, 0);
      break;


      case 'P':
          Serial.println("PLAY ");
             //sendCommand(CMD_PLAY_W_VOL, 0X0F01);//play the first song with volume 15 class
          //sendCommand(CMD_SINGLE_CYCLE_PLAY,0x0002); //play the second song repeatedly
          sendCommand(CMD_FOLDER_CYCLE,0x0100);
      break;


      case 'p':
          Serial.println("pause");
          sendCommand(CMD_PAUSE, 0);
      break;
      
      case 'n':
          Serial.println("Next");
          sendCommand(CMD_NEXT_SONG, 0);
      break;
      
     
      case 'u':
          Serial.println("Volume Up");
          sendCommand(CMD_VOLUME_UP, 0);
      break;


      case 'd':
          Serial.println("Volume Down");
          sendCommand(CMD_VOLUME_DOWN, 0);
      break;
      
      
      
/*
#define CMD_SET_VOLUME 0X06
#define CMD_SINGLE_CYCLE_PLAY 0X08
#define CMD_SEL_DEV 0X09
  #define DEV_TF 0X02
#define CMD_SLEEP_MODE 0X0A
#define CMD_WAKE_UP 0X0B
#define CMD_RESET 0X0C
#define CMD_PLAY 0X0D
#define CMD_PAUSE 0X0E
#define CMD_PLAY_FOLDER_FILE 0X0F
#define CMD_STOP_PLAY 0X16
#define CMD_FOLDER_CYCLE 0X17
#define CMD_SET_SINGLE_CYCLE 0X19
  #define SINGLE_CYCLE_ON 0X00
  #define SINGLE_CYCLE_OFF 0X01
#define CMD_SET_DAC 0X1A
  #define DAC_ON  0X00
  #define DAC_OFF 0X01
#define CMD_PLAY_W_VOL 0X22


#define CMD_SHUFFLE_PLAY 0x18
*/
      
      
      
      
      
      
      
      
      
      
      
      
  //  default:
  //       Serial.println("CMD");
  //          sendCommand(0X0+(int)c, 0);//play the first song with volume 15 class
     
      // if nothing else matches, do the default
      // default is optional
  }


      
      
      /*
        // Leer un byte y colocarlo en variable
        c = Serial.read();
 
        // Procesar comando de un solo byte
        if( c == 'P' )
        {
            
            Serial.println("PLAY ");
                  sendCommand(CMD_PLAY_W_VOL, 0X0F01);//play the first song with volume 15 class


        }
        
        else if ( c == 'p' )
        {
            Serial.println("pause");
            sendCommand(CMD_PAUSE, 0);//play the first song with volume 15 class
        }
        
        
        else if ( c == 'n' )
        {
            Serial.println("next");
            sendCommand(CMD_NEXT_SONG, 0);//play the first song with volume 15 class
        }
        //else{
          //cmd="0X0"+c;
         //Serial.println("next");
          //sendCommand(cmd, 0);
       // }
       
    }
    
    */
 
  }
 
}




  //////////////////////////// RTC /////////////////
  /*Function: Display time on the serial monitor*/
void printTime()
{
    clock.getTime();
    Serial.print(clock.hour, DEC);
    Serial.print(":");
    Serial.print(clock.minute, DEC);
    Serial.print(":");
    Serial.print(clock.second, DEC);
    Serial.print("    ");
    Serial.print(clock.month, DEC);
    Serial.print("/");
    Serial.print(clock.dayOfMonth, DEC);
    Serial.print("/");
    Serial.print(clock.year+2000, DEC);
    Serial.print(" ");
    Serial.print(clock.dayOfMonth);
    Serial.print("*");
    switch (clock.dayOfWeek)// Friendly printout the weekday
    {
        case MON:
          Serial.print("MON");
          break;
        case TUE:
          Serial.print("TUE");
          break;
        case WED:
          Serial.print("WED");
          break;
        case THU:
          Serial.print("THU");
          break;
        case FRI:
          Serial.print("FRI");
          break;
        case SAT:
          Serial.print("SAT");
          break;
        case SUN:
          Serial.print("SUN");
          break;
    }
    Serial.println(" ");
}
  //////////////////////////// RTC /////////////////




/*
void testdrawbitmap(const uint8_t *bitmap, uint8_t w, uint8_t h) {
  uint8_t icons[NUMFLAKES][3];
 
  // initialize
  for (uint8_t f=0; f< NUMFLAKES; f++) {
    icons[f][XPOS] = random(display.width());
    icons[f][YPOS] = 0;
    icons[f][DELTAY] = random(5) + 1;
    
    Serial.print("x: ");
    Serial.print(icons[f][XPOS], DEC);
    Serial.print(" y: ");
    Serial.print(icons[f][YPOS], DEC);
    Serial.print(" dy: ");
    Serial.println(icons[f][DELTAY], DEC);
  }


  while (1) {
    // draw each icon
    for (uint8_t f=0; f< NUMFLAKES; f++) {
      display.drawBitmap(icons[f][XPOS], icons[f][YPOS], logo16_glcd_bmp, w, h, WHITE);
    }
    display.display();
    delay(200);
    
    // then erase it + move it
    for (uint8_t f=0; f< NUMFLAKES; f++) {
      display.drawBitmap(icons[f][XPOS], icons[f][YPOS],  logo16_glcd_bmp, w, h, BLACK);
      // move it
      icons[f][YPOS] += icons[f][DELTAY];
      // if its gone, reinit
      if (icons[f][YPOS] > display.height()) {
    icons[f][XPOS] = random(display.width());
    icons[f][YPOS] = 0;
    icons[f][DELTAY] = random(5) + 1;
      }
    }
   }
}
*/


void testdrawchar(void) {
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);


  for (uint8_t i=0; i < 168; i++) {
    if (i == '\n') continue;
    display.write(i);
    if ((i > 0) && (i % 21 == 0))
      display.println();
  }    
  display.display();
}


void testdrawcircle(void) {
  for (int16_t i=0; i<display.height(); i+=2) {
    display.drawCircle(display.width()/2, display.height()/2, i, WHITE);
    display.display();
  }
}


void testfillrect(void) {
  uint8_t color = 1;
  for (int16_t i=0; i<display.height()/2; i+=3) {
    // alternate colors
    display.fillRect(i, i, display.width()-i*2, display.height()-i*2, color%2);
    display.display();
    color++;
  }
}


void testdrawtriangle(void) {
  for (int16_t i=0; i<min(display.width(),display.height())/2; i+=5) {
    display.drawTriangle(display.width()/2, display.height()/2-i,
                     display.width()/2-i, display.height()/2+i,
                     display.width()/2+i, display.height()/2+i, WHITE);
    display.display();
  }
}


void testfilltriangle(void) {
  uint8_t color = WHITE;
  for (int16_t i=min(display.width(),display.height())/2; i>0; i-=5) {
    display.fillTriangle(display.width()/2, display.height()/2-i,
                     display.width()/2-i, display.height()/2+i,
                     display.width()/2+i, display.height()/2+i, WHITE);
    if (color == WHITE) color = BLACK;
    else color = WHITE;
    display.display();
  }
}


void testdrawroundrect(void) {
  for (int16_t i=0; i<display.height()/2-2; i+=2) {
    display.drawRoundRect(i, i, display.width()-2*i, display.height()-2*i, display.height()/4, WHITE);
    display.display();
  }
}


void testfillroundrect(void) {
  uint8_t color = WHITE;
  for (int16_t i=0; i<display.height()/2-2; i+=2) {
    display.fillRoundRect(i, i, display.width()-2*i, display.height()-2*i, display.height()/4, color);
    if (color == WHITE) color = BLACK;
    else color = WHITE;
    display.display();
  }
}
   
void testdrawrect(void) {
  for (int16_t i=0; i<display.height()/2; i+=2) {
    display.drawRect(i, i, display.width()-2*i, display.height()-2*i, WHITE);
    display.display();
  }
}


void testdrawline() {  
  for (int16_t i=0; i<display.width(); i+=4) {
    display.drawLine(0, 0, i, display.height()-1, WHITE);
    display.display();
  }
  for (int16_t i=0; i<display.height(); i+=4) {
    display.drawLine(0, 0, display.width()-1, i, WHITE);
    display.display();
  }
  delay(250);
 
  display.clearDisplay();
  for (int16_t i=0; i<display.width(); i+=4) {
    display.drawLine(0, display.height()-1, i, 0, WHITE);
    display.display();
  }
  for (int16_t i=display.height()-1; i>=0; i-=4) {
    display.drawLine(0, display.height()-1, display.width()-1, i, WHITE);
    display.display();
  }
  delay(250);
 
  display.clearDisplay();
  for (int16_t i=display.width()-1; i>=0; i-=4) {
    display.drawLine(display.width()-1, display.height()-1, i, 0, WHITE);
    display.display();
  }
  for (int16_t i=display.height()-1; i>=0; i-=4) {
    display.drawLine(display.width()-1, display.height()-1, 0, i, WHITE);
    display.display();
  }
  delay(250);


  display.clearDisplay();
  for (int16_t i=0; i<display.height(); i+=4) {
    display.drawLine(display.width()-1, 0, 0, i, WHITE);
    display.display();
  }
  for (int16_t i=0; i<display.width(); i+=4) {
    display.drawLine(display.width()-1, 0, i, display.height()-1, WHITE);
    display.display();
  }
  delay(250);
}


void testscrolltext(void) {
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(10,0);
  display.clearDisplay();
  display.println("scroll");
  display.display();
 
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(1000);
  display.startscrollleft(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(1000);    
  display.startscrolldiagright(0x00, 0x07);
  delay(2000);
  display.startscrolldiagleft(0x00, 0x07);
  delay(2000);
  display.stopscroll();
}

