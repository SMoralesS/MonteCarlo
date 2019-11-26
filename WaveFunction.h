#include<iostream>
#include<vector>
#include<iomanip>
#include<stdlib.h>
#include<string>
#include<ctime>
#include<cmath>
#include<fstream>

using namespace std;

const double PI = 2.0*asin(1.0);

class particle{
	public:
		particle(int=100,int=100);
		vector<int> getProbabilities();	
		void restartPath(int,int);
		void setEpsilon(double eps);
		void evolution(int = 1000);
		void evolutionBouncer(int=1000);
		void printProbabilities();
		void fileProbabilities(string);
		void printPath();
		void filePath(string);
		vector<double> getPath();
		void setg(double grav);
	private:
		double energy();
		double energyBouncer();
		void trialConfig();
		void trialConfigBouncer();
		double epsilon;
		int timeSteps;
		int spaceSteps;
		vector<double> path;
		vector<int> prob;
		double g;
};
