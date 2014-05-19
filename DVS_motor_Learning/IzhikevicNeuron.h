#ifndef IZHIKEVICNEURON_H
#define IZHIKEVICNEURON_H


class IzhikevicNeuron
{
    public:
        IzhikevicNeuron();
        virtual ~IzhikevicNeuron();
        double getPotential();
        bool updatePotential();
        double getLastSpikeTime();
        int getNumSpikes();
        bool setParameters(double *);
        bool updatePotential(double, unsigned long int);

    protected:
        double inhibitor;

    private:
        double potential;
        long unsigned int lastSpikeTime;
        double a, b, c, d, k;
        double Vrest;
        double Vthreshold;
        double tau;
        double C;
        int numSpikes;

};

#endif // IZHIKEVICNEURON_H
