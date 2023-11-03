


#ifndef LDR_CFG_H_
#define LDR_CFG_H_

#define LDR_PIN	PINA0
#define LDR_Channel	CH_0
//we will use 4 LED lamps to how much light we are getting
//for the lowest light possible --> red
//then							--> red+grn
//								--> red+grn+blue
//								--> red+grn+blue+yellow
//defining the led pins
#define LDR_RED_PIN	PINB7
#define LDR_GRN_PIN	PINA4
#define LDR_BLU_PIN	PINA5
#define LDR_YEL_PIN	PINA6	


#endif /* LDR_CFG_H_ */