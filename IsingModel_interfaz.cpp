#include "IsingModel.h"

//Metodos de la clase spinConfiguration
spinConfiguration::spinConfiguration(int n,int opt){
	setSpinNum(n);
	setSpinConfiguration(opt);
	T=1;
	J=1;
}

spinConfiguration::spinConfiguration(vector<int> states){
	int n=states.size();	
	setSpinConfiguration(states);
	setSpinNum(n);
	T=1;
	J=1;
}

void spinConfiguration::setJ(int JJ){
	J=JJ;
}

void spinConfiguration::setT(double temperature){
	T=temperature;
}

void spinConfiguration::setSpinConfiguration(int opt){
	spins.clear();	
	spins.resize(spinNum);
	if(opt==1){
		for(int i=0;i<spinNum;i++) spins[i]=1;
	}
	else if(opt==-1){
		for(int i=0;i<spinNum;i++) spins[i]=pow(-1,i);
	}
	else if(opt==0){
		for(int i=0;i<spinNum;i++) spins[i]=rand()%(2)*2-1;
	}
}

void spinConfiguration::setSpinConfiguration(vector<int> states){
	spins = states;	
}

vector<int> spinConfiguration::getSpinConfiguration(){
	return spins;
}

void spinConfiguration::setSpinNum(int n){
	spinNum = n;
}

int spinConfiguration::getSpinNum(){
	return spinNum;
}

void spinConfiguration::printSpins(){
	int n = getSpinNum();
	for(int i=0;i<n;i++){
		if(spins[i]==1) cout << "x";
		else cout << "o";
	}
	cout << endl;
}

void spinConfiguration::fileSpins(string nombre_archivo){
	fstream spinsFile;
	spinsFile.open(nombre_archivo.c_str(),ios::app);
	spinsFile << endl;
	int n = getSpinNum();
	for(int i=0;i<n;i++){
		spinsFile << spins[i] << "\t";
	}
}

void spinConfiguration::fileSpinsEvolution(string nombre_archivo){
	ofstream spinsFile;
	spinsFile.open(nombre_archivo.c_str(),ofstream::out | ofstream::trunc);
	spinsFile.close();
	int n = getSpinNum();
	for(int i=0;i<1000;i++){
		checkTrial();
		fileSpins(nombre_archivo);
	}
}


vector<int> spinConfiguration::trialConfig(int i){
	vector<int> trialSpins(spinNum);
	trialSpins =spins;
	trialSpins[i]=trialSpins[i]*(-1);
	return trialSpins;
}

double spinConfiguration::energy(){
	double E=0;
	for(int i=0;i<spinNum;i++){
		if(i==(spinNum-1)) E-=J*spins[spinNum-1]*spins[0];
		else E-=J*spins[i]*spins[i+1];
	}
	return E;
}

void spinConfiguration::checkTrial(){
	int random,Eantes,Edespues;
	random = rand()%spinNum;
	double R,deltaE=0;
	if(random==(spinNum-1)) deltaE += J*2*spins[random]*(spins[0]+spins[random-1]);
	else if(random==0) deltaE += J*2*spins[random]*(spins[random+1]+spins[spinNum-1]);
	else deltaE += J*2*spins[random]*(spins[random+1]+spins[random-1]);
	if(deltaE<=0) {
		spins = trialConfig(random);
	}	
	else{
		R=exp(-deltaE/(Kb*T));
		double r = ((double)rand()/RAND_MAX);
		if(r<=R) spins = trialConfig(random);
	}
}

void spinConfiguration::equilibrate(){
	int aux = 0;
	for(int i=0;i<10*spinNum;i++){
		checkTrial();
		//printSpins();
	}
}

double spinConfiguration::getInternalEnergy(){
	double U,U2;
	for(int i=0;i<100000;i++){
		U+=energy();
		U2+=pow(energy(),2);
		checkTrial();
	}
	U=U/100000.;
	U2=U2/100000.;
	internalEnergy = U;
	fluctuations = U2;
	return U;
}


double spinConfiguration::getSpecificHeat(){
	double C;
	C = (fluctuations-pow(internalEnergy,2))/(pow(spinNum,2)*Kb*pow(T,2));
	specificHeat = C;
	return C;
}


