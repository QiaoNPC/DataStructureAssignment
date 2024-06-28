#pragma once
#include "import.h"
#include "QuickSort.hpp"
#include "MergeSort.hpp"

// Function to insert a PropertyNode in sorted order
void insertSorted(PropertyNode*& sorted, PropertyNode* newPropertyNode, bool (*compare)(const Property&, const Property&)) {
  if (!sorted || compare(newPropertyNode->property, sorted->property)) {
    newPropertyNode->next = sorted;
    sorted = newPropertyNode;
  } else {
    PropertyNode* current = sorted;
    while (current->next && !compare(newPropertyNode->property, current->next->property)) {
      current = current->next;
    }
    newPropertyNode->next = current->next;
    current->next = newPropertyNode;
  }
}

// Function to sort the linked list using insertion sort
PropertyNode* insertionSort(PropertyNode* head, bool (*compare)(const Property&, const Property&)) {
  PropertyNode* sorted = nullptr;
  PropertyNode* current = head;
  while (current) {
    PropertyNode* next = current->next;
    insertSorted(sorted, current, compare);
    current = next;
  }
  return sorted;
}