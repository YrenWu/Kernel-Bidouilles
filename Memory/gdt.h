#ifndef INCLUDE_GDT_H
#define INCLUDE_GDT_H

void lgdt(uint16_t addressGDT);
void gdtSetup(uint32_t ptr);

#endif