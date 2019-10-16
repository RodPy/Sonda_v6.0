float Sensibilidad=0.038;   //sensibilidad en voltios/amperios. 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  float Idc=calculoCorriente(100); //obtenemos la corriente promedio de 500 muestras
  Serial.print("Corriente: ");
  Serial.println(Idc, 3);
  delay(100); 
}

float calculoCorriente(int numeroMuestras)
{ 
  float lecturaWSC1700 = 0;
  float intensidad = 0;
  for (int i=0; i<numeroMuestras; i++)
  {
    lecturaWSC1700 = analogRead(A0) + (4.96 / 1023.0);   //lee tensión de sensor en A0.
    intensidad = intensidad + (lecturaWSC1700-2.5)/Sensibilidad;   //calculamos corriente y sumamos
  }
  intensidad = intensidad/numeroMuestras;
  return(intensidad);
}
