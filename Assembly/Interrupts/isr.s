#
#   Assembly for Interrupt service routines and common interrupt handler
#

.altmacro

.macro noErrorCodeISR int
.global isr\int
isr\int:
    cli
    pushl $0                   # error code 0
    pushl $\int                 # interrupt number
    jmp commonInterruptHandler    # jump to interrupt handler routine
.endm

.macro errorCodeISR int
.global isr\int
isr\int:
    cli
    pushl $\int                 # interrupt number
    jmp commonInterruptHandler    # jump to interrupt handler routine
.endm

# create interruption handlers
noErrorCodeISR 0    # 0x0 divide by zero            FAULT 
noErrorCodeISR 1    # 0x1 Debug                     FAULT/TRAP
noErrorCodeISR 2    # 0x2 Non-maskable interrupt    INTERRUPT
noErrorCodeISR 3    # 0x3 Breakpoint                TRAP
noErrorCodeISR 4    # 0x4 Overflow                  TRAP 
noErrorCodeISR 5    # 0x5 Bound range Exceeded      FAULT
noErrorCodeISR 6    # 0x6 Invalid opcode            FAULT
noErrorCodeISR 7    # 0x7 Device not available      FAULT
errorCodeISR 8      # 0x8 Double fault              ABORT (code 0)
noErrorCodeISR 9    # 0x9 Coprocessor Segment Overun FAULT  (obsolete > 486)
errorCodeISR 10     # 0xA Invalid TSS               FAULT 
errorCodeISR 11     # 0xB Segment not present       FAULT
errorCodeISR 12     # 0xC Stack segment fault       FAULT
errorCodeISR 13     # 0xD Genreal protection fault  FAULT
errorCodeISR 14     # 0xE Page fault                FAULT
noErrorCodeISR 15   # 0xF  Unknown interrupt exception 
noErrorCodeISR 16   # 0x10 Floating Point exception FAULT
errorCodeISR 17     # 0x11 Alignment check          FAULT
noErrorCodeISR 18   # 0x12 Machine check            ABORT
noErrorCodeISR 19   # 0x13 SIMD Floating Point Exception FAULT  
noErrorCodeISR 20   # 0x14 Virtualization exception FAULT
noErrorCodeISR 21   # 0x15-0x1D Reserved 
noErrorCodeISR 22   # 0x15-0x1D Reserved 
noErrorCodeISR 23   # 0x15-0x1D Reserved 
noErrorCodeISR 24   # 0x15-0x1D Reserved 
noErrorCodeISR 25   # 0x15-0x1D Reserved 
noErrorCodeISR 26   # 0x15-0x1D Reserved 
noErrorCodeISR 27   # 0x15-0x1D Reserved 
noErrorCodeISR 28   # 0x15-0x1D Reserved 
noErrorCodeISR 29   # 0x15-0x1D Reserved 
errorCodeISR 30     # 0x1E Security Exception       
noErrorCodeISR 31   # 0x1F Reserved

commonInterruptHandler:             # generic interrupt handler
    pushal
    pushl %ds
    pushl %es
    pushl %fs
    pushl %gs
    # addl $48, %esp                 
    
    call interruptHandler # call the C handler with exception code
    # subl $48, %esp

    # registers restauration from stack
    popl %gs
    popl %fs
    popl %es
    popl %ds

    popal

    # # esp restauration
    addl $8, %esp
    iret
