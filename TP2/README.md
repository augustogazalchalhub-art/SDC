# Trabajo Práctico 2 - Sistemas de Computación

## Descripción
Proyecto de integración entre C y Assembler (x86_64, sintaxis AT&T) aplicando la convención de llamadas System V AMD64 ABI. El sistema se conecta a la API REST del Banco Mundial mediante `libcurl` para extraer el Índice GINI de Argentina y delega el procesamiento matemático y manejo de memoria a una subrutina de bajo nivel.

Como requisito central, se implementa una técnica de saturación de registros para forzar el envío de un parámetro de coma flotante a través de la pila de memoria (Stack) en lugar de los registros de hardware.

## Estructura del Repositorio
- **Iteracion_1**: Código fuente en C puro con la lógica de conexión a la API web y extracción de datos JSON.
- **Iteracion_2**: Implementación final integrada. Contiene el código en C (`main_2.c`) que satura los registros de coma flotante (`%xmm0` a `%xmm7`) pasando ocho ceros como argumentos iniciales, obligando al noveno parámetro (`gini_float`) a viajar por el Stack. Se complementa con el código en Assembler (`calculo.s`) que extrae el dato de la memoria, lo procesa y lo retorna.
- **Imagenes**: Evidencia visual del análisis de depuración con GDB Dashboard documentando los estados de la memoria (Antes, Durante y Después del paso por la subrutina).

## Requisitos y Compilación
Se requiere entorno Linux de 64 bits con `gcc`, `gdb` y `libcurl`.
Para compilar la versión final:
- `as --64 -g -o calculo.o calculo.s`
- `gcc -g -O0 -c -o main_2.o main_2.c`
- `gcc -g main_2.c calculo.s -lcurl -o tp2_final`

## Análisis de Memoria (Stack Frame)

El proyecto incluye un análisis del comportamiento de la pila comprobado mediante GDB, validando el ciclo de vida del marco de pila durante la llamada a la función en Assembler:

* **Estado Previo:** Confirmación de que el valor flotante fue depositado en el Stack por C, quedando físicamente debajo de la dirección de retorno.
* **Armado del Frame:** Ejecución de `pushq %rbp` y `movq %rsp, %rbp` para resguardar el registro base del programa llamador y establecer el nuevo punto de referencia inamovible.
* **Procesamiento por Offset:** Uso del desplazamiento `16(%rbp)` para saltar los 16 bytes de datos de control (dirección de retorno y RBP guardado) y acceder al dato empujado por C directamente en la memoria para su conversión con `cvttss2siq`.
* **Limpieza y Retorno:** Desarmado del marco mediante `popq %rbp` y ejecución de `ret`, restaurando los punteros originales y transfiriendo el resultado final depositado en el registro `%rax` de vuelta al programa principal sin dejar pérdidas de memoria.