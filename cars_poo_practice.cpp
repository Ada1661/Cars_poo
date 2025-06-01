#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <cmath>

// Clasa de baza abstracta pentru orice tip de masina
class Masina {
protected:
    int an_productie;
    std::string nume_model;
    int viteza_max;
    float greutate;

public:
    Masina() : an_productie(0), nume_model(""), viteza_max(0), greutate(0.0f) {}

    Masina(const int& an_productie,
        const std::string& nume_model,
        const int& viteza_max,
        const float& greutate)
        : an_productie(an_productie),
        nume_model(nume_model),
        viteza_max(viteza_max),
        greutate(greutate)
    {}

    // Metoda pura: fiecare subclasa trebuie sa implementeze calculul autonomiei
    virtual float autonomie() const = 0;

    // Citire a atributelor comune tuturor masinilor
    virtual void citire() {
        std::cout << "Introdu datele comune ale masinii:\n";
        std::cout << "  Anul inceperii productiei: ";
        std::cin >> an_productie;
        std::cout << "  Numele modelului (fara spatii): ";
        std::cin >> nume_model;
        std::cout << "  Viteza maxima (km/h): ";
        std::cin >> viteza_max;
        std::cout << "  Greutatea (kg): ";
        std::cin >> greutate;
    }

    // Afisare a atributelor comune
    virtual void afiseaza() const {
        std::cout << "Anul inceperii productiei: " << an_productie << "\n";
        std::cout << "Numele modelului: " << nume_model << "\n";
        std::cout << "Viteza maxima: " << viteza_max << " km/h\n";
        std::cout << "Greutatea: " << greutate << " kg\n";
    }

    // Getteri
    int get_an_productie() const { return an_productie; }
    int get_viteza_max() const { return viteza_max; }
    float get_greutate() const { return greutate; }
    std::string get_nume_model() const { return nume_model; }

    // Setter pentru viteza maxima (necesar la optimizare)
    void set_viteza_max(int noua_viteza) { viteza_max = noua_viteza; }

    virtual ~Masina() {}
};


// Subclasa pentru masinile cu combustibil fosil
class Masina_combustibil_fosil : virtual public Masina {
protected:
    std::string tip_combustibil;
    float capacitate_rezervor; // in litri

public:
    Masina_combustibil_fosil()
        : Masina(),
        tip_combustibil(""),
        capacitate_rezervor(0.0f)
    {}

    Masina_combustibil_fosil(const int& an_productie,
        const std::string& nume_model,
        const int& viteza_max,
        const float& greutate,
        const std::string& tip_combustibil,
        const float& capacitate_rezervor)
        : Masina(an_productie, nume_model, viteza_max, greutate),
        tip_combustibil(tip_combustibil),
        capacitate_rezervor(capacitate_rezervor)
    {}

    // Autonomia pentru masina pe combustibil: sqrt(greutate) * capacitate_rezervor
    float autonomie() const override {
        return std::sqrt(greutate) * capacitate_rezervor;
    }

    // Citire campuri specifice masinii cu combustibil fosil
    void citire() override {
        Masina::citire();
        std::cout << "  Tip combustibil (benzina/motorina, fara spatii): ";
        std::cin >> tip_combustibil;
        std::cout << "  Capacitate rezervor (litri): ";
        std::cin >> capacitate_rezervor;
    }

    // Afisare campuri specifice + autonomie
    void afiseaza() const override {
        Masina::afiseaza();
        std::cout << "Tip combustibil: " << tip_combustibil << "\n";
        std::cout << "Capacitate rezervor: " << capacitate_rezervor << " litri\n";
        std::cout << "Autonomie (combustibil): " << autonomie() << "\n";
    }

    virtual ~Masina_combustibil_fosil() {}
};


// Subclasa pentru masinile electrice
class Masina_electrica : virtual public Masina {
protected:
    float capacitate_baterie; // in kWh

public:
    Masina_electrica()
        : Masina(),
        capacitate_baterie(0.0f)
    {}

