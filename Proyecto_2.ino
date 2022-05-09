#define mic 8
#define led1 2

#define trig 10
#define echo 9
#define led2 3

#define led3 4

#define green 12
#define red 13 

int ldr=A2;
#define led4 5

int val;
int valA;
int estado=0;

int duracion;
int distancia;

int valLdr=0;

int valA2;

//ASM
extern "C"{
  void START();
  
}

void setup() {
  //Monitor Serial
  Serial.begin(9600);
  
  pinMode(mic, INPUT);
  pinMode(led1 , OUTPUT);

  pinMode(echo, INPUT);
  pinMode(trig , OUTPUT);
  pinMode(led2 , OUTPUT);

  pinMode(led3 , OUTPUT);

  pinMode(green , OUTPUT);
  pinMode(red , OUTPUT);

  pinMode(led4 , OUTPUT);
  
}

void loop() {
  //ASM
  START();
  //Sensor de sonido
  //Salida analogica que define el valor minimmo para su activación
  valA = analogRead(A0);
  
  Serial.println(" ");
  Serial.print("Limite de sonido: ");
  Serial.println(valA);
  val = digitalRead(mic);
  if(val == HIGH){
    estado = !estado;
    delay(200);  
  }
  digitalWrite(led1 , estado);
  
  //Sensor ultrasonico
  digitalWrite(trig, HIGH);
  delay(1);
  digitalWrite(trig, LOW);
  duracion = pulseIn(echo, HIGH);
  //Valor especificado por el fabricante
  distancia = duracion/59;
  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm ");
  delay(200);
  if (distancia <=30 and distancia >=0){
    digitalWrite(led2 , HIGH);
    delay(distancia * 10);
    digitalWrite(led2 , LOW);
  }

  //Sensor ldr
  valLdr = analogRead(A2);
  Serial.print("LDR: ");
  Serial.println(valLdr);
  if(valLdr > 100){
    digitalWrite(led3 , HIGH);
    delay(500);  
    digitalWrite(led3 , LOW);
  }

  //Sensor temt600
  valA2 = analogRead(A1);
  Serial.print("Luz ambiental: " );
  Serial.println(valA2);
  //Pruebas de flash
  if (valA2 >= 870){
    digitalWrite(led4 , HIGH);
  }
  else{
    digitalWrite(led4 , LOW);
  }

  //Green red led  
  if(distancia <=30 and distancia >=0 and val == HIGH and valA2>=870 ){
    digitalWrite(red , HIGH);
    digitalWrite(green , LOW);   
  }else if(val == HIGH and valA2 >= 870 and valLdr > 100 ){
    digitalWrite(red , HIGH);
    digitalWrite(green , LOW);
    delay(200);
    digitalWrite(red , LOW);
    digitalWrite(green , HIGH);
  }else{
    digitalWrite(red , LOW);
    digitalWrite(green , HIGH);
  }

  Serial.println("-----------------------");
        
}
