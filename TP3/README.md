# Trabajo Práctico 3: Arquitectura y Fundamentos del Firmware UEFI

## Descripción
Comprender a bajo nivel el funcionamiento de la Interfaz de Firmware Extensible Unificada (UEFI) como entorno de pre-arranque. A lo largo de las distintas secciones, se aborda la interacción directa con la UEFI Shell, el ciclo de desarrollo y compilación de aplicaciones nativas en C, la ingeniería inversa de binarios PE/COFF, y culmina con la ejecución del código en hardware físico puro (Bare Metal) sorteando las restricciones de seguridad de la placa madre.

## Estructura del Proyecto
* **`Seccion_1` - Exploración del Entorno:** 
  Análisis del mapa de memoria (`memmap`), los *handles* y protocolos, y el manejo de la NVRAM (variables globales como `BootOrder`). Todo el entorno fue simulado utilizando QEMU y el firmware OVMF.

* **`Seccion_2` - Desarrollo, Compilación y Análisis de Seguridad:**
  Creación de una aplicación UEFI nativa (`aplicacion.c`). Incluye la corrección del proceso de compilación para Linux (ajustes en `objcopy` para formato PE/COFF e inclusión de la sección `.rodata`) y el análisis estático del binario resultante usando Ghidra para identificar instrucciones críticas como el breakpoint de software (`0xCC` / `INT 3`).

* **`Seccion_3` - Ejecución en Hardware Físico (Bare Metal):**
  Preparación de un medio de arranque USB en formato FAT32 y despliegue de la UEFI Shell oficial de TianoCore. Contiene la justificación y evidencia de la configuración de la BIOS de una placa madre real (modo UEFI Only y deshabilitación de Secure Boot) para correr la aplicación directamente sobre el hardware.

## Herramientas Utilizadas
- **Emulación:** QEMU con OVMF (`OVMF.fd`).
 ` sudo apt update`
 ` sudo apt install -y qemu-system-x86 ovmf gnu-efi build-essential binutils-mingw-w64`

- **Toolchain:** `gcc`, `ld`, `objcopy` y la librería `gnu-efi`.

- **Ingeniería Inversa:** Ghidra
 ` sudo apt install -y ghidra || sudo snap install ghidra --classic`

- **Hardware:**(para la etapa Bare Metal):
 - PC física con BIOS ASRock 
 - Pendrive Kingston DataTraveler 2 GB
