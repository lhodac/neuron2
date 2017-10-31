#include "Network.hpp"
#include "neuron.hpp"
#include "gtest/include/gtest/gtest.h"
#include <iostream>
#include <cmath>
using namespace std;


TEST (NeuronTest, membranePotential_) 
{
	Neuron neuron1;
		neuron1.update(0, 1, 1.0);
	EXPECT_EQ(20.0*(1.0-std::exp(-0.1/20.0)),neuron1.getMembranePotential());
}

TEST (NeuronTest, nbSpikes_)
{
	Neuron neuron2;
	Neuron neuron1;
	Network network; 													//Création Network car incrémentation se fait dans network
	
	network.addNeuron(&neuron1);
	network.addNeuron(&neuron2);
	network.update(0,924,1.01);
	EXPECT_EQ(0,neuron1.getNbSpikes());
	network.update(924,925,1.01);
	EXPECT_EQ(1,neuron1.getNbSpikes());
	EXPECT_EQ(0, neuron1.getMembranePotential());
}

TEST (NeuronTest, spikeTimes_)
{
	Neuron neuron3;
	Neuron neuron4;
	Network network;
	
	network.addNeuron(&neuron3);
	network.addNeuron(&neuron4);
	
	network.update(0,1000, 1.01);

	
	int spikeTime1((neuron3.getTimeSpikes())[0]);
	
	
	EXPECT_EQ(924,spikeTime1);
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	
	return RUN_ALL_TESTS();
}
