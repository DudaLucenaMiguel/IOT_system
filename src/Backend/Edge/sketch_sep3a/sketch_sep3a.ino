#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define I2C_SDA 4
#define I2C_SCL 5

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Adafruit_MPU6050 mpu;

bool mpuOnline = false;

void setup() {
  Serial.begin(115200);

  // Inicializa I2C no ESP32-C3
  Wire.begin(I2C_SDA, I2C_SCL);

  // 1. Inicializa OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Falha ao inicializar o display OLED!");
    while (true); // Sem display não há como prosseguir o teste visual
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Iniciando sensores...");
  display.display();

  // 2. Tenta inicializar MPU-6050 no endereco padrao (0x68)
  if (mpu.begin(0x68, &Wire)) {
    mpuOnline = true;
    Serial.println("MPU6050 conectado com sucesso!");
    
    // Configuracoes basicas de escala
    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  } else {
    // Tenta endereco alternativo (0x69)
    if (mpu.begin(0x69, &Wire)) {
      mpuOnline = true;
      Serial.println("MPU6050 conectado no endereco 0x69!");
    } else {
      mpuOnline = false;
      Serial.println("ERRO: MPU6050 nao encontrado!");
    }
  }

  delay(1000);
}

void loop() {
  display.clearDisplay();
  display.setCursor(0, 0);

  display.println("--- STATUS I2C ---");
  display.println("OLED (0x3C): OK");

  if (mpuOnline) {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    display.println("MPU6050: OK");
    display.println("---------------------");
    display.printf("Acel X: %.1f m/s2\n", a.acceleration.x);
    display.printf("Acel Y: %.1f m/s2\n", a.acceleration.y);
    display.printf("Acel Z: %.1f m/s2\n", a.acceleration.z);
  } else {
    display.println("MPU6050: NAO DETECTADO");
    display.println("---------------------");
    display.println("Checar: pinos soltos,");
    display.println("falta de solda ou");
    display.println("defeito no modulo.");
  }

  display.display();
  delay(200);
}