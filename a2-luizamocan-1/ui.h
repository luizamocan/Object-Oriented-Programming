
#ifndef UI_H
#define UI_H
#include "service.h"
#include <stdlib.h>



int is_valid_float(const char* str);
int is_valid_date(const char* date);
int is_valid_type(const char* type);
int read_int();
float read_float();
void read_string(char* buffer, size_t size);
void print_menu();
void start_ui(OfferService* service);



#endif //UI_H
