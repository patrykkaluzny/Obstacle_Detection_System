#ifndef CAN_H_
#define CAN_H_

#include "main.h"

#define _CAN1_TIM_RESEND TIM14
#define _CAN2_TIM_RESEND TIM13


void CAN_Conf(void);
void CAN_DecodeFrame(CanRxMsg* RxMessage);

void CAN1_SendFrameWithBuffer(uint32_t CANStdId, uint32_t *CANData1, uint32_t *CANData2);
void CAN2_SendFrameWithBuffer(uint32_t CANStdId, uint32_t *CANData1, uint32_t *CANData2);

u8 CAN1_ResendFrame(volatile CanTxMsg *CANPackage);
u8 CAN2_ResendFrame(volatile CanTxMsg *CANPackage);

u8 CAN1_Add2Buffer(CanTxMsg *CANPackage);
u8 CAN2_Add2Buffer(CanTxMsg *CANPackage);

u8 CAN1_CheckOverflow(void);
u8 CAN2_CheckOverflow(void);

void CAN_TurnOffPowerSaveMode(void); //power saving mode of tle7250V can transceiver
void CAN_TurnOnPowerSaveMode(void);




void Delay(int NumberOfCycles);

#endif /* CAN_H_ */
