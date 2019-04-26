//#define LED_1 9
//#define LED_2 10
//#define LED_3 11

#define IN1 3 //MOTOR ESQUERDO PARA FRENTE
#define IN2 5 //MOTOR ESQUERDO PARA TRAS

#define IN3 6 //MOTOR DIREITO PARA TRAS
#define IN4 9 //MOTOR DIREITO PARA FRENTE

//#include <string.h>

int count = 0;

void setup()
{
  /* Iniciando a Serial e passando a taxa de baudrate */
  Serial.begin(9600); 
  
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(13, OUTPUT);
  
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
 
void loop()
{
  if (Serial.available()) {
    const int leitura_brilho = Serial.parseInt();
    char letra = Serial.read();
    
    escreve_led(letra, leitura_brilho);
    //delay(10);
  }
  
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
    analogWrite(IN2, 100);
    analogWrite(IN4, 100);
    analogWrite(IN1, 0);
    analogWrite(IN3, 0);
    
    digitalWrite(13, HIGH);
    delay(20);
  }
  else if(letra == 'a' && brilho == 1){
    //digitalWrite (LED_1, 0);
    //digitalWrite (LED_2, 0);
    //digitalWrite(LED_3, 255);
    analogWrite(IN1, 100);
    analogWrite(IN3, 100);
    analogWrite(IN2, 0);
    analogWrite(IN4, 0);
    
    digitalWrite(13, HIGH);
    delay(20);
  }

}
