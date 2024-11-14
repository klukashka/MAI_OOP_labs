#pragma once
#include <memory_resource>
#include <list>
// #include <iostream>
// #include <type_traits>

class MyFixedMemoryResource : public std::pmr::memory_resource {
public:
    MyFixedMemoryResource(size_t block_size)
        : block_size_(block_size) {}

    void* do_allocate(std::size_t bytes, std::size_t alignment) override {
        if (!free_blocks_.empty()) {
            void* block = free_blocks_.front();
            free_blocks_.pop_front();
            return block;
        }
        
        void* new_block = ::operator new(block_size_, std::align_val_t{alignment});
        allocated_blocks_.push_back(new_block);
        return new_block;
    }

    void do_deallocate(void* p, std::size_t bytes, std::size_t alignment) override {
        free_blocks_.push_back(p);
    }

    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override {
        return this == &other;
    }

    ~MyFixedMemoryResource() {
        for (auto block : allocated_blocks_) {
            ::operator delete(block);
        }
    }

private:
    size_t block_size_;
    std::list<void*> free_blocks_;
    std::list<void*> allocated_blocks_;
};
