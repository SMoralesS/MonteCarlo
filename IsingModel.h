#include<iostream>
#include<vector>
#include<iomanip>
#include<stdlib.h>
#include<string>
#include<ctime>
#include<cmath>
#include<fstream>

using namespace std;

const double Kb = 1;

class spinConfiguration{
	public:
		//Constructor - genera una cadena de n espines  opcion (opt) dada por el usuario 
		//opt = -1: inicializa el sistema en frio (con los spin antiparalelos (-1,1,-1,1,...))
		//opt = 1: inicializa el sistema en frio (con los spin paralelos (1,1,1,1,...))
		//opt = 0: inicializa el sistema en caliente (con los spin organizados aleatoriamente
		spinConfiguration(int,int=0);
		//Constructor que inicializa un objeto spinConfiguration con una configuracion dada por el usuario
		spinConfiguration(vector<int>);
		void setJ(int); //Modifica el valor de J(J=1 es ferromagnetico, J=-1 es antiferromagnetico)
		void setT(double); //Modifica el valor de la temperatura
		vector<int> getSpinConfiguration(); //Permite al usuario obtener la configuracion de espines
		void setSpinConfiguration(int=0); //Permite modificar la configuracion de espines segun las opciones
		void setSpinConfiguration(vector<int>); //Permite modificar la configuracion de espines por una configuracion preestablecida
		int getSpinNum(); //Permite obtener la cantidad de espines
		void setSpinNum(int); //Permite modificar la cantidad de espines en la configuracion
		void printSpins(); //Imprime la cadena de espines diferenciandolos con x (up) y o (down)
		double getInternalEnergy(); //Permite obtener la energia interna del sistema
		double getSpecificHeat(); //Permite obtener el calor especifico del sistema
		double getMagnetization(); //Permite obtener la magnetizacion interna del sistema
		void fileSpins(string); //Extrae la configuracion en un archivo
		void fileSpinsEvolution(string); //Extrae la evolucion de la configuracion de espines durante 1000 pasos de tiempo
		void filePlotData(string); //Extrae las variables termodinamicas del sistema entre T=0.2 y T=6 en un archivo 
		
	private:
		vector<int> spins; //Vector con la configuracion de espines
		vector<double> energies; //Vector con las energias internas desde T=0.2 hasta T=6
		vector<double> magnetizations; //Vector con las magnetizaciones internas desde T=0.2 hasta T=6
		vector<double> specificHeats; //Vector con calores especificos desde T=0.2 hasta T=6
		int spinNum; //Cantidad de espines en la configuracion
		double T,internalEnergy,fluctuations,specificHeat,magnetization; //Variables termodinamicas
		int J; // energia de intercambio (interaccion espin-espin)
		double energy(); //Calculo de la energia para una configuracion especifica (InternalEnergy = promedio de energia)
		void checkTrial(); //Realiza el algoritmo de Metropolis una unica vez
		void equilibrate(); //Equilibra el sistema al realizar Metropolis 10000 veces
		vector<int> trialConfig(int); //invierte en una posicion especifica el espin
		void plotData(); //Extrae la informacion termodinamica del sistema
};

class spinConfiguration2D : public spinConfiguration{
	public:
		//Constructor - genera una configuracion de spin 2D de nxn segun la opcion (opt) dada por el usuario 
		//opt = -1: inicializa el sistema en frio (con los spin antiparalelos (-1,1,-1,1,...))
		//opt = 1: inicializa el sistema en frio (con los spin paralelos (1,1,1,1,...))
		//opt = 0: inicializa el sistema en caliente (con los spin organizados aleatoriamente
		spinConfiguration2D(int n=100,int opt=0) : spinConfiguration(n,opt){
			setSpinConfiguration2D(opt);
			T=10;
			J=1;
		}
		//Constructor que inicializa un objeto spinConfiguration2D con una configuracion dada por el usuario
		spinConfiguration2D(vector<vector<int>> states) : spinConfiguration(states[0]){
			setSpinConfiguration2D(states);
			T=10;
			J=1;
		}
		void setJ(int); //Permite al usuario escoger entre un sistema ferromagnetico (J=1) o una antiferromagnetico (J=-1)
		double setT(double temperature); //Permite al usuario modificar el valor de la temperatura
		void setSpinConfiguration2D(int); //Reinicia la configuracion segun la opcion (opt) dada por el usuario
		void setSpinConfiguration2D(vector<vector<int>> states); //Reinicia la configuracion con matriz states
		vector<vector<int>> getSpinConfiguration2D(); //Devuelve la configuracion actual de spins
		//Los siguientes 3 metodos calculan y entregan al usuario las propiedades del sistema		
		int getMagnetization(); 
		double getInternalEnergy(); 
		double getSpecificHeat();	
		void printSpinConfiguration2D(); //Imprime en pantalla la configuracion actual
		void fileSpinConfiguration2D(string); //Imprime en el archivo (nombre dado como argumento) la configuracion actual
		void equilibrate(int=10000); //Evoluciona el sistema un numero arbitrario de pasos
		void filePlotData(string nombre_archivo); //Entrega en un archivo las propiedades del sistema para T desde 0.2 hasta 6,
							  // donde las columnas son la energia interna, la magnetizacion y el calor especifico,
							  // respectivamente
	private:
		//Funciones internas de la clase
		vector<vector<int>> trialConfig2D(int i,int j); //devuelve la configuracion actual con el spin i,j invertido
		double energy(); //Devuelve la energia para una configuracion especifica (La energia interna es el promedio de esta)
		void checkTrial(); //Prueba una trialConfig2D y la cambia por la actual segun el algoritmo de Metropolis
		void plotData(); //Calcula los valores que se devuelven en el archivo en filePlotData
		
