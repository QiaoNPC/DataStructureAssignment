#pragma once
#include "import.h"

// Comparison functions for different data types
bool compareByAdsId(const Property& a, const Property& b) {
  return a.ads_id < b.ads_id;
}

bool compareByPropName(const Property& a, const Property& b) {
  return a.prop_name < b.prop_name;
}

bool compareByCompletionYear(const Property& a, const Property& b) {
  return a.completion_year < b.completion_year;
}

bool compareByMonthlyRent(const Property& a, const Property& b) {
  return a.monthly_rent < b.monthly_rent;
}

bool compareByLocation(const Property& a, const Property& b) {
  return a.location < b.location;
}

bool compareByPropertyType(const Property& a, const Property& b) {
  return a.property_type < b.property_type;
}

bool compareByRooms(const Property& a, const Property& b) {
  return a.rooms < b.rooms;
}

bool compareByParking(const Property& a, const Property& b) {
  return a.parking < b.parking;
}

bool compareByBathroom(const Property& a, const Property& b) {
  return a.bathroom < b.bathroom;
}

bool compareBySize(const Property& a, const Property& b) {
  return a.size < b.size;
}

bool compareByFurnished(const Property& a, const Property& b) {
  return a.furnished < b.furnished;
}

bool compareByRegion(const Property& a, const Property& b) {
  return a.region < b.region;
}

PropertyNode* sortProperties(PropertyNode* properties, int parameterChoice, bool useMergeSort) {
  PropertyNode* sorted = nullptr;

  switch (parameterChoice) {
    case 1:
      sorted = useMergeSort ? mergeSort(properties, compareByAdsId) : quickSort(properties, compareByAdsId);
      break;
    case 2:
      sorted = useMergeSort ? mergeSort(properties, compareByPropName) : quickSort(properties, compareByPropName);
      break;
    case 3:
      sorted = useMergeSort ? mergeSort(properties, compareByCompletionYear) : quickSort(properties, compareByCompletionYear);
      break;
    case 4:
      sorted = useMergeSort ? mergeSort(properties, compareByMonthlyRent) : quickSort(properties, compareByMonthlyRent);
      break;
    case 5:
      sorted = useMergeSort ? mergeSort(properties, compareByLocation) : quickSort(properties, compareByLocation);
      break;
    case 6:
      sorted = useMergeSort ? mergeSort(properties, compareByPropertyType) : quickSort(properties, compareByPropertyType);
      break;
    case 7:
      sorted = useMergeSort ? mergeSort(properties, compareByRooms) : quickSort(properties, compareByRooms);
      break;
    case 8:
      sorted = useMergeSort ? mergeSort(properties, compareByParking) : quickSort(properties, compareByParking);
      break;
    case 9:
      sorted = useMergeSort ? mergeSort(properties, compareByBathroom) : quickSort(properties, compareByBathroom);
      break;
    case 10:
      sorted = useMergeSort ? mergeSort(properties, compareBySize) : quickSort(properties, compareBySize);
      break;
    case 11:
      sorted = useMergeSort ? mergeSort(properties, compareByFurnished) : quickSort(properties, compareByFurnished);
      break;
    case 12:
      sorted = useMergeSort ? mergeSort(properties, compareByRegion) : quickSort(properties, compareByRegion);
      break;
    default:
      break;
  }

  return sorted;
}
