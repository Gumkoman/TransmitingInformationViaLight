/*Odbiornik stm32 */
#define sensorPin A0
#define deafultPin A1
bool key[7]={0,0,1,1,0,1,1};
bool output[11];
bool message[4];
bool currentBit;

int peroid = 1000;
int deafultVal=0;
int sensorVal=0;
int waitTime=0;

void setup() {
  //inicjalizacja wejść wyjsć
  pinMode(sensorPin,INPUT);
  pinMode(deafultPin,INPUT);
  //inicjalizacja komunikacji uatr 
  Serial.begin(115200);
  Serial.println("Witam");
}

void loop() {
  //poczatkowa wartosc czasu w chwili rozpoczecia nowej petli
  //unsigned long startTime = micros();
  unsigned long startTime = millis();
  //odczytanie wartosci deafult ( odczytywana z potencjometru) oraz z sensora (fotodioda)
  deafultVal = analogRead(deafultPin);
  sensorVal = analogRead(sensorPin);
  //porownanie wartosci deafult i sensor oraz ustalenie czy otrzymywana jest wartosc true czy false
  currentBit = checkBit(deafultVal,sensorVal);
  //zapisywanie nowego bitu na rzecz najstarszego bitu
  saveBit(currentBit);
  showDebugInfo();
  //sprawdzenie czy w kodzie znajduje się klucz wiadomości
  if(checkKey(output[0],output[1],output[2],output[3],output[4],output[5],output[6])== 1){
    setMessage();
    showMessage();
  }
  //ustalenie momentu w którym mikrokontrolewr zakoczyul dzialanie w tej iteracji petli
 // unsigned long endTime = micros();
  unsigned long endTime = millis();
  //wyliczenie czasu ktory nalezy odczekac aby iteracja petli trwala okresolna wartosc czasu
  waitTime = peroid - (int)(endTime-startTime);
 //delayMicroseconds(waitTime);
 delay(waitTime);
}
void showDebugInfo(){
  Serial.println("MEsage");
  for(int i=0;i<10;i++){
      Serial.print(output[i]);
    }
  Serial.println("koniec messeage");
  Serial.print("Sensor value");
  Serial.println(sensorVal);
  Serial.print("Deafult value");
  Serial.println(deafultVal);
  
}
//funkcja sprawdzajaca akutalnie przesyłaną wartosc
bool checkBit(int deafult, int sensor){
  if(sensor>deafult){
    return true;  
  }else{
    return false;  
  }
}
//funkcja przepisujaca tablice wyrzucajac z niej najstarsza wartosc na rzecz nowej wartosci
void saveBit(bool currentBit){
    for(int i=0;i<10;i++){
      output[i] = output[i+1];  
    }
    output[10] = currentBit;
}
void showMessage(){
    Serial.print("Otrzymano Wiadomosc: ");
    Serial.print(output[7]);
    Serial.print(output[8]);
    Serial.print(output[9]);
    Serial.print(output[10]);
    Serial.println(" ");
}
void setMessage(){
  
}
//funkcja sprawdzajaca czy w wiadomosci wykryto klucz
bool checkKey(bool input0,bool input1,bool input2,bool input3,bool input4,bool input5,bool input6){
    if((input0==key[0])&&(input1==key[1])&&(input2==key[2])&&(input3==key[3])&&(input4==key[4])&&(input5==key[5])&&(input6==key[6])){
      return true;
    }else{
      return false;  
    }
  
  }
