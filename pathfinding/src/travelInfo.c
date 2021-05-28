#include "travelInfo.h"
#include<stdio.h>
#include<stdlib.h>

TravelInfo* newTravelInfo(int from, int to, double weight){
    TravelInfo* tInfo = (TravelInfo*)malloc(sizeof(TravelInfo));
    tInfo->from = from;
    tInfo->to = to;
    tInfo->weight = weight;
}

void freeTravelInfo(TravelInfo** travelInfo){
    if(travelInfo && *travelInfo){ // only free allocated memory
        free(*travelInfo);
        *travelInfo = 0;
    }
}

void printTravelInfo(TravelInfo* travelInfo){
    if(travelInfo){
        printf("%d => %d (%3.3f)", travelInfo->from, travelInfo->to, travelInfo->weight);
    }
}
