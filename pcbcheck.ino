
int PIN_v1 = A1;
int PIN_v2 = A2;
int PIN_v3 = A3;


int PIN_v5 = A0;

int relay = 12;
int redled = 6;

int greenled = 5;

#define _INTERVAL_ON    20 // distance sensor interval (unit: ms)
#define _INTERVAL_chk   2000// 확인하는거 (unit ms)

float vin1, vin2, vin3, vin5 = 0;
float vout0, vout1, vout2, vout3, vout4, vout5 = 0.0; 
float vo0, vo1,vo2, vo3, vo4, vo5 = 0.0;
float filtered_voltage0, filtered_voltage1,  filtered_voltage2, filtered_voltage3, filtered_voltage4, filtered_voltage5 = 0.0;
float R1 = 30000.0;
float R2 = 7500.0;
int value0,value1, value2, value3, value4, value5 = 0;
int su1, su2, su3, su4, su5, su6 = 0;
bool event_on, event_chk, event_chk2,event_onbefore, eventt,event_chk5,event_chk6,event_on1, done;
unsigned long last_sampling_time_on;
unsigned long last_sampling_time_chk;

int judge1, judge2, judge5, judge6,errr = 0.0;


void setup() {
 
  Serial.begin(9600);

  

  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);

  pinMode(A5, INPUT);
  pinMode (relay, OUTPUT);
  pinMode (redled, OUTPUT);
  pinMode (greenled, OUTPUT);
  
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);

  event_on = true;

}

void loop() {
  
  value1 = analogRead(A1);
  value2 = analogRead(A2);
  value3 = analogRead(A3);
  
  value5 = analogRead(A0);
    
  
  vout1 = (value1 * 5.0) / 1024.0;
  vout2 = (value2 * 5.0) / 1024.0;
  vout3 = (value3 * 5.0) / 1024.0;
 
  vout5 = (value5 * 5.0) / 1024.0;
  




  // 여기 서보 내용을 검출 작동
  





// 불3개//

if(event_on){
  event_on = false;
  if(judge1>2 && judge2>2){

    judge1=0;
     judge2=0;
    digitalWrite(greenled,HIGH);
    digitalWrite(redled,LOW);
    Serial.println("goooood");
    done = true; // 여기 기다리는거로 변경
  }
  else if(vo1 == HIGH && vo2 == LOW && vo3 == LOW && vo5 == LOW){
    delay(30);
    

    event_on = true;
    judge1 = 0;
    judge2 = 0;
    delay(100);
  }
  
  else
  {
    event_chk = true;
  }

}

// 동작
if (event_chk){
  event_chk=false;

    digitalWrite(relay,LOW);
  delay (5); 
  digitalWrite(relay,HIGH);
  delay(100);
   
  if(judge1>5){
     digitalWrite(redled,HIGH);
    digitalWrite(greenled,LOW);
    judge2 = 0;
    judge1 = 0;
    errr = 0;
    done = true;
    Serial.print("redred");
  }
  else if(vo1 == HIGH && vo2 == HIGH && vo3 == HIGH && vo5 == LOW ){
 
  Serial.println("check1");
      Serial.print("V1=");
      Serial.println(vin1);
      Serial.print("V2=");
      Serial.println(vin2);
      Serial.print("V3=");
      Serial.println(vin3);
  
      Serial.print("V5=");
      Serial.println(vin5);
     
  
  event_chk = true;
  judge1++;
  
  
  }
  else{
    event_chk2=true;
  }
}


if(event_chk2){
  
  event_chk2 = false;
  if(judge2>5){
     digitalWrite(redled,HIGH);
    digitalWrite(greenled,LOW);
    judge2 = 0;
    judge1 = 0;
    errr = 0;
    done = true;
    Serial.print("redred");
  }
 else if(vo1 == LOW && vo2 == LOW && vo3 == LOW && vo5 == HIGH  ){
    

  Serial.println("check2");
      Serial.print("V1=");
      Serial.println(vin1);
      Serial.print("V2=");
      Serial.println(vin2);
      Serial.print("V3=");
      Serial.println(vin3);
      Serial.print("V5=");
      Serial.println(vin5);
     
  
  event_on=true;
  judge2++;
  delay(10);
  }
  
/*
  else {
    errr++;
    delay(30);
    if(errr>5){
      */
    Serial.println("errorrr");
    Serial.println(vin1);
    Serial.println(vin2);
    Serial.println(vin3);
    Serial.println(vin5);

    
    digitalWrite(redled,HIGH);
    digitalWrite(greenled,LOW);
    judge2 = 0;
    judge1 = 0;
    errr = 0;
    done = true;
    }
    else{
      delay(40);
      event_on = true;
      }
  
    

  }

}


if(done){
done = false;
delay(300);
if(vo1 == HIGH && vo2 == LOW && vo3 == LOW && vo5 == LOW){
digitalWrite(redled,LOW);
digitalWrite(greenled,LOW);
event_on = true;
errr = 0;
}
else{
   done = true;
  delay(100);
//  Serial.print("done");
  // event_on = true; // 지워
}
}

// 여기서 로우 하이 정해버림

vin1 = vout1 / ( R2 / ( R1 + R2) ); 
vin2 = vout2 / ( R2 / ( R1 + R2) );
vin3 = vout3 / ( R2 / ( R1 + R2) );
vin5 = vout5 / ( R2 / ( R1 + R2) );


if(vin1<4){
  vo1=LOW;
}
else{
  vo1=HIGH;
}

if(vin2<4){
  vo2=LOW;
}
else{
  vo2=HIGH;
}

if(vin3<4){
  vo3=LOW;
}
else{
  vo3=HIGH;
}


if(vin5<1){
  vo5=LOW;
}
else{
  vo5=HIGH;
}
  
// 여기서 제어


}
