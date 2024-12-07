#include "Simulation.h"
#include <iostream>
#include <fstream> 
#include "Auxiliary.h"
#include "Action.h"
extern Simulation* backup; 


//./bin/Simulation ./config_file.txt
//constructor
Simulation::Simulation(const string &configFilePatht):isRunning(true),planCounter(0),configFilePatht(configFilePatht){  
    std::cout << "Simulation constructor called!" << std::endl;
    configureFile();
    backup=nullptr;
};

//copy_comstructor
Simulation:: Simulation(const Simulation&other):isRunning(other.isRunning),planCounter(other.planCounter),facilitiesOptions(other.facilitiesOptions){
     for (int i=0;i<other.actionsLog.size();i++)
     {
        this->actionsLog.push_back(other.actionsLog[i]->clone());
    }
    for (int i=0;i<other.plans.size();i++)
    {
        this->plans.push_back(Plan(other.plans[i]));
    }
    for (int i=0;i<other.settlements.size();i++)
    {
        this->settlements.push_back(new Settlement(*other.settlements[i]));
    }
};

//copy_assignment
Simulation & Simulation:: operator=(const Simulation& other){
    if (&other != this)
    {
    for (BaseAction * action: actionsLog)
    {
        delete action;
    }
    for (Settlement * set: settlements)
    {
       delete set;
    }
    
    actionsLog.clear();
    settlements.clear();
    plans.clear();
    facilitiesOptions.clear();
    this->isRunning=other.isRunning;
    this->planCounter= other.planCounter;
    this->configFilePatht = other.configFilePatht;
     for (int i = 0; i < other.actionsLog.size(); i++)
    {
        this->actionsLog.push_back(other.actionsLog[i]->clone());
        std:: cout << "actions log [i] : " +  this->actionsLog[i]->toString() << std::endl;
    }
    for (int i = 0; i < other.planCounter; i++)
    {
          //const_cast<Plan&>(other.plans[i]).printStatus();
     //     other.plans[i].printStatus();
          this->plans.push_back(Plan(other.plans.at(i)));
         // this->plans.push_back(Plan(i,Settlement("MOSHE " + std::to_string(i),SettlementType::CITY),new NaiveSelection(),facilitiesOptions));
        // std:: cout << "plans [" + std::to_string(i)+ "]" << std::endl;
         
          //std:: cout << "plans!!!! [" + std::to_string(i)+ "]" << std::endl;
          this->plans[i].printStatus();

    }

    for (int i = 0; i < planCounter; i++)
    {
        // std:: cout << "plans [" + std::to_string(i)+ "]" << std::endl;
         this->plans[i].printStatus();
    }
    

    for (int i = 0; i < other.settlements.size(); i++)
    {
        this->settlements.push_back(new Settlement(*other.settlements[i]));
       //settlements.insert(settlements.begin() + i,new Settlement(*other.settlements[i]));
    }
   for (int i = 0; i < other.facilitiesOptions.size(); i++)
    {
        this->facilitiesOptions.push_back(FacilityType(other.facilitiesOptions[i]));
    }
    }
    return  *this;
};

Simulation:: ~Simulation(){
    for (BaseAction * action: actionsLog)
    {
        delete action;
    }
    for (Settlement * set: settlements)
    {
       delete set;
    }
     actionsLog.clear();
    settlements.clear();
    plans.clear();
    facilitiesOptions.clear();

};

void Simulation::start(){
    std:: cout << "The simulation has started" << std::endl;
    open();
};
 void Simulation::addPlan(const Settlement &settlement, SelectionPolicy *selectionPolicy){
   //  std:: cout << "settlment us  in add plan : " + settlement.toString() << std::endl;
   // std:: cout << "getNAME   in add plan : " + settlement.getName() << std::endl;
   std:: cout << "beforeplanPushBack : " << std::endl;
   plans.push_back(Plan(planCounter,settlement,selectionPolicy,facilitiesOptions));
    std:: cout << "afterPlanPushBack : " << std::endl;
   // std:: cout << plans.size() << std::endl;
     planCounter++;
 };

 void Simulation::addAction(BaseAction *action){
    actionsLog.push_back(action);
    action->act(*this);
   // std:: cout << "TEST NUM IS " + std::to_string(this->TESTNUM) << std::endl;

 };

bool Simulation::addSettlement(Settlement *settlement){
    settlements.push_back(settlement);
};

bool Simulation::addFacility(FacilityType facility){
    facilitiesOptions.push_back(facility);
    //std:: cout << "AFTER PUSH BACK SIZE IS "+std::to_string(facilitiesOptions.size()) << std::endl;
};
bool Simulation::isFacilityExists(const string &FacilityName){
      for (FacilityType f : facilitiesOptions)
    {
        if (f.getName()==FacilityName)
        {
            return true;
        }
        
    }
    return false;
};
bool Simulation::isSettlementExists(const string &settlementName){
    for (Settlement * st : settlements)
    {
        if (st->getName()==settlementName)
        {
            return true;
        }
        
    }
    return false;
    
};
 bool Simulation::isPlanExists(const int planID){
    if (planID<0 || planID>=planCounter)
    {
        return false;
    }
    return true;
 };


Settlement & Simulation::getSettlement(const string &settlementName){
    for (Settlement * st : settlements)
    {
        if (st->getName()==settlementName)
        {
            return *st;
        }
        
    }
};

Plan & Simulation::getPlan(const int planID){
  //  std::cout << "HETOOO $#3" << std::to_string(planID) << std::endl;
  //  std::cout << "Moshe" << plans.size() << std::endl;
  //  std::cout << "Moshe" << plans.at(planID).toString() << std::endl;
  //  std::cout <<"!!!##test2 getPlan for plan p with id "+std::to_string(planID)+", the life quality score is : " +std::to_string(plans[planID].getlifeQualityScore()) << std::endl;
    return plans[planID];
};


