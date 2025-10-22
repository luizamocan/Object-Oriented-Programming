

#include "domain.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Offer* create_offer(const char* type, const char* destination, const char* date, float price) {
    Offer* o = (Offer*)malloc(sizeof(Offer));
    o->type = strdup(type);
    o->destination = strdup(destination);
    o->date = strdup(date);
    o->price = price;
    return o;
}

void destroy_offer(Offer* offer) {
    free(offer->type);
    free(offer->destination);
    free(offer->date);
    free(offer);
}

void print_offer(const Offer* offer) {
    printf("%s | %s | %s | %.2f\n", offer->type, offer->destination, offer->date, offer->price);
}
