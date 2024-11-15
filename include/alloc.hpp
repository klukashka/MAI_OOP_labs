#pragma once
#include <memory_resource>
#include <list>
#include <iostream>
// #include <type_traits>

class MyFixedMemoryResource : public std::pmr::memory_resource {
private:
    struct Block {
        size_t offset;
        size_t size;
    };

    static constexpr size_t max_size = 600;
    char buffer[max_size];
    std::list<Block> used_blocks;

public:
    void* do_allocate(size_t bytes, size_t alignment) override {
        if (bytes == 0) {
            return nullptr;
        }

        size_t result = 0;
        for (const auto& b : used_blocks) {
            if (result + bytes <= b.offset || result >= b.offset + b.size) {
                continue;
            } else {
                result = b.offset + b.size;
            }
        }

        if (result + bytes > max_size) {
            throw std::bad_alloc();
        }

        used_blocks.push_back({result, bytes});
        used_blocks.sort([](const Block& a, const Block& b) {
            return a.offset < b.offset;
        });

        // std::cout << "Allocated: " << result << ", size: " << bytes << std::endl;
        return buffer + result;
    }

    void do_deallocate(void* ptr, size_t bytes, size_t alignment) override {
        // std::cout << "Deallocated: " << ptr << ", size: " << bytes << std::endl;
        for (auto it = used_blocks.begin(); it != used_blocks.end(); ++it) {
            if (ptr == buffer + it->offset) {
                used_blocks.erase(it);
                return;
            }
        }
        throw std::logic_error("Trying to deallocate unallocated block");
    }

    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override {
        return this == &other;
    }

    ~MyFixedMemoryResource() {
        if (!used_blocks.empty()) {
            std::cout << "Memory not freed: " << used_blocks.size() << " blocks remain" << std::endl;
        }
    }
};