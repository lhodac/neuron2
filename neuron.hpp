#ifndef NEURON_H
#define NEURON_H

#include <iostream>
#include <vector>
#include <array>
#include <fstream>
#include <cmath>
#include <cassert>
#include <random>
#include "Constants.hpp"





class Neuron {
	
private:
		
	double membranePotential_;
	int nbSpikes_;
	bool refractory_;
	double refractoryTime_;
	std::vector<double> spikeTimes_;
	std::array<double,BUFFER_SIZE> buffer_;
	std:: vector<Neuron*> postNeurons_;
	

public:
	double getMembranePotential() const;
	int getNbSpikes() const;
	std::vector<double> getTimeSpikes() const;
	std::vector<Neuron*> getPostNeurons() const;
	bool isRefractory() const;


	
	void setMembranePotential(double potential);
	void setRefractory(bool r);


	bool update(int currentStep,int nbSteps, double I_ext);
	void addTimeSpike(double time);
	void addPostNeuron(std:: vector<Neuron*> postNeurons);
	double solveDifferentialEquation(double I_ext) const;
	double updateBuffer();
	void receive(int currentStep);

	
	Neuron();
	~Neuron();
	
	
	};




#endif
