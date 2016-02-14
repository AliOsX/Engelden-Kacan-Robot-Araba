
#include <AFMotor.h> 
#include <Ultrasonic.h>
#include <Servo.h>
Servo basservo;
Ultrasonic ultrasonic(12,13); // (Trig PIN,Echo PIN)
AF_DCMotor motorsag(1,MOTOR12_8KHZ);  // Motorları tanımla
AF_DCMotor motorsol(2,MOTOR12_8KHZ);
const bool TRUE = 1; // Lojik değer sabitleri. 
const bool FALSE =0;
const int motorhiz = 150;
const int enyakinnesne = 20; 
bool onengel,solengel,solcapraz,sagcapraz,sagengel;

void setup() {
pinMode(A0,INPUT_PULLUP);
pinMode(A1,INPUT_PULLUP);
motorsag.setSpeed(motorhiz); 
motorsol.setSpeed (motorhiz); // Motor hız kontrol. 
basservo.attach(9); // Servo 9. ayak. Karttaki Servo 2 kısmı
basservo.write(90); 
delay(200);

}

void loop()
{
  /* Serbest Bırak */ 
 motorsol.run(RELEASE);
 motorsag.run(RELEASE);
 /* Tarama İşlemi */ 
 onengel = bastarama(85,105);
 //IR Okuma 
if (!digitalRead(A0))
onengel=TRUE;
if(!digitalRead(A1))
onengel=TRUE;
if (onengel==FALSE)
{
  sagcapraz=bastarama(45,50);
  solcapraz=bastarama(135,140);
}

if (onengel==TRUE)
{
   sagengel=bastarama(0,10);
   sagcapraz=bastarama(45,50);
   solcapraz=bastarama(135,140);
   solengel=bastarama(175,180);
}

 
if (onengel == FALSE && solcapraz == FALSE && sagcapraz == FALSE )
{
motorsag.run(FORWARD);
motorsol.run(FORWARD);
delay(500);
}

else if (onengel == FALSE && solcapraz == TRUE )
{
  motorsag.run(BACKWARD);
  motorsol.run(FORWARD);
  delay(150);
}

else if (onengel == FALSE && sagcapraz == TRUE)
{
  motorsag.run(FORWARD);
  motorsol.run(BACKWARD);
  delay(150);
}

if(onengel== TRUE)
{
  if(solengel==TRUE || solcapraz == TRUE )
  {
    motorsol.run(FORWARD);
    motorsag.run(BACKWARD);
    delay(300);
  }

 else if(sagengel==TRUE || sagcapraz == TRUE)
 {
  motorsol.run (BACKWARD);
  motorsag.run(FORWARD);
  delay(300);
 }

else if(sagengel == TRUE && solengel == TRUE)
{
  motorsol.run(BACKWARD);
  motorsag.run(BACKWARD);
  delay(300);
  motorsol.run (BACKWARD);
  motorsag.run(FORWARD);
  delay(300);
}
else if(solengel==FALSE && sagengel == FALSE)
{
  bool yon = random(0, 1);
  if (yon==0)
  {
  motorsol.run(BACKWARD);
  motorsag.run(FORWARD);
  delay(300);
  }
  else if(yon==1)
  {
    motorsol.run(FORWARD);
    motorsag.run(BACKWARD);
    delay(300);
  }
}
}

delay(100);
}

bool bastarama(byte ilkaci, byte sonaci) // Sırayla tarama işlemini yap ve en yakın objeyi esas al
{
int sonolcum;
basservo.write(ilkaci);
delay(100);
for (int i=ilkaci; i<sonaci; i+=1)
{
 
 int olcum = ultrasonic.Ranging(CM);
 basservo.write(i);
 delay(5);
 if (olcum<sonolcum)
 sonolcum=olcum;
}


bool sondurum;
if (sonolcum<enyakinnesne)
sondurum=1;
else
sondurum=0;
return sondurum;
}


