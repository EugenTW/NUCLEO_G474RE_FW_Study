#include "stm32g474xx.h"

#define GPIOAEN (1U<<0)
#define GPIOCEN (1U<<2)
#define PIN5 (1U<<5)
#define PIN13 (1U<<13)
#define LED_PIN PIN5
#define BTN_PIN PIN13

int main(void) {
    RCC->AHB2ENR |= GPIOAEN;
    RCC->AHB2ENR |= GPIOCEN;

    // out put pin
    GPIOA->MODER |= (1U << 10);
    GPIOA->MODER &= ~(1U << 11);

    // in put pin
    GPIOC->MODER &= ~(1U << 26);
    GPIOC->MODER &= ~(1U << 27);

    while (1) {
        if (GPIOC->IDR & BTN_PIN) {
            GPIOA->BSRR = (1U << 21);
        } else {
            GPIOA->BSRR = LED_PIN;
        }
    }
}
