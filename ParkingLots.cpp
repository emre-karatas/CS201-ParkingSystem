//
// Emre Karatas - 22001641
//
#include "ParkingLots.h"
#include "Cars.h"
#include <iostream>
using namespace std;


ParkingLots::ParkingLots() {
    this -> contents = new Cars*[rows];
    for(int i = 0; i < rows; i++)
    {
        contents[i] = new Cars[columns];
    }
    for( int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
        {
            contents[i][j] = Cars();
        }
    }

}
ParkingLots::ParkingLots(int lotId, int rows, int columns) {
    this -> rows = rows;
    this -> columns = columns;
    this -> contents = new Cars*[rows];
    for ( int i = 0; i < rows; i++)
    {
        contents[i] = new Cars[columns];
    }
    this -> lotId = lotId;
}
ParkingLots::ParkingLots(const ParkingLots &parkingLots) {
    this -> lotId = parkingLots.lotId;
    this -> rows = parkingLots.rows;
    this -> columns = parkingLots.columns;
    delete this -> contents;
    this -> contents = new Cars*[rows];
    for(int i = 0; i < rows; i++)
    {
        contents[i] = new Cars[columns];
    }
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
        {
            this-> contents[i][j] = Cars(contents[i][j].getCarType(),contents[i][j].getPlateNumber());
        }
    }
}
ParkingLots::~ParkingLots()
{

}

void ParkingLots::operator=(ParkingLots p) {
    this -> lotId = p.getLotId();
    this -> rows = p.getRows();
    this -> columns = p.getColumns();
    delete this -> contents;
    this-> contents = new Cars*[rows];
    for(int i = 0; i < rows; i++)
    {
        contents[i] = new Cars[columns];
    }
    for (int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
        {
            this ->contents[i][j] = Cars(p.contents[i][j].getCarType(),p.contents[i][j].getPlateNumber());
        }
    }


}
int ParkingLots::numberOfEmptySpaces() {
    char emptySpace = '+';
    int emptyCount = 0;
    for (int i = 0; i < this -> rows; i++)
    {
        for(int j = 0; j < this -> columns; j++)
        {
            if(this -> contents[i][j].getCarType() == emptySpace)
            {
                emptyCount++;
            }
        }
    }
    return  emptyCount;

}

int ParkingLots::getLotId() {
    return this -> lotId;
}
int ParkingLots::getRows() {
    return this -> rows;
}
int ParkingLots::getColumns() {
    return this -> columns;
}