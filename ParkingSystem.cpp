//
// Emre Karatas
//   22001641
//
#include <iostream>
using namespace std;
#include "ParkingSystem.h"
#include "Cars.h"

    ParkingSystem::ParkingSystem()
    {

        lotCount = 0;
        lotList = new ParkingLots[1];
        lotList[0] = ParkingLots();
    }
    ParkingSystem::~ParkingSystem()
    {
        for(int i = 0; i < lotCount; i++)
        {
            for(int j = 0; j < lotList[i].getRows(); j++)
            {
                delete[] lotList[i].contents[j];
            }
        }
        delete[] lotList->contents;

        delete[] lotList;

    }

    bool ParkingSystem::lotIdChecker(int lotId) {
        bool found = false;
        if(lotCount != 0)
        {

            for(int i = 0; i < lotCount; i++)
            {
                if(lotList[i].getLotId() == lotId)
                {
                    found = true;
                }
            }
        }
        return found;
    }
    void ParkingSystem::createLot(int id, int rows, int columns)
    {

        int minRows = 1;
        int minColumns = 1;
        int maxRows = 12;
        int maxColumns = 12;
        if(lotCount > 0)
        {
            bool lotExists = lotIdChecker(id);
            if(lotExists)
            {
                cout << "Cannot create the parking lot " << id << ", a lot with this ID already exists" << endl;
            }
            else
            {
                if(rows > maxRows || columns > maxColumns || columns < minColumns || rows < minRows )
                {
                    cout << "Cannot create the parking lot " << id << ", dimensions exceed acceptable bounds" << endl;
                }
                else
                {
                    lotCount++;
                    ParkingLots* system = new ParkingLots[lotCount];
                    for(int i = 0; i < lotCount-1; i++)
                    {
                        system[i] =  ParkingLots(lotList[i].getLotId(),lotList[i].getRows(),lotList[i].getColumns());
                    }
                    delete[] lotList;
                    system[lotCount-1] =  ParkingLots(id,rows,columns);
                    lotList = new ParkingLots[lotCount];
                    for(int i = 0; i < lotCount; i++)
                    {
                        lotList[i] =  ParkingLots(system[i].getLotId(),system[i].getRows(), system[i].getColumns());
                    }
                    delete[] system;
                    cout << "Parking lot with " << id << " and dimensions " << "(" << rows << "," << columns << ") has been added to the system" << endl;
                }
            }
        }
        else
        {
            if(rows > maxRows || columns > maxColumns || columns < minColumns || rows < minRows )
            {
                cout << "Cannot create the parking lot " << id << ", dimensions exceed acceptable bounds" << endl;
            }
            else
            {
                lotCount++;
                lotList[0] = ParkingLots(id,rows,columns);
                cout << "Parking lot with " << id << " and dimensions " << "(" << rows << "," << columns << ") has been added to the system" << endl;

            }

        }


    }
