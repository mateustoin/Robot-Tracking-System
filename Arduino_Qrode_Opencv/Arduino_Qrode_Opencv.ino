//#define LED_1 9
//#define LED_2 10
//#define LED_3 11

#define IN1 3 //MOTOR ESQUERDO PARA FRENTE
#define IN2 5 //MOTOR ESQUERDO PARA TRAS

#define IN3 6 //MOTOR DIREITO PARA TRAS
#define IN4 9 //MOTOR DIREITO PARA FRENTE

#include <string.h>
#include <Servo.h>

Servo servo;

int count = 0;

void setup()
{
  /* Iniciando a Serial e passando a taxa de baudrate */
  Serial.begin(9600); 
//  pinMode (LED_1, OUTPUT);
//  digitalWrite (LED_1, LOW);
//  pinMode (LED_2, OUTPUT);
//  digitalWrite (LED_2, LOW);
//  pinMode (LED_3, OUTPUT);
//  digitalWrite (LED_3, LOW);
//  pinMode (LED_BUILTIN, OUTPUT);
//  digitalWrite (LED_BUILTIN, LOW);

  servo.attach(6);
  servo.write(0);
}
 
void loop()
{
  if (Serial.available()) {
    const int leitura_brilho = Serial.parseInt();
    char letra = Serial.read();
    
    escreve_led(letra, leitura_brilho);
    //delay(10);
  }
  
//  Serial.print(++count);
//  Serial.print(",");
//  Serial.flush();
}

void escreve_led (char* letra, int brilho){
  if (letra == 'a' && brilho == 255){
    //digitalWrite (LED_1, brilho);
    //digitalWrite (LED_2, 0);
    //digitalWrite (LED_3, 0);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }
  else if (letra == 'a' && brilho == 0){
    //digitalWrite (LED_1, 0);
    //digitalWrite (LED_2, 255);
    //digitalWrite(LED_3, 0);
    analogWrite(IN2, 200);
    analogWrite(IN4, 200);
    analogWrite(IN1, 0);
    analogWrite(IN3, 0);
  }
  else if(letra == 'a' && brilho == 1){
    //digitalWrite (LED_1, 0);
    //digitalWrite (LED_2, 0);
    //digitalWrite(LED_3, 255);
    analogWrite(IN1, 200);
    analogWrite(IN3, 200);
    analogWrite(IN2, 0);
    analogWrite(IN4, 0);
    
  }


  /*if (letra == 'b' && brilho == 255){
    digitalWrite (LED_2, brilho);
  }else if (letra == 'a' && brilho == 0){
    digitalWrite (LED_2, brilho);
  }

  if (letra == 'c' && brilho == 255){
    digitalWrite (LED_3, brilho);
  }else if (letra == 'a' && brilho == 0){
    digitalWrite (LED_3, brilho);
  }*/

  if (letra == 's'){
    servo.write(brilho);
  }
}
