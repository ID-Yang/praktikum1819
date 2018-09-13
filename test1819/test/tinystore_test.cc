// ---------------------------------------------------------------------------
// IMLAB
// ---------------------------------------------------------------------------

#include <memory>
#include "imlab/tinystore.h"
#include "gtest/gtest.h"

using Relation = imlab::Relation;
using Row = imlab::Row;

namespace {

TEST(RelationTest, MethodsImplemented) {
    std::unique_ptr<Relation> rel;
    Row* row;
    ASSERT_NO_THROW(rel = std::make_unique<Relation>(1024));
    ASSERT_NO_THROW(rel->Insert(42, 43, 44));
    ASSERT_NO_THROW(row = rel->Lookup(42));
    ASSERT_NO_THROW(rel->Remove(row));
}

TEST(RelationTest, LookupValue) {
    Relation rel(1024);
    rel.Insert(42, 43, 44);
    auto row = rel.Lookup(42);
    ASSERT_NE(row, nullptr);
    EXPECT_EQ(row->a, 42);
    EXPECT_EQ(row->b, 43);
    EXPECT_EQ(row->c, 44);
}

TEST(RelationTest, LookupChainedValues) {
    unsigned n = 1024;
    Relation rel(n);

    auto k1 = 0 * n + 42;
    auto k2 = 1 * n + 42;
    auto k3 = 2 * n + 42;
    rel.Insert(k1, k1 + 1, k1 + 2);
    rel.Insert(k2, k2 + 1, k2 + 2);
    rel.Insert(k3, k3 + 1, k3 + 2);

    auto r3 = rel.Lookup(k3);
    ASSERT_NE(r3, nullptr);
    EXPECT_EQ(r3->a, k3);
    EXPECT_EQ(r3->b, k3 + 1);
    EXPECT_EQ(r3->c, k3 + 2);

    auto r2 = rel.Lookup(k2);
    ASSERT_NE(r2, nullptr);
    EXPECT_EQ(r2->a, k2);
    EXPECT_EQ(r2->b, k2 + 1);
    EXPECT_EQ(r2->c, k2 + 2);

    auto r1 = rel.Lookup(k1);
    ASSERT_NE(r1, nullptr);
    EXPECT_EQ(r1->a, k1);
    EXPECT_EQ(r1->b, k1 + 1);
    EXPECT_EQ(r1->c, k1 + 2);
}

TEST(RelationTest, RemoveValue) {
    Relation rel(1024);
    rel.Insert(42, 43, 44);
    auto row = rel.Lookup(42);
    ASSERT_NE(row, nullptr);

    rel.Remove(row);

    row = rel.Lookup(42);
    EXPECT_EQ(row, nullptr);
}

TEST(RelationTest, RemoveChainedValues) {
    unsigned n = 1024;
    Relation rel(n);

    auto k1 = 0 * n + 42;
    auto k2 = 1 * n + 42;
    auto k3 = 2 * n + 42;
    rel.Insert(k1, k1 + 1, k1 + 2);
    rel.Insert(k2, k2 + 1, k2 + 2);
    rel.Insert(k3, k3 + 1, k3 + 2);

    auto r1 = rel.Lookup(k1);
    auto r2 = rel.Lookup(k2);
    auto r3 = rel.Lookup(k3);
    ASSERT_NE(r1, nullptr);
    ASSERT_NE(r2, nullptr);
    ASSERT_NE(r3, nullptr);

    EXPECT_EQ(r1->a, k1);
    EXPECT_EQ(r1->b, k1 + 1);
    EXPECT_EQ(r1->c, k1 + 2);

    EXPECT_EQ(r2->a, k2);
    EXPECT_EQ(r2->b, k2 + 1);
    EXPECT_EQ(r2->c, k2 + 2);

    EXPECT_EQ(r3->a, k3);
    EXPECT_EQ(r3->b, k3 + 1);
    EXPECT_EQ(r3->c, k3 + 2);

    rel.Remove(r3);

    r1 = rel.Lookup(k1);
    r2 = rel.Lookup(k2);
    r3 = rel.Lookup(k3);
    ASSERT_NE(r1, nullptr);
    ASSERT_NE(r2, nullptr);
    ASSERT_EQ(r3, nullptr);

    rel.Remove(r2);

    r1 = rel.Lookup(k1);
    r2 = rel.Lookup(k2);
    r3 = rel.Lookup(k3);
    ASSERT_NE(r1, nullptr);
    ASSERT_EQ(r2, nullptr);
    ASSERT_EQ(r3, nullptr);

    rel.Remove(r1);

    r1 = rel.Lookup(k1);
    r2 = rel.Lookup(k2);
    r3 = rel.Lookup(k3);
    ASSERT_EQ(r1, nullptr);
    ASSERT_EQ(r2, nullptr);
    ASSERT_EQ(r3, nullptr);
}


}  // namespace