Cars* ParkingSystem::parkedCarsFinder(int id)
{
    int foundLocation;
    for(int i = 0; i < lotCount; i++)
    {
        if(lotList[i].getLotId() == id)
        {
            foundLocation = i;
        }
    }
    Cars* parkedCars = new Cars[lotList[foundLocation].getRows()*lotList[foundLocation].getColumns()];
    int counter = 0;
    for(int i = 0; i < lotList[foundLocation].getRows(); i++)
    {
        for(int j = 0; j < lotList[foundLocation].getColumns(); j++)
        {
            if(i > 0)
            {
                if(lotList[foundLocation].contents[i][j].getCarType() == 'b' && lotList[foundLocation].contents[i-1][j].getCarType() == 'b')
                {
                    parkedCars[counter].setPlateNumber( lotList[foundLocation].contents[i][j].getPlateNumber());
                    counter++;

                }
                else if ( lotList[foundLocation].contents[i][j].getCarType() == 'a')
                {
                    parkedCars[counter].setPlateNumber(lotList[foundLocation].contents[i][j].getPlateNumber());
                    counter++;

                }
            }
            else if( i == 0)
            {
                if(lotList[foundLocation].contents[0][j].getCarType() == 'a')
                {
                    parkedCars[counter].setPlateNumber(lotList[foundLocation].contents[0][j].getPlateNumber());
                    counter++;
                }
            }
        }
    }
    if(counter != 0)
    {
        for(int i = 0; i < counter-1; i++)
        {
            cout <<  parkedCars[i].getPlateNumber() << ", ";
        }
        cout << parkedCars[counter-1].getPlateNumber() << endl;
    }
    else
    {
        cout << "no cars yet " << endl;
    }
    return parkedCars;
    //delete[] parkedCars;
}

    void ParkingSystem::removeLot(int id)
    {

        bool found = false;
        static int location;
        bool emptyLot = false;
        for ( int i = 0; i < lotCount; i++)
        {
            if( lotList[i].getLotId() == id)
            {
                found = true;
                location = i;

            }
        }
        if(lotList[location].numberOfEmptySpaces() == lotList[location].getRows() * lotList[location].getColumns() )
        {
            emptyLot = true;
        }
        if ( found && emptyLot )
        {
            lotCount--;
            ParkingLots* newList = new ParkingLots[lotCount];
            for( int i = 0; i < lotCount; i++)
            {
                for(int i = 0; i <= lotCount; i++)
                {
                    if( i < location)
                    {
                        newList[i] = ParkingLots(lotList[i].getLotId(),lotList[i].getRows(),lotList[i].getColumns());

                    }
                    else if ( location < i)
                    {
                        newList[i-1] =  ParkingLots(lotList[i].getLotId(),lotList[i].getRows(),lotList[i].getColumns());
                    }

                }

            }
            cout << "Lot " << id << " has  been successfully removed from the system" << endl;
            for(int i = 0; i < lotList[location].getRows(); i++)
            {
                delete[] lotList[location].contents[i];
            }
            delete[] lotList[location].contents;
            delete[] lotList;
            lotList = new ParkingLots[lotCount];
            for ( int i = 0; i < lotCount; i++)
            {
                lotList[i] =   ParkingLots(newList[i].getLotId(),newList[i].getRows(),newList[i].getColumns());

            }
            delete[] newList;

        }
        else if ( found && !emptyLot)
        {

            int rowIndex = lotList[location].getRows();
            int columnIndex = lotList[location].getColumns();
            for(int i = 0; i < rowIndex*columnIndex-lotList[location].numberOfEmptySpaces(); i++)
            {
                for(int j = 0; j < rowIndex; j++)
                {
                    for(int k = 0; k < columnIndex; k++)
                    {
                        if(lotList[location].contents[j][k].getCarType() != '+')
                        {
                            if( j > 0)
                            {
                                if(lotList[location].contents[j][k].getCarType() == 'b' && lotList[location].contents[j-1][k].getCarType() == 'b')
                                {

                                        cout << "Heavy-duty car with number plate " << lotList[location].contents[j][k].getPlateNumber() << " car has been removed from slot " << intToLocation(j) << k+1 << ", lot " << lotList[location].getLotId() << endl;
                                        lotList[location].contents[j][k] = Cars();
                                        lotList[location].contents[j-1][k] = Cars();

                                }
                                else if (lotList[location].contents[j][k].getCarType() == 'a')
                                {
                                    cout << "Light-duty car with number plate " << lotList[location].contents[j][k].getPlateNumber() << " car has been removed from slot " << intToLocation(j) << k+1 << ", lot " << lotList[location].getLotId() << endl;
                                    lotList[location].contents[j][k] = Cars();
                                }

                            }
                            else
                            {
                                if(lotList[location].contents[0][k].getCarType() == 'a')
                                {
                                    cout << "Light-duty car with number plate " << lotList[location].contents[0][k].getPlateNumber() << " car has been removed from slot " << intToLocation(j) << k+1 << ", lot " << lotList[location].getLotId() << endl;
                                    lotList[location].contents[0][k] = Cars();

                                }
                            }

                        }
                    }
                }


            }
            cout << "Lot " << lotList[location].getLotId() << " has been successfully removed from the system" << endl;
            lotCount--;

        }
        else
        {
            cout << "Lot " << id << " is not in the system" << endl;
        }


    }

    void ParkingSystem::listLots()
    {
        if (!lotCount)
        {
            cout << "No lots to list" << endl;
        }
        else
        {
            cout << "List of lots: " << endl;
            for (int i = 0; i < lotCount; i++)
            {
                cout<< "ID: " << lotList[i].getLotId() << ", Dim: (" << lotList[i].getRows() << "," << lotList[i].getColumns() <<"), number of empty parking spaces: " << lotList[i].numberOfEmptySpaces() <<  endl;
            }

        }



    }
    void ParkingSystem::lotContents(int id)
    {
        bool occured = false;
        int location;
        for(int i = 0; i < lotCount; i++)
        {
            if(lotList[i].getLotId() == id)
            {
                occured = true;
                location = i;
            }
        }
        if(!occured)
        {
            cout << "The lot you look does not exist in the system" << endl;
        }
        else
        {
            cout << "ID : " << id <<  ", empty slots: " << lotList[location].numberOfEmptySpaces() << ", parked cars: ";
            parkedCarsFinder(id) ;
        }
        cout << endl;
        columnsPrinter(location);
        cout << endl;

        for(int i = 0; i < lotList[location].getRows(); i++)
        {
            cout << intToLocation(i) << " ";
            for(int j = 0; j < lotList[location].getColumns(); j++)
            {
                if( j < 9)
                    cout << lotList[location].contents[i][j].getCarType() << " ";
                else
                    cout << lotList[location].contents[i][j].getCarType() << "  ";

            }
            cout << endl;
        }
        cout << endl;

    }

    void ParkingSystem:: columnsPrinter(int foundLocation)
    {
        int columns = lotList[foundLocation].getColumns();
        switch (columns)
        {
            case 12:
                cout << "  1 2 3 4 5 6 7 8 9 10 11 12";
                break;
            case 11:
                cout << "  1 2 3 4 5 6 7 8 9 10 11";
                break;
            case 10:
                cout << "  1 2 3 4 5 6 7 8 9 10";
                break;
            case 9:
                cout << "  1 2 3 4 5 6 7 8 9";
                break;
            case 8:
                cout << "  1 2 3 4 5 6 7 8";
                break;
            case 7:
                cout << "  1 2 3 4 5 6 7";
                break;
            case 6:
                cout << "  1 2 3 4 5 6";
                break;
            case 5:
                cout << "  1 2 3 4 5";
                break;
            case 4:
                cout << "  1 2 3 4";
                break;
            case 3:
                cout << "  1 2 3";
                break;
            case 2:
                cout << "  1 2";
                break;
            case 1:
                cout << "  1";
                break;
            default:
                cout << "     invalid index          ";
                break;

        }

    }


    int ParkingSystem::rowFinder(char c)
    {
        string letters = "ABCDEFGHIJKL";
        int index;
        for (int i = 0; i < 12; i++)
        {
            if (c == letters.at(i))
            {
                index = i;
                break;
            }
            else
            {
                    index = 13;
            }
        }
            return index;
    }

    string ParkingSystem::intToLocation(int letterNumber) {
        string letter;
        string letters = "ABCDEFGHIJKL";
        letter = letters[letterNumber];
        return letter;

    }
    bool ParkingSystem::plateNumberChecker(int plateNumber) {
        bool unique = true;
        for (int i = 0; i < lotCount; i++)
        {
            for (int j = 0; j < lotList[i].getRows(); j++)
            {
                for(int k = 0; k < lotList[i].getColumns(); k++)
                {
                    if(lotList[i].contents[j][k].getPlateNumber() == plateNumber)
                    {
                        unique = false;
                    }
                }
            }
        }
        return unique;
    }

    int ParkingSystem::columnFinder(string location)
    {
        if( location.length() == 3)
        {
            return  (location[1]-48) * 10 + location[2]-48;
        }
        else
        {
            return location[1] - 48;
        }

    }
    void ParkingSystem::parkCar(int lotId, string location,string carType, int plateNumber)
    {
        int rowIndex = rowFinder(location.at(0));
        int columnIndex = columnFinder(location);
        bool lotFound = false;
        int lotLocation;
        for(int i = 0; i < lotCount; i++)
        {
            if(lotId == lotList[i].getLotId())
            {
                lotFound = true;
                lotLocation= i;
            }
        }
        if(lotFound && plateNumberChecker(plateNumber))
        {
            if( carType == "a")
            {

                if((lotList[lotLocation].contents[rowIndex][columnIndex-1].getCarType() == 'a' || lotList[lotLocation].contents[rowIndex][columnIndex-1].getCarType() == 'b') )
                {

                    cout << "Cannot park light-duty car with plate number " << plateNumber << " at location " << location << ", already occupied " << endl;
                }
                else
                {
                    cout << "Light-duty car with plate number " << plateNumber << " has been parked at location " << location << ", lot " << lotId << endl;
                    lotList[lotLocation].contents[rowIndex][columnIndex-1] = Cars('a',plateNumber);
                }

            }
            else
            {

                if ( rowIndex > 0 )
                {
                    if(lotList[lotLocation].contents[rowIndex][columnIndex-1].getCarType() == '+' && lotList[lotLocation].contents[rowIndex-1][columnIndex-1].getCarType() == '+' )
                    {
                        lotList[lotLocation].contents[rowIndex][columnIndex-1] = Cars('b',plateNumber);
                        lotList[lotLocation].contents[rowIndex-1][columnIndex-1] = Cars(Cars('b',plateNumber));
                        cout << "Heavy-duty car with plate number " << plateNumber << " has been parked at location " << location << ", lot " << lotId << endl;

                    }
                    else if (lotList[lotLocation].contents[rowIndex][columnIndex-1].getCarType() == '+' && lotList[lotLocation].contents[rowIndex-1][columnIndex-1].getCarType() != '+')
                    {
                        cout << "Cannot park heavy-duty car with plate number " << plateNumber << " at location " << location << ", not enough space" << endl;
                    }
                    else if (lotList[lotLocation].contents[rowIndex][columnIndex-1].getCarType() != '+' && lotList[lotLocation].contents[rowIndex][columnIndex-1].getCarType() != '+' )
                    {
                        cout << "Cannot park heavy-duty car with plate number " << plateNumber << " at location " << location << ", already occupied " << endl;
                    }
                }
                else
                {
                    cout << "Cannot park heavy-duty car with plate number " << plateNumber << " at location " << location << ", not enough space" << endl;
                }
            }

        }
        else
        {
            cout << "Lot " << lotId << " is not in the system" << endl;
        }

    }


    void ParkingSystem::findCar(int plateNumber)
    {
        bool found = false;
        int lotId;
        string locationLetter;
        int locationNumber;
        char carType;
        for( int i = 0; i < lotCount; i++)
        {
            for(int j = 0; j < lotList[i].getRows(); j++)
            {
                for(int k = 0; k < lotList[i].getColumns(); k++)
                {
                    if(lotList[i].contents[j][k].getPlateNumber() == plateNumber)
                    {
                        found = true;
                        lotId = lotList[i].getLotId();
                        locationLetter = intToLocation(j);
                        locationNumber = k+1;
                        carType = lotList[i].contents[j][k].getCarType();


                    }
                }
            }
        }

        if ( found)
        {
            if( carType == 'a')
            {
                cout << "Light-duty car with number plate " << plateNumber << " is at location " << locationLetter << locationNumber << ", lot " << lotId << endl;
            }
            else if ( carType == 'b' )
            {
                cout << "Heavy-duty car with number plate " << plateNumber << " is at location " << locationLetter << locationNumber << ", lot " << lotId << endl;

            }
            else
            {
                cout << "The car with number plate " << plateNumber << " is not in the system " << endl;
            }

        }
        else
        {
            cout << "The car with number plate " << plateNumber << " is not in the system " << endl;
        }

    }


    void ParkingSystem::removeCar(int plateNumber)
    {
        bool carFound = false;
        int rowIndex;
        int columnIndex;
        int lotIndex;
        for(int i = 0; i < lotCount; i++)
        {
            for(int j = 0; j < lotList[i].getRows(); j++)
            {
                for(int k = 0; k < lotList[i].getColumns();k++)
                {
                    if(lotList[i].contents[j][k].getPlateNumber() == plateNumber)
                    {
                        carFound = true;
                        rowIndex = j;
                        columnIndex = k;
                        lotIndex = i;
                    }
                }
            }
        }
        if(carFound)
        {
            if(lotList[lotIndex].contents[rowIndex][columnIndex].getCarType() == 'a')
            {
                lotList[lotIndex].contents[rowIndex][columnIndex] = Cars();
                cout << "Light-duty car with number plate " << plateNumber << " car has been removed from slot " << intToLocation(rowIndex) << columnIndex + 1 << " lot " << lotList[lotIndex].getLotId() << endl;
            }
            else if(lotList[lotIndex].contents[rowIndex][columnIndex].getCarType() == 'b' || lotList[lotIndex].contents[rowIndex-1][columnIndex].getCarType() == 'b')
            {
                if(rowIndex > 0)
                {
                    lotList[lotIndex].contents[rowIndex][columnIndex] = Cars();
                    lotList[lotIndex].contents[rowIndex-1][columnIndex] = Cars();
                    cout << "Heavy-duty car with number plate " << plateNumber << " car has been removed from slot " << intToLocation(rowIndex) << columnIndex + 1 << " lot " << lotList[lotIndex].getLotId() << endl;

                }

            }
            else
            {
                cout << "Invalid car type. Nothing removed" << endl;
            }
        }
        else
        {
            cout << "The car with number plate " << plateNumber << " is not in the system" << endl;
        }

    }


