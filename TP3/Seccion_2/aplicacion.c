#include <efi.h>
#include <efilib.h>

EFI_STATUS EFIAPI efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *
  SystemTable) {
  volatile unsigned char code[] = {
    0xCC
  };
  uefi_call_wrapper(SystemTable -> ConOut -> ClearScreen, 1, SystemTable -> ConOut);
  uefi_call_wrapper(SystemTable -> ConOut -> OutputString, 2, SystemTable -> ConOut,
    L"Iniciando analisis de seguridad...\r\n");
  if (code[0] == 0xCC) {
    uefi_call_wrapper(SystemTable -> ConOut -> OutputString, 2, SystemTable -> ConOut,
      L"Breakpoint estatico alcanzado.\r\n");
  }
  uefi_call_wrapper(SystemTable -> BootServices -> Stall, 1, 5000000);
  return EFI_SUCCESS;
}

