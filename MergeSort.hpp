#pragma once
#include "import.h"

// Function to merge two sorted linked lists
PropertyNode* merge(PropertyNode* left, PropertyNode* right, bool (*compare)(const Property&, const Property&)) {
    if (!left) return right;
    if (!right) return left;

    PropertyNode* merged = nullptr;
    if (compare(left->property, right->property)) {
        merged = left;
        merged->next = merge(left->next, right, compare);
    } else {
        merged = right;
        merged->next = merge(left, right->next, compare);
    }

    return merged;
}

// Function to split the linked list into two halves
void splitList(PropertyNode* head, PropertyNode** left, PropertyNode** right) {
    if (!head || !head->next) {
        *left = head;
        *right = nullptr;
        return;
    }

    PropertyNode* slow = head;
    PropertyNode* fast = head->next;

    while (fast) {
        fast = fast->next;
        if (fast) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *left = head;
    *right = slow->next;
    slow->next = nullptr;
}

// Merge sort function for linked list
PropertyNode* mergeSort(PropertyNode* head, bool (*compare)(const Property&, const Property&)) {
    if (!head || !head->next) {
        return head;
    }

    PropertyNode* left = nullptr;
    PropertyNode* right = nullptr;

    splitList(head, &left, &right);

    left = mergeSort(left, compare);
    right = mergeSort(right, compare);

    return merge(left, right, compare);
}