		//Variables internas de la clase
		vector<vector<int>> spins2D; //Matriz con los valores de los spin
		//Vectores con los valores de las propiedades del sistema para diferentes valores de T		
		vector<double> energies; 
		vector<double> magnetizations;
		vector<double> specificHeats;
		int spinNum; //Lado de la rejilla de spin
		double T; //Temperatura del sistema
		int J;
		double internalEnergy; //Energia interna del sistema
		double fluctuations; //Fluctuaciones del sistema (prom(E^2))
		double magnetization; //Magnetizacion del sistema
		double specificHeat; //Calor especifico del sistema
};


class spinConfiguration3D : public spinConfiguration2D{
	public:
		//Constructor - genera una configuracion de spin 3D de nxnxn segun la opcion (opt) dada por el usuario 
		//opt = -1: inicializa el sistema en frio (con los spin antiparalelos (-1,1,-1,1,...))
		//opt = 1: inicializa el sistema en frio (con los spin paralelos (1,1,1,1,...))
		//opt = 0: inicializa el sistema en caliente (con los spin organizados aleatoriamente
		spinConfiguration3D(int n=100,int opt=0) : spinConfiguration2D(n,opt){
			setSpinConfiguration3D(opt);
			T=10;
			J=1;
		}
		//Constructor que inicializa un objeto spinConfiguration3D con una configuracion dada por el usuario
		spinConfiguration3D(vector<vector<vector<int>>> states) : spinConfiguration2D(states[0]){
			setSpinConfiguration3D(states);
			T=10;
			J=1;
		}
		void setJ(int); //Permite al usuario escoger entre un sistema ferromagnetico (J=1) o una antiferromagnetico (J=-1)
		double setT(double temperature); //Permite al usuario modificar el valor de la temperatura
		void setSpinConfiguration3D(int); //Reinicia la configuracion segun la opcion (opt) dada por el usuario
		void setSpinConfiguration3D(vector<vector<vector<int>>>); //Reinicia la configuracion con matriz states
		vector<vector<vector<int>>> getSpinConfiguration3D(); //Devuelve la configuracion actual de spins
		//Los siguientes 3 metodos calculan y entregan al usuario las propiedades del sistema		
		int getMagnetization(); 
		double getInternalEnergy(); 
		double getSpecificHeat();
		double energy();
		void checkTrial();
		void printSpinConfiguration3D(); //Imprime en pantalla la configuracion actual
		void fileSpinConfiguration3D(string); //Imprime en el archivo (nombre dado como argumento) la configuracion actual
		void equilibrate(int=10000); //Evoluciona el sistema un numero arbitrario de pasos
		void filePlotData(string nombre_archivo); //Entrega en un archivo las propiedades del sistema para T desde 0.2 hasta 6,
							  // donde las columnas son la energia interna, la magnetizacion y el calor especifico,
							  // respectivamente
	private:
		//Funciones internas de la clase
		vector<vector<vector<int>>> trialConfig3D(int,int,int); //devuelve la configuracion actual con el spin i,j invertido
		 //Devuelve la energia para una configuracion especifica (La energia interna es el promedio de esta)
		 //Prueba una trialConfig3D y la cambia por la actual segun el algoritmo de Metropolis
		void plotData(); //Calcula los valores que se devuelven en el archivo en filePlotData
		
		//Variables internas de la clase
		vector<vector<vector<int>>> spins3D; //Matriz con los valores de los spin
		//Vectores con los valores de las propiedades del sistema para diferentes valores de T		
		vector<double> energies; 
		vector<double> magnetizations;
		vector<double> specificHeats;
		int spinNum; //Lado del cubo de espines
		double T; //Temperatura del sistema
		int J;
		double internalEnergy; //Energia interna del sistema
		double fluctuations; //Fluctuaciones del sistema (prom(E^2))
		double magnetization; //Magnetizacion del sistema
		double specificHeat; //Calor especifico del sistema
};


