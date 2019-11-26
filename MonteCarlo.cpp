#include "IsingModel.h"
#include "WaveFunction.h"


/*
Codigo realizado por: Santiago Morales Saldarriaga

Resumen:
Codigo en el, mediante Monte Carlo, se soluciona el modelo de Ising (1D,2D y 3D) y se encuentra la función de onda (el cuadrado) de sistemas físicos con potencial conocido.

En este codigo se hace uso de las clases spinConfiguration, spinConfiguration2D, spinConfiguration3D y particle. Las tres primeras están declaradas en el archivo IsingModel.h y la ultima en WaveFunction.h, en los archivos IsingModel_interfaz.cpp y WaveFunction_interfaz.cpp se definen los metodos de las clases, respectivamente.

spinConfiguration, spinConfiguration2D, spinConfiguration3D: son clases que definen objetos que buscan contener las propiedades de un arreglo n dimensional (n=1,2,3) de espines segun el modelo de Ising.

particle: es una clase en donde se busca definir objetos que pueden evolucionar cuanticamente, en donde es posible definir su evolucion segun dos potenciales, evolution lo evoluciona como un oscilador armonico cuantico y evolutionBouncer como un "rebotador cuantico".

nota: Se recomienda correr este codigo por partes, Ising2D e Ising3D requieren de tiempo de computo bastante significativo. Tambien se le podría disminuir la cantidad de espines a estas configuraciones para obtener un tiempo de computo bastante menor,
*/

int main(){
	srand(time(NULL));
//Ising 1D
	spinConfiguration spin(200,1);
	//Propiedades termodinamicas
		spin.filePlotData("dataFerro.dat");
		spin.setSpinConfiguration(1);
		spin.setJ(-1);
		spin.filePlotData("dataAntiFerro.dat");
	//Guardar las configuraciones durante la evolucion del sistema.
		//Bajas temperaturas
			spin.setT(1);
			//Ferromagneticos
			spin.setJ(1);
			spin.setSpinConfiguration(1);
			spin.fileSpinsEvolution("data/spins1DFerroBT.dat");
			//Antiferromagneticos
			spin.setSpinConfiguration(1);
			spin.setJ(-1);
			spin.fileSpinsEvolution("data/spins1DAntiFerroBT.dat");
		//Altas temperaturas
			spin.setT(10);
			//Ferromagneticos
			spin.setJ(1);
			spin.setSpinConfiguration(1);
			spin.fileSpinsEvolution("data/spins1DFerroAT.dat");
			//Antiferromagneticos
			spin.setSpinConfiguration(1);
			spin.setJ(-1);
			spin.fileSpinsEvolution("data/spins1DAntiFerroAT.dat");
	/*
//Ising 2D
	spinConfiguration2D spin2D(200,1);
	//Propiedades termodinamicas
		spin2D.setJ(-1);
		spin2D.filePlotData("data2DAntiFerro.dat");
	//Guardar las configuraciones durante la evolucion del sistema
		//Bajas temperaturas
			spin2D.setT(1);
			spin2D.fileSpinConfiguration2D("data/spinConfigurationFerroBT0.dat");
			string fileName;
			for(int i=1;i<6;i++){
				fileName = "data/spinConfigurationFerroBT"+to_string(20000*i)+".dat";
				spin2D.equilibrate(20000);
				spin2D.fileSpinConfiguration2D(fileName);
			}
			spin2D.setSpinConfiguration2D(1);
			spin2D.setJ(-1);
			spin2D.fileSpinConfiguration2D("data/spinConfigurationAntiFerroBT0.dat");
			for(int i=1;i<6;i++){
				fileName = "data/spinConfigurationAntiFerroBT"+to_string(20000*i)+".dat";
				spin2D.equilibrate(20000);
				spin2D.fileSpinConfiguration2D(fileName);
			}
		//Altas temperaturas
			spin2D.setT(10);
			spin2D.setSpinConfiguration2D(1);
			spin2D.fileSpinConfiguration2D("data/spinConfigurationFerroAT0.dat");
			for(int i=1;i<6;i++){
				fileName = "data/spinConfigurationFerroAT"+to_string(20000*i)+".dat";
				spin2D.equilibrate(20000);
				spin2D.fileSpinConfiguration2D(fileName);
			}
			spin2D.setSpinConfiguration2D(1);
			spin2D.setJ(-1);
			spin2D.fileSpinConfiguration2D("data/spinConfigurationAntiFerroAT0.dat");
			for(int i=1;i<6;i++){
				fileName = "data/spinConfigurationAntiFerroAT"+to_string(20000*i)+".dat";
				spin2D.equilibrate(20000);
				spin2D.fileSpinConfiguration2D(fileName);
			}
//Ising 3D
	//Propiedades termodinamicas
		spinConfiguration3D spin3D(30,1);
		spin3D.filePlotData("data/data3DFerro.dat");
		spin3D.setSpinConfiguration3D(1);
		spin3D.setJ(-1);
		spin3D.filePlotData("data/data3DAntiFerro.dat");

//Funcion de onda a partir de la solucion de integrales de camino
		particle particle(100,100); 
	//Particula cuantica rebotando en una pared bajo accion de la gravedad
		particle.setEpsilon(0.05);
		particle.evolutionBouncer(1000000);
		particle.filePath("data/pathBouncer.dat");
		particle.fileProbabilities("data/probBouncer.dat");
	//Oscilador armonico cuantico
		particle.restartPath(100,100);
		particle.setEpsilon(0.1);
		particle.evolution(10000000);
		particle.filePath("data/pathOscilador.dat");
		particle.fileProbabilities("data/probOscilador.dat");
	return 0;*/
}
