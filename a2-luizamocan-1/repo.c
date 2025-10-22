
#include "repo.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

OfferRepo* create_repo() {
    OfferRepo* repo = (OfferRepo*)malloc(sizeof(OfferRepo));
    repo->offers = NULL;
    repo->count = 0;
    repo->capacity = 0;
    return repo;
}


Offer* clone_offer(const Offer* offer) {
    Offer* new_offer = (Offer*)malloc(sizeof(Offer));
    new_offer->type = strdup(offer->type);
    new_offer->destination = strdup(offer->destination);
    new_offer->date = strdup(offer->date);
    new_offer->price = offer->price;
    return new_offer;
}

OfferRepo* clone_repo(const OfferRepo* repo) {
    OfferRepo* new_repo = create_repo();
    new_repo->count = repo->count;
    new_repo->capacity = repo->capacity;
    new_repo->offers = (Offer**)malloc(repo->capacity * sizeof(Offer*));

    for (int i = 0; i < repo->count; i++) {
        new_repo->offers[i] = clone_offer(repo->offers[i]);
    }
    return new_repo;
}




void destroy_repo(OfferRepo* repo) {
    for (int i = 0; i < repo->count; i++) {
        destroy_offer(repo->offers[i]);
    }
    free(repo->offers);
    free(repo);
}

void add_offer(OfferRepo* repo, Offer* offer) {
    if (repo->count >= repo->capacity) {
        size_t new_capacity = repo->capacity == 0 ? 1 : repo->capacity * 2;
        Offer** new_offers = realloc(repo->offers, new_capacity * sizeof(Offer*));

        if (!new_offers) {
            printf("Memory allocation failed!\n");
            return;
        }

        repo->offers = new_offers;
        repo->capacity = (int)new_capacity;
    }
    repo->offers[repo->count++] = offer;
}

int find_offer_index(const OfferRepo* repo, const char* destination, const char* date) {
    for (int i = 0; i < repo->count; i++) {
        if (strcmp(repo->offers[i]->destination, destination) == 0 && strcmp(repo->offers[i]->date, date) == 0)
            return i;
    }
    return -1;
}

void delete_offer(OfferRepo* repo, const char* destination, const char* date) {
    int index = find_offer_index(repo, destination, date);
    if (index == -1) return;
    destroy_offer(repo->offers[index]);
    for (int i = index; i < repo->count - 1; i++) {
        repo->offers[i] = repo->offers[i + 1];
    }
    repo->count--;
}

void update_offer(OfferRepo* repo, const char* destination, const char* date, const char* new_date, float new_price) {
    int index = find_offer_index(repo, destination, date);
    if (index == -1) return;
    free(repo->offers[index]->date);
    repo->offers[index]->date = strdup(new_date);
    repo->offers[index]->price = new_price;
}

void print_offers(const OfferRepo* repo) {
    for (int i = 0; i < repo->count; i++) {
        print_offer(repo->offers[i]);
    }
}
