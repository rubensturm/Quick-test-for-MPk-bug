.global asm_signal_entry
asm_signal_entry:
    xorl %ecx, %ecx
    xorl %edx, %edx
    xorl %eax, %eax
    wrpkru
    ret