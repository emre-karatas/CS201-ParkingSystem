//
// Emre Karatas - 22001641
//

#ifndef HW01_PARKINGLOTS_H
#define HW01_PARKINGLOTS_H
#include "Cars.h"
using namespace std;

class ParkingLots
{
public:
    ParkingLots();
    ParkingLots(int lotId, int rows, int columns);
    ParkingLots(const ParkingLots& parkingLots);
    ~ParkingLots();
    void operator=(ParkingLots p);
    int getLotId();
    int numberOfEmptySpaces();
    int getRows();
    int getColumns();
    Cars** contents;

private:
    int lotId;
    int rows;
    int columns;
};

#endif //HW01_PARKINGLOTS_H
