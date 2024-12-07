#pragma once
#include <string>
#include <vector>
#include "Facility.h"
#include "Plan.h"
#include "Settlement.h"
using std::string;
using std::vector;

class BaseAction;
class SelectionPolicy;

class Simulation {
    public:
        Simulation(const string &configFilePath);
        void start();
        void addPlan(const Settlement &settlement, SelectionPolicy *selectionPolicy);
        void addAction(BaseAction *action);
        bool addSettlement(Settlement *settlement);
        bool addFacility(FacilityType facility);
        bool isSettlementExists(const string &settlementName);
        bool isFacilityExists(const string &FacilityName);
        bool isPlanExists(const int planID);
        Settlement &getSettlement(const string &settlementName);
        Plan &getPlan(const int planID);
        void step();
        void close();
        void open();
        void configureFile();
        void printActionLog() const;
        Simulation(const Simulation&other);
        Simulation & operator=(const Simulation& other);
        ~Simulation();
        int TESTNUM;
        vector<Plan> plans;
    private:
        bool isRunning;
        int planCounter; //For assigning unique plan IDs WE MAKING IT PUBLIC 
        vector<BaseAction*> actionsLog;
        vector<Settlement*> settlements;
        vector<FacilityType> facilitiesOptions;
        string configFilePatht;
};