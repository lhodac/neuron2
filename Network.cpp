#include "Network.hpp"
#include <random>

using namespace std;

Neuron Network::getNeuron(int n)
{
	return *(neurons_[n]);
}

/*void Network::reset()													//Permet de reset a tout moment le tableau de pointeurs de Neuron en libérant la mémoire
{
	if (!neurons_.empty()){
			for(auto neuron: neurons_){
				delete neuron;
				neuron = nullptr;
			}
	}
	neurons_.clear();
}*/

void Network::addNeuron(Neuron* neuron)
{
		neurons_.push_back(neuron);
}
void Network::update(int currentStep,int nbSteps, double I_ext)
{	
	while(currentStep < nbSteps)
	{	
		if (neurons_[0] != nullptr and !neurons_.empty()){

		bool spike((neurons_[0])->update(currentStep, nbSteps, I_ext));
		
		if(neurons_[1] != nullptr){

			neurons_[1]-> update(currentStep,nbSteps, 0);

			if(spike) {
				
				neurons_[1]-> receive(currentStep);
				}
			}
		}

		++currentStep;		

		cout << currentStep * H << endl << " 1er Neuron: "<< getNeuron(0).getMembranePotential() << "			";
		cout << " 2ème Neuron: "<< getNeuron(1).getMembranePotential() << endl;
	}
}


Network::Network()
{
}
Network::~Network()
{
}
