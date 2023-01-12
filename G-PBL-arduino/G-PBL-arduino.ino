int TRIG = 0;
int ECHO = 1;
int get_thermoPin = 2; // 体温受け取り用
int raspy_thermoPin = 3; // raspyへの体温出力用
int check = 4;

double duration = 0;
double distance = 0;
double speed_of_sound = 331.5 + 0.6 * 15; // 15℃の気温の想定
double thermo = 0;
double get_thermo = 0;
double raspy_thermo = 0;
double checking = 0;

void setup(){
  Serial.begin( 9600 );

  pinMode(ECHO, INPUT );
  pinMode(TRIG, OUTPUT );
  pinMode(get_thermoPin, INPUT);
  pinMode(raspy_thermoPin, OUTPUT);
  pinMode(check,INPUT);
}

void loop() {
  digitalWrite(TRIG, LOW); 
  delayMicroseconds(2); 
  digitalWrite( TRIG, HIGH );
  delayMicroseconds( 10 ); 
  digitalWrite( TRIG, LOW );
  duration = pulseIn( ECHO, HIGH ); // 往復にかかった時間が返却される[マイクロ秒]

  if (duration > 0) {
    duration = duration / 2; // 往路にかかった時間
    distance = duration * speed_of_sound * 100 / 1000000;
    
    if(distance <= 40) {
      Serial.print("ON\n");
      /*    
       ここで体温測定のプログラム取る
       
      */
      
       thermo = distance;    // 実際にはthermo = analogread(get_thermo) 距離40cmを40℃としてテスト
       raspy_thermo = thermo * 1024 / 40;   // 40℃までをサンプリングレート1024でA/D変換
       
       /*確認用
       Serial.print("Analog : ");
       Serial.print(thermo );
       Serial.print(" A/D : ");
       Serial.print(raspy_thermo );
       Serial.print(" D/A : "); 
       Serial.print(raspy_thermo * 40 / 1024 );
       Serial.print("\n");
       */

       analogWrite(raspy_thermoPin,raspy_thermo); // raspyへ0~1024で入力
     
    }else{
      Serial.print("OFF\n");
    }
  }

  delay(200);
}
