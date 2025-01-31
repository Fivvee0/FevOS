#pragma once

#include <types.h>

uint8_t inb(uint16_t port);

uint16_t inw(uint16_t port);

void outb(uint16_t port, uint8_t value);

void outw(uint16_t port, uint16_t data);
