#include <stdio.h>
#include <stdint.h>

typedef union {

uint8_t byte;
struct{
	uint8_t bit0 : 1; /*Pin 0 > Led0*/
	uint8_t bit1 : 1;
	uint8_t bit2 : 1;
	uint8_t bit3 : 1;
	uint8_t bit4 : 1;
	uint8_t bit5 : 1;
	uint8_t bit6 : 1;
	uint8_t bit7 : 1;/*Pin 7 > Led7*/
}bits;
} Puerto_t;

volatile Puerto_t PORTA_SIM;

const uint8_t PATRONES[] = {
    0b00000001,
    0b00000011,
    0b00000111,
    0b00001111,
    0b00011111,
    0b00111111,
    0b01111111,
    0b11111111,
};

#define NUM_PATRONES = (sizeof(PATRONES) / (sizeof(PATRONES[0])));

void imprimirByteBinario(uint8_t valor){
    printf("0b");
    for(int i = 7; i>=0;i--){
        printf("%d",(valor >> i) & 1);
        if(i == 4) printf("_");
    }
    printf("\n");
};


void mostrarEstadoPuerto(void){
    printf("PORTA_SIM:");
    imprimirByteBinario(PORTA_SIM.byte);
    printf("0x%02X = %3d",PORTA_SIM.byte,PORTA_SIM.byte);
    printf("\n");
    printf("LEDS: ");
    for(int i = 7; i>=0; i--){
        printf("[%d]%s ",i,(PORTA_SIM.byte >> i) & 1 ? "ON" : "OFF");
    };
    printf("\n");
}

void pinSet(uint8_t pin){
    /* Para prender un led en especidifco sin afectar a los demas*/
    PORTA_SIM.byte |= (1 << pin);
}

void pinClear(uint8_t pin){
    /* Apagar un led sin afectar a los demas */
    PORTA_SIM.byte &= ~(1 << pin);
}

void pinToggle(uint8_t pin){
    /* Invertir el led sin afectar a los demas */
    PORTA_SIM.byte ^= (1 << pin);
}

uint8_t leerPin(uint8_t pin){
    /* Retorna un 1 si el pin esta encendido y 0 sino */
    return (PORTA_SIM.byte << pin) & 1 ? 1 : 0;
}

void setValoresPuerto(void){
    /* Setea los 8 valores iniciales del puerto en una sola accion*/
    PORTA_SIM.byte = ~PORTA_SIM.byte;
}

int main(){
    printf("=== Simulador de Registro de Hardware ===\n\n");

    printf("[ Paso 1 ] Estado inicial del puerto:\n");
    PORTA_SIM.byte = 0x00;
    mostrarEstadoPuerto();

    printf("\n[ Paso 2 ] Encendiendo pin 0 y pin 3:\n");
    pinSet(0);
    pinSet(3);
    mostrarEstadoPuerto();

    printf("\n[ Paso 3 ] Apagando pin 0:\n");
    pinClear(0);
    mostrarEstadoPuerto();

    printf("\n[ Paso 4 ] Toggle del pin 3 (x3 veces):\n");
    pinToggle(3);
    mostrarEstadoPuerto();
    pinToggle(3);
    mostrarEstadoPuerto();
    pinToggle(3);
    mostrarEstadoPuerto();

    printf("\n[ Paso 5 ] Leer pines:\n");
    printf("  leerPin(3) = %d  (esperado: 1)\n", leerPin(3));
    printf("  leerPin(0) = %d  (esperado: 0)\n", leerPin(0));

    setValoresPuerto();
    mostrarEstadoPuerto();


    printf("\n=== FIN ===\n");
    return 0;
}
