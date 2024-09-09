/*    
Name: Rianna Pais (#5517988)
Lab Section: CSE 130A (Final Project)
Date: 04/24/2024

This is a program that runs a simulated illness checker for a user specified amount of patients. It utilizes multiple namespaces, structs, loops, functions, 
base/derived classes, and other OOP principles to print a report about each patient's symptoms and sickness. Each of the seven symptoms is randomly assigned a
value of either 'present' or 'absent'. Then, based upon which symptoms are present, the program checks whether the patient has either COVID-19, a Cold, the Flu, 
or none of them. Then a chart is printed showing the stats for the group of patients.
*/
	// included headers and namespace
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <list>
#include <cmath>
using namespace std;
	// check namespace for evaluating symptoms as either true or false, and incrementing counts
namespace Check{
	bool CS(string symptom){
		if (symptom == "present")
			return true;
		else
			return false;
	}
	void add2(int &count){
		count += 2;
	}
	void add1(int &count){
		count += 1;
	}
}
using namespace Check;
	// the patients class that privatly holds seven symptoms (and boolean values for the three ilnesses) and publicly creates a pointer to hold them
class Patients{
		struct Symptoms{
			string fever;
			string cough;
			string sob;
			string runnyNose;
			string headaches;
			string sneezing;
			string fatigue;
			bool covid = false;
			bool cold = false;
			bool flu = false;
	// initializer to randomly assign each symptom to either 'present' or 'absent'
			Symptoms(){
				fever = (rand() % 2 == 1) ? "present" : "absent"; // if even (picks 0), symptom is 'absent'
				cough = (rand() % 2 == 1) ? "present" : "absent"; // if odd (picks 1), symptom is 'present'
				sob = (rand() % 2 == 1) ? "present" : "absent";
    			runnyNose = (rand() % 2 == 1) ? "present" : "absent";
    			headaches = (rand() % 2 == 1) ? "present" : "absent";
    			sneezing = (rand() % 2 == 1) ? "present" : "absent";			
				fatigue = (rand() % 2 == 1) ? "present" : "absent"; 	
			}
		};
	// constructor and destructor for the patients class that initializes each member of the pointer (pts) to have their own randomized symptoms
	public:	
		Symptoms *pts;
		int userNum=0;
		Patients(int num):userNum(num){
			pts = new Symptoms[userNum];
		}
		~Patients(){
			delete[] pts;
		}
};
	// the illness class that inherits from patients and provides multiple functions for checking illness that its objects can use
class Illness:public Patients{
	public: 
		Illness(int num):Patients(num){}
	// the covid checking function that uses a count to weigh common vs. occasional symptoms to decide whether or not a patient has covid	
		void checkCovid(){ 
			int covidC;
			for (int i = 0; i < userNum; i++){ // the for loop checks each patient for covid
				covidC=0;
				if (!CS(pts[i].sneezing)){ // if the patient has sneezing they will automatically not have covid
					if (CS(pts[i].fever))
						add2(covidC);
					if (CS(pts[i].cough))
						add2(covidC);
					if (CS(pts[i].sob))
						add2(covidC);
					if (CS(pts[i].runnyNose))
						add1(covidC);
					if (CS(pts[i].headaches))
						add1(covidC);
					if (CS(pts[i].fatigue))
						add1(covidC);
					if (covidC >= 8)
						pts[i].covid = true;
					else
					pts[i].covid = false;
				} else {
					pts[i].covid = false;}
			}
		}	
		inline bool getCovid(int index) const{
			return pts[index].covid;
		}
	// the cold checking function that uses a count to weigh common vs. occasional symptoms to decide whether or not the patient has a cold
		void checkCold(){
			int coldC;
			for (int i = 0; i < userNum; i++){ // the for loop checks each patient for a cold
				coldC=0;
				if (!CS(pts[i].sob)){ // if a patient has shortness of breath they will automatically not have a cold
					if (CS(pts[i].runnyNose))
						add2(coldC);
					if (CS(pts[i].sneezing))
						add2(coldC);
					if (CS(pts[i].fever))
						add1(coldC);
					if (CS(pts[i].cough))
						add1(coldC);
					if (CS(pts[i].headaches))
						add1(coldC);
					if (CS(pts[i].fatigue))
						add1(coldC);
					if (coldC >= 6)
						pts[i].cold = true;
					else 
						pts[i].cold = false;
				} else {
					pts[i].cold = false;}
			}
		}
		inline bool getCold(int index) const{
			return pts[index].cold;
		}
	// the flu checking function which uses a count to weigh common vs. occasional symptoms to decide whether or not the patient has the flu
		void checkFlu(){
			int fluC;
			for (int i = 0; i < userNum; i++){ // the for loop checks each patient for the flu
				fluC=0;
				if (!CS(pts[i].sob) && !CS(pts[i].sneezing)){ // if the patient has shortness of breath or sneezing, they will automatically not have the flu
					if (CS(pts[i].fever))
						add2(fluC);
					if (CS(pts[i].cough)) 
						add2(fluC);
					if (CS(pts[i].headaches)) 
						add2(fluC);
					if (CS(pts[i].fatigue))
						add2(fluC);
					if (CS(pts[i].runnyNose))
						add1(fluC);
					if (fluC >= 6)
						pts[i].flu = true;
					else 
						pts[i].flu = false;
				} else {
					pts[i].flu = false;}
			}
		}
		inline bool getFlu(int index) const{
			return pts[index].flu;
		}
	// the function doubl checks to make a patient has not coincidentally benn assigned multiple illnesses	
		void doubleCheck(){
			for (int i = 0; i < userNum; i++){
				if (pts[i].flu){
					pts[i].covid = false;
					pts[i].cold = false;
				} else if (pts[i].cold){
					pts[i].covid = false;}	
			}
		}
};
	// the report namespace that holds all the functions for printing the first and final reports for the sickness stats
