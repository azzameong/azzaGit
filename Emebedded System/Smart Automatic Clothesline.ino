#define KIPAS_A 2
#define KIPAS_B 3
#define DINAMO_A 4
#define DINAMO_B 5
#define LED 6
#define tombolOn 8
#define tombolOff 9
#define potentio A2
#define LDR A1
#define raindrop A0

int state = 0;
int LDR_threshold = 1000;
int state_keluar = HIGH;

int raindrop_val = 0;
int LDR_val = 0;

int waktuSensor_sebelum = 0;

int kondisi = 0;
int kondisi_sebelum = 0;

int posisi = 0;

byte speed = 15;

void cekKondisi();
void mesinMati();
void menuSetting();

void setup() {
  pinMode(DINAMO_A, OUTPUT);
  pinMode(DINAMO_B, OUTPUT);
  pinMode(KIPAS_A, OUTPUT);
  pinMode(KIPAS_B, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(tombolOn, INPUT_PULLUP);
  pinMode(tombolOff, INPUT_PULLUP);
  pinMode(LDR, INPUT);
  pinMode(raindrop, INPUT);
  pinMode(potentio, INPUT);

  Serial.begin(9600);
}

void loop() {
  int tombolOn_state = digitalRead(tombolOn);
  int tombolOff_state = digitalRead(tombolOff);

  if (tombolOff_state == LOW) {
    mesinMati();
    state = 0;
  }

  if (tombolOn_state == LOW) {
    int waktuTekan_tombol = millis();

    while (tombolOn_state == LOW) {  //menunggu tombol dilepas
      tombolOn_state = digitalRead(tombolOn);
    }

    int waktuLepas_tombol = millis();

    if (waktuLepas_tombol - waktuTekan_tombol >= 3000) {  //tombol ditekan lebih dari 3 detik
      menuSetting();
    } else {  //tombol ditekan kurang dari 3 detik
      state = 1;
    }
  }

  if (state == 1) {
    cekKondisi();
  }
}


void cekKondisi() {
  //MESIN MENYALA
  digitalWrite(LED, HIGH);

  int waktuSensor = millis();

  if ((waktuSensor - waktuSensor_sebelum) > 2000) {
    waktuSensor_sebelum = waktuSensor;
    raindrop_val = analogRead(raindrop);  //BACA SENSOR RAINDROP
    LDR_val = analogRead(LDR);            //BACA SENSOR LDR
    Serial.println(LDR_val);
    Serial.println(raindrop_val);
  }

  if (LDR_val > LDR_threshold && raindrop_val > 400) kondisi = 1;       //KONDISI TERANG KERING
  else if (LDR_val < LDR_threshold && raindrop_val < 400) kondisi = 2;  //KONDISI GELAP BASAH
  else if (LDR_val > LDR_threshold && raindrop_val < 400) kondisi = 3;  //KONDISI TERANG BASAH
  else if (LDR_val < LDR_threshold && raindrop_val > 400) kondisi = 4;  //KONDISI GELAP KERING

  if (kondisi_sebelum != kondisi) {
    kondisi_sebelum = kondisi;

    switch (kondisi) {
      case 1:
        Serial.println("terang kering");

        if (posisi == 0) {
          digitalWrite(DINAMO_A, 0);
          digitalWrite(DINAMO_B, speed);
          posisi = 1;
        }
        digitalWrite(KIPAS_A, LOW);
        digitalWrite(KIPAS_B, LOW);

        delay(150);
        //BERHENTI
        digitalWrite(DINAMO_A, 0);
        digitalWrite(DINAMO_B, 0);
        break;

      case 2:
        Serial.println("gelap basah");

        if (posisi == 1) {
          digitalWrite(DINAMO_A, speed);
          digitalWrite(DINAMO_B, 0);
          posisi = 0;
        }
        digitalWrite(KIPAS_A, HIGH);
        digitalWrite(KIPAS_B, LOW);

        delay(150);
        //BERHENTI
        digitalWrite(DINAMO_A, 0);
        digitalWrite(DINAMO_B, 0);
        break;

      case 3:
        Serial.println("terang basah");

        if (posisi == 1) {
          digitalWrite(DINAMO_A, speed);
          digitalWrite(DINAMO_B, 0);
          posisi = 0;
        }
        digitalWrite(KIPAS_A, HIGH);
        digitalWrite(KIPAS_B, LOW);

        delay(150);
        //BERHENTI
        digitalWrite(DINAMO_A, 0);
        digitalWrite(DINAMO_B, 0);
        break;

      case 4:
        Serial.println("gelap kering");

        if (posisi == 1) {
          digitalWrite(DINAMO_A, speed);
          digitalWrite(DINAMO_B, 0);
          posisi = 0;
        }
        digitalWrite(KIPAS_A, LOW);
        digitalWrite(KIPAS_B, LOW);

        delay(150);
        //BERHENTI
        digitalWrite(DINAMO_A, 0);
        digitalWrite(DINAMO_B, 0);
        break;
    }
  }
  Serial.println(posisi);
}

void mesinMati() {
  //MESIN MATI
  digitalWrite(LED, LOW);
  kondisi_sebelum = 0;

  if (posisi == 1) {
    digitalWrite(DINAMO_A, speed);
    digitalWrite(DINAMO_B, 0);
    posisi = 0;
  }
  digitalWrite(KIPAS_A, LOW);
  digitalWrite(KIPAS_B, LOW);

  delay(150);
  //BERHENTI
  digitalWrite(DINAMO_A, 0);
  digitalWrite(DINAMO_B, 0);
}

void menuSetting() {
  //SET THRESHOLD LDR
  for (int i = 1; i <= 3; i++) {
    digitalWrite(LED, HIGH);
    delay(500);
    digitalWrite(LED, LOW);
    delay(500);
  }

  do {
    int potentio_val = analogRead(potentio);
    Serial.println(potentio_val);
    LDR_threshold = map(potentio_val, 0, 1023, 0, 1023);
    int tombolOn_state = digitalRead(tombolOn);
    state_keluar = tombolOn_state;
    Serial.println(state_keluar);
  } while (state_keluar == HIGH);
}
