#include "AppLed.hpp"

AppLed::AppLed() {
    // Enable GPIOA clock (AHB2 bus)
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

    // Small delay to ensure clock is stable
    volatile int delay = 10000;
    while (delay--) __asm__("nop");

    // Set PA5 as general output mode (MODER = 01)
    GPIOA->MODER &= ~(0x3 << (5 * 2));
    GPIOA->MODER |=  (0x1 << (5 * 2));

    // Disable pull-up/pull-down
    GPIOA->PUPDR &= ~(0x3 << (5 * 2));

    // Push-pull output
    GPIOA->OTYPER &= ~(1 << 5);

    // Output speed: low (optional)
    GPIOA->OSPEEDR &= ~(0x3 << (5 * 2));
}

void AppLed::on() {
    GPIOA->ODR |= (1 << 5);
}

void AppLed::off() {
    GPIOA->ODR &= ~(1 << 5);
}
