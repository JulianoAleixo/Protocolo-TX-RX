bool podeLer, podePrintar;
byte save[20], rx, msgEmByte;
int addressTX, addressRX, val, stx;

void setup() {
  pinMode(A1, INPUT);
  pinMode(2, INPUT_PULLUP);
  Serial.begin(9600);

  attachInterrupt(digitalPinToInterrupt(2), pulso, FALLING);
}

void loop() {
  if (podeLer == true) {
    limpar();
    leByte();
    podeLer = false;

    if (save[0] != 60) {
      limpar();  
    }

    if (save[1] == 0b00110001) { // 1?
      addressTX = 1;
    }
    if (save[1] == 0b00110010) { // 2?
      addressTX = 2;
    }
    if (save[1] == 0b00110011) { // 3?
      addressTX = 3;
    }
    if (save[1] == 0b00110100) { // 4?
      addressTX = 4;
    }

    if (save[2] == 0b00110001) { // 1?
      addressRX = 1;
    }
    if (save[2] == 0b00110010) { // 2?
      addressRX = 2;
    }
    if (save[2] == 0b00110011) { // 3?
      addressRX = 3;
    }
    if (save[2] == 0b00110100) { // 4?
      addressRX = 4;
    }

    if (addressRX == 2) {
      Serial.print("Transmissor: ");
      Serial.println(addressTX);
      Serial.println(" ");
      Serial.print("Receptor: ");
      Serial.println(addressRX);
      Serial.println(" ");
      Serial.print("Mensagem: ");
      
      for (int i = 3; i < 20; i++) {
        if (save[i] == 62) {
          save[i] = 0;
        }
        Serial.write(save[i]);
      }
      Serial.println(" ");
    }
    else {
      limpar();  
    }
  }
}

void leByte() {
  msgEmByte = 0;
  //de 4x que executa o for de dentro vai executar uma vez o for de fora
  for (int j = 0; j < 20; j++) { // executa de 20 em 20
    for (int i = 0; i < 4; i++) { // Faz um byte, executa 80 vezes
      val = analogRead(A1);
      if ((val > 50 && val < 200)) {
        rx = 0 << 6;
      }
      else if ((val > 300 && val < 450)) {
        rx = 1 << 6;
      }
      else if ((val > 550 && val < 700)) {
        rx = 2 << 6;
      }
      else if ((val > 800 && val < 950)) {
        rx = 3 << 6;
      }
      msgEmByte = msgEmByte >> 2;
      msgEmByte = msgEmByte + rx;
      delay(83);
    }
    save[j] = msgEmByte;
    if (save[j] == 62) { // ETX?
      break;
    }
  }
}

void pulso() {
  delay(40); //começa a ler a partir da metade do nível do sinal
  podeLer = true;
}

void limpar() { // Limpa todas as posições do Buffer
  for (int i = 0; i < 20; i++) {
    save[i] = 0;  
  }  
}
