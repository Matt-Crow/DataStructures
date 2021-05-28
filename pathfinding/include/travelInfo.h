#ifndef TRAVEL_INFO
#define TRAVEL_INFO

typedef struct TravelInfo {
    int from;
    int to;
    int weight;
} TravelInfo;

TravelInfo* newTravelInfo(int from, int to, int weight);
void freeTravelInfo(TravelInfo** travelInfo);

void printTravelInfo(TravelInfo* travelInfo);

#endif
