#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1013.25)
#define pinSensorChuvaAna A1
#define pinSensorChuvaDig 8


int temperatura;
int humidade;
float pressao;
int indiceUv;
int leituraPorta;
String textRadUv;
String statusChuva;


Adafruit_BME280 bme; // I2C


unsigned long delayTime;

void setup() {
    pinMode(pinSensorChuvaDig, INPUT);
    Serial.begin(9600);
    while(!Serial);    // time to get serial running
    Serial.println(F("BME280 test"));

    unsigned status;
    status = bme.begin(0x76);
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
        Serial.print("SensorID was: 0x"); Serial.println(bme.sensorID(),16);
        Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
        Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
        Serial.print("        ID of 0x60 represents a BME 280.\n");
        Serial.print("        ID of 0x61 represents a BME 680.\n");
        while (1) delay(10);
    }
    
    Serial.println("-- Default Test --");
    delayTime = 4000;

    Serial.println();
}


void loop() { 
    getValoresBme();
    getValoresRadUv();
    printValues();
    delay(delayTime);
}

int getValoresBme() {
  temperatura = bme.readTemperature();
  pressao = bme.readPressure();
  humidade = bme.readHumidity();
}

void printValues() {
    int leituraPorta = analogRead(A0);
    Serial.print("Temperatura = ");
    Serial.print(temperatura);
    Serial.println(" °C");

    Serial.print("Pressão = ");
    Serial.print(pressao / 100.0F);
    Serial.println(" hPa");

    Serial.print("Approx. Altitude = ");
    Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
    Serial.println(" m");

    Serial.print("Humidade = ");
    Serial.print(humidade);
    Serial.println(" %");

    Serial.print("Valor porta: ");
    Serial.print(leituraPorta);
    Serial.print(" - Indice: ");
    Serial.println(indiceUv);
    Serial.print("Nível Radiação UV: ");
    Serial.println(textRadUv);

    if (digitalRead(pinSensorChuvaDig)) {
      statusChuva = "Não está chovendo";
      Serial.println(statusChuva);
    } else {
      statusChuva = "Está chovendo";
      Serial.println(statusChuva);
    }
    Serial.print("Valor analógico:");
    Serial.println(analogRead(pinSensorChuvaAna));

    Serial.println();
}

int getValoresRadUv() {
  int leituraPorta = analogRead(A0);
  //De acordo com a leitura define o indice UV corrrspondente
  if (leituraPorta <= 10) {
    indiceUv = 0;
    textRadUv = "Baixo";
  } else if (leituraPorta > 10 && leituraPorta <= 46) {
    indiceUv = 1;
    textRadUv = "Baixo";
  } else if (leituraPorta > 46 && leituraPorta <= 65) {
    indiceUv = 2;
    textRadUv = "Baixo";
  } else if (leituraPorta > 65 && leituraPorta <= 83) {
    indiceUv = 3;
    textRadUv = "Moderado";
  } else if (leituraPorta > 83 && leituraPorta <= 103) {
    indiceUv = 4;
    textRadUv = "Moderado";
  } else if (leituraPorta > 103 && leituraPorta <= 124) {
    indiceUv = 5;
    textRadUv = "Moderado";
  } else if (leituraPorta > 124 && leituraPorta <= 142) {
    indiceUv = 6;
    textRadUv = "Alto";
  } else if (leituraPorta > 142 && leituraPorta <= 162) {
    indiceUv = 7;
    textRadUv = "Alto";
  } else if (leituraPorta > 162 && leituraPorta <= 180) {
    indiceUv = 8;
    textRadUv = "Muito alto";
  } else if (leituraPorta > 180 && leituraPorta <= 200) {
    indiceUv = 9;
    textRadUv = "Muito alto";
  } else if (leituraPorta > 200 && leituraPorta <= 221) {
    indiceUv = 10;
    textRadUv = "Muito alto";
  } else {
    indiceUv = 11;
    textRadUv = "Extremo";
  }
}
