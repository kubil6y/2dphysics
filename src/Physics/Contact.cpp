#include "Contact.h"

void Contact::ResolvePenetration() {
    float totalInvMass = a->invMass + b->invMass;
    if (totalInvMass < 1e-6) {
        return;
    }
    float da = depth / (a->invMass + b->invMass) * a->invMass;
    float db = depth / (a->invMass + b->invMass) * b->invMass;
    a->position -= normal * da;
    b->position -= normal * db;
}
