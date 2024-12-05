#ifndef LED_HEADLIGHTS_NVIC_H
#define LED_HEADLIGHTS_NVIC_H

#include "stm32f30x_misc.h"
#include "stm32f30x_can.h"
#include "stm32f30x_gpio.h"
#include "drivers/gpio.h"

extern CanRxMsg rx_msg;

void nvic_can_mode_init();
void USB_HP_CAN1_TX_IRQHandler(void);
void USB_LP_CAN1_RX0_IRQHandler(void);
void CAN1_RX1_IRQHandler(void);

#endif // LED_HEADLIGHTS_NVIC_H