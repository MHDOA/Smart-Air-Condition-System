#ifndef SIM800L_H_
#define SIM800L_H_
#include <avr/io.h>

void sim800_init(void);
void sim800_call(const char *phone);
void sim800_hangup(void);
void sim800_send_sms(const char *phone, const char *msg);

#endif