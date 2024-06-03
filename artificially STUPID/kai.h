#pragma once
#include <random>
#include <vector>

const int maxLayers = 4;
const int maxNeuronPerLayer = 10;
const int maxConnections = maxNeuronPerLayer * maxNeuronPerLayer;

auto toTableFromNumber(int numberToConv) {
	int x = 0;
	int y = 0;
	struct data {
		int a, b;
	};
	switch (numberToConv) {
	case(1):
		break;
	case(2):
		x = 1;
		y = 0;
		break;
	case(3):
		x = 2;
		y = 0;
		break;
	case(4):
		x = 0;
		y = 1;
		break;
	case(5):
		x = 1;
		y = 1;
		break;
	case(6):
		x = 2;
		y = 1;
		break;
	case(7):
		x = 0;
		y = 2;
		break;
	case(8):
		x = 1;
		y = 2;
		break;
	case(9):
		x = 2;
		y = 2;
		break;
	default:
		return data {};

	}

	return data{x,y};
}
float mathMax(float a, float b) {
	if (a > b) {
		return a;
	}
	return b;
}
float randomFloat(float lower, float upper) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> distribution(lower, upper);
	return distribution(gen);
}

class neuron {
public:
	float activation = 0.0;
	float bias = 0.0;
	float connections[maxNeuronPerLayer]; // connectuions but backwards
};

class brain {
private:

	class layer // here so main 
	{
	private:
	public:
		int layerId = 1;
		vector<neuron> neuronsInLayer;
		void buildLayer(int neuronCount)
		{
			neuronsInLayer.resize(neuronCount);
			if (layerId != 0) {
				for (int i = 0; i < neuronsInLayer.size(); ++i)
				{
					cout << i << endl;
					neuronsInLayer[i].activation = randomFloat(0, 0.1);
					neuronsInLayer[i].bias = randomFloat(0, 0.1);
					//neuronsInLayer[i].connections.resize(maxNeuronPerLayer);
					for (int index = 0; index < maxNeuronPerLayer; ++index) {
						neuronsInLayer[i].connections[index] = randomFloat(-1.0, 1.0);
					}
				}
			}
			else {
				for (int i = 0; i < neuronsInLayer.size(); ++i)
				{
					cout << i << endl;
					neuronsInLayer[i].activation = 0.0;
						neuronsInLayer[i].bias = 0.0;
					//neuronsInLayer[i].connections.resize(maxNeuronPerLayer);

				}
			}

		}
	};



public: // public!!!!!!!!!!!!!!!!!!!! yippe!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	vector<layer> layersInBrain;

	int buildBrain() 
	{
		layersInBrain.resize(4);
		layer& inputLayer = layersInBrain[0];
		inputLayer.layerId = 0;
		inputLayer.buildLayer(9);

		for (int i = 0; i < 2; ++i) {
			layersInBrain[i+1].layerId = i+1;
			layersInBrain[i+1].buildLayer(maxNeuronPerLayer);
		}

		layer& outputLayer = layersInBrain[3];
		outputLayer.layerId = 3;
		outputLayer.buildLayer(9);

		return 0;
	}

	int initInputNeurons(char gameTable[3][3]) {
		if (layersInBrain[0].neuronsInLayer.size() < 1) {
			cout << "empty";
		}
		for (int i = 0; i < 9; ++i) {
			float activate = 0.0;
			char cellChar = ' ';
			switch (i) {
			case(0):
				cellChar = gameTable[0][0];
				break;
			case(1):
				cellChar = gameTable[1][0];
				break;
			case(2):
				cellChar = gameTable[2][0];
				break;
			case(3):
				cellChar = gameTable[0][1];
				break;
			case(4):
				cellChar = gameTable[1][1];
				break;
			case(5):
				cellChar = gameTable[2][1];
				break;
			case(6):
				cellChar = gameTable[0][2];
				break;
			case(7):
				cellChar = gameTable[1][2];
				break;
			case(8):
				cellChar = gameTable[2][2];
				break;
			}

			switch (cellChar) {
			case(' '):
				activate = 100.0; // if cell is clear
				break;
			case('X'):
				activate = 0.0; // if opponent owns cell
				break;
			case('O'):
				activate = 0.0; // if you own cell
				break;
			}
			layersInBrain[0].neuronsInLayer[i].activation = activate;
		}
		return 0;
	}
	float forwardPass(char gameTable[3][3])
	{	
		float maxConfidenceValue = 0.0;
		int maxConfidenceSlot = 0;
		for (int i = 0; i < layersInBrain.size(); ++i) {
			if (i == 0) {continue;}
			for (int cNeuron = 0; cNeuron < layersInBrain[i].neuronsInLayer.size();++cNeuron) {
				neuron& currentNeuron = layersInBrain[i].neuronsInLayer[cNeuron];
				for (int n = 0; n < layersInBrain[i - 1].neuronsInLayer.size(); ++n) {
					neuron& currentPreviousNeuron = layersInBrain[i - 1].neuronsInLayer[n];
					currentNeuron.activation += currentPreviousNeuron.activation * currentNeuron.connections[n] + currentNeuron.bias;
				}
				
				if (i == 3) {
					cout << endl << maxConfidenceValue << "::" << cNeuron;
					auto result = toTableFromNumber(cNeuron);
					if (maxConfidenceValue < currentNeuron.activation && gameTable[result.a][result.b] == ' ') {
						maxConfidenceSlot = cNeuron;
						maxConfidenceValue = currentNeuron.activation;
					}
				}
			}
		}
		return maxConfidenceSlot;
	}

};
