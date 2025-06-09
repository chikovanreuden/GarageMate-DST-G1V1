const int led_red_pin = 3;
const int led_yellow_pin = 4;
const int led_green_pin = 2;

const int trig_Pin = 6;  
const int echo_Pin = 5; 

const int poti_1_pin = A2;
const int poti_2_pin = A3;

float duration, distance;

float threshhold_red, threshhold_yellow;

void setup() {  
  pinMode(led_red_pin, OUTPUT); 
  pinMode(led_yellow_pin, OUTPUT); 
  pinMode(led_green_pin, OUTPUT); 

	pinMode(trig_Pin, OUTPUT);  
	pinMode(echo_Pin, INPUT);

  digitalWrite(led_green_pin, HIGH);
  digitalWrite(led_yellow_pin, HIGH);
  digitalWrite(led_red_pin, HIGH);

	Serial.begin(9600);

} 

int VALUE_MIN = 0;
int VALUE_MAX = 100;

void loop() {
  int analogValue1 = analogRead(poti_1_pin);
  int value = map(analogValue1, 0, 1023, VALUE_MIN, VALUE_MAX);
  Serial.print( "poti_1  " );
  Serial.print( analogValue1 );
  Serial.print( ", " );
  Serial.println( value );

  int analogValue2 = analogRead(poti_2_pin);
  int value2 = map(analogValue2, 0, 1023, VALUE_MIN, VALUE_MAX);
  Serial.print( "poti_2  " );
  Serial.print( analogValue2 );
  Serial.print( ", " );
  Serial.println( value2 );

	digitalWrite(trig_Pin, LOW);  
	delayMicroseconds(2);  
	digitalWrite(trig_Pin, HIGH);  
	delayMicroseconds(10);  
	digitalWrite(trig_Pin, LOW);

  duration = pulseIn(echo_Pin, HIGH);

  distance = (duration*.0343)/2;
  Serial.print( "distance " );
  Serial.println( distance );
  threshhold_red = 5.00 + value;

  threshhold_yellow = threshhold_red + 1.00 + value2;
  threshhold_yellow = threshhold_yellow * 1.50;

  // if( distance <= 30.00 ) {
  if( distance < threshhold_red ) {
    digitalWrite(led_green_pin, LOW);
    digitalWrite(led_yellow_pin, LOW);
    digitalWrite(led_red_pin, HIGH);
  // } else if( distance <= 80.00 ) {
  } else if( distance < threshhold_yellow ) {
    digitalWrite(led_green_pin, LOW);
    digitalWrite(led_yellow_pin, HIGH);
    digitalWrite(led_red_pin, LOW);
  } else {
    digitalWrite(led_green_pin, HIGH);
    digitalWrite(led_yellow_pin, LOW);
    digitalWrite(led_red_pin, LOW);
  }
  delay(200); 

}
