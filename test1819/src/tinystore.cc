// ---------------------------------------------------------------------------
// IMLAB
// ---------------------------------------------------------------------------

#include "imlab/tinystore.h"
#include <cassert>
#include "imlab/error.h"

using Relation = imlab::Relation;
using Row = imlab::Row;
using NotImplementedException = imlab::NotImplementedException;

// Construct a relation
Relation::Relation(uint64_t index_size) : size(0), index_size(index_size) {
    // Make sure the index size is a power of two
    assert((index_size & (index_size - 1)) == 0);

    throw NotImplementedException();

    // TODO
}

// Construct a relation
Relation::~Relation() {
    // TODO
}

// Insert a new row
void Relation::Insert(uint64_t a, uint64_t b, uint64_t c) {
    throw NotImplementedException();

    // TODO
}

// Find a row using the index
Row* Relation::Lookup(uint64_t a) {
    throw NotImplementedException();

    // TODO
}

// Remove a row
void Relation::Remove(Row* row) {
    throw NotImplementedException();

    // TODO
}

// Computes index into hash table for attribute value a
uint64_t Relation::Hash(uint64_t a) {
    return a & (index_size - 1);
}
