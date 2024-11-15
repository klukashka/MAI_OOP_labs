#include <gtest/gtest.h>
#include "../include/list.hpp"
#include "../include/alloc.hpp"


// ------------ Allocators -----------

TEST(Allocator, test_00){
    MyFixedMemoryResource allocator;

    void* ptr1 = allocator.do_allocate(100, alignof(char));
    ASSERT_NE(ptr1, nullptr) << "Memory allocation failed for 100 bytes";
    
    void* ptr2 = allocator.do_allocate(50, alignof(char));
    ASSERT_NE(ptr2, nullptr) << "Memory allocation failed for 50 bytes";
    
    void* ptr3 = allocator.do_allocate(200, alignof(char));
    ASSERT_NE(ptr3, nullptr) << "Memory allocation failed for 200 bytes";
}

TEST(Allocator, test01){
    MyFixedMemoryResource allocator;

    void* ptr1 = allocator.do_allocate(100, alignof(char));
    void* ptr2 = allocator.do_allocate(50, alignof(char));

    // allocator.do_deallocate(ptr1, 100, alignof(char));
    // allocator.do_deallocate(ptr2, 50, alignof(char));

    // No exceptions should be thrown, and no memory should leak
    ASSERT_NO_THROW(allocator.do_deallocate(ptr1, 100, alignof(char)));
    ASSERT_NO_THROW(allocator.do_deallocate(ptr2, 50, alignof(char)));
}

TEST(Allocator, test_02){
    MyFixedMemoryResource allocator;

    void* ptr1 = allocator.do_allocate(100, alignof(char));
    void* ptr2 = allocator.do_allocate(50, alignof(char));

    // Deallocate both blocks
    allocator.do_deallocate(ptr1, 100, alignof(char));
    allocator.do_deallocate(ptr2, 50, alignof(char));

    // Now try allocating again and reuse the memory
    void* ptr3 = allocator.do_allocate(50, alignof(char));
    ASSERT_NE(ptr3, nullptr) << "Failed to reuse memory for 50 bytes";

    void* ptr4 = allocator.do_allocate(100, alignof(char));
    ASSERT_NE(ptr4, nullptr) << "Failed to reuse memory for 100 bytes";
}

TEST(Allocator, test_03){
    MyFixedMemoryResource allocator;
    void* ptr = allocator.do_allocate(0, alignof(char));
    ASSERT_EQ(ptr, nullptr) << "Allocating zero bytes should return nullptr";
}

// ------------ MyList ---------------

MyFixedMemoryResource my_resource;
std::pmr::polymorphic_allocator<int> allocator(&my_resource);

TEST(MyList, test_00) {
    MyList<int, std::pmr::polymorphic_allocator<int>> list(allocator);
    EXPECT_TRUE(list.IsEmpty());  // Should be empty initially
    EXPECT_EQ(list.Size(), 0);    // Size should be 0
}

TEST(MyList, test_01) {
    MyList<int, std::pmr::polymorphic_allocator<int>> list(5, allocator);
    EXPECT_EQ(list.Size(), 5);    // Size should be 5
    EXPECT_FALSE(list.IsEmpty()); // Should not be empty
}

TEST(MyList, test_02) {
    MyList<int, std::pmr::polymorphic_allocator<int>> list({1, 2, 3, 4, 5}, allocator);
    EXPECT_EQ(list.Size(), 5);    // Size should be 5
    EXPECT_EQ(list.Front(), 1);   // First element should be 1
}

TEST(MyList, test_03) {
    MyList<int, std::pmr::polymorphic_allocator<int>> list(allocator);
    list.PushFront(1);
    list.PushFront(2);
    list.PushBack(3);

    EXPECT_EQ(list.Size(), 3);    // Size should be 3
    EXPECT_EQ(list.Front(), 2);   // Front should be 2
    auto it = list.Begin();
    ++it;
    EXPECT_EQ(*it, 1);            // Second element should be 1
    ++it;
    EXPECT_EQ(*it, 3);            // Last element should be 3
}

TEST(MyList, test_04) {
    MyList<int, std::pmr::polymorphic_allocator<int>> list({1, 2, 3}, allocator);
    list.PopFront();
    
    EXPECT_EQ(list.Size(), 2);   // Size should be 2
    EXPECT_EQ(list.Front(), 2);   // New front should be 2
}

TEST(MyList, test_05) {
    MyList<int, std::pmr::polymorphic_allocator<int>> list({1, 2, 3}, allocator);
    auto it = list.Begin();
    ++it;  // Move to second element (2)
    list.InsertAfter(it, 4);  // Insert 4 after 2
    
    EXPECT_EQ(list.Size(), 4);  // Size should be 4
}

