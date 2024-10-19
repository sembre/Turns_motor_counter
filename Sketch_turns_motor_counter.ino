#include <Keypad.h>
#include <LiquidCrystal.h>
#define LCD_Backlight 4
// Pin konfigurasi
const int motorPin = 13;        // Pin untuk motor
const int startButtonPin = 2;   // Pin untuk tombol start
const int switchPin = 3;        // Pin untuk saklar penghitung putaran

int count = 0;                  // Variabel untuk menyimpan jumlah putaran saat ini
int targetTurns = 0;            // Jumlah putaran yang diinput dari keypad
bool motorRunning = false;      // Status motor
bool keypadLocked = false;      // Status penguncian keypad

// Setup LCD (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(14, 15, 16, 17, 18, 19);  // Sesuaikan pin LCD dengan rangkaian Anda

// Setup keypad (4x4)
const byte ROWS = 4;  // 4 baris
const byte COLS = 4;  // 4 kolom
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {12, 11, 10, 9};    // Pin untuk baris keypad
byte colPins[COLS] = {8, 7, 6, 5};       // Pin untuk kolom keypad

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  pinMode(motorPin, OUTPUT);             // Set pin motor sebagai output
  pinMode(startButtonPin, INPUT_PULLUP); // Set pin tombol sebagai input
  pinMode(switchPin, INPUT_PULLUP);      // Set pin saklar sebagai input
  analogWrite(LCD_Backlight, 120);       // Adjust for LCD_Backlight
  lcd.begin(16, 2);                      // Inisialisasi LCD 16x2
  lcd.print("Set Turns: ");              // Pesan awal pada LCD

  Serial.begin(9600);
  Serial.println("Masukkan jumlah putaran menggunakan keypad:");
}

void loop() {
  // Baca tombol start
  if (digitalRead(startButtonPin) == LOW && !motorRunning) {
    // Pastikan motor hanya bisa mulai jika keypad sudah dikunci (dengan tombol '#')
    if (keypadLocked) {
      startMotor();
    } else {
      Serial.println("Keypad belum dikunci. Tekan '#' untuk memulai motor.");
      lcd.setCursor(0, 1);
      lcd.print("Lock first (#)     ");
    }
  }

  // Baca saklar untuk menghitung putaran
  if (digitalRead(switchPin) == LOW && motorRunning) {
    delay(10);  // Debounce
    if (digitalRead(switchPin) == LOW) {
      count++;
      Serial.print("Putaran saat ini: ");
      Serial.println(count);

      // Tampilkan putaran saat ini di LCD
      lcd.setCursor(0, 1);    // Pindah ke baris kedua
      lcd.print("Turns:     ");
      lcd.print(count);

      // Matikan motor jika jumlah putaran sudah mencapai target
      if (count >= targetTurns) {
        stopMotor();
      }
    }
  }

  // Input dari keypad
  char key = keypad.getKey();

  if (key != NO_KEY) {
    if (key == '*') {
      // Reset jumlah putaran dan buka kunci
      targetTurns = 0;
      keypadLocked = false;
      Serial.println("Jumlah putaran direset.");
      lcd.setCursor(11, 0);
      lcd.print("         ");      // Bersihkan tampilan sebelumnya
      lcd.setCursor(0, 1);
      lcd.print("Set Turns:       "); // Pesan untuk memasukkan kembali
    }

    // Input jumlah putaran hanya jika keypad belum terkunci
    if (!keypadLocked) {
      if (key >= '0' && key <= '9') {
        targetTurns = targetTurns * 10 + (key - '0');
        Serial.print("Jumlah putaran yang diinginkan: ");
        Serial.println(targetTurns);

        // Tampilkan jumlah putaran diinginkan di LCD
        lcd.setCursor(11, 0);   // Pindah ke posisi di baris pertama
        lcd.print(targetTurns);
      } else if (key == '#') {
        // Kunci input keypad setelah tombol '#' ditekan
        if (targetTurns > 0) {
          keypadLocked = true;
          Serial.println("Keypad dikunci.");
          lcd.setCursor(0, 1);
          lcd.print("Locked            ");
        } else {
          Serial.println("Masukkan jumlah putaran sebelum mengunci.");
          lcd.setCursor(0, 1);
          lcd.print("Set turns first   ");
        }
      }
    }
  }
}

void startMotor() {
  digitalWrite(motorPin, HIGH);  // Nyalakan motor
  motorRunning = true;
  count = 0;                     // Reset hitungan putaran
  Serial.println("Motor mulai berjalan...");
  lcd.setCursor(0, 1);           // Tampilkan pesan di baris kedua
  lcd.print("Turns: 0            ");   // Kosongkan jumlah putaran awal
}

void stopMotor() {
  digitalWrite(motorPin, LOW);   // Matikan motor
  motorRunning = false;
  Serial.println("Motor berhenti.");
  lcd.setCursor(0, 1);
  lcd.print("Motor Stopped ");
}
