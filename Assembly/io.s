        
# outb - send 8 bits to I/O port
# stack : [esp + 8] data
#         [esp + 4] I/O port address
#         [esp    ] return address
.global outb   

outb:
    mov 8(%esp), %al # data to send in al register
    mov 4(%esp), %dx # port address in dx
    out %al, %dx     # send data to port
    ret              


# inb - return 8 bits from I/O port
# stack : [esp + 4] I/O port address
#         [esp    ] return address
.global inb

inb:
    mov 4(%esp), %dx # I/O port address in dx 
    in  %dx, %al   	 # read bytes from I/O port, move it in al
    ret              # return bytes in al
    