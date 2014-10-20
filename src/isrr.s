.macro isr num
    .global isr\num
    isr\num:
        cli
        push $0
        push $\num
        jmp isr_common_stub
.endm

isr 0
isr 1
isr 2
isr 3
isr 4
isr 5
isr 6
isr 7
isr 8
isr 9
isr 10
isr 11
isr 12
isr 13
isr 14
isr 15
isr 16
isr 17
isr 18
isr 19
isr 20
isr 21
isr 22
isr 23
isr 24
isr 25
isr 26
isr 27
isr 28
isr 29
isr 30
isr 31

isr_common_stub:
    pusha
    pushw %ds
    pushw %es
    pushw %fs
    pushw %gs
    movl $0x10, %eax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs
    movl %esp, %eax
    pushl %eax
    movl $fault_handler, %eax
    call *%eax
    popl %eax
    popw %gs
    popw %fs
    popw %es
    popw %ds
    popa
    addl $8, %esp
    iret

