#include "FreeRTOS.h"
#include "task.h"

#include "ch32v30x.h"
#include "system_ch32v30x.h"

/**
 * @brief Initialize SysTick interrupt.
 *
 */
void vPortSetupTimerInterrupt(void) {
    /* Configure SysTick and interrupts. */
    SysTick->SR = 0UL;
    SysTick->CTLR = 0UL;
    SysTick->CNT = 0UL;

    NVIC_EnableIRQ(SysTicK_IRQn);

    SysTick->CMP = configCPU_CLOCK_HZ / configTICK_RATE_HZ;
    SysTick->CTLR = 0x1E;  /* COUNTDOWN | AUTO RELOAD | HCLK/8 | INT */
    SysTick->CTLR |= 0x20; /* INIT */
    SysTick->CTLR |= 0x01; /* EN */
}
