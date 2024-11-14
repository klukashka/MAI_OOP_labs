// #pragma once
// #include "../include/list.hpp"

// #define MIN_CAP static_cast<size_t>(10)

// // template <class T> class Node;
// // template <class T> class List_iterator;


// template <class T, typename allocator_type> 
// List<T, allocator_type>::List(const allocator_type& alloc) noexcept : head_(nullptr), tail_(nullptr), sz_(0) {}

// template <class T, typename allocator_type>
// List<T, allocator_type>::List(const List& other, const allocator_type& alloc) noexcept {
//     head_ = nullptr;
//     tail_ = nullptr;
//     sz_ = 0;
//     for (Node<T>* cur = other.head_; cur != 0; cur = cur -> next_) {
//         push_back(cur->value);
//     }
// }

// template <class T, typename allocator_type> 
// List<T, allocator_type>::~List() noexcept{
//     // while (!this->empty()){
//     //     this->pop_back();
//     // }
//     // this->allocator_.deallocate(this->head_, sz_);
//     Node<T>* current = head_; 
//     while (current) {
//         Node<T>* next = current->next;
//         allocator_type::destroy(current);
//         allocator_type::deallocate(current, 1); 
//         current = next;
//     }
// }

// template <class T, typename allocator_type>
// void List<T, allocator_type>::push_back(const T& other)
// {
//     // Node<T>* new_link = new Node<T> (other);
//     Node<T>* new_link = allocator_type::allocate(1);  // Allocate memory for 1 node
//     allocator_type::construct(new_link, other);
//     if (!head_){
//         head_ = new_link;
//         tail_ = new_link;
//     } else {
//         tail_->next = new_link;    
//         tail_ = new_link;
//     }
//     ++sz_;
// }

// template <class T, typename allocator_type>
// bool List<T,allocator_type>::empty() const {
//     return this->sz_ == 0;
// }

// template <class T, typename allocator_type>
// size_t List<T, allocator_type>::size() const {
//     return this->sz_;
// }

// template <class T, typename allocator_type>
// T& List<T, allocator_type>::back() const {
//     return this->tail_.value;
// }

// template <class T, typename allocator_type>
// T& List<T, allocator_type>::front() const {
//     return this->head_.value;
// }

// template <class T, typename allocator_type>
// void List<T, allocator_type>::push_front(const T& other){
//     // Node<T>* newnode = new Node<T> (other);
//     Node<T>* newnode = allocator_type::allocate(1);  // Allocate memory for 1 node
//     allocator_type::construct(newnode, other);
//     if (head_){
//         newnode->next = head_;
//         head_ = newnode;
//     } else {
//         head_ = newnode;
//         tail_ = newnode;
//     }
// }

// template <class T, typename allocator_type>
// void List<T, allocator_type>::pop_front() {
//     if (empty()) {
//         return;  // Do nothing if the list is empty
//     }

//     // Save the current head node
//     Node<T>* oldHead = head_;

//     // Move head to the next node
//     head_ = head_->next;

//     // Deallocate memory for the old head node
//     allocator_type::destroy(oldHead);  // Call the destructor of the Node
//     allocator_type::deallocate(oldHead, 1);  // Deallocate the memory
//     --sz_;  // Decrement the size of the list
// }

// template <class T, typename allocator_type>
// void List<T, allocator_type>::pop_back() {
//     if (empty()) {
//         return;  // Do nothing if the list is empty
//     }

//     if (head_->next == nullptr) {  // Special case: Only one element in the list
//         // Only one node in the list, so pop_front() is equivalent here
//         pop_front();
//         return;
//     }

//     // Traverse the list to find the second-to-last node
//     Node<T>* current = head_;
//     while (current->next && current->next->next) {
//         current = current->next;  // Move to the next node
//     }

//     // `current` is now the second-to-last node
//     Node<T>* tail = current->next;  // The last node (tail)
//     current->next = nullptr;  // Remove the reference to the last node

//     // Deallocate the memory for the tail node
//     allocator_type::destroy(tail);  // Destroy the tail node
//     allocator_type::deallocate(tail, 1);  // Deallocate the memory
//     --sz_;  // Decrement the size of the list

//     // Node<T>* tmp = this->head_;
//     // while (tmp->next != this->tail_){
//     //     tmp = tmp->next;
//     // }
//     // this->allocator_.deallocate(this->tail_, 1);
//     // this->tail_ = tmp->next;
// }

// template <class T, typename allocator_type>
// void List<T, allocator_type>::insert(iterator pos, const T& other) {

// }

// template <class T, typename allocator_type>
// void List<T, allocator_type>::erase(iterator& pos) {

// }

// template <class T, typename allocator_type>
// List<T>& List<T, allocator_type>::operator=(const List<T>& other) {

// }
