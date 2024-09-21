// C++ code
//

// # DEFINE NOME AOS COMPONENTES/PORTAS


//BUZZER
#define buzzer 8

//LED RGB
#define ledVermelho 10
#define ledVerde 9
#define ledAzul 11

//PORTA QUE VERIFICA O TOQUE DO ARAME
#define touch 7

//VIDAS QUE DEFINEM O ESTADO DOS LEDS VERDES
#define vida1 3
#define vida2 5
#define vida3 6

//BOTÃO QUE RENICIA O JOGO CASO GANHE OU PERCA
#define reset 4

//ARAME FINAL QUE INDICA QUE O JOGADOR GANHOU
#define vitoria 12


//DEFINAÇÃO DE VARIÁVEIS

int vidas = 3; //NÚMERO DE VIDAS

bool safe = true; //ESTADO DE TOQUE
int cont = 0; //CONTAGEM PARA O CIRCUITO NÃO CONTINUAR LENDO O TOQUE
int touchI; //VARIÁVEL QUE VAI SER USADA PARA ARMAZENAR A INFORMAÇÃO DE INPUT
int resetI;
int vitoriaI;


void setup()
{
  pinMode(ledVermelho, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAzul, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(vida1, OUTPUT);
  pinMode(vida2, OUTPUT);
  pinMode(vida3, OUTPUT);
  pinMode(reset, INPUT_PULLUP);//COM PULL_UP NÃO É NECESSÁRIO O USO DE UM RESISTOR
  pinMode(touch, INPUT_PULLUP);
  pinMode(vitoria, INPUT_PULLUP);
}

void loop()
{
  touchI = digitalRead(touch);//touchI TERÁ O VALOR DA LEITURA DE touch
  resetI = digitalRead(reset);
  vitoriaI = digitalRead(vitoria);
  
  if(vitoriaI == 0){ //SE O JOGADOR GANHAR / SE HAVER TOQUE
    
    
    while(resetI == 1){//ENQUANTO RESET NÃO FOR APERTADO
      //VERDE
      analogWrite(ledVerde, 255);
      delay(300);
      
      //VERDE ÁGUA
      analogWrite(ledAzul, 128);
      delay(300);
      
      //CIANO
      analogWrite(ledVerde, 255);
      analogWrite(ledAzul, 255);
      delay(300);
      
      //AZUL CLARO
      analogWrite(ledVerde, 128);
      analogWrite(ledAzul, 255);
      delay(300);
      
      //AZUL ESCURO
      analogWrite(ledVerde, 0);
      analogWrite(ledAzul, 255);
      delay(300);
      
      //ROXO
      analogWrite(ledVermelho, 127);
      analogWrite(ledAzul, 255);
      delay(300);
      
      //ROSA
      analogWrite(ledVermelho, 255);
      analogWrite(ledAzul, 255);
      delay(300);
      
      //ROSA SHOCK
      analogWrite(ledVermelho, 255);
      analogWrite(ledAzul, 128);
      delay(300);
      analogWrite(ledVermelho, 0);
      analogWrite(ledAzul, 0);
      
      resetI = digitalRead(reset);//O VALOR É NOVAMENTE INICIADO POIS NÃO É POSSÍVEL SAIR DO LOOP
      
	  //REINICIA O JOGO
      if(resetI == 0){
        analogWrite(ledVerde, 0);
        analogWrite(ledVermelho, 0);
        analogWrite(ledAzul, 0);
        vidas=3;
        safe=true;
        cont=0;
        break;
      }
      
    }
  }
  
  if(vidas > 0){ //SE O JOGADOR ETIVER VIVO
    
    if(touchI == 0){ //CASO HAJA O TOQUE DOS ARAMES
      
      vidas--;
      safe = false;
      for(int i = 0; i<4; i++){//LED PICA EM VERMELHO E BUZZER É ATIVADO
        tone(buzzer, 150*(vidas));
        digitalWrite(ledVermelho, 255);
        delay(200); 
        digitalWrite(ledVermelho, 0);
        noTone(buzzer); 
        delay(200);
      }
      
    }
  }
  
  
  if (vidas==3) {//SE AS VIDAS ESTIVEREM CHEIAS 
	  
    analogWrite(vida1, 255);
    analogWrite(vida2, 255);
    analogWrite(vida3, 255);
    
    
    } else if (vidas==2) {//SE TIVER 2 VIDAS
      analogWrite(vida1, 255);
      analogWrite(vida2, 255);
    
      while(safe==false){//ENQUANTO A POSIÇÃO FOR DESFAVORÁVEL
          for(int i = 0; i <256; i++){//OSCILA A POTENCIA DO LED VERMELHO
            analogWrite(vida3,i);
            delay(5);
          }
        analogWrite(vida3,0);
        cont++;
        if(cont>2){//SE A CONTAGEM FOR MAIOR QUE 2
            safe=true;//POSIÇÃO FAVORÁVEL
          	cont=0;//CONTAGEM VOLTA A ZERO PARA AS PRÓXIMAS CONTAGENS
          }
      }
    
    analogWrite(vida3, 0);
      
    
    } else if (vidas==1) {//SE TIVER 1 VIDA
      analogWrite(vida1, 255);
      analogWrite(vida3, 0);
      
      while(safe==false){
          for(int i = 0; i <256; i++){
            analogWrite(vida2,i);
            delay(5);
          }
        analogWrite(vida2,0);
        cont++;
        if(cont>2){
            safe=true;
          	cont=0;
          }
      }
    
    analogWrite(vida2, 0);
      
    
    } else if (vidas==0) {//SE NÃO TIVER VIDAS
      analogWrite(vida1,0);
      analogWrite(vida2,0);
      analogWrite(vida3,0);
    
      if(resetI == 1){//SE NÃO HOUVER TOQUE NO BOTÃO RESET
        analogWrite(ledVermelho, 255);
        delay(200);
        analogWrite(ledVermelho,0);
        delay(200);

      }else{//CASO HAJA TOQUE NO BOTÃO RESET
        digitalWrite(ledVermelho, 0);
        vidas=3;
        safe=true;
        cont=0;
      }
      
   }
 
}