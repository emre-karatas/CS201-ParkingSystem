//
// Emre Karatas - 22001641
//

#ifndef HW01_CARS_H
#define HW01_CARS_H
using namespace std;

class Cars{
public:
    char getCarType() const;
    int getPlateNumber() const;
    Cars();
    Cars(char carType, int plateNumber);
    Cars(const Cars& cars);
    ~Cars();
    void operator=(Cars cars);
    void setPlateNumber(int plateNumber);


private:
    int plateNumber;
    char carType;

};

#endif //HW01_CARS_H
