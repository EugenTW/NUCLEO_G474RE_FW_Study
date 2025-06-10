#include "stm32g474xx.h"

// GPIO defines
constexpr uint32_t GPIOAEN = (1U << 0);
constexpr uint32_t GPIOCEN = (1U << 2);
constexpr uint32_t PIN5 = (1U << 5);
constexpr uint32_t PIN13 = (1U << 13);

class GpioLedButton {
public:
    static void init() {
        // Enable GPIOA and GPIOC clocks
        RCC->AHB2ENR |= GPIOAEN;
        RCC->AHB2ENR |= GPIOCEN;

        // Set PA5 as output
        GPIOA->MODER &= ~(3U << (5 * 2)); // Clear both bits
        GPIOA->MODER |= (1U << (5 * 2)); // Set MODER5[1:0] = 01

        // Set PC13 as input
        GPIOC->MODER &= ~(3U << (13 * 2)); // Clear both bits (input = 00)
    }

    static void setLed(bool on) {
        if (on)
            GPIOA->BSRR = (PIN5 << 16); // Set PA5 (LED ON)
        else
            GPIOA->BSRR = PIN5; // Reset PA5 (LED OFF)
    }

    static bool isButtonPressed() {
        // Button pressed when PC13 is low (active-low button)
        return (GPIOC->IDR & PIN13) == 0;
    }
};

int main() {
    GpioLedButton::init();

    while (true) {
        if (GpioLedButton::isButtonPressed()) {
            GpioLedButton::setLed(false);
        } else {
            GpioLedButton::setLed(true);
        }
    }
}
