#ifndef TRAVEL_INFO
#define TRAVEL_INFO

typedef struct TravelInfo {
    int from;
    int to;
    double weight;
} TravelInfo;

TravelInfo* newTravelInfo(int from, int to, double weight);
void freeTravelInfo(TravelInfo** travelInfo);

void printTravelInfo(TravelInfo* travelInfo);

#endif
