
#define pwm 11
#define dir 8
#define cSensor A0 

int option;
int velMax=10;
int velMin=0;

float Sensibilidad=0.038;   //sensibilidad en voltios/amperios. 


void setup() {

  pinMode     (pwm,OUTPUT);
  pinMode     (dir,OUTPUT);
  pinMode     (cSensor,INPUT);
  analogWrite (pwm, 0);
  digitalWrite(dir, HIGH);   
  Serial.begin(9600);
}

void loop() {

//  float Idc=calculoCorriente(100); //obtenemos la corriente promedio de 500 muestras
//  Serial.print("Corriente: ");
//  Serial.println(Idc, 3);
    
    if (Serial.available()>0){
      //leemos la opcion enviada
      option=Serial.read();
    
        if(option=='a') {
          velMax++;
          analogWrite(pwm,velMax);
          Serial.println(velMax);
          float Idc=calculoCorriente(100); //obtenemos la corriente promedio de 500 muestras
          Serial.print("Corriente: ");
          Serial.println(Idc, 3);

//        bajarSonda(35);
        }
    
        if(option=='b') {
          velMax--;
          analogWrite(pwm,velMax);
          Serial.println(velMax);
//        subirSonda(35);
        }
         
        if(option=='c') {
//         digitalWrite(dir, HIGH);
         }
         
        if(option=='d') {
//         digitalWrite(dir, LOW);
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

float calculoCorriente(int numeroMuestras){ 
  float lecturaWSC1700 = 0;
  float intensidad = 0;
  for (int i=0; i<numeroMuestras; i++)
  {
    lecturaWSC1700 = analogRead(cSensor) + (4.96 / 1023.0);        //lee tensión de sensor en A0.
    intensidad = intensidad + (lecturaWSC1700-2.5)/Sensibilidad;   //calculamos corriente y sumamos
  }
  intensidad = intensidad/numeroMuestras;
  return(intensidad);
}
