/* 
 * Author: Himanshu Akolkar
*/


#include <applyReceptiveFieldThread.h>


applyReceptiveField::applyReceptiveField()
{
}


void applyReceptiveField::readFile2Weight()
{

}


void applyReceptiveField::init()
{
}

void applyReceptiveField::updatePotential()
{
}

void applyReceptiveField::(double a11, double a12, double a22, double eigValue, double * eigVector){
    double tmp;
    if (a12 != 0){
        tmp = 1 / sqrt(a12*a12 + (eigValue - a22)*(eigValue - a22) );
        *eigVector = tmp * (eigValue - a22);
        *(eigVector+1) = tmp * a12;
    }
    else{
        if (a11 == eigValue){
            *eigVector = 1;
            *(eigVector + 1) = 0;
        }
        else {
            *eigVector = 0;
            *(eigVector + 1) = 1;
        }
    }
}



void LKLocalFlow::setGuaWeights(double stdDev){
    double * tmpPtr;

    if (GuaWeight == NULL){
        GuaWeight = new double [windowLength*windowLength];
    }


//    for (int i = 0; i < windowLength*windowLength; ++i) {
//        *(GuaWeight + i) = 1;
//    }
//
//    return;


    double tmp, tmp2;
    double* rowTmp = new double [windowLength];
    for (int idx = 0; idx < windowLength; ++idx) {
        *(rowTmp + idx) = (idx - neighborRadius)*(idx - neighborRadius);
    }

    tmpPtr = GuaWeight;
    for (int i = 0; i < windowLength; ++i) {
        tmp = *(rowTmp + i);
        for (int j = 0; j < windowLength; ++j) {
             *tmpPtr = *(rowTmp + j) + tmp;
             tmpPtr++;
        }
    }

    tmp = 2 * stdDev * stdDev;
    tmp2 = tmp;
    tmp = - 1 / tmp;
    tmp2 = 1 / ( tmp2 * 3.14);
    tmpPtr = GuaWeight;
    for (int i = 0; i < windowLength; ++i) {
        for (int j = 0; j < windowLength; ++j) {
            *tmpPtr = tmp2 * exp(*tmpPtr * tmp);
            tmpPtr++;
        }
    }
	delete [] rowTmp;
}

LKLocalFlow::~LKLocalFlow(){
    if (GuaWeight != NULL){
        delete [] GuaWeight;
    }

    cout << "LK local flow is closed finely" << endl;
}