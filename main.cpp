#include <iostream>
#include <cstring>
#include <string>
#include <vector>
class Jucatori{
private:
    std::string  nume;
    int salariu_club;
    int salariu_sponsor;
public:


    Jucatori(std::string nume="", int salariu=0, int salariu_sponsor=0, int salariu_total=0) {
        this->nume = nume;
        this->salariu_club= salariu;
        this->salariu_sponsor=salariu_sponsor;

    }


    ~Jucatori() {


    }


    Jucatori (const Jucatori &juc)
    {
        this->nume=juc.nume;
        this->salariu_club=juc.salariu_club;
        this->salariu_sponsor=juc.salariu_sponsor;
    }


    //Constructor de afisare
    friend std::ostream &operator<<(std::ostream &os, const Jucatori &jucatori) {
        os << "Nume: " << jucatori.nume << "| Salariu Club: " << jucatori.salariu_club << "| Salariu Sponsor:"<<jucatori.salariu_sponsor ;
        return os;
    }

    //Constructor de citire

    friend std::istream& operator>>(std::istream& is, Jucatori& other)
    {
        std::cout<<"Nume: ";
        is >> other.nume;
        std::cout<<"Salariu Club: ";
        is >> other.salariu_club;
        std::cout<<"Salariu sponsor: ";
        is >> other.salariu_sponsor;
        return is;
    }

    //operatori de atribuire
    Jucatori& operator=(const Jucatori& other)
    {

        this->nume = other.nume;
        this->salariu_club=other.salariu_club;

        this->salariu_sponsor=other.salariu_sponsor;
        return *this;


    }

    //functie de afisare
    void afis()
    {
        std::cout<<"Nume: "<<nume<<" , Salariu Club: "<< salariu_club<<"Salariu_sponsor : "<<salariu_sponsor<<std::endl;
    }

    const std::string &getNumeJucator() const
    {
        return nume;
    }

    const int &getSalariu() const
    {
        return salariu_club;
    }






};

class Staff{
private:
    std::string Meserie;
    std::string Nume;
    int Salariu;
public:
    Staff(const std::string &meserie="", const std::string &nume="", int salariu=0) : Meserie(meserie), Nume(nume),
    Salariu(salariu) {}

    virtual ~Staff() {}

    friend std::istream &operator>>(std::istream &is, Staff &staff)
    {
        std::cout<<"Meseria: "<<std::endl;
        is >> staff.Meserie;
        std::cout<<"Nume: "<<std::endl;
        is >> staff.Nume;
        std::cout<<"Salariu: "<<std::endl;
        is >> staff.Salariu;

        return is;
    }


    friend std::ostream &operator<<(std::ostream &out, const Staff &staff)
    {
        out << "Meseria: " << staff.Meserie;
        out << " | Nume: " << staff.Nume;
        out << " | Salariu" << staff.Salariu;

        return out;
    }

    const int &getSalariu() const
    {
        return Salariu;
    }

};
class Echipe{
private:

    std::string NumeEchipa;
    std::string Antrenor;
    int SalariuAntrenor;
    std::vector<Staff> staff;
    int NumarStaff;
    int NumarJucatori;
    std::vector<Jucatori> jucatori;

public:

    Echipe(const std::string numeEchipa="",const std::string antrenor="",int salariu_antrenor=0,const std::vector<Staff>& staff={},int Numar_staf=0, int numarJucatori=0, const std::vector<Jucatori>& jucatori={}) : NumeEchipa(
            numeEchipa),Antrenor(antrenor),SalariuAntrenor(salariu_antrenor),staff(staff),NumarStaff(Numar_staf), NumarJucatori(numarJucatori),jucatori(jucatori)  {}

    ~Echipe() {

    }

    //constructor de afisare
    friend std::ostream &operator<<(std::ostream  &out, const Echipe &echipe)
    {
        out << "Numele echipei: " << echipe.NumeEchipa << std::endl;
        out << "Antrenor: "<< echipe.Antrenor<<" | Salariu:"<<echipe.SalariuAntrenor<<std::endl;

        if(echipe.NumarStaff>0)
        out << "Staff: "<<std::endl;
        for(int i=0;i<echipe.NumarStaff;i++)
            out << echipe.staff[i] << std::endl;

        if(echipe.NumarJucatori>0)
        {   out<<"Jucatori: "<<std::endl;
            for (int i = 0; i < echipe.NumarJucatori; i++)
                out << echipe.jucatori[i] << std::endl;
        }
        return out;
    }

    //constructor de citire
    friend std::istream& operator>>(std::istream& is, Echipe& other)
    {
        std::cout<<"Nume Echipa: ";
        is>> other.NumeEchipa;
        return is;

    }

    //Angajarea unui nou jucator
    void AdaugareJucator(const Jucatori &jucator)
    {
        NumarJucatori++;
        jucatori.push_back(jucator);
    }

    //concedierea unui jucator
    void ConcediereJucator(const std::string &ConcediereJucator)
    {
        for(int i=0;i<NumarJucatori;i++)
            if(jucatori[i].getNumeJucator() == ConcediereJucator)
            {
                jucatori.erase(jucatori.begin()+i);
                NumarJucatori--;
                break;
            }
    }

