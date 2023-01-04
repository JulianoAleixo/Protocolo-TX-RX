# Protocolo-TX-RX
Um protocolo simples criado para comunicar 2 arduinos.


Descrição: 

  Esse projeto foi feito durante o projeto integrado do segundo trimestre da turma de Telecomunicações de 2022 da ETE FMC.
  
  O objetivo era transmitir uma informação de um arduino mega para o outro, utilizando no transmissor um divisor de tensão para 4 simbolos diferentes e um multiplexador. Para isso, foi necessário utilizar conceitos de mascaramento de bit e tratamento de bit.
  
  Além de montar o circuito, foi necessário criar um protocolo simples, mas eficiente que contem os conceitos iniciais de um protocolo de comunicação.
  
  
Funcionalidades:

  O protocolo pode ser adaptado para diferentes usos. Um exemplo é a comunicação entre diferentes MCU ou com o computador utilizando a serial dele.
  
  
Como utilizar: 

  O formato do protocolo é bem simples: Um caracter de início (STX), um caracter para o endereço do TX, um caracter para o endereço do RX, informação 1, caracter separador, informação 2, caracter de fim (ETX). Um exemplo de mensagem seria "<12Ola_Mundo>", sendo o '<' e '>' o STX e ETX, '1' e '2' os endereços de TX e RX e o separador o '_'. 
  
  
Autores:

  Juliano Moreira Aleixo
  
  Lindsey Mariane Souza e Silva
  
Orientadores:

  Ana Letícia Gomes Gonçalves 
  
  Alan Lima Lemes
