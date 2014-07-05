//#ifndef IZHIKEVICNEURON_H
//#define IZHIKEVICNEURON_H

#include <yarp/os/all.h>
#include <yarp/sig/vector.h>

class receptiveField
{
    public:
        receptiveField();
        virtual ~receptiveField();
        
        void setWeights(std::string, vector, int);
        bool setFieldSize(int);

        yarp::os::vector getWeights();
	    int getFieldSize();
	
    protected:
        double inhibitor;

    private:
        int size;
	    yarp::os::vector weightVector;
};

#endif // IZHIKEVICNEURON_H


