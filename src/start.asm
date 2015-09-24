global _start
_start:
    mov esp, _temp_stack
    push ebx
	extern get_ram
	call get_ram
	cli
	extern all_install
	call all_install
    ret

ALIGN 4
mboot:
    MULTIBOOT_PAGE_ALIGN	equ 1<<0
    MULTIBOOT_MEMORY_INFO	equ 1<<1
    MULTIBOOT_AOUT_KLUDGE	equ 1<<16
    MULTIBOOT_HEADER_MAGIC	equ 0x1BADB002
    MULTIBOOT_HEADER_FLAGS	equ MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEMORY_INFO | MULTIBOOT_AOUT_KLUDGE
    MULTIBOOT_CHECKSUM	equ -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)
    EXTERN code, bss, end
    dd MULTIBOOT_HEADER_MAGIC
    dd MULTIBOOT_HEADER_FLAGS
    dd MULTIBOOT_CHECKSUM
    dd mboot
    dd code
    dd bss
    dd end
    dd _start

global gdt_flush
gdt_flush:
	extern gp
    lgdt [gp]
	ret
extern pd

global pmode
pmode:
	extern pg_install
	call pg_install
	mov eax, [pd]
	mov CR3, eax
	mov eax, CR0
    or eax, 1
	;or eax, 0x80000000
    mov CR0, eax
    jmp 08h:pm
pm:
	mov ax, 10h
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
	mov esp, _sys_stack
	extern kmain
	call kmain
    ret
global flush_cache
flush_cache:
    INVD
    ret

global idt_load
extern idtp
idt_load:
    lidt [idtp]
    ret

global _isr0
global _isr1
global _isr2
global _isr3
global _isr4
global _isr5
global _isr6
global _isr7
global _isr8
global _isr9
global _isr10
global _isr11
global _isr12
global _isr13
global _isr14
global _isr15
global _isr16
global _isr17
global _isr18
global _isr19
global _isr20
global _isr21
global _isr22
global _isr23
global _isr24
global _isr25
global _isr26
global _isr27
global _isr28
global _isr29
global _isr30
global _isr31

_isr0:
    cli
    push byte 0
    push byte 0
    jmp isr_common_stub

_isr1:
    cli
    push byte 0
    push byte 1
    jmp isr_common_stub

_isr2:
    cli
    push byte 0
    push byte 2
    jmp isr_common_stub

_isr3:
    cli
    push byte 0
    push byte 3
    jmp isr_common_stub

_isr4:
    cli
    push byte 0
    push byte 4
    jmp isr_common_stub

_isr5:
    cli
    push byte 0
    push byte 5
    jmp isr_common_stub

_isr6:
    cli
    push byte 0
    push byte 6
    jmp isr_common_stub

_isr7:
    cli
    push byte 0
    push byte 7
    jmp isr_common_stub

_isr8:
    cli
    push byte 8
    jmp isr_common_stub

_isr9:
    cli
    push byte 0
    push byte 9
    jmp isr_common_stub

_isr10:
    cli
    push byte 10
    jmp isr_common_stub

_isr11:
    cli
    push byte 11
    jmp isr_common_stub

_isr12:
    cli
    push byte 12
    jmp isr_common_stub

_isr13:
    cli
    push byte 13
    jmp isr_common_stub

_isr14:
    cli
    push byte 14
    jmp isr_common_stub

_isr15:
    cli
    push byte 0
    push byte 15
    jmp isr_common_stub

_isr16:
    cli
    push byte 0
    push byte 16
    jmp isr_common_stub

_isr17:
    cli
    push byte 0
    push byte 17
    jmp isr_common_stub

_isr18:
    cli
    push byte 0
    push byte 18
    jmp isr_common_stub

_isr19:
    cli
    push byte 0
    push byte 19
    jmp isr_common_stub

_isr20:
    cli
    push byte 0
    push byte 20
    jmp isr_common_stub

_isr21:
    cli
    push byte 0
    push byte 21
    jmp isr_common_stub

