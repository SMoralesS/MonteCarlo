#include "WaveFunction.h"

//Oscilador armonico

particle::particle(int N,int M){
	timeSteps = N;
	spaceSteps = M;
	path.assign(N, 0);
	prob.assign(M, 0);
	epsilon=0.5;
	g=2;
}

void particle::restartPath(int N,int M){
	timeSteps = N;
	spaceSteps = M;
	path.assign(N, 0);
	prob.assign(M, 0);
	//epsilon=1./timeSteps;
}

void particle::setEpsilon(double eps){
	epsilon=eps;
}

double particle::energy(){
	double E=0;
	for(int i=1;i<timeSteps;i++) E+=0.5*pow((path[i]-path[i-1])/epsilon,2)+0.5*pow((path[i]+path[i-1])/2,2);
	return E;
}

void particle::trialConfig(){
	int randTime,b,m,elem;
	double newE,oldE,deltaE,change,R;
	randTime = 1+rand()%(timeSteps-1);
	change = 2*(((double)rand()/(RAND_MAX))-0.5);
	oldE = energy();
	path[randTime] += change;
	newE = energy();
	deltaE = newE - oldE;
	//Metropolis
	R=exp(-epsilon*deltaE);
	double r = ((double)rand()/RAND_MAX);
	if(deltaE>0 and R<=r) path[randTime] -= change;
	b=spaceSteps/2;
	m = b/3;
	elem = m*path[randTime]+b;
	if(elem<0) elem = 0;
	else if(elem>(spaceSteps-1)) elem = spaceSteps-1;
	prob[elem] += 1;
}

void particle::evolution(int iter){
	for(int i=0;i<iter;i++) trialConfig();
}

vector<int> particle::getProbabilities(){
	return prob;
}

void particle::printProbabilities(){
	for(int i=0;i<prob.size();i++) cout << prob[i] << " ";
	cout << endl;
}

void particle::fileProbabilities(string nombre_archivo){
	fstream probFile;
	probFile.open(nombre_archivo.c_str(),ios::out);
	for(int i=0;i<prob.size();i++) probFile << prob[i] << endl;
}

vector<double> particle::getPath(){
	return path;
}

void particle::printPath(){
	for(int i=0;i<path.size();i++) cout << path[i] << " ";
	cout << endl;
}

void particle::filePath(string nombre_archivo){
	fstream pathFile;
	pathFile.open(nombre_archivo.c_str(),ios::out);
	for(int i=0;i<path.size();i++) pathFile << path[i] << endl;
}

//Caida libre con rebote - QMbouncer

void particle::setg(double grav){
	g=grav;
}

double particle::energyBouncer(){
	double E=0;
	for(int i=1;i<timeSteps;i++) E+=0.5*pow((path[i]-path[i-1])/epsilon,2)+g*(path[i]+path[i-1])/2.;
	return E;
}

void particle::trialConfigBouncer(){
	int randTime,elem;
	double newE,oldE,deltaE,change,R,m;
	randTime = 1+rand()%(timeSteps-1);
	change = 2*(((double)rand()/(RAND_MAX))-0.5);
	if((path[randTime] + change)>0){
		oldE = energyBouncer();
		path[randTime] += change;
		newE = energyBouncer();
		deltaE = newE - oldE;
		//Metropolis
		R=exp(-epsilon*deltaE);
		double r = ((double)rand()/RAND_MAX);
		if(deltaE>0 and R<=r) path[randTime] -= change;;
		m = 12.5;
		elem = m*path[randTime];
		if(elem<=0) elem = 0;
		else if(elem>(spaceSteps-1)) elem = spaceSteps-1;
		if(elem != 0 and elem !=(spaceSteps-1)) prob[elem] += 1;
	}
}

void particle::evolutionBouncer(int iter){
	for(int i=0;i<iter;i++) trialConfigBouncer();
}


