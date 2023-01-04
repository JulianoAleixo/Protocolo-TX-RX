byte buf[20];

byte mask[4];
byte buf_simb[80];

int cont = 2;
bool buffer_certo = false;
bool tx_pronto = false;
bool tx_esperando = false;
bool tx_go = false;

int cont_simb = 0;

// const int addressTX = 0b00110001; // TX 1
const int addressTX = 0b00110010; // TX 2
// const int addressTX = 0b00110011; // TX 3
// const int addressTX = 0b00110100; // TX 4

void setup() {
  for (int j = 0; j < 20; j++) {
    buf[j] = 0;
  }

  pinMode(22, OUTPUT);
  pinMode(24, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(28, OUTPUT);

  pinMode(3, INPUT_PULLUP);

  digitalWrite(22, 0);
  digitalWrite(24, 0);
  digitalWrite(26, 0);
  digitalWrite(28, 0);

  attachInterrupt(digitalPinToInterrupt(3),mandar,FALLING);

  Serial.begin(9600);
}

void loop() {
  if(tx_go==true)
  {
    enviaSimbolo();
  }

  
  while ((Serial.available() > 0) && (tx_esperando == false)) {
    buf[cont] = Serial.read();
    if (buf[cont] == '\n') { // ETX _ ">"
      Serial.println("Recebeu ETX");
      buffer_certo = true;
      
      buf[0] = 60;
      buf[1] = addressTX;
      buf[cont + 1] = 62;
      break;
    }
    if (cont > 19) {
      Serial.println("ERRO");
      Serial.println(buf[0]);

      for (int j = 0; j < 20; j++) { // Zera o Buffer
        buf[j] = 0;
      }

      cont = 2;
      buffer_certo = false;
      break;
    }
    cont++;
  }

  if (buffer_certo == true) {
    Serial.println("Recebeu buffer certo"); 
    buffer_certo = false;
    tx_esperando = true;
    for (int j = 0; j <= cont; j++) {
      Serial.println(buf[j], BIN);
    }
    bitParaSimbolo();
    cont = 2;
    Serial.println("Quadro esperando para ser enviado");
  }
}

void bitParaSimbolo() {

  mask[0] = 0b00000011; 
  mask[1] = 0b00001100;
  mask[2] = 0b00110000;
  mask[3] = 0b11000000;

  byte resul = 0;
  cont_simb = 0;

  for (int i = 0; i <= cont; i++) {
    for (int j = 0; j < 4; j++) {
      resul = buf[i] & mask[j];

      if (j == 1) {
        resul = resul >> 2;
      }
      else if (j == 2) {
        resul = resul >> 4;
      }
      else if (j == 3) {
        resul = resul >> 6;
      }

      if (resul == 0x00) {
        buf_simb[cont_simb] = 0x00;
      }
      if (resul == 0x01) {
        buf_simb[cont_simb] = 0x01;
      }
      if (resul == 0x02) {
        buf_simb[cont_simb] = 0x02;
      }
      if (resul == 0x03) {
        buf_simb[cont_simb] = 0x03;
      }
      cont_simb++;
    }
  }
  tx_pronto = true;
}

void enviaSimbolo() {
  for (int i = 0; i < cont_simb; i++) {
    if (buf_simb[i] == 0x00) { // 00
      digitalWrite(22, 1);
      digitalWrite(24, 0);
      digitalWrite(26, 0);
      digitalWrite(28, 0);
      delay(83);
    }
    else if (buf_simb[i] == 0x01) { // 01
      digitalWrite(22, 0);
      digitalWrite(24, 1);
      digitalWrite(26, 0);
      digitalWrite(28, 0);
      delay(83);
    }
    else if (buf_simb[i] == 0x02) { // 10     00-00-01-10
      digitalWrite(22, 0);
      digitalWrite(24, 0);
      digitalWrite(26, 1);
      digitalWrite(28, 0);
      delay(83);
    }
    if (buf_simb[i] == 0x03) { // 11
      digitalWrite(22, 0);
      digitalWrite(24, 0);
      digitalWrite(26, 0);
      digitalWrite(28, 1);
      delay(83);
    }  
  }
  for (int j = 0; j < 20; j++) {
      buf[j] = 0;
    }
  digitalWrite(22, 0);
  digitalWrite(24, 0);
  digitalWrite(26, 0);
  digitalWrite(28, 0);
  Serial.println("Fim");

  tx_esperando = false;
  tx_pronto = false;
  tx_go = false;
}

void mandar() {
  if (tx_pronto == true) {
      tx_go=true;
  }
}
