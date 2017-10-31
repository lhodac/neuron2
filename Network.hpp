#ifndef NETWORK_H
#define NETWORK_H
#include "neuron.hpp"

constexpr unsigned int nbNeurons(20);
typedef std::array<std::array<bool, nbNeurons>, nbNeurons> Matrice;

class Network{
	
private:

	std::vector<Neuron*> neurons_;
	bool spike_;
	Matrice neuronsRelations_;

public:
	Neuron getNeuron(int n);
	void addNeuron(Neuron* neuron);
	void reset();
	void update(int currentStep, int nbSteps, double I_ext);
	Network();
	~Network();
	
	
	
	
	};
#endif

