//Author: SadgunKumar Peddi
//Designation: Embedded Engineer

#include <stdint.h>

// 1. Define Base Addresses (From RM0008 Section 3.3)
#define RCC_BASE      0x40021000
#define GPIOC_BASE     0x40011000

// 2. Define Register Offsets (From RM0008 Section 7 & 9)
#define RCC_APB2ENR   (*(volatile uint32_t *)(RCC_BASE + 0x18))
#define GPIOC_CRH     (*(volatile uint32_t *)(GPIOC_BASE + 0x04))
#define GPIOC_ODR     (*(volatile uint32_t *)(GPIOC_BASE + 0x0C))

void delay(int count) {
    for (int i = 0; i < count * 1000; i++) {
        __asm("nop"); // Assembly "No Operation" to prevent compiler optimization
    }
}

int main(void) {
    // STEP A: Enable Clock for GPIOC (Section 7.3.7 - Bit 4 is IOPCEN)
    RCC_APB2ENR |= (1 << 4);

    // STEP B: Configure PC13 as Output (Section 9.2.2 - CRH Register)
    // PC13 is controlled by bits [23:20] of CRH.
    // Setting 0010 (Output mode 2MHz, Push-Pull)
    GPIOC_CRH &= ~(0xF << 20); // Clear bits 20,21,22,23
    GPIOC_CRH |=  (0x2 << 20); // Set bits 21 (Mode1) to 1 for 2MHz Output

    while (1) {
        // STEP C: Toggle PC13 (Section 9.2.4 - ODR Register)
        GPIOC_ODR ^= (1 << 13);

        delay(500); // Simple software delay
    }
}
