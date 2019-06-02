#include <dht11.h>
#define DHT11PIN 2 
#include <Servo.h>
Servo myservo;
dht11 DHT11;
int data;
String enerji= "Enerji Kullanılmıyor";
int PVKONTROL=6;
int RUZGARKONTROL=7;
int ROLE=11;

int LDRPIN=A2;
int PVPIN=A3;
int RUZGARPIN=A4;
int BATARYAPIN=8;

int LDRDEGER=0;
int PVDEGER=0;
int RUZGARDEGER=0;

 
void setup()
{
  Serial.begin(9600); 
  myservo.attach(12);  
 
  pinMode(RUZGARKONTROL,OUTPUT);
  pinMode(PVKONTROL,OUTPUT);
  pinMode(ROLE,OUTPUT);
  pinMode(BATARYAPIN,OUTPUT);

 


}

void loop()

{  
  LDRDEGER=analogRead(LDRPIN);
  LDRDEGER=map(LDRDEGER,0,1023,0,255);
  
  PVDEGER=analogRead(PVPIN);
  PVDEGER=2*(map(PVDEGER,0,1023,0,255));
  
  RUZGARDEGER=analogRead(RUZGARPIN);
  RUZGARDEGER=2*(map(RUZGARDEGER,0,1023,0,255));

 

  int t = DHT11.temperature ;
  int chk = DHT11.read(DHT11PIN);
  
  
Serial.print("|");
Serial.print((float)DHT11.temperature, 2);  
Serial.print(" °C");
Serial.print("|");
Serial.print("%");
Serial.println((float)DHT11.humidity, 2);
Serial.print("|");


if (t>28 )            
{ digitalWrite(ROLE,LOW);
  }
  else
  { digitalWrite(ROLE,HIGH);
    }


 if (RUZGARDEGER>100)
 {  digitalWrite(RUZGARKONTROL,HIGH);
    digitalWrite(PVKONTROL,LOW);
    digitalWrite(BATARYAPIN,LOW);
    enerji = "Ruzgar Enerjisi" ;
    
  }
else if (RUZGARDEGER<100){
   digitalWrite(RUZGARKONTROL,LOW);
   digitalWrite(PVKONTROL,LOW);
   digitalWrite(BATARYAPIN,LOW);

}
  if (PVDEGER>100)
  {
    digitalWrite(RUZGARKONTROL,LOW);
    digitalWrite(PVKONTROL,HIGH);
    digitalWrite(BATARYAPIN,LOW);
    enerji = "Gunes Enerjisi" ;
  }
else if (PVDEGER<100){
   digitalWrite(RUZGARKONTROL,LOW);
   digitalWrite(PVKONTROL,LOW);
   digitalWrite(BATARYAPIN,LOW);    

}
    
    myservo.write(180);


    
if (Serial.available())   
{                
   int data = Serial.read();
   delay(100);
 


    
  if(data=='P'){
    
      if (LDRDEGER<150)              
  {
   myservo.write(0);
 
  }
  else 
  {   myservo.write(180);
    }
    delay(50);
  data='P';
  }
 
  if  (data=='K'){  
 myservo.write(180);
 data='K';
 }
  
 
    

     
if(data=='O'){


  
    digitalWrite(RUZGARKONTROL,LOW);
    digitalWrite(PVKONTROL,LOW);
    digitalWrite(BATARYAPIN,HIGH);
    enerji= "Batarya Enerjisi" ;  

  }   
  
  
  
  if(data=='C'){
     digitalWrite(RUZGARKONTROL,LOW);
     digitalWrite(PVKONTROL,LOW);
     digitalWrite(BATARYAPIN,LOW);
    String enerji= "Enerji Kullanilmiyor" ;
   }
}
   Serial.println(enerji);
   delay(500);

}

