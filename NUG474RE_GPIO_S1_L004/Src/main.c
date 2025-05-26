// #include "stm32g474xx.h" // CMSIS device header
//
// void simple_delay(volatile uint32_t t) {
//     while (t--);
// }
//
// int main(void) {
//     // 1. Enable GPIOA clock (RCC->AHB2ENR)
//     RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
//     (void)RCC->AHB2ENR; // Synchronize after enabling clock
//
//     // 2. Set PA5 as output (MODER[11:10] = 01)
//     GPIOA->MODER &= ~(GPIO_MODER_MODE5_Msk);
//     GPIOA->MODER |= (1U << GPIO_MODER_MODE5_Pos);
//
//     // 3. Set PA5 to push-pull output (OTYPER bit5 = 0)
//     GPIOA->OTYPER &= ~(GPIO_OTYPER_OT5);
//
//     // 4. Output speed and pull-up/down settings (optional)
//     // GPIOA->OSPEEDR |= (1U << (5 * 2));
//     // GPIOA->PUPDR  &= ~(3U << (5 * 2));
//
//     while (1) {
//         // LED ON (PA5 = 0)
//         GPIOA->ODR &= ~GPIO_ODR_OD5;
//         simple_delay(800000);
//         // LED OFF (PA5 = 1)
//         GPIOA->ODR |= GPIO_ODR_OD5;
//         simple_delay(800000);
//     }
// }

// #include <stdint.h>
//
// typedef struct {
//     volatile uint32_t MODER;
//     volatile uint32_t OTYPER;
//     volatile uint32_t OSPEEDR;
//     volatile uint32_t PUPDR;
//     volatile uint32_t IDR;
//     volatile uint32_t ODR;
//     volatile uint32_t BSRR;
//     volatile uint32_t LCKR;
//     volatile uint32_t AFR[2];
//     volatile uint32_t BRR;
//     uint32_t RESERVED[245];
// } GPIO_TypeDef;
//
// typedef struct {
//     uint32_t RESERVED0[19];
//     volatile uint32_t AHB2ENR;
// } RCC_TypeDef;
//
// #define GPIOA_BASE   (0x48000000UL)
// #define RCC_BASE     (0x40021000UL)
//
// #define GPIOA        ((GPIO_TypeDef *) GPIOA_BASE)
// #define RCC          ((RCC_TypeDef   *) RCC_BASE)
//
// #define PIN5         (1U << 5)
//
// void simple_delay(volatile uint32_t t) {
//     while (t--);
// }
//
// int main(void) {
//     RCC->AHB2ENR |= (1U << 0);
//     (void)RCC->AHB2ENR;
//
//     GPIOA->MODER &= ~(3U << (5 * 2));
//     GPIOA->MODER |=  (1U << (5 * 2));
//
//     GPIOA->OTYPER &= ~(1U << 5);
//
//     while (1) {
//         GPIOA->ODR &= ~PIN5;
//         simple_delay(800000);
//         GPIOA->ODR |= PIN5;
//         simple_delay(800000);
//     }
// }

#include <stdint.h>

// Direct register address defines for GPIOA and RCC
#define GPIOA_ODR_ADDR    (0x48000014UL)
#define GPIOA_MODER_ADDR  (0x48000000UL)
#define GPIOA_OTYPER_ADDR (0x48000004UL)
#define RCC_AHB2ENR_ADDR  (0x4002104CUL)

// Direct volatile pointers to registers
#define GPIOA_ODR     (*(volatile uint32_t*)GPIOA_ODR_ADDR)
#define GPIOA_MODER   (*(volatile uint32_t*)GPIOA_MODER_ADDR)
#define GPIOA_OTYPER  (*(volatile uint32_t*)GPIOA_OTYPER_ADDR)
#define RCC_AHB2ENR   (*(volatile uint32_t*)RCC_AHB2ENR_ADDR)

#define PIN5   (1U << 5)

void simple_delay(volatile uint32_t t) {
    while (t--);
}

int main(void) {
    // 1. Enable GPIOA clock
    RCC_AHB2ENR |= (1U << 0);
    (void)RCC_AHB2ENR; // Synchronize after enabling clock

    // 2. Set PA5 as output (MODER[11:10] = 01)
    GPIOA_MODER &= ~(3U << (5 * 2));
    GPIOA_MODER |=  (1U << (5 * 2));

    // 3. Set PA5 to push-pull output (OTYPER bit 5 = 0)
    GPIOA_OTYPER &= ~(1U << 5);

    while (1) {
        // LED ON (PA5 = 0)
        GPIOA_ODR &= ~PIN5;
        simple_delay(800000);

        // LED OFF (PA5 = 1)
        GPIOA_ODR |= PIN5;
        simple_delay(800000);
    }
}
