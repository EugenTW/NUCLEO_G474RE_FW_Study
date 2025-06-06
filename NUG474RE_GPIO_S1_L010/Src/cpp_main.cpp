#include "stm32g474xx.h"

constexpr uint32_t GPIOAEN = (1U << 0);
constexpr uint32_t PIN5 = (1U << 5);
constexpr uint32_t LED_PIN = PIN5;

class GPIOController {
public:
    static void enableGPIOAClock() {
        RCC->AHB2ENR |= GPIOAEN;
    }

    static void configurePA5AsOutput() {
        // Clear MODER11:10 for pin 5
        GPIOA->MODER &= ~(3U << (5 * 2));
        // Set MODER10 = 1, MODER11 = 0 → output mode
        GPIOA->MODER |=  (1U << (5 * 2));
    }

    static void togglePA5() {
        GPIOA->ODR ^= LED_PIN;
    }

    static void delay(volatile int count) {
        while (count--) {
            __asm__ volatile("nop");
        }
    }
};

int main() {
    GPIOController::enableGPIOAClock();
    GPIOController::configurePA5AsOutput();

    while (true) {
        GPIOController::togglePA5();
        GPIOController::delay(100000);
    }
}
