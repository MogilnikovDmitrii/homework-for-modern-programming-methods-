#include "doubly_linked_list.hpp"

#include <iostream>

using DmMog::DoublyLinkedList;

template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
	Node* current = begin;

    while(current != nullptr){
        Node* next_node = current->next;
        delete current;
        current = next_node;
    }
    begin = nullptr;
    end = nullptr;
}

template<typename T>
std::size_t DoublyLinkedList<T>::get_size() const noexcept {
	Node* current = begin;
    size_t lenght = 0;
    while(current != nullptr){
        current = current->next;
        lenght++;
    }
    return lenght;
}

template<typename T>
bool DoublyLinkedList<T>::has_item(const T& value) const noexcept {
	Node* current = begin;
    while(current != nullptr){
        if(current->value == value){
            return true;
        }
        current = current->next;
    }
    return false;
}

template<typename T>
void DoublyLinkedList<T>::print() const noexcept {
	Node* current = begin;
    while(current != nullptr){
        std::cout << current->value << " ";
        current = current->next;
    }
    std::cout << "\n";
}

template<typename T>
void DoublyLinkedList<T>::push_back(const T& value) {
    Node* new_node = new Node(value); 

    new_node->prev = end;             
    new_node->next = nullptr;         

    if (end) {
        end->next = new_node;
    } else {                          
        begin = new_node;
    }

    end = new_node;                  
}

template<typename T>
bool DoublyLinkedList<T>::remove_first(const T& value) noexcept {
	Node* current = begin;
    while(current != nullptr){
        if(current->value == value){
            Node* to_delete = current;
            if (current == begin && current == end) {
                begin = end = nullptr;
            } else if (current == begin) {
                begin = begin->next;
                begin->prev = nullptr;
            } else if (current == end) {
                end = end->prev;
                end->next = nullptr;
            } else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
            }
            delete to_delete;
            return true;
        }
        current = current->next;
    }
    return false;
}



// Явная инстанциация для int (можно убрать или добавить другие типы)
template class DoublyLinkedList<int>;