#pragma once
#include "import.h"

#include <iostream>
#include <string>

using namespace std;

struct Property {
  double ads_id;
  string prop_name;
  int completion_year;
  double monthly_rent;
  string location;
  string property_type;
  string rooms;
  bool parking;
  int bathroom;
  double size;
  string furnished;
  vector<string> facilities;
  vector<string> additional_facilities;
  string region;
};

// PropertyNode structure for linked list
struct PropertyNode {
  Property property;
  PropertyNode* next;
};

// Function to display properties
void displayProperties(PropertyNode* head) {
  PropertyNode* current = head;
  while (current) {
    cout << current->property.ads_id << " | ";
    cout << current->property.prop_name << " | ";
    cout << "$" << fixed << setprecision(0) << current->property.monthly_rent << " | ";
    cout << current->property.rooms << " rooms" << " | ";
    // cout << current->property.bathroom << " bathroom" << " | ";
    cout << current->property.location << " | ";
    // cout << current->property.property_type << " | ";
    // cout << current->property.size << " sqft" << " | ";
    // cout << current->property.furnished << " | ";
    cout << current->property.region << endl;
    current = current->next;
  }
}

void freeList(PropertyNode* head) {
  while (head) {
    PropertyNode* temp = head;
    head = head->next;
    delete temp;
  }
}