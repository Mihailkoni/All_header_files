#pragma once

#include <iostream>
using namespace std;

struct Circle {
    int data;
    Circle* next;
    Circle* prev;
};

void delete_List(Circle*& head) { 
    if (head == nullptr) {
        return;
    }
    Circle* slider = head;
    Circle* next_Circle;
    do {
        next_Circle = slider->next;
        delete slider;
        slider = next_Circle;
    } while (slider != head);
    head = nullptr;
}

void add_to_list(Circle*& head, int info) { 
    Circle* new_Circle = new Circle();
    new_Circle->data = info;
    if (head == nullptr) {
        new_Circle->next = new_Circle;
        new_Circle->prev = new_Circle;
        head = new_Circle;
    }
    else {
        Circle* last_Circle = head->prev;
        new_Circle->prev = last_Circle;
        new_Circle->next = head;
        last_Circle->next = new_Circle;
        head->prev = new_Circle;
    }
}

void remove_after(Circle*& head, int info) { 
    if (head == nullptr) {
        cout << "List is empty";
        return;
    }
    Circle* slider = head;
    do {
        if (slider->data == info) {
            Circle* next_Circle = slider->next;
            if (slider == head && next_Circle == head) {
                return;
            }
            if (next_Circle == head->prev) {
                slider->next = head;
                head->prev = slider;
                delete next_Circle;
                slider = slider->next;
            }
            else if (next_Circle == head) {
                slider = slider->next;
            }
            else {
                slider->next = next_Circle->next;
                next_Circle->next->prev = slider;
                delete next_Circle;
                slider = slider->next;
            }
        }
        else { slider = slider->next; }
    } while (slider != head);
}

bool search_in_list(Circle* head, int info) {
    if (head == nullptr) {
        return 0;
    }
    Circle* slider = head;
    do {
        if (slider->data == info) {
            return 1;
        }
        slider = slider->next;
    } while (slider != head);
    return 0;
}

void print_list(Circle* head) {
    if (head == nullptr) {
        cout << "List is empty";
        return;
    }
    Circle* slider = head;
    do {
        cout << slider->data << " ";
        slider = slider->next;
    } while (slider != head);
}

void reverse_print_List(Circle* head) {
    if (head == nullptr) {
        cout << "List is empty";
        return;
    }
    Circle* slider = head->prev;
    do {
        cout << slider->data << " ";
        slider = slider->prev;
    } while (slider != head->prev);

}

void simmetric_Diff(Circle*& head1, Circle*& head2, Circle*& head3) {
    if (head1 == nullptr) {
        return;
    }
    if (head2 == nullptr) {
        return;
    }
    Circle* slider1 = head1;
    Circle* slider2 = head2;
    do {
        bool flag = false;
        do {
            if (slider1->data == slider2->data) {
                flag = true;
                break;
            }
            slider2 = slider2->next;
        } while (slider2 != head2);
        if (flag == false) {
            add_to_list(head3, slider1->data);
        }
        slider2 = head2;
        slider1 = slider1->next;
    } while (slider1 != head1);

    do {
        bool flag = false;
        do {
            if (slider2->data == slider1->data) {
                flag = true;
                break;
            }
            slider1 = slider1->next;
        } while (slider1 != head1);
        if (flag == false) {
            add_to_list(head3, slider2->data);
        }
        slider1 = head1;
        slider2 = slider2->next;
    } while (slider2 != head2);
}

void delete_from_list(Circle*& head, int value) { 
    if (head == nullptr) {
        return;
    }

    Circle* current = head;
    do {
        if (current->data == value) {
            if (current == head) {
                if (current->next == head) {
                    delete current;
                    head = nullptr;
                    return;
                }
                else {
                    Circle* temp = head;
                    while (temp->next != head) {
                        temp = temp->next;
                    }
                    temp->next = head->next;
                    head = head->next;
                    head->prev = temp;
                    delete current;
                    return;
                }
            }
            else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
                delete current;
                return;
            }
        }
        current = current->next;
    } while (current != head);
}