    Masina_electrica(const int& an_productie,
        const std::string& nume_model,
        const int& viteza_max,
        const float& greutate,
        const float& capacitate_baterie)
        : Masina(an_productie, nume_model, viteza_max, greutate),
        capacitate_baterie(capacitate_baterie)
    {}

    // Autonomia pentru masina electrica: capacitate_baterie * greutate^2
    float autonomie() const override {
        return capacitate_baterie * greutate * greutate;
    }

    // Citire campuri specifice masinii electrice
    void citire() override {
        Masina::citire();
        std::cout << "  Capacitate baterie (kWh): ";
        std::cin >> capacitate_baterie;
    }

    // Afisare campuri specifice + autonomie
    void afiseaza() const override {
        Masina::afiseaza();
        std::cout << "Capacitate baterie: " << capacitate_baterie << " kWh\n";
        std::cout << "Autonomie (electrica): " << autonomie() << "\n";
    }

    virtual ~Masina_electrica() {}
};


// Subclasa pentru masinile hibride (combustibil + electric)
class Masina_hibrida : public Masina_combustibil_fosil, public Masina_electrica {
public:
    Masina_hibrida()
        : Masina(), Masina_combustibil_fosil(), Masina_electrica()
    {}

    Masina_hibrida(const int& an_productie,
        const std::string& nume_model,
        const int& viteza_max,
        const float& greutate,
        const std::string& tip_combustibil,
        const float& capacitate_rezervor,
        const float& capacitate_baterie)
        : Masina(an_productie, nume_model, viteza_max, greutate),
        Masina_combustibil_fosil(an_productie, nume_model, viteza_max, greutate, tip_combustibil, capacitate_rezervor),
        Masina_electrica(an_productie, nume_model, viteza_max, greutate, capacitate_baterie)
    {}

    // Autonomia hibrida = autonomie combustibil + autonomie electrica
    float autonomie() const override {
        return Masina_combustibil_fosil::autonomie() + Masina_electrica::autonomie();
    }

    // Citire campuri pentru masina hibrida (apeleaza intai la clasa de combustibil)
    void citire() override {
        Masina_combustibil_fosil::citire();
        std::cout << "  Capacitate baterie (kWh): ";
        std::cin >> capacitate_baterie;
    }

    // Afisare campuri specifice + autonomie
    void afiseaza() const override {
        Masina_combustibil_fosil::afiseaza();
        std::cout << "Capacitate baterie: " << capacitate_baterie << " kWh\n";
        std::cout << "Autonomie (hibrida): " << autonomie() << "\n";
    }

    virtual ~Masina_hibrida() {}
};


// Clasa pentru gestionarea unui sistem de masini si tranzactii
class Sistem_gestionare {
    std::vector<std::shared_ptr<Masina>> masini;
    std::vector<std::string> tranzactii;

public:
    // Adauga o masina (orice obiect derivat din Masina)
    void adauga_masina(const std::shared_ptr<Masina>& masina) {
        masini.push_back(masina);
    }

    // Adauga o tranzactie simpla (doar un string)
    void adauga_tranzactie(const std::string& tranzactie) {
        tranzactii.push_back(tranzactie);
    }

    // Returneaza primul model adaugat (exemplu de "cel mai vandut")
    std::shared_ptr<Masina> cel_mai_vandut_model() const {
        if (masini.empty())
            return nullptr;
        return masini.front();
    }

    // Returneaza modelul cu autonomia maxima
    std::shared_ptr<Masina> model_cu_autonomie_maxima() const {
        if (masini.empty())
            return nullptr;
        return *std::max_element(
            masini.begin(), masini.end(),
            [](const std::shared_ptr<Masina>& a, const std::shared_ptr<Masina>& b) {
                return a->autonomie() < b->autonomie();
            }
        );
    }