namespace Report{
	namespace Before{
		void printReport(){ // this function prints the symptoms/sickness table
			cout << "Welcome to my symptoms checker!" << endl << endl << "Guide:\t\t*Common\t\t+Sometimes/Rarely\t\t-NO" << endl;
			cout << "======================================================================" << endl;
			cout << "Symptoms\t\t|   COVID-19\t|   Cold\t|    Flu" << endl;
			cout << "======================================================================" << endl; 
			cout << "Fever\t\t\t|     *\t\t|     +\t\t|     *" << endl << "Cough\t\t\t|     *\t\t|     +\t\t|     *" << endl;
			cout << "Shortness of Breath\t|     *\t\t|     -\t\t|     -" << endl << "Runny Nose\t\t|     +\t\t|     *\t\t|     +" << endl << "Headaches\t\t|     +\t\t|     +\t\t|     *" << endl;
			cout << "Sneezing\t\t|     -\t\t|     *\t\t|     -" << endl << "Fatigue\t\t\t|     +\t\t|     +\t\t|     *" << endl;
			cout << "======================================================================" << endl << endl;			
		}
	}
	namespace After{
		void printReport(int covidpts, int coldpts, int flupts, int healthypts){ // this function prints the numerical distribution of illnesses for the patients
			cout << "======================================================================" << endl << "Symptoms Checker..." << endl;
			cout << covidpts << " patients have symptoms of COVID-19" << endl;
			cout << coldpts << " patients have symptoms of a Cold" << endl;
			cout << flupts << " patients have symptoms of the Flu" << endl;
			cout << healthypts << " patients may or may not have some other illness" << endl;
			cout << "======================================================================" << endl << endl;
		}
		void printPercents(int userNum, int covidpts, int coldpts, int flupts, int healthypts){ // this function prints the visual distribution (in percents) of illnesses for the patients
			float fCovidpc = (float)covidpts/userNum;
			fCovidpc = round(fCovidpc*100);
			float fColdpc = (float)coldpts/userNum;
			fColdpc = round(fColdpc*100);
			float fFlupc = (float)flupts/userNum;
			fFlupc = round(fFlupc*100);
			float fHealthypc = (float)healthypts/userNum;
			fHealthypc = round(fHealthypc*100);
			int iCovidpc = (int)fCovidpc;
			int iColdpc = (int)fColdpc;
			int iFlupc = (int)fFlupc;
			int iHealthypc = (int)fHealthypc;
			cout << "Percentage of each illness:" << endl; //am i meant to print + of percent or of patients?
			cout << "COVID-19)\t\t[" << fCovidpc << "%] ";
			for (int i = 0; i < iCovidpc; i++){
				cout << "+";}
			cout << endl;
			cout << "Cold)\t\t\t[" << fColdpc << "%] ";
			for (int i = 0; i < iColdpc; i++){
				cout << "+";}
			cout << endl;
			cout << "Flu)\t\t\t[" << fFlupc << "%] ";
			for (int i = 0; i < iFlupc; i++){
				cout << "+";}
			cout << endl;
			cout << "Healthy/Other illness)\t[" << fHealthypc << "%] ";
			for (int i = 0; i < iHealthypc; i++){
				cout << "+";}
			cout << endl;
		}
	}
}
	// main body of code that initializes the random number seed and allows the user to enter their desired numbr of patients for the simluation
int main(){
	srand(time(NULL));
	using namespace Report::Before;
	printReport();
	int userNum=0;
	cout << "Enter the number of patients: ";
	cin >> userNum;
	cout << "Thank you!" << endl << endl;
	// creations of objects within the derived illness class that then checks for each illness amongst the patient objects
	Illness sickpts(userNum);
	sickpts.checkCovid();
	sickpts.checkCold();
	sickpts.checkFlu();
	sickpts.doubleCheck();
	int covidpts=0;
	int coldpts=0;
	int flupts=0; 
	int healthypts=0;
	// for loop that calculates the number of objects with each illness
	for (int i = 0; i < userNum; i++){
		if (sickpts.getCovid(i))
			covidpts++;
		if (sickpts.getCold(i))
			coldpts++;
		if (sickpts.getFlu(i))
			flupts++;
		if (!sickpts.getCovid(i) && !sickpts.getCold(i) && !sickpts.getFlu(i))
			healthypts++;
	}	
	// functions to print the final report
	using namespace Report::After;
	printReport(covidpts, coldpts, flupts, healthypts);
	printPercents(userNum, covidpts, coldpts, flupts, healthypts);
	return 0;
}