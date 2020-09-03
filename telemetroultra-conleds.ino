iint inches = 0;// declara variables en pulgadas 
long cm = 0;  // declara variables en cm en Long para mayor número de decimales

/*Se define una función readUltrasonicDistance al inicio para llamarla posteriormente 
en la función loop es del tipo Long par aumentar precisión en los decimales */


/*función readUltrasonicDistance calcula la distancia en cm hasta el objeto 
trig emite una frecuencia en HZ y Eco la recibe en el mismo terminal llamado SIG */

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  //TRIG COMO SEMÑAL DE SALIDA 
  digitalWrite(triggerPin, LOW);// TRIG EN ESTADO APAGADO
  delayMicroseconds(2); // SE ESPERA UN TIEMPO DE 2 ms 
  digitalWrite(triggerPin, HIGH);// Se enciende TRIG 
  delayMicroseconds(10); //10 ms encendido Trig
  digitalWrite(triggerPin, LOW);// se Apagda Triig
  pinMode(echoPin, INPUT);// Se enciende ECO 
  // lectura de pin echo con el retorno de la señal
  return pulseIn(echoPin, HIGH); //función devuelve valor de tipo long
}

/*Función Setup que se ejecuta 1 sola vez y configura el sistema */
void setup()
{
  
  Serial.begin(9600);// comunicación serial 9600 baudios(9600 caracteres por segundo)
  
  pinMode(8, OUTPUT); //LED VERDE COMO SALIDA EN PIN 8
  pinMode(7, OUTPUT); //LED AMARILLO COMO SALIDA EN PIN 7
  pinMode(4, OUTPUT);  // LED ROJO COMO SALIDA EN PIN 4
}

/**Función Loop se ejecuta en forma cíclica */
void loop()  
{
   /*float variable número entero con 2 decimales*/
  float distancia = 0.01723*readUltrasonicDistance(2, 2);
  
  /* Condiciones para diferentes distancias */
  
  if(distancia > 336)  // LEDS APAGADOS FUERA DEL RANGO OPERACIONAL
   {
  digitalWrite(4, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);    
  } 
 
 if((distancia <= 336) && (distancia >= 200)) {
  /*SÓLO ENCIENDE LED ROJO */
  digitalWrite(4, HIGH); 
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  } 
  else {
   digitalWrite(4, LOW); 
  }
  if((distancia < 200) && (distancia >= 100)) {
    
    digitalWrite(7, HIGH);//SÓLO ENCIENDE LED AMARILLO 
  } 
  else {
    digitalWrite(7, LOW); 
  }
  if(distancia < 100 ) {
    digitalWrite(8, HIGH);// SÓLO ENCIENDE LED VERDE
  } 
  else {
    digitalWrite(8, LOW); 
  }
                                      
  /* COMPARACIÓN DE RANGO ENTRE MONITOR EN SERIE Y VALOR VISUAL DEL SENSOR*/                                    
  Serial.print("distancia: ");// IMPRIMIR EN MONITOR EN SERIE 
  Serial.println(distancia+1.8);//IMPRIME VALOR DISTANCIA "CALIBRADA"
 
  delay(100); // esperar 100 ms
}
