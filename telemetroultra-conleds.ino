/*
   ################
   #   Lab15125   #
   ################
 
   Este codigo tiene como objetivo dar muestra de un uso practico de:
   Sensor ultrasonico ping (parallax)

   Según la hoja de datos de Parallax para el PING))), 
   hay 73,746 microsegundos por pulgada o 29,034 microsegundos por centimetro 
   (es decir, el sonido viaja a 1130 pies (o 34442.4cm) por segundo). 
   Este da la distancia recorrida por el ping, ida y vuelta, 
   por lo que dividimos por 2 para obtener la distancia del obstáculo.
   ver: 
   https://www.parallax.com/sites/default/files/downloads/28015-PING-Sensor-Product-Guide-v2.0.pdf
        [En el PDF: TO_IN = 73_746' Inches ; TO_CM = 29_034' Centimeters ]

   El circuito:
     * +V conectado a sensor PING))) en +5V
     * GND conectado a sensor PING))) en GND (ground)
     * SIG conectado a sensor PING))) en pin digital 7
     * LED conectado a pin 9 (PWM)

   Funcion
   readUltrasonicDistance(int triggerPin, int echoPin): Referencia obtenida de sensor ultrasonico tinkercad.com
*/
int inches = 0;//declara variables pulgadas
int cm = 0;// decalara vaiables en centímetos 

/*Se define una función readUltrasonicDistance al inicio 
para poder llamarla en el loop es del tipo long para 
aumentar la presición y tener mayor cantidad de decimsles 
Triger emite frecuencia y eco recibe mismo terminal SIG*/

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Inicializar LOW para limpiar trigger por 2 microsegundos
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Inicializar trigger en HIGH por 8 microsegundos para comenzar
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // lectura de pin echo con el retorno de la señal
  return pulseIn(echoPin, HIGH);
}


/*FUNCIÓN SETUP QUE SE EJECUTA 1 SOLA VEZ Y CONFIGURA EL SISTEMA */

void setup()
{
  Serial.begin(9600);// comunicación serial 9600 caracteres por segundo
  pinMode(8, OUTPUT); //salida LED VERDE
  pinMode(7, OUTPUT); //salida LED AMARILLO
  pinMode(4, OUTPUT); //salida LED ROJO
}

/*FUNCIÓN LOOP SE EJECUTA EN FORMA CICLICA */
void loop()
{ 
 //FLOAT VARIABLE NÚMERO ENTERO CON 2 DECIMALES 
  float distancia = 0.01723 * readUltrasonicDistance(2, 2);
  /*CONDICIONES PARA DIFERENTES DISTANCIAS*/
  if((distancia < 336) && (distancia >= 200)) 
  {
    digitalWrite(4, HIGH); //ENCIENDE LED ROJO
    digitalWrite(7, LOW); // LED AMARILLO APAGADO
    digitalWrite(8, LOW); // LED VERDE APAGADO
  } 
  else {
    digitalWrite(4, LOW); //LED ROJO APAGADO
  }
  /*CONDICION PARA CIERTA DISTANCIA */
  if((distancia < 200) && (distancia >= 100)) {
    digitalWrite(7, HIGH);//LED AMARILLO ENCENDIDO
  } 
  else {
    digitalWrite(7, LOW); //LED AMARILLO APAGADO
  }
  /*CONDICIÓN PARA CIERTA DISTANCIA*/
  if(distancia < 100) {
    digitalWrite(8, HIGH);//LED VERDE ENCIENDE A UNA DISTANCIA MENOR A 100 cm
  } 
  else {
    digitalWrite(8, LOW); //LED VERDE APAGADO
  }
  /*SE COMPARA MONITOR SERIE CON VALOR VISUAL DEL SENSOR SUS RANGO*/
  Serial.print("distancia: "); //IMPRIMIR EN MONITOR SERIE
  Serial.println(distancia+1.8); // IMPRIME VALOR DE DISTANCIA 
  delay(10); // Delay a little bit to improve simulation performance
}
