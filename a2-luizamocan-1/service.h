

#ifndef SERVICE_H
#define SERVICE_H

#include "repo.h"

typedef struct {
    OfferRepo* repo;

    OfferRepo** undo_stack;
    int undo_count;
    int undo_capacity;

    OfferRepo** redo_stack;
    int redo_count;
    int redo_capacity;
}UndoRedoService;

typedef struct {
    OfferRepo* repo;
    UndoRedoService* undo_redo_service;
}OfferService;




OfferService* create_service(OfferRepo* repo);
void destroy_service(OfferService* service);
void service_add_offer(const OfferService* service, const char* type, const char* destination, const char* date, float price);
void service_delete_offer(const OfferService* service, const char* destination, const char* date);
void service_update_offer(const OfferService* service, const char* destination, const char* date, const char* new_date, float new_price);
void service_print_offers(const OfferService* service);
void initialize_offers(const OfferService* service);
void display_offers(const OfferService* service, const char* search);
void display_offers_given_type(const OfferService* service, const char* search_type, const char* departure_date);
void push_undo_state(UndoRedoService* service);
void push_redo_state(UndoRedoService* service);
void undo(UndoRedoService* service);
void redo(UndoRedoService* service);

#endif //SERVICE_H
