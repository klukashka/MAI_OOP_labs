#pragma once

#include <cstdlib>
#include <iterator>
#include <utility>

template <typename T, typename allocator_ = std::pmr::polymorphic_allocator<T>>
class MyList {
private:
    struct Node {
        Node* next_;
        T value_;
        Node() = default;
        explicit Node(Node* next) : next_(next) {}
        Node(Node* next, const T& value) : next_(next), value_(value) {}
        ~Node() = default;
    };
    template <bool IsConst>
    struct MyListIterator {
    private:
        friend class MyList<T, allocator_>;

        explicit MyListIterator(Node* ptr) : head_(ptr) {
        }

    public:
        using value_type = T;
        using reference_type = std::conditional_t<IsConst, const value_type&, value_type&>;
        using pointer_type = std::conditional_t<IsConst, const value_type*, value_type*>;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;
        MyListIterator() = default;

        MyListIterator(const MyListIterator& it) : head_(it.head_) {}

        MyListIterator& operator=(const MyListIterator& other) {
            head_ = other.head_;
            return *this;
        }

        std::conditional_t<IsConst, const T&, T&> operator*() const {
            return head_->value_;
        }

        std::conditional_t<IsConst, const T*, T*> operator->() const {
            return &(head_->value_);
        }

        MyListIterator& operator++() {
            head_ = head_->next_;
            return *this;
        }

        MyListIterator operator++(int) {
            auto copy = *this;
            ++*this;
            return copy;
        }

        bool operator==(const MyListIterator& other) const {
            return (head_ == other.head_);
        }

        bool operator!=(const MyListIterator& other) const {
            return !(other == *this);
        }

        explicit operator MyListIterator<true>() const {
            return MyListIterator(head_);
        }

        ~MyListIterator() noexcept = default;

    private:
        std::conditional_t<IsConst, const Node*, Node*> head_;
    };

    using allocator_traits = std::allocator_traits<typename std::allocator_traits<allocator_>::template rebind_alloc<Node>>;

public:
    using Iterator = MyListIterator<false>;
    using ConstIterator = MyListIterator<true>;

    MyList() : head_(nullptr), alloc_(allocator_()) {}

    explicit MyList(const allocator_& alloc)
        : head_(nullptr), alloc_(std::allocator_traits<allocator_>::select_on_container_copy_construction(alloc)) {
    }

    explicit MyList(size_t sz, const allocator_& alloc = allocator_())
        : head_(nullptr), alloc_(std::allocator_traits<allocator_>::select_on_container_copy_construction(alloc)) {
        Node* new_node = nullptr;
        size_t created_object = 0;
        Node* last_node = nullptr;
        try {
            while (created_object < sz) {
                new_node = allocator_traits::allocate(alloc_, 1);
                try {
                    allocator_traits::construct(alloc_, new_node, nullptr, T());
                    if (created_object == 0) {
                        head_ = new_node;
                    } else {
                        last_node->next_ = new_node;
                    }
                    last_node = new_node;
                    ++created_object;
                } catch (...) {
                    allocator_traits::deallocate(alloc_, new_node, 1);
                    throw;
                }
            }
        } catch (...) {
            Node* next_node = nullptr;
            new_node = head_->next_;
            for (size_t i = 0; i < created_object; ++i){
                next_node = new_node->next_;
                allocator_traits::destroy(alloc_, new_node);
                allocator_traits::deallocate(alloc_, new_node, 1);
                new_node = next_node;
            }
            throw;
        }
    }