double spinConfiguration::getMagnetization(){
	double M=0,Mlocal=0;
	for(int i=0;i<100000;i++){
		checkTrial();
		Mlocal=0;
		for(int j=0;j<spinNum;j++) Mlocal += spins[j];
		M += Mlocal;
	}
	magnetization = M/100000.;
	return M;
}


void spinConfiguration::plotData(){
	energies.clear();
	specificHeats.clear();
	magnetizations.clear();
	for(T=0.2;T<=6;T+=0.05){
		setSpinConfiguration(1);
		equilibrate();
		getInternalEnergy();
		getSpecificHeat();
		getMagnetization();
		energies.push_back(internalEnergy);
		specificHeats.push_back(specificHeat);
		magnetizations.push_back(magnetization);
	}
}


void spinConfiguration::filePlotData(string nombre_archivo){
	plotData();
	fstream dataFile;
	dataFile.open(nombre_archivo.c_str(),ios::out);
	for(int i=0;i<magnetizations.size();i++){
		dataFile << "\t" << energies[i] << "\t" << magnetizations[i] <<"\t"<< specificHeats[i] << endl;
	}
}

//Metodos de la clase spinConfiguration2D

void spinConfiguration2D::setSpinConfiguration2D(int opt){
	spinNum = spinConfiguration::getSpinNum();
	spins2D.resize(spinNum);
	for (int i = 0; i < spinNum; ++i){
    		spins2D[i].resize(spinNum);
		spinConfiguration::setSpinConfiguration(opt);
		spins2D[i]=spinConfiguration::getSpinConfiguration();
	}
}

void spinConfiguration2D::setSpinConfiguration2D(vector<vector<int>> states){
	spinNum = states.size();
	spins2D = states;
}

void spinConfiguration2D::setJ(int JJ){
	J=JJ;
}

double spinConfiguration2D::setT(double temperature){
	T=temperature;
}

vector<vector<int>> spinConfiguration2D::getSpinConfiguration2D(){
	return spins2D;
}

void spinConfiguration2D::printSpinConfiguration2D(){
	for(int i=0;i<spinNum;i++){
		for(int j=0;j<spinNum;j++) {
			if(spins2D[i][j]==1) cout << "x";
			else cout << "o";
		}
		cout << endl;
	}
	cout << endl;
}


void spinConfiguration2D::fileSpinConfiguration2D(string nombre_archivo){
	fstream ConfigFile;
	ConfigFile.open(nombre_archivo.c_str(),ios::out);
	for(int i=0;i<spinNum;i++){
		for(int j=0;j<spinNum;j++) {
			ConfigFile << spins2D[i][j] << "\t";
		}
		ConfigFile << endl;
	}
}

vector<vector<int>> spinConfiguration2D::trialConfig2D(int i,int j){
	vector<vector<int>> trialSpins;
	trialSpins =spins2D;
	trialSpins[i][j]=trialSpins[i][j]*(-1);
	return trialSpins;
}

double spinConfiguration2D::energy(){
	double E=0;
	for(int i=0;i<spinNum;i++){
		for(int k=0;k<spinNum;k++){
			//columns
			if(i==(spinNum-1)) E-=J*spins2D[spinNum-1][k]*spins2D[0][k];
			else E-=J*spins2D[i][k]*spins2D[i+1][k];
			//rows
			if(k==(spinNum-1)) E-=J*spins2D[i][spinNum-1]*spins2D[i][0];
			else E-=J*spins2D[i][k]*spins2D[i][k+1];
		}
	}
	return E;
}

int spinConfiguration2D::getMagnetization(){
	int M=0;
	for(int i=0;i<spinNum;i++){
		for(int j=0;j<spinNum;j++) M += spins2D[i][j];
	}
	magnetization = M;
	return M;
}


