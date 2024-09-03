#pragma once

#include <iostream>
#include <string>
#include <functional>

/*
	初步实现List结构：支持insert remove find函数 
	
	Node1   Node2
	------   --------
	head   ->  head   -> NULL  
    ------   --------	 
*/

template <typename T>
class MyList {
public:
	struct Node {
    	T data;
    	Node* next;
    	Node(T val) : data(val), next(NULL) {}
	};

private:
    Node* head;

public:
    MyList() : head(NULL) {}

    ~MyList() {
        Node* current = head;
        while (current != NULL) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }
	
    void insert(T value) {
        Node* newNode = new Node(value);
        if (head == NULL) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    void remove(T value) {
        if (head == NULL) return;

        // If head needs to be removed
        if (head->data == value) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        Node* current = head;
        while (current->next != NULL && current->next->data != value) {
            current = current->next;
        }

        if (current->next != NULL) {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
        }
    }

	Node* beginNode()
	{
		return head;
	}
	
    void display() const {
        Node* current = head;
        while (current != NULL) {
            std::cout << current->data << ""<<std::endl;
            current = current->next;
        }
    }
};