    template <typename InputIt>
    MyList(InputIt first, InputIt last, const allocator_& alloc = allocator_())
        : head_(nullptr), alloc_(std::allocator_traits<allocator_>::select_on_container_copy_construction(alloc)) {
        Node* new_node = nullptr;
        size_t created_object = 0;
        Node* last_node = nullptr;
        try {
            while (first != last){
                new_node = allocator_traits::allocate(alloc_, 1);
                try {
                    allocator_traits::construct(alloc_, new_node, nullptr, *(first++));
                    if (created_object == 0) {
                        head_ = new_node;
                    } else {
                        last_node->next_ = new_node;
                    }
                    last_node = new_node;
                    ++created_object;
                } catch (...) {
                    allocator_traits::deallocate(alloc_, new_node, 1);
                    throw;
                }
            }
        } catch (...) {
            Node* next_node = nullptr;
            new_node = head_->next_;
            for (size_t i = 0; i < created_object; ++i){
                next_node = new_node->next_;
                allocator_traits::destroy(alloc_, new_node);
                allocator_traits::deallocate(alloc_, new_node, 1);
                new_node = next_node;
            }
            throw;
        }
    }
    MyList(const std::initializer_list<T>& other, const allocator_& alloc = allocator_())
        : head_(nullptr), alloc_(std::allocator_traits<allocator_>::select_on_container_copy_construction(alloc)) {
        Node* new_node = nullptr;
        size_t created_object = 0;
        Node* last_node = nullptr;
        try {
            for (auto it = other.begin(); it != other.end(); ++it){
                new_node = allocator_traits::allocate(alloc_, 1);
                try {
                    allocator_traits::construct(alloc_, new_node, nullptr, *it);
                    if (created_object == 0) {
                        head_ = new_node;
                    } else {
                        last_node->next_ = new_node;
                    }
                    last_node = new_node;
                    ++created_object;
                } catch (...) {
                    allocator_traits::deallocate(alloc_, new_node, sizeof(Node));
                    throw;
                }
            }
        } catch (...) {
            Node* next_node = nullptr;
            new_node = head_->next_;
            for (size_t i = 0; i < created_object; ++i){
                next_node = new_node->next_;
                allocator_traits::destroy(alloc_, new_node);
                allocator_traits::deallocate(alloc_, new_node, sizeof(Node));
                new_node = next_node;
            }
            throw;
        }
    }

    MyList(const MyList& other, const allocator_& alloc)
        : head_(nullptr), alloc_(std::allocator_traits<allocator_>::select_on_container_copy_construction(other.alloc_)) {
        Node* new_node = nullptr;
        size_t created_object = 0;
        Node* last_node = nullptr;
        try {
            for (auto it = other.Begin(); it != other.End(); ++it){
                new_node = allocator_traits::allocate(alloc_, 1);
                try {
                    allocator_traits::construct(alloc_, new_node, nullptr, *it);
                    if (created_object == 0) {
                        head_ = new_node;
                    } else {
                        last_node->next_ = new_node;
                    }
                    last_node = new_node;
                    ++created_object;
                } catch (...) {
                    allocator_traits::deallocate(alloc_, new_node, sizeof(Node));
                    throw;
                }
            }
        } catch (...) {
            Node* next_node = nullptr;
            new_node = head_->next_;
            for (size_t i = 0; i < created_object; ++i) {
                next_node = new_node->next_;
                allocator_traits::destroy(alloc_, new_node);
                allocator_traits::deallocate(alloc_, new_node, sizeof(Node));
                new_node = next_node;
            }
            throw;
        }
    }

    size_t Size() const noexcept {
        size_t sz = 0;
        if (head_ == nullptr) {
            return 0u;
        }
        Node* node = head_;
        while (node != nullptr) {
            ++sz;
            node = node->next_;
        }
        return sz;
    }

    bool IsEmpty() const noexcept {
        return (head_ == nullptr);
    }

    Iterator InsertAfter(Iterator it, const T& value){
        Node* new_node = nullptr;
        try {
            new_node = allocator_traits::allocate(alloc_, sizeof(Node));
            allocator_traits::construct(alloc_, new_node, it.head_->next_, value);
            it.head_->next_ = new_node;
            ++it;
        } catch (...) {
            allocator_traits::deallocate(alloc_, new_node, sizeof(Node));
            throw;
        }
        return it;
    }

    template <typename... Args>
    Iterator EmplaceAfter(Iterator it, Args&&... args){
        Node* new_node = nullptr;
        try {
            new_node = allocator_traits::allocate(alloc_, sizeof(Node));
            allocator_traits::construct(alloc_, new_node, it.head_->next_, std::forward<Args>(args)...);
            it.head_->next_ = new_node;
            ++it;
        } catch (...) {
            allocator_traits::deallocate(alloc_, new_node, sizeof(Node));
            throw;
        }
        return it;
    }

