#include <stdbool.h>

#include "FreeRTOS.h"
#include "debug.h"
#include "task.h"

#include "ch32v30x.h"
#include "system_ch32v30x.h"

extern void Fault_Handler(void);

static void led_task(void *param) {
    GPIO_InitTypeDef led_pin = {.GPIO_Mode = GPIO_Mode_Out_PP, .GPIO_Speed = GPIO_Speed_50MHz, .GPIO_Pin = GPIO_Pin_0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_Init(GPIOC, &led_pin);

    while (true) {
        GPIO_SetBits(GPIOC, GPIO_Pin_0);
        printf("LED pin state %u\r\n", GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_0));
        vTaskDelay(100);
        GPIO_ResetBits(GPIOC, GPIO_Pin_0);
        printf("LED pin state %u\r\n", GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_0));
        vTaskDelay(100);
    }
}

int main(void) {
    SystemInit();
    SystemCoreClockUpdate();
    USART_Printf_Init(115200);

    xTaskCreate(led_task, "LED_TSK", 256, NULL, tskIDLE_PRIORITY + 1, NULL);

    vTaskStartScheduler();

    // we should never get here
    Fault_Handler();
}
