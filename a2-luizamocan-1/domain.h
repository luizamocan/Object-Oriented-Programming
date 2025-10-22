
#ifndef DOMAIN_H
#define DOMAIN_H

typedef struct {
    char* type;
    char* destination;
    char* date; // YYYY-MM-DD
    float price;
} Offer;

Offer* create_offer(const char* type, const char* destination, const char* date, float price);
void destroy_offer(Offer* offer);
void print_offer(const Offer* offer);

#endif //DOMAIN_H