    template <typename... Args>
    void EmplaceFront(Args&&... args) {
        Node* new_node = nullptr;
        try {
            new_node = allocator_traits::allocate(alloc_, sizeof(Node));
            allocator_traits::construct(alloc_, new_node, head_, std::forward<Args>(args)...);
            head_ = new_node;
        } catch (...) {
            allocator_traits::deallocate(alloc_, new_node, sizeof(Node));
            throw;
        }
    }

    template <typename... Args>
    void EmplaceBack(Args&&... args) {
        Node* new_node = nullptr;
        Node* tmp = head_;
        try {
            new_node = allocator_traits::allocate(alloc_, sizeof(Node));
            allocator_traits::construct(alloc_, new_node, nullptr, std::forward<Args>(args)...);
            if (head_ == nullptr) {
                head_ = new_node;
            } else {
                while (tmp->next_ != nullptr) {
                    tmp = tmp->next_;
                }
                tmp->next_ = new_node;
            }
        } catch (...) {
            allocator_traits::deallocate(alloc_, new_node, sizeof(Node));
            throw;
        }
    }

    Iterator EraseAfter(Iterator it) {
        Node* next_node = it.head_->next_->next_;
        allocator_traits::destroy(alloc_, it.head_->next_);
        allocator_traits::deallocate(alloc_, it.head_->next_, sizeof(Node));
        it.head_->next_ = next_node;
        return Iterator(next_node);
    }

    void PushFront(const T& value) {
        EmplaceFront(value);
    }

    void PushBack(const T& value) {
        EmplaceBack(value);
    }

    void PopFront() {
        if (IsEmpty()) {
            throw;
        }
        Node* next_node = head_->next_;
        allocator_traits::destroy(alloc_, head_);
        allocator_traits::deallocate(alloc_, head_, sizeof(Node));
        head_ = next_node;
    }

    void PopBack() {
        if (IsEmpty()) {
            throw std::out_of_range("Error: cannot pop from an empty list");
        }

        if (head_->next_ == nullptr) {
            allocator_traits::destroy(alloc_, head_);
            allocator_traits::deallocate(alloc_, head_, sizeof(Node));
            head_ = nullptr;
            return;
        }

        Node* current = head_;
        while (current->next_ && current->next_->next_) {
            current = current->next_;
        }

        Node* last_node = current->next_;
        current->next_ = nullptr;

        allocator_traits::destroy(alloc_, last_node);
        allocator_traits::deallocate(alloc_, last_node, sizeof(Node));
    }

    Iterator Find(const T& value) {
        Iterator it = Begin();
        for (; it != End(); ++it) {
            if (it == End()) {
                break;
            }
            if (*it == value) {
                break;
            }
        }
        return it;
    }

    ConstIterator Find(const T& value) const {
        ConstIterator it = Cbegin();
        for (; it != Cend(); ++it) {
            if (it == End()) {
                break;
            }
            if (*it == value) {
                break;
            }
        }
        return it;
    }

    void Swap(MyList& other) {
        if (allocator_traits::propagate_on_container_swap::value) {
            std::swap(alloc_, other.alloc_);
        }
        std::swap(other.head_, head_);
    }

    Iterator Begin() {
        return Iterator(head_);
    }

    ConstIterator Begin() const {
        return ConstIterator(head_);
    }

    Iterator End() {
        return Iterator(nullptr);
    }

    ConstIterator End() const {
        return ConstIterator(nullptr);
    }

    ConstIterator Cbegin() const {
        return ConstIterator(head_);
    }

    ConstIterator Cend() const {
        return ConstIterator(nullptr);
    }

    void Clear() {
        Node* next_node = nullptr;
        while (head_ != nullptr) {
            next_node = head_->next_;
            allocator_traits::destroy(alloc_, head_);
            allocator_traits::deallocate(alloc_, head_, sizeof(Node));
            head_ = next_node;
        }
    }

    T& Front() {
        return head_->value_;
    }

    const T& Front() const {
        return head_->value_;
    }

    ~MyList() {
        Clear();
    }

private:
    Node* head_;
    typename std::allocator_traits<allocator_>::template rebind_alloc<Node> alloc_;
};