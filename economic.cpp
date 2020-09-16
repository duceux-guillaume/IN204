#include "economic.hpp"

void AgentEconomic::FlamberLaThune(double prix) {
    _argent -= prix;
}

void AgentEconomic::GagnerDeLaThune(double salaire) {
    _argent += salaire;
}

double AgentEconomic::Solde() const {
    return _argent;
}

void Entreprise::Recruter(AgentEconomic const& agent) {
    _salarie.push_back(agent);
}

void Entreprise::Virer(AgentEconomic const& agent) {
    _salarie.pop_back();    
}

double Entreprise::Solde() const {
    return AgentEconomic::Solde() + _autre_banque;
}


Entreprise::Entreprise(double solde_initial, std::string const& den, std::string const& forme, PersonnePhysique const& dirigeant): 
    AgentEconomic(solde_initial/2, den, forme), _salarie(1, dirigeant), _autre_banque(solde_initial/2) {}

std::ostream& operator<<(std::ostream& out, AgentEconomic const& r) {
    out << r.Nom() << " " << r.Forme() << " " << r.Solde();
    return out;
}
