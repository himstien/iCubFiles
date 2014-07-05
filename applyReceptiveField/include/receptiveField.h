#ifndef RECEPTIVEFIELD_H
#define RECEPTIVEFIELD_H

#include <yarp/os/all.h>
#include <yarp/sig/all.h>

class receptiveField
{
    public:
        receptiveField();
        virtual ~receptiveField();
        
        void setWeights(std::string, yarp::sig::Vector, int);
        bool setFieldSize(int);

        yarp::sig::Vector getWeights();
	int getFieldSize();
	
    protected:
        double inhibitor;

    private:
        int size;
	    yarp::sig::Vector weightVector;
};

#endif // RECEPTIVEFIELD_H


