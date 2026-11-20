#include <stdio.h>

void funcion_hija(int a, int b) {
    int resultado = a + b;
    printf("El resultado calculado en el stack frame hijo es: %d\n", resultado);
}

int main() {
    printf("Iniciando aplicación de stack frame...\n");
    funcion_hija(10, 20);
    printf("Stack frame hijo destruido. Retornando a main.\n");
    return 0;
}
