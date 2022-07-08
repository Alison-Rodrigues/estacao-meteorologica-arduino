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
int leitura_porta;
String textRadUv;


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
    int leitura_porta = analogRead(A0);
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
    Serial.print(leitura_porta);
    Serial.print(" - Indice: ");
    Serial.println(indiceUv);
    Serial.print("Nível Radiação UV: ");
    Serial.println(textRadUv);

    if (digitalRead(pinSensorChuvaDig)) {
    Serial.println("Não está chovendo");
    } else {
      Serial.println("Está chovendo");
    }
    Serial.print("Valor analógico:");
    Serial.println(analogRead(pinSensorChuvaAna));

    Serial.println();
}

int getValoresRadUv() {
  int leitura_porta = analogRead(A0);
  //De acordo com a leitura define o indice UV corrrspondente
  if (leitura_porta <= 10) {
    indiceUv = 0;
    textRadUv = "Baixo";
  } else if (leitura_porta > 10 && leitura_porta <= 46) {
    indiceUv = 1;
    textRadUv = "Baixo";
  } else if (leitura_porta > 46 && leitura_porta <= 65) {
    indiceUv = 2;
    textRadUv = "Baixo";
  } else if (leitura_porta > 65 && leitura_porta <= 83) {
    indiceUv = 3;
    textRadUv = "Moderado";
  } else if (leitura_porta > 83 && leitura_porta <= 103) {
    indiceUv = 4;
    textRadUv = "Moderado";
  } else if (leitura_porta > 103 && leitura_porta <= 124) {
    indiceUv = 5;
    textRadUv = "Moderado";
  } else if (leitura_porta > 124 && leitura_porta <= 142) {
    indiceUv = 6;
    textRadUv = "Alto";
  } else if (leitura_porta > 142 && leitura_porta <= 162) {
    indiceUv = 7;
    textRadUv = "Alto";
  } else if (leitura_porta > 162 && leitura_porta <= 180) {
    indiceUv = 8;
    textRadUv = "Muito alto";
  } else if (leitura_porta > 180 && leitura_porta <= 200) {
    indiceUv = 9;
    textRadUv = "Muito alto";
  } else if (leitura_porta > 200 && leitura_porta <= 221) {
    indiceUv = 10;
    textRadUv = "Muito alto";
  } else {
    indiceUv = 11;
    textRadUv = "Extremo";
  }
}
