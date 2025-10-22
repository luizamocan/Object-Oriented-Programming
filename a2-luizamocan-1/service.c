#include "service.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

OfferService* create_service(OfferRepo* repo) {
    OfferService* service = (OfferService*)malloc(sizeof(OfferService));
    service->repo = repo;
    service->undo_redo_service = (UndoRedoService*)malloc(sizeof(UndoRedoService));
    //service->undo_redo_service->undo_stack = NULL;
    //service->undo_redo_service->undo_count = 0;
    //service->undo_redo_service->undo_capacity = 0;
    //service->undo_redo_service->redo_stack = NULL;
    //service->undo_redo_service->redo_count = 0;
    //service->undo_redo_service->redo_capacity = 0;
    service->undo_redo_service->undo_stack = (OfferRepo**)malloc(sizeof(OfferRepo*) * 10);
    service->undo_redo_service->undo_capacity = 10;
    service->undo_redo_service->undo_count = 0;

    service->undo_redo_service->redo_stack = (OfferRepo**)malloc(sizeof(OfferRepo*) * 10);
    service->undo_redo_service->redo_capacity = 10;
    service->undo_redo_service->redo_count = 0;
    return service;
}

void destroy_service(OfferService* service) {
    destroy_repo(service->repo);

    for (int i = 0; i < service->undo_redo_service->undo_count; i++)
        destroy_repo(service->undo_redo_service->undo_stack[i]);
    free(service->undo_redo_service->undo_stack);

    for (int i = 0; i < service->undo_redo_service->redo_count; i++)
        destroy_repo(service->undo_redo_service->redo_stack[i]);
    free(service->undo_redo_service->redo_stack);

    free(service->undo_redo_service);
    free(service);
}

void push_undo_state(UndoRedoService* service) {
    if (service->undo_count >= service->undo_capacity) {
        service->undo_capacity *= 2;
        OfferRepo** temp = (OfferRepo**)realloc(service->undo_stack, service->undo_capacity * sizeof(OfferRepo*));
        if (!temp) {
            printf("Memory allocation failed for undo stack\n");
            return;
        }
        service->undo_stack = temp;
    }
    service->undo_stack[service->undo_count++] = clone_repo(service->repo);
}
void push_redo_state(UndoRedoService* service) {
    if (service->redo_count >= service->redo_capacity) {
        service->redo_capacity *= 2;
        OfferRepo** temp = (OfferRepo**)realloc(service->redo_stack, service->redo_capacity * sizeof(OfferRepo*));
        if (!temp) {
            printf("Memory allocation failed for redo stack\n");
            return;
        }
        service->redo_stack = temp;
    }
    service->redo_stack[service->redo_count++] = clone_repo(service->repo);
}

void undo(UndoRedoService* service) {
    if (service->undo_count == 0) {
        printf("No more undo available.\n");
        return;
    }

    OfferRepo* previous_repo = service->undo_stack[--service->undo_count];
    push_redo_state(service);

    destroy_repo(service->repo);
    service->repo = previous_repo;
}

void redo(UndoRedoService* service) {
    if (service->redo_count == 0) {
        printf("No more redo available.\n");
        return;
    }

    OfferRepo* next_repo = service->redo_stack[--service->redo_count];
    push_undo_state(service);

    destroy_repo(service->repo);
    service->repo = next_repo;
}


void service_add_offer(const OfferService* service, const char* type, const char* destination, const char* date, float price) {
    push_undo_state(service->undo_redo_service);
    Offer* offer = create_offer(type, destination, date, price);
    add_offer(service->repo, offer);
}

void service_delete_offer(const OfferService* service, const char* destination, const char* date) {
    push_undo_state(service->undo_redo_service);
    delete_offer(service->repo, destination, date);
}

void service_update_offer(const OfferService* service, const char* destination, const char* date, const char* new_date, float new_price) {
    push_undo_state(service->undo_redo_service);
    update_offer(service->repo, destination, date, new_date, new_price);
}

void service_print_offers(const OfferService* service) {
    print_offers(service->repo);
}

void initialize_offers(const OfferService* service) {
    service_add_offer(service,"city-break","Milano","2025-05-28",850.5f);
    service_add_offer(service, "city-break", "Paris", "2025-08-19", 700);
    service_add_offer(service, "seaside", "Bali", "2025-08-25", 1400);
    service_add_offer(service, "mountain", "Carpathians", "2025-11-15", 1100);
    service_add_offer(service, "city-break", "Rome", "2025-03-20", 850);
    service_add_offer(service, "seaside", "Santorini", "2025-09-10", 1600);
    service_add_offer(service, "mountain", "Saint Moritz", "2026-02-09", 1410);
    service_add_offer(service, "seaside", "Maldives", "2025-06-15", 1500);
    service_add_offer(service, "mountain", "Swiss Alps", "2025-12-20", 2000);
    service_add_offer(service, "city-break", "Venice", "2025-10-30", 658.4f);

}
void display_offers(const OfferService* service, const char* search) {
    Offer** filtered=(Offer**)malloc(service->repo->count*sizeof(Offer*));
    int filtered_index=0;

    for (int i = 0; i < service->repo->count; i++) {
        if (strlen(search)==0 || strstr(service->repo->offers[i]->destination, search)) {
            filtered[filtered_index++] = service->repo->offers[i];
        }

    }
    for (int i=0; i< filtered_index-1; i++) {
        for (int j=i+1; j<filtered_index; j++) {
            if (filtered[i]->price > filtered[j]->price) {
                Offer* aux=filtered[i];
                filtered[i]=filtered[j];
                filtered[j]=aux;
            }
        }
    }

    for ( int i=0; i < filtered_index; i++) {
        print_offer(filtered[i]);
    }
    free(filtered);
}

void display_offers_given_type(const OfferService* service, const char* search_type, const char* departure_date) {
    Offer** filtered=(Offer**)malloc(service->repo->count*sizeof(Offer*));
    int filtered_index=0;

    for (int i = 0; i < service->repo->count; i++) {
        if (strcmp(search_type, service->repo->offers[i]->type) == 0 && strcmp(departure_date, service->repo->offers[i]->date) < 0) {
            filtered[filtered_index++] = service->repo->offers[i];
        }
    }
    for (int i=0; i< filtered_index; i++) {
        print_offer(filtered[i]);
    }
    free(filtered);
}
