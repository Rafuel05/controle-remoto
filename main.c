#include <16F877A.h>
#device ADC=16

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O

#use delay(crystal=4000000)
#use i2c(Master, Fast=100000, sda=PIN_C4, scl=PIN_C3, force_sw)  
#include "i2c_Flex_LCD.c"

// Defini��es dos pinos
#define IR_PIN      PIN_B0      // Pino do receptor IR
#define RELE1_PIN   PIN_D0      // Pino do rel� 1
#define RELE2_PIN   PIN_D1      // Pino do rel� 2

// Vari�veis globais
unsigned int16 ir_code[2];      // Array para armazenar o c�digo IR

void read_ir_code() {
   int8 i;
   unsigned int16 count;
   
   // Limpa os c�digos anteriores
   ir_code[0] = 0;
   ir_code[1] = 0;
   
   // Aguarda o in�cio do sinal (quando o pino vai para 0)
   while(input(IR_PIN) == 1);
   delay_ms(4); // Aguarda meio do pulso inicial
   
   // L� os bits
   for(i = 0; i < 32; i++) {
      count = 0;
      // Aguarda pulso subir
      while(input(IR_PIN) == 0 && count < 100) {
         count++;
         delay_us(100);
      }
      
      count = 0;
      delay_us(600); // Aguarda tempo de refer�ncia
      
      // L� o bit
      if(input(IR_PIN) == 0) { // Pulso longo = 1
         if(i < 16) {
            ir_code[0] |= (1 << i);
         } else {
            ir_code[1] |= (1 << (i-16));
         }
      }
      
      // Aguarda fim do bit
      while(input(IR_PIN) == 1 && count < 100) {
         count++;
         delay_us(100);
      }
   }
}

void main() {
   // Inicializa��o do LCD
   lcd_init(0x4E, 16, 2);
   lcd_backlight_led(ON);
   
   // Configura��o dos pinos
   set_tris_b(0b00000001);  // RB0 como entrada (IR)
   set_tris_d(0b11111100);  // RD0 e RD1 como sa�da (Rel�s)
   
   // Inicializa��o das portas
   output_d(0x00);          // Todos os pinos de PORTD em n�vel baixo
   
   // Mensagem inicial
   printf(lcd_putc, "\fEsperando Sinal");
   printf(lcd_putc, "\nAperte botao...");
   
   while(TRUE) {
      // Se detectar sinal IR (pino vai para 0)
      if(input(IR_PIN) == 0) {
         // L� o c�digo
         read_ir_code();
         
         // Mostra o c�digo no LCD
       
         
         if(ir_code[0] == 0x00F0 && ir_code[1] == 0x00FB) {
            output_toggle(RELE1_PIN);  // Inverte estado do rel� 1
          
            output_toggle(RELE2_PIN);  // Inverte estado do rel� 2
           
            printf(lcd_putc, " \f Lampada 1");
            printf(lcd_putc, " \n Lampada 2");
         }
         
         
         // Verifica qual bot�o foi pressionado
         else if((ir_code[0] == 0x00FE && ir_code[1] == 0x0074) 
         || (ir_code[0] == 0x00F0 && ir_code[1] == 0x00F7)) {
            output_toggle(RELE1_PIN);  // Inverte estado do rel� 1
            printf(lcd_putc, " \f Lampada 1");   // Indica no LCD
         }
         else if((ir_code[0] == 0x00FE && ir_code[1] == 0x0072) || 
              
         (ir_code[0] == 0x00F0 && ir_code[1] == 0x00F5)) {  
            output_toggle(RELE2_PIN);  // Inverte estado do rel� 2
            printf(lcd_putc, " \f Lampada 2");   // Indica no LCD
         }
         else{
            printf(lcd_putc, "\fCod: %04LX", ir_code[0]);
            printf(lcd_putc, "\n     %04LX", ir_code[1]);
         }
         
         // Espera soltar o bot�o e um tempo extra
         while(input(IR_PIN) == 0);
         delay_ms(200);
      }
   }
}