void Simulation::step(){
    for (int i = 0; i < plans.size(); i++)
    {
       plans[i].step();
   //    std::cout <<"$$$finished step for plan p : the life quality score is : " + std::to_string(plans[i].getlifeQualityScore()) << std::endl;
    }
};

void Simulation::close(){
       int index = 0;
       while (index<planCounter)
       {
            std:: cout <<"PlanId: "+std::to_string(index) << std::endl;
            plans[index].printStatus();
            index++;
       }

    isRunning=false;
};

void Simulation::configureFile(){
   // std:: cout <<"enetered configurefile : " + configFilePatht << std::endl;
    std::ifstream file(configFilePatht);  
    std::string line;
    //this is extracting a line 
    while (std::getline(file, line)) {
      //  std:: cout <<"enetered get line "  << std::endl;
        //this is checking this is not a note hehara
         if (line.empty() || line[0] == '#') {
            continue;  
        }
        else{
         //  std:: cout <<"line is : " + line << std::endl;
           vector<string> arguments =  Auxiliary::parseArguments(line);
           //case 1 if it is a settlment 
            if (arguments[0]=="settlement")
            {
                 std:: cout <<" WHATS UP!!!! : " + arguments[1] << std::endl;
                this->addSettlement(new Settlement(arguments[1],static_cast<SettlementType>(std::stoi(arguments[2]))));
            }
            //case 2 if facility
            if (arguments[0]=="facility")
            {
               this->addFacility(FacilityType(arguments[1],static_cast<FacilityCategory>(std::stoi(arguments[2])),(std::stoi(arguments[3])),
               (std::stoi(arguments[4])),(std::stoi(arguments[5])),(std::stoi(arguments[6]))));
          //     std::cout << "facility options size : " +std::to_string(facilitiesOptions.size()) << std::endl;
            }
           //  std::cout << "final facility options size : " +std::to_string(facilitiesOptions.size()) << std::endl;
            //case 3 if its a plan 
            if (arguments[0]=="plan")
            {
                if (isSettlementExists(arguments[1]))
                {
                    //IMPORTANAT & BEFORE settlename
                     std:: cout <<" WHATS UP this is settlmentNAME in PLANNNN!!!! : " + arguments[1] << std::endl;
                    Settlement &settle = this->getSettlement(arguments[1]);
            //        std::cout << "in plan init: argument[1] is : " + arguments[1] << std::endl;
              //      std::cout << "in plan init: settlename is : " + settle_name.toString() << std::endl;
                //    std::cout << "gwt NAME  : " + settle_name.getName() << std::endl;

                
                    if (arguments[2]=="nve"){
                        addPlan(settle,new NaiveSelection());
                        //plans.push_back(Plan(planCounter,settle_name,new NaiveSelection(),this->facilitiesOptions));
                    }
                    if (arguments[2]=="bal"){
                        addPlan(settle,new BalancedSelection(0,0,0));
                       // plans.push_back(Plan(planCounter,settle_name,new BalancedSelection(0,0,0),this->facilitiesOptions));
                    }
                    if (arguments[2]=="eco")
                    {
                        addPlan(settle,new EconomySelection());
                      ///plans.push_back(Plan(planCounter,settle_name,new EconomySelection(),this->facilitiesOptions));
                    }
                    if (arguments[2]=="env")
                    {
                        addPlan(settle,new SustainabilitySelection());
                     // plans.push_back(Plan(planCounter,settle_name,new SustainabilitySelection(),this->facilitiesOptions));
                   
                    }
            }
            }

        }
}   
};

void Simulation::open(){
    std::string userInput;
   
   BaseAction *a;
   while (isRunning) {
        std::getline(std::cin, userInput);
        vector<string> arguments =  Auxiliary::parseArguments(userInput);

        if (arguments[0]=="step")
        {
        //    std:: cout <<"t1" << std::endl;
            a =new SimulateStep(std::stoi(arguments[1]));
        }
        if (arguments[0]=="plan")
        {
            a =new AddPlan(arguments[1],arguments[2]);
        }   
        if (arguments[0]=="settlement")
        {
           a=new AddSettlement(arguments[1],static_cast<SettlementType>(std::stoi(arguments[2])));
        }
        if (arguments[0]=="facility")
        {
           a=new AddFacility(arguments[1],static_cast<FacilityCategory>(std::stoi(arguments[2])),std::stoi(arguments[3]),std::stoi(arguments[4]),std::stoi(arguments[5]),std::stoi(arguments[6]));
        }
        if (arguments[0]=="planStatus")
        {
          // std:: cout <<"t2" + getPlan(0).getlifeQualityScore()<< std::endl;
          // a=new PrintPlanStatus(std::stoi(arguments[1]));
          a = new PrintPlanStatus(std::stoi(arguments[1]));
        }
        if (arguments[0]=="changePolicy")
        {
           a=new ChangePlanPolicy(std::stoi(arguments[1]),arguments[2]);
        }
        if (arguments[0]=="log")
        {
           a=new PrintActionsLog();
        }
        if (arguments[0]=="close")
        {
           a=new Close();
        }
        if (arguments[0]=="backup")
        {
           a=new BackupSimulation();
        }
        if (arguments[0]=="restore")
        {
           a=new RestoreSimulation();
        }
        this->addAction(a);
        //std:: cout <<"t2" + std::to_string(getPlan(0).getlifeQualityScore())<< std::endl;
   }
};

void Simulation:: printActionLog() const{
    for (int i = 0; i < actionsLog.size()-1; i++)
    {
        std:: cout << actionsLog[i]->toString() << std::endl;        
    }
};

