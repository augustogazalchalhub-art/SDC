# Sección 1: Exploración del Entorno UEFI

En esta primera sección, se configura el entorno emulado con QEMU y OVMF para explorar cómo UEFI gestiona los dispositivos, la memoria y el proceso de arranque antes de cargar el sistema operativo.

## Respuestas a las Preguntas de Razonamiento

**1. Al ejecutar el comando `map` y `dh`, vemos protocolos e identificadores en lugar de puertos de hardware fijos ¿Cuál es la ventaja de seguridad y compatibilidad de este modelo frente al antiguo BIOS?**

La principal ventaja de este modelo basado en identificadores y protocolos es la abstracción de hardware, donde el código no necesita saber si un dispositivo de almacenamiento es NVMe, SATA o un pendrive USB; simplemente busca un identificador (handle) que implemente un protocolo estándar de lectura de bloques. Esto  desacopla por completo el software de los componentes físicos y permite integrar el hardware moderno o soportar distintas arquitecturas de procesador sin romper programas de arranque existentes.

**2. Observando las variables `Boot####` y `BootOrder`, ¿cómo determina el Boot Manager la secuencia de arranque?**

Las variables enumeradas (Boot0000, Boot0001, Boot0002, etc.) almacenan individualmente la ruta física y lógica de cada dispositivo o sistema operativo disponible (como un disco NVMe, un pendrive USB o un cargador de red). Por su parte, la variable BootOrder funciona como una lista maestra que contiene los números de esas entradas ordenados por prioridad (por ejemplo: 0001 0000 0002). El Boot Manager simplemente lee BootOrder e intenta ejecutar cada entrada en ese orden exacto hasta que logra arrancar.

**3. En el mapa de memoria (`memmap`), existen regiones marcadas como `RuntimeServicesCode` ¿Por qué estas áreas son un objetivo principal para los desarrolladores de malware (Bootkits)?**

En estas áreas la información almacenada ahí no se limpia cuando arranca la computadora, sino que queda residente en la memoria para que el S0 la siga usando. Si un malware logra esconderse en esa zona, se asegura de seguir ejecutándose con privilegios máximos y de forma invisible, burlando a los antivirus del sistema operativo.
