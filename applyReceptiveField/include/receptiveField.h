#ifndef RECEPTIVEFIELD_H
#define RECEPTIVEFIELD_H
 
#include <yarp/os/all.h>
#include <yarp/sig/all.h>
 
class receptiveField
{
    public:
        receptiveField();
        virtual ~receptiveField();
         
        bool setFieldSize(int, int);
        bool setWeightsFile(std::string);
         
         
        int getFieldSizeX();
        int getFieldSizeY();
         
        double getWeightAt(int, int);
        void setWeights();
         
        bool normalizeWeights();
        bool multiplyWeights();
        bool scaleUpWeights();
         
        bool isValid();
     
    protected:
        double inhibitor;
 
 
    private:
        int fieldSizeX;
        int fieldSizeY;
        yarp::sig::Vector weightVector;
        bool valid;
};
 
#endif // RECEPTIVEFIELD_H

