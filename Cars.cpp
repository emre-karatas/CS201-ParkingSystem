//
//Emre Karatas-22001641
//
#include "Cars.h"
using namespace std;

Cars::Cars() {
    this -> carType = '+';
}

Cars::Cars(char carType, int plateNumber) {
    this -> carType = carType;
    this -> plateNumber = plateNumber;
}

Cars::Cars(const Cars &cars) {
    if(cars.carType != '+')
    {
        plateNumber = cars.plateNumber;
    }
    this -> carType = cars.carType;
}
Cars::~Cars() {

}
void Cars::operator=(Cars cars) {
    if(cars.carType != '+')
        this -> plateNumber = cars.plateNumber;
    this -> carType = cars.carType;
}
char Cars::getCarType() const {
    return carType;
}
int Cars::getPlateNumber() const{
    return plateNumber;
}
void Cars::setPlateNumber(int plateNumber)
{
    this -> plateNumber = plateNumber;
}