_isr22:
    cli
    push byte 0
    push byte 22
    jmp isr_common_stub

_isr23:
    cli
    push byte 0
    push byte 23
    jmp isr_common_stub

_isr24:
    cli
    push byte 0
    push byte 24
    jmp isr_common_stub

_isr25:
    cli
    push byte 0
    push byte 25
    jmp isr_common_stub

_isr26:
    cli
    push byte 0
    push byte 26
    jmp isr_common_stub

_isr27:
    cli
    push byte 0
    push byte 27
    jmp isr_common_stub

_isr28:
    cli
    push byte 0
    push byte 28
    jmp isr_common_stub

_isr29:
    cli
    push byte 0
    push byte 29
    jmp isr_common_stub

_isr30:
    cli
    push byte 0
    push byte 30
    jmp isr_common_stub

_isr31:
    cli
    push byte 0
    push byte 31
    jmp isr_common_stub

extern fault_handler

isr_common_stub:
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp
    push eax
    mov eax, fault_handler
    call eax
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    iret




global irq0
global irq1
global irq2
global irq3
global irq4
global irq5
global irq6
global irq7
global irq8
global irq9
global irq10
global irq11
global irq12
global irq13
global irq14
global irq15

irq0:
    cli
    push byte 0
    push byte 32
    jmp irq_common_stub

irq1:
    cli
    push byte 0
    push byte 33
    jmp irq_common_stub

irq2:
    cli
    push byte 0
    push byte 34
    jmp irq_common_stub

irq3:
    cli
    push byte 0
    push byte 35
    jmp irq_common_stub

irq4:
    cli
    push byte 0
    push byte 36
    jmp irq_common_stub

irq5:
    cli
    push byte 0
    push byte 37
    jmp irq_common_stub

irq6:
    cli
    push byte 0
    push byte 38
    jmp irq_common_stub

irq7:
    cli
    push byte 0
    push byte 39
    jmp irq_common_stub

irq8:
    cli
    push byte 0
    push byte 40
    jmp irq_common_stub

irq9:
    cli
    push byte 0
    push byte 41
    jmp irq_common_stub

irq10:
    cli
    push byte 0
    push byte 42
    jmp irq_common_stub

irq11:
    cli
    push byte 0
    push byte 43
    jmp irq_common_stub

irq12:
    cli
    push byte 0
    push byte 44
    jmp irq_common_stub

irq13:
    cli
    push byte 0
    push byte 45
    jmp irq_common_stub

irq14:
    cli
    push byte 0
    push byte 46
    jmp irq_common_stub


irq15:
    cli
    push byte 0
    push byte 47
    jmp irq_common_stub

extern irq_handler

irq_common_stub:
    pusha
    push ds
    push es
    push fs
    push gs

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp

    push eax
    mov eax, irq_handler
    call eax
    pop eax

    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    iret

global sys1

sys1:
    cli
    push byte 0
    push byte 48
    jmp syscall_stub

extern syscall_handler

syscall_stub:
    pusha
    push ds
    push es
    push fs
    push gs

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp

    push eax
    mov eax, syscall_handler
    call eax
    pop eax

    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    sti
    iret

global read_cr0
read_cr0:
	mov eax, cr0
	retn
global write_cr0
write_cr0:
	push ebp
	mov ebp, esp
	mov eax, [ebp+8]
	mov cr0, eax
	pop ebp
	retn

global read_cr3
read_cr3:
	mov eax, cr3
	retn

global write_cr3
write_cr3:
	push ebp
	mov ebp, esp
	mov eax, [ebp+8]
	mov cr3, eax
	pop ebp
	retn
global flush_tlb
flush_tlb:
    mov eax,cr3
    mov cr3,eax
    ret
global set_timer_interval
set_timer_interval:
    mov al, 0x36
    out 0x43, al
    mov ax, 1193 ;11931820/1000
    out 0x40, al
    mov al, ah
    out 0x40, al
    ret

SECTION .bss
    resb 8192
_sys_stack:
	resb 128
_temp_stack:
