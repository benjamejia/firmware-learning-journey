#include <stdio.h>
#include <stdint.h>

void greet()
{
	printf("Tamños de datos <stdio.h>!\n");
	printf("El tamaño de int: %d\n",sizeof(int));
	printf("El tamaño de char: %d\n",sizeof(char));
	printf("El tamaño de float: %d\n",sizeof(float));
	printf("El tamaño de double: %d\n",sizeof(double));

uint8_t pequeno = 255;
uint32_t grande = 4000000000;	

printf("Tamaños de datos fijos <stdint.h>!\n");
	printf("El tamaño de uint8_t:%d\n",sizeof(pequeno));
	printf("El tamaño de uint32_t:%d\n",sizeof(grande));

pequeno = pequeno + 1; 
    printf("Pequeño + 1: %u (¡Se desbordó a cero!)\n", pequeno);

}

int main()
{
	greet();
	return 0;
}
