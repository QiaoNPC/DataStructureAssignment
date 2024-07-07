#pragma once
#include "import.h"

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
    string* facilities;
    size_t facilities_size; // store the size of the facilities array
    string* additional_facilities;
    size_t additional_facilities_size; // store the size of the additional facilities array
    string region;
};

// PropertyNode structure for linked list
struct PropertyNode {
    Property property;
    PropertyNode* next;
};

// Function to display properties
void displayProperties(PropertyNode* head, const vector<int>& columnChoices) {
    PropertyNode* current = head;
    while (current) {
        for (int choice : columnChoices) {
            switch (choice) {
                case 1:
                    cout << fixed << setprecision(0) << current->property.ads_id << " | ";
                    break;
                case 2:
                    cout << current->property.prop_name << " | ";
                    break;
                case 3:
                    cout << current->property.completion_year << " | ";
                    break;
                case 4:
                    cout << "$" << fixed << setprecision(0) << current->property.monthly_rent << " | ";
                    break;
                case 5:
                    cout << current->property.location << " | ";
                    break;
                case 6:
                    cout << current->property.property_type << " | ";
                    break;
                case 7:
                    cout << current->property.rooms << " rooms" << " | ";
                    break;
                case 8:
                    cout << current->property.parking << " parking" << " | ";
                    break;
                case 9:
                    cout << current->property.bathroom << " bathroom" << " | ";
                    break;
                case 10:
                    cout << current->property.size << " sqft" << " | ";
                    break;
                case 11:
                    cout << current->property.furnished << " | ";
                    break;
                case 12:
                    cout << current->property.region << " | ";
                    break;
                case 13:
                    for (size_t j = 0; j < current->property.facilities_size; ++j) {
                        cout << current->property.facilities[j] << ", ";
                    }
                    cout << " | ";
                    break;
                case 14:
                    for (size_t j = 0; j < current->property.additional_facilities_size; ++j) {
                        cout << current->property.additional_facilities[j] << ", ";
                    }
                    cout << " | ";
                    break;
                default:
                    cout << "Invalid column choice." << endl;
                    break;
            }
        }
        cout << endl;
        current = current->next;
    }
}

void freeList(PropertyNode* head) {
    while (head) {
        PropertyNode* temp = head;
        delete[] head->property.facilities;
        delete[] head->property.additional_facilities;
        head = head->next;
        delete temp;
    }
}
