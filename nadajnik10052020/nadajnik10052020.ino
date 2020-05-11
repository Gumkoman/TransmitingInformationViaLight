/*STM32 nadajnik*/

#define ledPin D9
#define buttonPin D6
#define messagePin0 D2
#define messagePin1 D3
#define messagePin2 D4
#define messagePin3 D5

int peroid = 1000;
bool message[11]={0,0,1,1,0,1,1,0,0,0,0};
unsigned int waitTime;
bool flag = false;
int timer = 0;

void setup() {
  //inicjalizacja wejśc/wyjsć
  pinMode(ledPin,OUTPUT);
  pinMode(buttonPin,INPUT);
  pinMode(messagePin0,INPUT);
  pinMode(messagePin1,INPUT);
  pinMode(messagePin2,INPUT);
  pinMode(messagePin3,INPUT);
  //inicjalizacja portu szeregowego  

}

void loop() {
  //unsigned long startTime = micros(); //czas poczatkowy
  unsigned long startTime = millis(); //czas poczatkowy
  
  //Sprawdzenie czy przycisk jest klikniety oraz czy nie wysyłana jest już wiadomość
  if((digitalRead(buttonPin)==HIGH)&&(flag==false)){
    flag = true;//flaga sygnalizuyjąca czy wiadomość jest wysyłana
    getMessage();//pobranie wiadomosci 4 bitowej

  }  
  if(flag!=0){

    if(timer<12){
      blinkLight(message[timer-1]);//zapalenie diody   
    }else{//po wyslaniu wiadomosci zmiana wartosci timera i flagi do wartosci poczatkowej
      timer = 0;
      flag = false;  
    }
    timer++;//dodanie wartosci do timera tak by w następnej iteracji wysyłany był kolejny bit  
  }else{//dzialanie lampki gdy nie wysyla informacji
    digitalWrite(ledPin,HIGH);
  }
  
  unsigned long endTime = millis();
  //unsigned long endTime = micros();
  waitTime = peroid - (int)(endTime-startTime);//ustalenie czasu ktory należy odczekać aby jedna iteracja pętli wykonywała sie w określonym czasie
  //delayMicroseconds(waitTime);
  delay(waitTime);
}

//funkcja pobierająca wartości z 4 polowego przełacznika typu DIP switch
void getMessage(){
  message[7] = digitalRead(messagePin0);
  message[8] = digitalRead(messagePin1);
  message[9] = digitalRead(messagePin2);
  message[10] = digitalRead(messagePin3);

}

//funkcja zapalająca ledy, jedna opcja ustawia ledy na swiecienie lub nie druga na swiecenie w 100% lub 50%
void blinkLight(bool value){
  //digitalWrite(ledPin,value);  
  if(value == true){
    analogWrite(ledPin,255);  
  }else{
    analogWrite(ledPin,127);
  }
}