    // Creste viteza maxima a unui model cu un procent dat
    void optimizeaza_viteza(const std::string& nume_model, int procent) {
        for (auto& masina : masini) {
            if (masina->get_nume_model() == nume_model) {
                int viteza_curenta = masina->get_viteza_max();
                int noua_viteza = static_cast<int>(viteza_curenta * (1.0f + procent / 100.0f));
                masina->set_viteza_max(noua_viteza);
                std::cout << "Viteza maxima a modelului \""
                    << nume_model
                    << "\" a fost actualizata de la "
                    << viteza_curenta
                    << " km/h la "
                    << noua_viteza
                    << " km/h.\n";
                return;
            }
        }
        std::cout << "Model \"" << nume_model << "\" nu a fost gasit in sistem.\n";
    }

    // Afiseaza toate masinile din sistem
    void afiseaza_toate_masini() const {
        if (masini.empty()) {
            std::cout << "Nu exista masini in sistem.\n";
            return;
        }
        std::cout << "\n----- Lista masini din sistem -----\n";
        for (const auto& masina : masini) {
            masina->afiseaza();
            std::cout << "-----------------------------------\n";
        }
    }
};


int main() {
    Sistem_gestionare sistem;
    bool ruleaza = true;

    // Loop principal: utilizatorul poate adauga diferite tipuri de masini
    while (ruleaza) {
        std::cout << "\nAlegeti tipul de masina pe care doriti sa o adaugati:\n";
        std::cout << "  1. Masina combustibil fosil\n";
        std::cout << "  2. Masina electrica\n";
        std::cout << "  3. Masina hibrida\n";
        std::cout << "  4. Iesire si afisare rezultate\n";
        std::cout << "Optiunea dvs: ";

        int optiune;
        std::cin >> optiune;

        switch (optiune) {
        case 1: {
            // Citire si adaugare masina combustibil fosil
            auto m = std::make_shared<Masina_combustibil_fosil>();
            std::cout << "\nCitire masina pe combustibil fosil:\n";
            m->citire();  // va intreba si tip_combustibil, capacitate_rezervor
            sistem.adauga_masina(m);
            std::cout << "Masina pe combustibil fosil adaugata cu succes.\n";
            break;
        }
        case 2: {
            // Citire si adaugare masina electrica
            auto m = std::make_shared<Masina_electrica>();
            std::cout << "\nCitire masina electrica:\n";
            m->citire();  // va intreba capacitate_baterie dupa campurile comune
            sistem.adauga_masina(m);
            std::cout << "Masina electrica adaugata cu succes.\n";
            break;
        }
        case 3: {
            // Citire si adaugare masina hibrida
            auto m = std::make_shared<Masina_hibrida>();
            std::cout << "\nCitire masina hibrida:\n";
            m->citire();
            // citire() pentru hibrid va intreba si campurile din combustibil, apoi capacitate baterie
            sistem.adauga_masina(m);
            std::cout << "Masina hibrida adaugata cu succes.\n";
            break;
        }
        case 4: {
            // Terminare adaugari si afisare rapoarte
            ruleaza = false;
            break;
        }
        default: {
            std::cout << "Optiune invalida. Incercati din nou.\n";
            break;
        }
        }
    }

    // Afisare toate masinile adaugate
    sistem.afiseaza_toate_masini();

    // Afisare model cu autonomia maxima
    auto best_auto = sistem.model_cu_autonomie_maxima();
    if (best_auto) {
        std::cout << "\nModelul cu autonomia maxima este: "
            << best_auto->get_nume_model()
            << " cu autonomie = "
            << best_auto->autonomie()
            << "\n";
    }

    // Optimizare viteza pentru un model ales de utilizator
    std::cout << "\nOptimizare viteza pentru un model.\n";
    std::string model_de_optimizat;
    int procent_optimizare;
    std::cout << "Introdu numele modelului (fara spatii), de ex. FordFocus: ";
    std::cin >> model_de_optimizat;
    std::cout << "Introdu procentul de crestere a vitezei (ex: 10 pentru +10%): ";
    std::cin >> procent_optimizare;
    sistem.optimizeaza_viteza(model_de_optimizat, procent_optimizare);

    // Afisare masini dupa optimizare
    sistem.afiseaza_toate_masini();

    return 0;
}
