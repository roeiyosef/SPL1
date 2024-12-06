#include "Settlement.h"

Settlement:: Settlement(const string &name, SettlementType type):name(name),type(type){};
const string  & Settlement::getName() const{return name;};
SettlementType Settlement::getType() const{return type;};
const string Settlement::toString() const{return "settlement<"+name+"><"+settlementTypeToString(type)+">";};

string Settlement::settlementTypeToString(SettlementType type) const{ 
                switch (type) {
                     case SettlementType::VILLAGE: return "0";
                     case SettlementType::CITY: return "1";
                     case SettlementType::METROPOLIS: return "2";
                }
    }