#pragma once
#include <iostream>
#include <exception>

namespace myStack {
    template <typename T>
    class Node {
    public:
        T info;
        Node* next;
        Node* prev;
        Node(T value) { info = value; next = prev = nullptr; }
    };

    template <typename U>
    class Stack {
    private:
        Node<U>* head;
        Node<U>* current;

    public:
        Stack() { head = current = nullptr; }

        ~Stack() {
            while (!isEmpty()) {
                pop();
            }
        }

        bool isEmpty() const {
            return head == nullptr || current == nullptr;
        }

        U top() const {
            if (isEmpty()) throw std::exception("Stack is empty!");
            return current->info;
        }

        void push(U value) {
            Node<U>* item = new Node<U>(value);
            if (isEmpty()) {
                head = current = item;
            }
            else {
                current->next = item;
                item->prev = current;
                current = item;
            }
        }

        void pop() {
            if (!isEmpty()) {
                if (head != current) {
                    current = current->prev;
                    delete current->next;
                    current->next = nullptr;
                }
                else {
                    delete head;
                    head = current = nullptr;
                }
            }
        }

        void show() const {
            if (isEmpty())
                std::cout << "Stack is empty!\n";
            else {
                Node<U>* p = head;
                while (p != nullptr) {
                    std::cout << " " << p->info;
                    p = p->next;
                }
                std::cout << std::endl;
            }
        }
    };
}