void spinConfiguration2D::checkTrial(){
	int i,j;
	i = rand()%spinNum;
	j = rand()%spinNum;
	double R,deltaE=0;
	//vecinos a los arriba-abajo
	if(i==(spinNum-1)) deltaE += 2*J*spins2D[i][j]*(spins2D[0][j]+spins2D[i-1][j]);
	else if(i==0) deltaE += 2*J*spins2D[i][j]*(spins2D[i+1][j]+spins2D[spinNum-1][j]);
	else deltaE += 2*J*spins2D[i][j]*(spins2D[i+1][j]+spins2D[i-1][j]);
	//vecinos a los lados
	if(j==(spinNum-1)) deltaE += 2*J*spins2D[i][j]*(spins2D[i][0]+spins2D[i][j-1]);
	else if(j==0) deltaE += 2*J*spins2D[i][j]*(spins2D[i][j+1]+spins2D[i][spinNum-1]);
	else deltaE += 2*J*spins2D[i][j]*(spins2D[i][j+1]+spins2D[i][j-1]);

	if(deltaE<=0) {
		spins2D = trialConfig2D(i,j);
	}	
	else{
		R=exp(-deltaE/(Kb*T));
		double r = ((double)rand()/RAND_MAX);
		if(r<=R) spins2D = trialConfig2D(i,j);
	}
}

void spinConfiguration2D::equilibrate(int iter){
	int aux = 0;
	for(int i=0;i<iter;i++){
		checkTrial();
	}
}

double spinConfiguration2D::getInternalEnergy(){
	double U,U2;
	for(int i=0;i<100000;i++){
		U+=energy();
		U2+=pow(energy(),2);
		checkTrial();
	}
	U=U/100000.;
	U2=U2/100000.;
	internalEnergy = U;
	fluctuations = U2;
	return U;
}

double spinConfiguration2D::getSpecificHeat(){
	double C;
	C = (fluctuations-pow(internalEnergy,2))/(pow(spinNum,2)*Kb*pow(T,2));
	specificHeat = C;
	return C;
}

void spinConfiguration2D::plotData(){
	energies.clear();
	specificHeats.clear();
	magnetizations.clear();
	for(T=0.2;T<=6;T+=0.05){
		//setSpinConfiguration2D(1);
		//equilibrate(10*pow(spinNum,2));
		equilibrate(100000);
		getInternalEnergy();
		getSpecificHeat();
		getMagnetization();
		energies.push_back(internalEnergy);
		specificHeats.push_back(specificHeat);
		magnetizations.push_back(magnetization);
	}
}

void spinConfiguration2D::filePlotData(string nombre_archivo){
	plotData();
	fstream data2DFile;
	data2DFile.open(nombre_archivo.c_str(),ios::out);
	for(int i=0;i<magnetizations.size();i++){
		data2DFile << "\t" << energies[i] << "\t" << magnetizations[i] <<"\t"<< specificHeats[i] << endl;
	}
}

//Metodos de la clase spinConfiguration3D

void spinConfiguration3D::setSpinConfiguration3D(int opt){
	spinNum = spinConfiguration::getSpinNum();
	spins3D.resize(spinNum);
	for (int i = 0; i < spinNum; ++i){
		spins3D[i]=spinConfiguration2D::getSpinConfiguration2D();
	}
}

void spinConfiguration3D::setSpinConfiguration3D(vector<vector<vector<int>>> states){
	spinNum = states.size();
	spins3D = states;
}

void spinConfiguration3D::setJ(int JJ){
	J=JJ;
}

double spinConfiguration3D::setT(double temperature){
	T=temperature;
}

vector<vector<vector<int>>> spinConfiguration3D::getSpinConfiguration3D(){
	return spins3D;
}

vector<vector<vector<int>>> spinConfiguration3D::trialConfig3D(int i,int j,int k){
	vector<vector<vector<int>>> trialSpins;
	trialSpins =spins3D;
	trialSpins[i][j][k]=trialSpins[i][j][k]*(-1);
	return trialSpins;
}

double spinConfiguration3D::energy(){
	double E=0;
	for(int i=0;i<spinNum;i++){
		for(int j=0;j<spinNum;j++){
			for(int k=0;k<spinNum;k++){
				//is
				if(i==(spinNum-1)) E-=J*spins3D[spinNum-1][j][k]*spins3D[0][j][k];
				else E-=J*spins3D[i][j][k]*spins3D[i+1][j][k];
				//js
				if(j==(spinNum-1)) E-=J*spins3D[i][spinNum-1][k]*spins3D[i][0][k];
				else E-=J*spins3D[i][j][k]*spins3D[i][j+1][k];
				//ks
				if(k==(spinNum-1)) E-=J*spins3D[i][j][spinNum-1]*spins3D[i][j][0];
				else E-=J*spins3D[i][j][k]*spins3D[i][j][k+1];
			}
		}
	}
	return E;
}