    //Transferul unui jucator de la o echipa la alta
    void TransferJucator(Echipe &echipa, const Jucatori &jucator)
    {
        echipa.AdaugareJucator(jucator);
        this->ConcediereJucator(jucator.getNumeJucator());

    }
    //Suma salarilor staffului
    int BugetStaff()
    {
        int s;
        s=0;
        for(int i=0;i<NumarStaff;i++)
            s=s+staff[i].getSalariu();

        return s;
    }

    //Suma salarilor angajatilor din club
    int BugetSalarii()
    {
        int s;
        s=SalariuAntrenor+this->BugetStaff();
        for(int i=0;i<NumarJucatori;i++)
            s=s+jucatori[i].getSalariu();

        return s;
    }

    void SchimbareAntrenor(const std::string &NumeAntrenor,const int &salariu)
    {
        Antrenor=NumeAntrenor;
        SalariuAntrenor=salariu;
    }

    void SchimbareSalariuAntrnor(const int &salariu)
    {
        SalariuAntrenor=salariu;
    }

    const int &getSalariuAntrenor() const
    {
        return SalariuAntrenor;
    }

    const std::string &getNumeleAntrenorului() const
    {
        return Antrenor;
    }




};
void meniu()
{
    std::cout<<"1.Antrenor"<<std::endl;
    std::cout<<"2.Staff"<<std::endl;
    std::cout<<"3.Jucatori"<<std::endl;
    std::cout<<"4.Afisare Echipa"<<std::endl;
    std::cout<<"5.Iesi din aplicatie"<<std::endl<<std::endl;
    std::cout<<"Alege:"<<std::endl;
}
int main() {

    Echipe echipa;


    int alg;
    bool m= true;
    std::cin>>echipa;
    while (m)
    {

        meniu();
        std::cin>>alg;
        switch (alg)
        {

            case 1:{

                        int alg1;
                        bool n= true;
                        while(n)
                        {
                            std::cout<<"1.Angajare antrenor"<<std::endl;
                            std::cout<<"2.Schimbare antrenor"<<std::endl;
                            std::cout<<"3.Schimbare salariu antrenor"<<std::endl;
                            std::cout<<"4.Afisare salariu antrenor"<<std::endl;
                            std::cout<<"5.Afisare nume antrenor"<<std::endl;
                            std::cout<<"6.Inapoi"<<std::endl<<std::endl;
                            std::cout<<"Alege: "<<std::endl;
                            std::cin>>alg1;
                            switch (alg1)
                            {
                                case 1:
                                {
                                    std::string a;
                                    int b;
                                    std::cout<<"Numele antrenorului: ";
                                    std::cin>>a;
                                    std::cout<<"Salariu antrenor:";
                                    std::cin>>b;
                                    echipa.SchimbareAntrenor(a,b);
                                    break;
                                }
                                case 2:
                                {
                                    std::string a;
                                    int b;
                                    std::cout<<"Numele noului antrenorului: ";
                                    std::cin>>a;
                                    std::cout<<"Salariu noului antrenor:";
                                    std::cin>>b;
                                    echipa.SchimbareAntrenor(a,b);
                                    break;
                                }
                                case 3:
                                {
                                    std::cout<<"Noul salariu al antrenorului:";
                                    int a;
                                    std::cin>>a;
                                    echipa.SchimbareSalariuAntrnor(a);
                                    break;

                                }
                                case 4:
                                {
                                    if(echipa.getSalariuAntrenor()==0)
                                    {
                                        std::cout<<"Echipa nu are un antrenor"<<std::endl;
                                        break;

                                    }


                                    std::cout<<echipa.getSalariuAntrenor()<<std::endl;
                                    break;
                                }
                                case 5:
                                {
                                    std::cout<<echipa.getNumeleAntrenorului()<<std::endl;
                                    break;
                                }
                                case 6:
                                {
                                    n= false;
                                    break;
                                }

                            }
                        }

                    }
            case 2:
            {

            }
            case 3:
            {

            }
            case 4:
            {
                std::cout<<echipa;
                break;
            }
            case 5:
            {
                m= false;
                break;
            }


        }

    }

//    Jucatori juc1("Toma",100,100);
//    Jucatori juc2("ana",100,100);
//    Jucatori juc3("raluca",100,100);
//
//    Staff staff1("Bucatar","Ion",30);
//    Staff staff2("Preparator Fizic","Eduard",20);
//    Staff staff3("Naturist","Matei",45);
//
//
//
//    Echipe echipa2("Steaus","Iordanescu",1000,{staff1,staff2,staff3},3,3, {juc1,juc2,juc3});
//    Echipe echipa1("arsenal","ronaldo",1000,{staff1,staff2},2,2,{juc2,juc3});
//    echipa2.TransferJucator(echipa1,juc1);
//    std::cout<<echipa2;
//    std::cout<<echipa1;
//    std::cout << echipa1.BugetSalarii()<<std::endl;
//    echipa1.SchimbareAntrenor("Beligoool",10);
//    std::cout<<echipa1;
//    std::cout<<echipa1.BugetStaff();
//
//    Echipe ech;
//    std::cin>>ech;
//    ech.AdaugareJucator(juc1);
//    ech.SchimbareAntrenor("Marian",110);
//    std::cout<<ech;
//
//
//
//
//
//
//
//
//
//

    return 0;
}