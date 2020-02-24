
#ifndef APP_INC_MAIN_H_
#define APP_INC_MAIN_H_

// Include device header
#include "stm32f429xx.h"


static void SystemClock_Config(void);
int my_printf(const char *format, ...);
int my_sprintf(char *out, const char *format, ...);


#endif /* APP_INC_MAIN_H_ */
