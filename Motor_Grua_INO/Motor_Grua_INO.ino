
#define pwm 11
#define dir 8


int option;
int velMax=0;
int velMin=0;
void setup() {
  // put your setup code here, to run once:
  pinMode (pwm,OUTPUT);
  pinMode (dir,OUTPUT);
  analogWrite(pwm, 0);
  digitalWrite(dir, HIGH);   
  Serial.begin(9600);
  
}

void loop() {
    
  if (Serial.available()>0){
    //leemos la opcion enviada
    option=Serial.read();
    
    if(option=='a') {
      velMax++;
      analogWrite(pwm,velMax);
      Serial.println(velMax);
      
//  bajarSonda(35);
    }
    if(option=='b') {
      velMax--;
       analogWrite(pwm,velMax);
             Serial.println(velMax);
//    subirSonda(35);
    }
    
      
      if(option=='c') {
          digitalWrite(dir, HIGH);
         }
  
      if(option=='d') {
          digitalWrite(dir, LOW);
        // analogWrite(pwm,velMin);
         
 
    }
  }
   
}



void bajarSonda(int velMax){
  analogWrite(pwm,velMin);
  digitalWrite(dir, HIGH);
  delay(250);
  for(int i=0; i==velMax;i=i+5){
    delay(200);
    analogWrite(pwm,i);

  }
}

void subirSonda(int velMax){
  analogWrite(pwm,velMin);
  digitalWrite(dir, LOW);
  delay(250);
  for(int i=0; i==velMax;i=i+5){
    delay(200);
    analogWrite(pwm,i);
  }
  
} 


