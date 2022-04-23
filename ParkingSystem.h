//
// Emre Karatas - 22001641
//

#ifndef HW01_PARKINGSYSTEM_H
#define HW01_PARKINGSYSTEM_H
#include "ParkingLots.h"
#include <string>
using namespace std;

class ParkingSystem{
public:
    ParkingSystem();
    ~ParkingSystem();

    void createLot(int id, int rows, int columns);
    void removeLot(int id);
    void listLots();
    void lotContents(int id);
    void parkCar(int lotId,string location,string carType, int plateNumber);
    void findCar(int plateNumber);
    void removeCar(int plateNumber);
    int rowFinder(char c);
    int columnFinder(string location);
    string intToLocation(int letterNumber);
    bool lotIdChecker(int lotId);
    bool plateNumberChecker(int plateNumber);
    Cars* parkedCarsFinder(int id);
    void columnsPrinter(int foundLocation);

private:
    ParkingLots* lotList;
    int lotCount;

};
#endif //HW01_PARKINGSYSTEM_H
