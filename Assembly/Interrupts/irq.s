#
#   Assembly for Interrupt request
#

.altmacro

.macro irq number offset
.global irq\number
irq\number :
    cli
    pushl $0                   
    pushl $\offset                 
    jmp commonIrqStub    # jump to interrupt handler routine
.endm

irq 0, 32
irq 1, 33
irq 2, 34
irq 3, 35
irq 4, 36
irq 5, 37
irq 6, 38
irq 7, 39
irq 8, 40
irq 9, 41
irq 10, 42
irq 11, 43
irq 12, 44
irq 13, 45
irq 14, 46
irq 15, 47

commonIrqStub: 

    pushal
    pushl %ds
    pushl %es
    pushl %fs
    pushl %gs           
    
    call irqHandler # call the C handler with exception code
    
    # registers restauration from stack
    popl %gs
    popl %fs
    popl %es
    popl %ds

    popal

    # esp restauration
    addl $8, %esp
    iret
