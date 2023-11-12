

#ifndef TWI_H_
#define TWI_H_
#include "../../LIB/Std_Types.h"
#include "../../LIB/MemMap.h"
#include "../../LIB/Utils.h"

typedef enum
{  
	PRESCALER1, 
	PRESCALER4, 
	PRESCALER16, 
	PRESCALER64

} TWI_PRESCALER;

typedef struct
{
	TWI_PRESCALER prescaler;
	u16 adress_slave;
}TWI_ConfigType;
/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
/* I2C Status Bits in the TWSR Register */
#define TWI_START         0x08 // start has been sent
#define TWI_REP_START     0x10 // repeated start 
#define TWI_MT_SLA_W_ACK  0x18 // Master transmit ( slave address + Write request ) to slave + Ack received from slave
#define TWI_MT_SLA_R_ACK  0x40 // Master transmit ( slave address + Read request ) to slave + Ack received from slave
#define TWI_MT_DATA_ACK   0x28 // Master transmit data and ACK has been received from Slave.
#define TWI_MR_DATA_ACK   0x50 // Master received data and send ACK to slave
#define TWI_MR_DATA_NACK  0x58 // Master received data but doesn't send ACK to slave

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void TWI_init(const TWI_ConfigType * Config_Ptr);
void TWI_start(void);
void TWI_stop(void);
void TWI_write(u8 data);
u8 TWI_readWithACK(void); //read with send Ack
u8 TWI_readWithNACK(void); //read without send Ack
u8 TWI_getStatus(void);

#endif /* TWI_H_ */