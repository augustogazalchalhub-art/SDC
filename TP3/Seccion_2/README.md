# Sección 2: Desarrollo, Compilación y Análisis de Seguridad

En esta segunda sección se armó una aplicación nativa en C para UEFI, se compiló al formato PE/COFF y se analizó con Ghidra para entender cómo se ven las instrucciones a bajo nivel.

## Respuestas a las Preguntas de Razonamiento

**4. ¿Por qué utilizamos `SystemTable->ConOut->OutputString` en lugar de la función `printf` de C?**

Porque `printf` pertenece a la librería estándar de C, y para que esa librería funcione necesita que haya un sistema operativo de fondo gestionando la consola. Como en la etapa UEFI el sistema operativo todavía no existe tenemos que usar `OutputString`, que es la función nativa que nos da el firmware a través de la System Table para poder imprimir texto en la pantalla.

**5. En el pseudocódigo de Ghidra, la condición `0xCC` suele aparecer como `-52`. ¿A qué se debe este fenómeno y por qué importa en ciberseguridad?**

Pasa porque descompiladores como Ghidra suelen interpretar los arreglos de bytes (`unsigned char`) como números enteros con signo por defecto. En el sistema binario de complemento a dos de 8 bits, el valor hexadecimal `0xCC` (que es 204 en decimal) se traduce matemáticamente como `-52`. Esto es importantísimo en ciberseguridad porque `0xCC` es el código máquina de la instrucción `INT 3` (un breakpoint de software). Los analistas de malware buscan esto constantemente para detectar técnicas de evasión o anti-depuración, y si no sabés que el descompilador te lo disfraza de `-52`, se te puede pasar por alto la firma del hardware.

## Correcciones en la Compilación (`objcopy`)

Para que el ejecutable se genere bien en versiones modernas de Linux, se le tuvo que hacer dos ajustes clave al comando `objcopy` de la guía original:

* **Cambiar `--target=` por `-O `:** La bandera vieja le exigía a la herramienta que tanto el archivo que entra como el que sale tuvieran formato EFI. Como el archivo intermedio (`.so`) es de Linux (formato ELF), el comando fallaba tirando error de formato. Poniendo `-O` (Output) se le dice  a la herramienta que agarre lo que venga y que *solamente* convierta el archivo de salida al formato UEFI.

* **Agregar `-j .rodata`:** Esta bandera le indica al compilador que incluya la sección de memoria de "solo lectura" (Read-Only Data). Si no se agrega, los textos fijos del código (como `L"Iniciando analisis de seguridad..."`) quedaban afuera del archivo final, haciendo que el programa funcione perfecto en el emulador pero con los textos completamente invisibles.
