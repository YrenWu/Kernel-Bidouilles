/** managed by Global Descriptors Table

Segment
    a logically contiguous chunk of memory with consistent properties (CPU's speaking) 
Segment Register
    a register of your CPU that refers to a segment for a special use (e.g. SS, CS, DS ...) 
Selector
    a reference to a descriptor you can load into a segment register; the selector is an offset of a descriptor table entry. These entries are 8 bytes long, therefore selectors can have values 0x00, 0x08, 0x10, 0x18, ... 
Descriptor
    a memory structure (part of a table) that tells the CPU the attributes of a given segment 
*/

#define NULL_DESCRIPTOR		0x00 // First descriptor (NULL)
#define CS_DESCRIPTOR		0x9A // Code Segment Descriptor
#define DS_DESCRIPTOR		0x92 // Data Segment Descriptor

// DPL : Descriptor privilege level (ring level)