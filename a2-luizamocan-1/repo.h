
#ifndef REPO_H
#define REPO_H

#include "domain.h"




typedef struct {
    Offer** offers;
    int count;
    int capacity;
}OfferRepo;



OfferRepo* create_repo();
void destroy_repo(OfferRepo* repo);
void add_offer(OfferRepo* repo, Offer* offer);
int find_offer_index(const OfferRepo* repo, const char* destination, const char* date);
void delete_offer(OfferRepo* repo, const char* destination, const char* date);
void update_offer(OfferRepo* repo, const char* destination, const char* date, const char* new_date, float new_price);
void print_offers(const OfferRepo* repo);
Offer* clone_offer(const Offer* offer);
OfferRepo* clone_repo(const OfferRepo* repo);



#endif //REPO_H
