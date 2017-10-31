#include "neuron.hpp"
#include "Constants.hpp"


using namespace std;

//GETTERS
double Neuron:: getMembranePotential() const
{
	return membranePotential_;
}
int Neuron:: getNbSpikes() const
{
	return nbSpikes_;
}
vector<double> Neuron:: getTimeSpikes() const
{
	return spikeTimes_;
}
vector<Neuron*> Neuron:: getPostNeurons() const
{
	return postNeurons_;
}

bool Neuron:: isRefractory() const
{
	return refractory_;
}


//SETTERS
void Neuron:: setMembranePotential(double potential)
{
	membranePotential_= potential;
}

void Neuron:: setRefractory(bool r)
{
	refractory_= r;
}

//To add one time at the spikeTimes table
void Neuron::addTimeSpike(double time)
{
	spikeTimes_.push_back(time);
}

void Neuron::addPostNeuron(vector<Neuron*> postNeurons)
{
	for (size_t i(0); i<postNeurons.size(); ++i)
	postNeurons_[i]=postNeurons[i];
}

//To update the simulation at each steps, it returns a boolean because we need to know if there is a spike or not
bool Neuron::update(int currentStep, int nbSteps, double I_ext)
{
	//cerr << "Update Neuron" << endl;
	bool isSpiking(false);
	
	if(membranePotential_ >= TH_POTENTIAL and !refractory_) {
	
		isSpiking = true;
		addTimeSpike(currentStep*H);
		++nbSpikes_;
		cerr << "Nombre de spikes: " << getNbSpikes() << endl;
		setRefractory(true);
		setMembranePotential(0.0);
		cerr << getMembranePotential() << endl << "SPIKE JUST HAPPENED" <<endl;
		}
		
	if(refractory_){
		setMembranePotential(0.0);
		cerr << getMembranePotential() << endl << "REFRACTORY" <<endl;
		--refractoryTime_;
			
			if (refractoryTime_ <= 0.0) { 
				refractoryTime_= REFRACTORY_TIME;
				setRefractory(false);
				}
		}

	if(membranePotential_<= TH_POTENTIAL and !refractory_) { 
		setMembranePotential(solveDifferentialEquation(I_ext)+ updateBuffer()); 
		} 
	return isSpiking;


}

//To solve the equation of the potential
double Neuron:: solveDifferentialEquation(double I_ext) const
{
	return C1 * membranePotential_ + I_ext * R * C2;
}


double Neuron:: updateBuffer()
{
	for (size_t i (0); i < buffer_.size() ; ++i){
		buffer_[i] = buffer_[i+1];
		}
	buffer_[buffer_.size()-1] = 0.0;


	//cerr << "Buffer: 	" << buffer_[0] << endl;
	return buffer_[0];
}

void Neuron:: receive(int currentStep)
{
	//cerr<<"Spike received at time " << (currentStep * H/10) << endl;
	buffer_[DELAY*10] += J;
}

//Constructor: we initialise the values at 0.0 and false
Neuron:: Neuron()
: membranePotential_(0.0), nbSpikes_(0), refractory_(false), refractoryTime_(REFRACTORY_TIME)
{
	for(auto& b : buffer_){
		b= 0.0;
		}
	spikeTimes_.clear();
	
	for (auto& pN : postNeurons_){
		pN= nullptr;
	}
}

//Destructor: we clear the times vector
Neuron:: ~Neuron()
{
	
}




