.macro irq num
    .global irq\num
    irq\num:
        cli
        push $0
        push $\num
        jmp irq_common_stub
.endm

irq 0
irq 1
irq 2
irq 3
irq 4
irq 5
irq 6
irq 7
irq 8
irq 9
irq 10
irq 11
irq 12
irq 13
irq 14
irq 15

irq_common_stub:
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
    movl $irq_handler, %eax
    call *%eax
    popl %eax
    popw %gs
    popw %fs
    popw %es
    popw %ds
    popa
    addl $8, %esp
    iret

