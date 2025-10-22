#include "ui.h"
#include "repo.h"
#include "service.c"

int main() {
    OfferRepo* repo = create_repo();
    OfferService* service = create_service(repo);

    start_ui(service);

    destroy_service(service);
    destroy_repo(repo);
    return 0;
}
