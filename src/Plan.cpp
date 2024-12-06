//DONT FORGETTTTT TO IMPLEMENT HERE COPY CONSTRUCTOR WHY? BECAUSE BACKUP ! WHEN YOU COPY THE PLAN IT HAS DYNAMIC MEMORY SO YOU NEED TO ADRESS IT PROPERLY
#include "Plan.h"
#include <iostream>
Plan:: Plan(const int planId, const Settlement &settlement, SelectionPolicy *selectionPolicy, const vector<FacilityType> &facilityOptions)
:plan_id(planId),settlement(settlement),selectionPolicy(selectionPolicy),facilityOptions(facilityOptions),status(PlanStatus::AVALIABLE),
life_quality_score(0),economy_score(0),environment_score(0){
    constructionLimit = static_cast<int>(settlement.getType()) + 1;
};

Plan :: Plan(const Plan& other)
:plan_id(other.plan_id),status(other.status),
life_quality_score(other.life_quality_score),economy_score(other.economy_score),environment_score(other.environment_score),
constructionLimit(other.constructionLimit),facilityOptions(other.facilityOptions),settlement(other.settlement){

    this->selectionPolicy = other.selectionPolicy->clone();
    //std:: cout << "this->selectionpolicy : " + selectionPolicy->toString() << std::endl;
    std:: cout << "this->getNameSettlment : " + this->settlement.getName() << std::endl;
    for (int i = 0; i < other.facilities.size(); i++)
    {
        this->facilities.push_back(new Facility(*other.facilities[i]));
    }
    for (int i = 0; i < other.underConstruction.size(); i++)
    {
        this->underConstruction.push_back(new Facility(*other.underConstruction[i]));
    }    
};

const int Plan::getlifeQualityScore() const{return life_quality_score;};
const int Plan::getEconomyScore() const{return economy_score;};
const int Plan::getEnvironmentScore() const{return environment_score;};

void Plan::setSelectionPolicy(SelectionPolicy *selectionPolicy){
    delete this->selectionPolicy;
    this->selectionPolicy = selectionPolicy;
};


void Plan::step(){
    while (this->status==PlanStatus::AVALIABLE)
    {
     //    std:: cout << "enetered while planstatus = avaialable " << std::endl;
     //    std:: cout << "settlment name is :  " + (settlement.getName()) << std::endl;
      //   std:: cout << "the plan Scores is : LIFE SCORE: "+ std::to_string(this->life_quality_score)+" ECONOMYSCORE: " +std::to_string(this->economy_score) + " ENIORMENTSCPRE :" +std::to_string(this->environment_score) << std::endl;
    std:: cout << "facilityoptions size is : " + std::to_string(facilityOptions.size()) << std::endl;
        //FacilityType ft = (this->selectionPolicy)->selectFacility(facilityOptions);
     //   std:: cout << "selectedFaciliyType is :  :  " + (ft.toString()) << std::endl;
        this->addFacility(new Facility((this->selectionPolicy)->selectFacility(facilityOptions),this->settlement.getName()));
        
    //    std:: cout << "NEW!!! plan Scores is : LIFE SCORE: "+ std::to_string(this->life_quality_score)+" ECONOMYSCORE: " +std::to_string(this->economy_score) + " ENIORMENTSCPRE :" +std::to_string(this->environment_score) << std::endl;
    //    std:: cout << "MAYBE CRASH here" << std::endl;
     //   std:: cout << "UnderConstruction.size()" + std::to_string(underConstruction.size()) << std::endl;
     //   std:: cout << "construction limit is : " + std::to_string(constructionLimit) << std::endl;
        if (underConstruction.size() == constructionLimit)
        {
            this->status =PlanStatus::BUSY;
        }
    }
    for (int i = 0; i < underConstruction.size(); i++) {
       // std:: cout << "faciliy  in under construction is :  " + underConstruction[i]->toString() << std::endl;
         if (underConstruction[i]->step() ==FacilityStatus::OPERATIONAL)
         {
         //   std:: cout << "terminated here???" << std::endl;
             this->life_quality_score = this->life_quality_score + underConstruction[i]->getLifeQualityScore();
             this->economy_score = this->economy_score + underConstruction[i]->getEconomyScore();
             this->environment_score = this->environment_score + underConstruction[i]->getEnvironmentScore();
             facilities.push_back(underConstruction[i]); 
             underConstruction.erase(underConstruction.begin()+i);   
         }
    }
    if (underConstruction.size()<constructionLimit)
    {
        this->status = PlanStatus::AVALIABLE;
    }
    
};

//CHECK IF CAN DO BETTER WITH STATIC CAST 
void Plan::printStatus(){
    //std:: cout << settlement.getName()  << std::endl;
    std:: cout <<"SettlementName: " + this->settlement.getName()  << std::endl;
    std:: cout <<"PlanStatus: " + statusString(status)<< std::endl;
    std:: cout <<"SelectionPolicy: " +  this->selectionPolicy->toString()  << std::endl;
    std:: cout <<"LifeQualityScore " +std::to_string(this->life_quality_score)  << std::endl;
    std:: cout <<"EconomyScore " + std::to_string(this->economy_score)  << std::endl;
    std:: cout <<"EnviormentScore " + std::to_string(this->environment_score) << std::endl;
    for (Facility * f1 : this->facilities)
    {
        std:: cout <<"FacilityName: " + f1->getName() +"" << std::endl;
        std:: cout <<"FacilityStatus: OPERATIONAL"  << std::endl;
    }
    for (Facility  * f2 : this->underConstruction)
    {
        std:: cout <<"FacilityName: " + f2->getName() +"" << std::endl;
        std:: cout <<"FacilityStatus: UNDER_CONSTRUCTIONS"  << std::endl;
    }
    
};
string Plan::statusString(PlanStatus status){
      switch (status) {
        case PlanStatus::AVALIABLE:
            return "AVAILABLE";
        case PlanStatus::BUSY:
            return "BUSY";
      }
};

string Plan::getSelectionPolicy() const{
    return this->selectionPolicy->toString();
};

const vector<Facility*> & Plan::getFacilities() const{return this->facilities;};

void Plan::addFacility(Facility* facility){
    this->underConstruction.push_back(facility);
};
//DONT FORGET !!!
const string Plan::toString() const{
    return "PLAM";
};