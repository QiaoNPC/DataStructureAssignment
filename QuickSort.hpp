#pragma once
#include "import.h"

// Function to partition the linked list around a pivot
PropertyNode* partition(PropertyNode* head, PropertyNode* end, PropertyNode** newHead, PropertyNode** newEnd, bool (*compare)(const Property&, const Property&)) {
    PropertyNode* pivot = end;
    PropertyNode* prev = nullptr;
    PropertyNode* curr = head;
    PropertyNode* tail = pivot;

    // During partition, both newHead and newEnd will be updated
    while (curr != pivot) {
        if (compare(curr->property, pivot->property)) {
            if (!*newHead)
                *newHead = curr;

            prev = curr;
            curr = curr->next;
        } else {
            if (prev)
                prev->next = curr->next;

            PropertyNode* temp = curr->next;
            curr->next = nullptr;
            tail->next = curr;
            tail = curr;
            curr = temp;
        }
    }

    if (!*newHead)
        *newHead = pivot;

    *newEnd = tail;

    return pivot;
}

// Function to get the tail of the linked list
PropertyNode* getTail(PropertyNode* head) {
    while (head != nullptr && head->next != nullptr)
        head = head->next;
    return head;
}

// Function to perform the recursive QuickSort
PropertyNode* quickSortRecur(PropertyNode* head, PropertyNode* end, bool (*compare)(const Property&, const Property&)) {
    if (!head || head == end)
        return head;

    PropertyNode* newHead = nullptr;
    PropertyNode* newEnd = nullptr;

    PropertyNode* pivot = partition(head, end, &newHead, &newEnd, compare);

    if (newHead != pivot) {
        PropertyNode* temp = newHead;
        while (temp->next != pivot)
            temp = temp->next;
        temp->next = nullptr;

        newHead = quickSortRecur(newHead, temp, compare);

        temp = getTail(newHead);
        temp->next = pivot;
    }

    pivot->next = quickSortRecur(pivot->next, newEnd, compare);

    return newHead;
}

// QuickSort function for the linked list
PropertyNode* quickSort(PropertyNode* head, bool (*compare)(const Property&, const Property&)) {
    PropertyNode* end = getTail(head);
    return quickSortRecur(head, end, compare);
}
