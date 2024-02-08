#include <LiquidCrystal.h>
#include <dht_nonblocking.h>
#define DHT_SENSOR_TYPE DHT_TYPE_11

static const int DHT_SENSOR_PIN = 2;
DHT_nonblocking dht_sensor( DHT_SENSOR_PIN, DHT_SENSOR_TYPE );

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// Define connection pins:
#define pirPin 4
#define ledPin 13

// Create variables:
int val = 0;
bool motionState = false; // We start with no motion detected.


void setup() {
  Serial.begin( 9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  
    // Configure the pins as input or output:
  pinMode(ledPin, OUTPUT);
  pinMode(pirPin, INPUT);
}


static bool measure_environment( float *temperature, float *humidity )
{
  
  if( dht_sensor.measure( temperature, humidity ) == true )
  {
    return( true );
  }
  return ( true );
}

void loop() {
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 0);
  bool repeat = true;
  double x;
  double y;
  
  float temperature;
  float humidity;
  
  while (repeat)
  {
      // Read out the pirPin and store as val:
    val = digitalRead(pirPin);
    
    // If motion is detected (pirPin = HIGH), do the following:
    if (val == HIGH) {
      double timer = 30;
      x = 0;
      y = 0;
      lcd.setCursor(0, 0);
      lcd.print( "                        ");
      lcd.setCursor(0, 1);
      lcd.print( "                        ");
      lcd.setCursor(0, 0);
      lcd.print("Motion detected!");
      lcd.setCursor(0, 1);
      lcd.print("Starting A/C...");
      motionState = true;
      delay(3000);
      
      /* Measure temperature and humidity.  If the functions returns
        true, then a measurement is available. */
      if(measure_environment( &temperature, &humidity ) == true)                      //Issue where this doesn't run
      {
        lcd.setCursor(0, 0);
        lcd.print( "                        ");
        lcd.setCursor(0, 0);
        lcd.print( "Temp = " );
        y = ((temperature * (9/5)) + 32);                                   
        lcd.print( y, 1 );                                                  
        lcd.print( " F");
         
        /*
        lcd.setCursor(0, 0);
        lcd.print( "Humi = ");
        lcd.print( humidity, 1);
        lcd.print( "%");
        */
        delay(7000);
        //y = 40;                                               Set Fake Value here                                          
        if (y > 80 )
        {
          x = y - 68;
          lcd.setCursor(0, 0);
          lcd.print( "                        ");    
          lcd.setCursor(0, 0);
          lcd.print("Temp. Hot");
          lcd.setCursor(0, 1);
          lcd.print("Change: -");
          lcd.print(x, 1);
          delay(5000);
          lcd.setCursor(0, 0);
          lcd.print( "                        ");    
          lcd.setCursor(0,0);
          lcd.print("New Temp = 68 F");
        }
        if (y < 50 )
        {
          x = 68 - y;
          lcd.setCursor(0, 0);
          lcd.print( "                        ");    
          lcd.setCursor(0, 0);
          lcd.print("Temp. Cold");
          lcd.setCursor(0, 1);
          lcd.print( "                        ");    
          lcd.setCursor(0, 1);
          lcd.print("Change: +");
          lcd.print(x, 1);
          delay(5000);
          lcd.setCursor(0, 0);
          lcd.print( "                        ");    
          lcd.setCursor(0,0);
          lcd.print("New Temp = 68 F");
        }
        lcd.setCursor(0, 1);
        lcd.print( "                        ");    
        while (timer != 0)
        {
          lcd.setCursor(0, 1);
          lcd.print("Motion Timer: ");
          lcd.print(timer, 1);                                                          
          timer--;                                                                      //Add temp resistor back
          delay(1000);
        }
      }
    }
    else {
      lcd.setCursor(0, 0);
      lcd.print( "                        ");
      lcd.setCursor(0, 1);
      lcd.print( "                        ");
      lcd.setCursor(0, 0);
      lcd.print("No Motion...");
      delay(500);
    }
  }

}

