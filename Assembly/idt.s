#
#   Assembly for setting up Interrupt Descriptor Table with LIDT x86 instruction 
#

.global  loadIDT
# stack: [esp + 4] address of 1st entry of IDT
#        [esp    ] return address

loadIDT:
    mov 4(%esp), %eax  # IDT address in EAX
    lidt (%eax)  			# load Interruption descriptor table
    ret                    
