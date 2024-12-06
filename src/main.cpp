#include "Simulation.h"
#include <iostream>
using std::vector;

using namespace std;

Simulation* backup = nullptr;

int main(int argc, char** argv){
   // cout << "moses" << endl;
    if(argc!=2){
       cout << "usage: simulation <config_path>" << endl;
       return 0;
   }
    string configurationFile = argv[1];

    /*FacilityType t1 = FacilityType("school",FacilityCategory::ECONOMY,5,1,1,1);
    FacilityType t2 = FacilityType("park",FacilityCategory::LIFE_QUALITY,3,1,2,4);

    std::vector<FacilityType> facilities;
    facilities.push_back(FacilityType(t1));
    facilities.push_back(FacilityType(t2));

    NaiveSelection n = NaiveSelection();
    n.selectFacility(facilities);
    cout <<n.getLast() << endl;
    n.selectFacility(facilities);
    cout <<n.getLast() << endl;

    NaiveSelection *n2 = n.clone();
    cout <<(*n2).getLast() << endl;
*/
   Simulation simulation(configurationFile);
   simulation.start();
   if(backup!=nullptr){
  delete backup;
 	backup = nullptr;
 }
 //return 0;
 // vector<FacilityType> facilityOptions;
 // Settlement s1("BEER SHEVA",SettlementType::CITY);
 // std:: cout << "erteswter:  "+ s1.getName() << std::endl;
 // Settlement s2("Tel AVIV",SettlementType::CITY);
 // std:: cout << "erteswter:  "+ s2.getName() << std::endl;
  
//  Plan p1(0,s1,new NaiveSelection(),facilityOptions);
//  Plan p2(1,s2,new EconomySelection(),facilityOptions);
return 0;
}