void spinConfiguration3D::checkTrial(){
	int i,j,k;
	i = rand()%spinNum;
	j = rand()%spinNum;
	k = rand()%spinNum;
	double R,deltaE=0;
	//vecinos a los arriba-abajo
	if(i==(spinNum-1)) deltaE += 2*J*spins3D[i][j][k]*(spins3D[0][j][k]+spins3D[i-1][j][k]);
	else if(i==0) deltaE += 2*J*spins3D[i][j][k]*(spins3D[i+1][j][k]+spins3D[spinNum-1][j][k]);
	else deltaE += 2*J*spins3D[i][j][k]*(spins3D[i+1][j][k]+spins3D[i-1][j][k]);
	//vecinos a los lados
	if(j==(spinNum-1)) deltaE += 2*J*spins3D[i][j][k]*(spins3D[i][0][k]+spins3D[i][j-1][k]);
	else if(j==0) deltaE += 2*J*spins3D[i][j][k]*(spins3D[i][j+1][k]+spins3D[i][spinNum-1][k]);
	else deltaE += 2*J*spins3D[i][j][k]*(spins3D[i][j+1][k]+spins3D[i][j-1][k]);
	//vecinos atras-adelante
	if(k==(spinNum-1)) deltaE += 2*J*spins3D[i][j][k]*(spins3D[i][j][0]+spins3D[i][j][k-1]);
	else if(i==0) deltaE += 2*J*spins3D[i][j][k]*(spins3D[i][j][k+1]+spins3D[i][j][spinNum-1]);
	else deltaE += 2*J*spins3D[i][j][k]*(spins3D[i][j][k+1]+spins3D[i][j][k-1]);

	if(deltaE<=0) {
		spins3D = trialConfig3D(i,j,k);
	}	
	else{
		R=exp(-deltaE/(Kb*T));
		double r = ((double)rand()/RAND_MAX);
		if(r<=R) spins3D = trialConfig3D(i,j,k);
	}
}

void spinConfiguration3D::equilibrate(int iter){
	int aux = 0;
	for(int i=0;i<iter;i++){
		checkTrial();
	}
}

int spinConfiguration3D::getMagnetization(){
	int M=0;
	for(int i=0;i<spinNum;i++){
		for(int j=0;j<spinNum;j++){
			for(int k=0;k<spinNum;k++) M += spins3D[i][j][k];
		} 
	}
	magnetization = M;
	return M;
}

double spinConfiguration3D::getInternalEnergy(){
	double U,U2;
	for(int i=0;i<10000;i++){
		U+=energy();
		U2+=pow(energy(),2);
		checkTrial();
	}
	U=U/10000.;
	U2=U2/10000.;
	internalEnergy = U;
	fluctuations = U2;
	return U;
}

double spinConfiguration3D::getSpecificHeat(){
	double C;
	C = (fluctuations-pow(internalEnergy,2))/(pow(spinNum,2)*Kb*pow(T,2));
	specificHeat = C;
	return C;
}

void spinConfiguration3D::plotData(){
	energies.clear();
	specificHeats.clear();
	magnetizations.clear();
	for(T=0.2;T<=12;T+=0.1){
		//setSpinConfiguration3D(1);
		//equilibrate(10*pow(spinNum,2));
		equilibrate(10000);
		getInternalEnergy();
		getSpecificHeat();
		getMagnetization();
		energies.push_back(internalEnergy);
		specificHeats.push_back(specificHeat);
		magnetizations.push_back(magnetization);
	}
}

void spinConfiguration3D::filePlotData(string nombre_archivo){
	plotData();
	fstream data3DFile;
	data3DFile.open(nombre_archivo.c_str(),ios::out);
	for(int i=0;i<magnetizations.size();i++){
		data3DFile << "\t" << energies[i] << "\t" << magnetizations[i] <<"\t"<< specificHeats[i] << endl;
	}
}



