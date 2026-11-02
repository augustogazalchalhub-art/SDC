# Sección 3: Ejecución en Hardware Físico (Bare Metal)

En esta última sección se trasladó el binario `aplicacion.efi` fuera del entorno virtualizado (QEMU/OVMF) para ejecutarlo de manera directa sobre el hardware físico de la computadora (Bare Metal), interactuando con el firmware nativo de la placa madre.

## 1. Preparación del Medio de Arranque (USB)

Para que el firmware reconozca la unidad de almacenamiento externa como un dispositivo booteable según la especificación UEFI:

1. Se particionó y formateó el pendrive en **FAT32**, ya que es el sistema de archivos estándar obligatorio que los drivers del firmware UEFI saben interpretar nativamente.
2. Se creó la estructura de directorios estandarizada `/EFI/BOOT/`.
3. Se descargó el binario de la **UEFI Shell de TianoCore** (`Shell.efi`). De esta manera, el Boot Manager ejecuta la Shell por defecto al seleccionar el medio de arranque.
4. Se copió `aplicacion.efi` a la raíz de la unidad.

## 2. Configuración del Firmware (BIOS Setup)

Antes de iniciar, se ingresó al Setup de la placa madre para ajustar dos parámetros críticos:

* **Modo UEFI Only (CSM Disabled):** Garantiza que la placa inicie en modo nativo de 64 bits utilizando la base de datos de protocolos y handles de UEFI, evitando la emulación Legacy BIOS.

* **Desactivación de Secure Boot (Disabled):** 
  * *Justificación de seguridad:* Secure Boot valida criptográficamente que cada ejecutable (`.efi`, drivers y bootloaders) contenga una firma digital respaldada por certificados de confianza cargados en la base de datos de la BIOS (típicamente de Microsoft o del fabricante de la placa). Como `aplicacion.efi` y la Shell fueron compilados por nosotros en un entorno de desarrollo sin certificados oficiales, mantener Secure Boot activo provocaría que el firmware bloquee el arranque por violación de seguridad.

## 3. Ejecución en la UEFI Shell

Una vez iniciado el equipo desde el pendrive:

1. La Shell montó los volúmenes disponibles en el equipo.
2. Se invocó directamente el binario `aplicacion.efi`.
3. El programa ejecutó la rutina en C, limpiando la pantalla mediante `SystemTable->ConOut->ClearScreen` e imprimiendo los mensajes a través de `OutputString` sin intervención de ningún kernel ni sistema operativo.