TEST(MyList, test_06) {
    MyList<int, std::pmr::polymorphic_allocator<int>> list({1, 2, 3, 4}, allocator);
    auto it = list.Begin();
    ++it;  // Move to second element (2)
    list.EraseAfter(it);  // Erase element 3
    
    EXPECT_EQ(list.Size(), 3);    // Size should be 3
}

TEST(MyList, test_07) {
    MyList<int, std::pmr::polymorphic_allocator<int>> list({1, 2, 3, 4, 5}, allocator);
    auto it = list.Find(3);
    
    EXPECT_NE(it, list.End());  // Should find 3
    EXPECT_EQ(*it, 3);          // Should be the value 3
}

TEST(MyList, test_08) {
    MyList<int, std::pmr::polymorphic_allocator<int>> list({1, 2, 3, 4, 5}, allocator);
    auto it = list.Find(6);
    
    EXPECT_EQ(it, list.End());  // Should not find 6
}

// TEST(MyList, test_09) {
//     MyList<int, std::pmr::polymorphic_allocator<int>> list1({1, 2, 3}, allocator);
//     MyList<int, std::pmr::polymorphic_allocator<int>> list2({4, 5, 6}, allocator);
    
//     list1.Swap(list2);
    
//     EXPECT_EQ(list1.Size(), 3);
//     EXPECT_EQ(list2.Size(), 3);
//     EXPECT_EQ(list1.Front(), 4);
//     EXPECT_EQ(list2.Front(), 1);
// }

TEST(MyList, test_10) {
    MyList<int, std::pmr::polymorphic_allocator<int>> original({1, 2, 3, 4}, allocator);
    MyList<int, std::pmr::polymorphic_allocator<int>> copy(original, allocator);
    
    EXPECT_EQ(copy.Size(), original.Size());
    EXPECT_EQ(copy.Front(), original.Front());
}

TEST(MyList, test_11) {
    MyList<int, std::pmr::polymorphic_allocator<int>> original({1, 2, 3}, allocator);
    MyList<int, std::pmr::polymorphic_allocator<int>> assigned(original, allocator);
    
    EXPECT_EQ(assigned.Size(), original.Size());  // Sizes should be equal
    EXPECT_EQ(assigned.Front(), original.Front()); // Front elements should be the same
}

TEST(MyList, test_12) {
    MyList<int, std::pmr::polymorphic_allocator<int>> list(allocator);
    list.EmplaceFront(10);
    list.EmplaceFront(20);
    
    EXPECT_EQ(list.Size(), 2);  // Size should be 2
    EXPECT_EQ(list.Front(), 20); // Front element should be 20
}

TEST(MyList, test_13) {
    MyList<int, std::pmr::polymorphic_allocator<int>> list({1, 2, 3, 4}, allocator);
    list.Clear();
    
    EXPECT_TRUE(list.IsEmpty());  // List should be empty after clear
    EXPECT_EQ(list.Size(), 0);    // Size should be 0
}

TEST(MyList, test_14) {
    MyList<int, std::pmr::polymorphic_allocator<int>> empty_list(allocator);
    EXPECT_TRUE(empty_list.IsEmpty());  // Should be empty
    MyList<int, std::pmr::polymorphic_allocator<int>> non_empty_list({1, 2, 3}, allocator);
    EXPECT_FALSE(non_empty_list.IsEmpty());  // Should not be empty
}

TEST(MyList, test_15) {
    MyList<int, std::pmr::polymorphic_allocator<int>> list(allocator);
    list.EmplaceBack(1);
    list.EmplaceBack(2);
    list.EmplaceBack(3);

    EXPECT_EQ(list.Size(), 3);  // Size should be 3
    auto it = list.Begin();
    EXPECT_EQ(*it, 1);  // First element should be 1
    ++it;
    EXPECT_EQ(*it, 2);  // Second element should be 2
    ++it;
    EXPECT_EQ(*it, 3);  // Third element should be 3
}

TEST(MyList, test_16) {
    MyList<int, std::pmr::polymorphic_allocator<int>> list(allocator);
    const int n = 1000;
    for (int i = 0; i < n; ++i){
        list.PushBack(i);
    }
    EXPECT_EQ(list.Size(), n);
    for (int i = 0; i < n; ++i){
        list.PopBack();
    }
    EXPECT_TRUE(list.IsEmpty());
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}