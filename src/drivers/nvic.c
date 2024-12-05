#include "nvic.h"

CanRxMsg rx_msg;

void nvic_can_mode_init()
{
    NVIC_InitTypeDef NVIC_InitStructure;

    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

    // Interrupts from receiver 
    NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX1_IRQn;
    NVIC_Init(&NVIC_InitStructure);

    // Interrupts from transmitter
    NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;  
    NVIC_Init(&NVIC_InitStructure);

    NVIC_EnableIRQ(CAN1_RX1_IRQn);
    NVIC_EnableIRQ(USB_LP_CAN1_RX0_IRQn);

    CAN_ITConfig(CAN1, (CAN_IT_FMP1), ENABLE);
    CAN_ITConfig(CAN1, (CAN_IT_FMP0), ENABLE);
}

/**
 * Handles CAN1 TX irq
 */
void USB_HP_CAN1_TX_IRQHandler(void)

{
    gpio_write_bit(GPIOE, GPIO_Pin_8, Bit_SET);
	CAN_ClearITPendingBit(CAN1, CAN_IT_TME);

	
}

void USB_LP_CAN1_RX0_IRQHandler(void)
{
    gpio_write_bit(GPIOE, GPIO_Pin_8, Bit_SET);
	CAN_ClearITPendingBit(CAN1, CAN_IT_FMP0);
}

/**
 * Handles CAN1 RX1 request
 */
void CAN1_RX1_IRQHandler(void)
{
    gpio_write_bit(GPIOE, GPIO_Pin_8, Bit_SET);

    CAN_Receive(CAN1, CAN_FIFO1, &rx_msg);
    CAN_FIFORelease(CAN1, CAN_FIFO1);

    CAN_ClearITPendingBit(CAN1, CAN_IT_FMP1);
}