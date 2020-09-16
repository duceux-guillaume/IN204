#ifndef ECONOMIC_HPP
#define ECONOMIC_HPP

#include <iostream>
#include <vector>

class AgentEconomic
{
private:
    std::string _denomination;

protected:
    double _argent;
    std::string _forme;

public:
    AgentEconomic(double solde_initial, std::string const &den, std::string const &forme) : _argent(solde_initial), _denomination(den), _forme(forme) {}
    AgentEconomic(std::string const &den, std::string const &forme) : _argent(0), _denomination(den), _forme(forme) {}

    void FlamberLaThune(double quantite);
    void GagnerDeLaThune(double salaire);

    virtual double Solde() const;

    std::string const &Nom() const
    {
        return _denomination;
    }

    std::string const &Forme() const
    {
        return _forme;
    }

        ~AgentEconomic() {
        std::cout << "destructor AgentEconomic" << std::endl;
    }
};

class PersonnePhysique : public AgentEconomic
{
public:
    PersonnePhysique(double solde, std::string const &nom) : AgentEconomic(nom, "Personne Physique")
    {
        _argent = 0;
    }
};

class Entreprise : public AgentEconomic
{
protected:
    std::vector<AgentEconomic> _salarie;
    double _autre_banque;

public:
    Entreprise(double solde_initial, std::string const &den, std::string const &forme, PersonnePhysique const &dirigeant);
    void Recruter(AgentEconomic const &agent);
    void Virer(AgentEconomic const &agent);

    double Solde() const override;
    ~Entreprise() {
        std::cout << "destructor Entreprise" << std::endl;
    }
};

class Association : public Entreprise
{
public:
    Association(double solde_initial, std::string const &den, std::string const &forme, PersonnePhysique const &dirigeant) : Entreprise(solde_initial, den, forme, dirigeant) {}
};

std::ostream &operator<<(std::ostream &out, AgentEconomic const &r);


#endif // !ECONOMIC_HPP
