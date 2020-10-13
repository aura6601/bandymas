using namespace std;

#include <iostream>
#include <vector>
#include <numeric>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdio>
#include <sstream> 

#include "isNumber.h"
#include "rezultatai.h"

//#include "rezultatai.h"
//#include "duomenys.h""
//#include "studentas.h"
//#include "rusiavimas.h"

struct duomenys
{
    string vardai;
    string pavardes;
    vector<string> pazymiai;
};

struct studentas
{
    string vardai;
    string pavardes;
    vector<int> pazymiai;
};

struct rusiavimas
{
    string vardai;
    string pavardes;
    double vidurkiai;
    double medianos;
};
//double gal_rez(int egzaminas, vector<int> nd);
double vid(int egzaminas, vector<int> nd);
double gal_mediana(int egzaminas, vector<int> nd);
void spausdinimas(vector<string> vardai, vector<string> pavardes, vector<double> galutinis1, vector<double> galutiniai, vector<double>galutiniai2);

bool palygintiVardus(rusiavimas& a, rusiavimas& b) { return a.vardai < b.vardai; };
bool palygintiPavardes(rusiavimas& a, rusiavimas& b) { return a.pavardes < b.pavardes; };

double vid(int egzaminas, vector<int>nd)
{
    double v;
    v = accumulate(nd.begin(), nd.end(), 0.000) / nd.size();

    return v;
}

//double gal_rez(int egzaminas, vector<int> nd)
//{
  //  double vidurkis, galutinis1;

//    vidurkis = accumulate(nd.begin(), nd.end(), 0.000) / nd.size();
  //  galutinis1 = (0.4 * vidurkis) + (0.6 * egzaminas);

    //return galutinis1;
//}

double gal_mediana(int egzaminas, vector<int> nd)
{
    vector<double> skaiciai;
    for (int i = 0; i < nd.size(); i++) {
        skaiciai.push_back(nd.at(i));
    }

    skaiciai.push_back(egzaminas);

    sort(skaiciai.begin(), skaiciai.end());

    if (skaiciai.size() % 2 == 0)
    {
        return (skaiciai[skaiciai.size() / 2 - 1] + skaiciai[skaiciai.size() / 2]) / 2;
    }
    else
    {
        return skaiciai[skaiciai.size() / 2];
    }
}


int main()
{
    ofstream myfile;
    fstream infile;

    int sk, egzaminas{}, tmp;

    vector<int> nd;
    vector<string> vardai;
    vector<string> pavardes;
    vector<double>galutinis1;
    vector<double> galutiniai;
    vector<double> galutiniai2;

    string vardas, pavarde, vardas_i, pavarde_i;

    int egzaminai;

    string atsakymas;

    cout << "Ar norite,  kad duomenys butu nuskaityti is failo? ('N'-ne/'T'-taip)\n";
    cin >> atsakymas;

    if (atsakymas == "T")
    {
        vector<studentas> studentai;
        vector<duomenys> info;
        vector<int> tikrinimas;

        string failo_pav;

        cout << "Iveskite failo pavadinima: \n";
        cin >> failo_pav;

        infile.open(failo_pav);

        int rows = 0, cols = 0;
        string eilute, reiksme;

        while (getline(infile, eilute)) {
            rows++;
            if (rows == 1)
            {
                stringstream ss(eilute);
                while (ss >> reiksme)
                    cols++;
            }
        }
        infile.close();

        infile.open(failo_pav);

        string rez;
        vector<string> visi_rezultatai_i;
        vector<string> visi_rezultatai;

        if (infile.fail())
        {
            perror(nullptr);
            return 1;
        }
        else
        {

            for (int i = 0; i < 1; i++)
            {
                infile >> vardas_i >> pavarde_i;

                for (int j = 0; j < cols - 2; j++)
                {
                    infile >> rez;
                    visi_rezultatai_i.push_back(rez);
                }

                info.push_back(duomenys{ vardas_i, pavarde_i, visi_rezultatai_i });
                visi_rezultatai_i.clear();

                vector<string>().swap(visi_rezultatai_i);
            }

            for (int i = 1; i < rows; i++)
            {
                infile >> vardas >> pavarde;

                for (int j = 0; j < cols - 2; j++)
                {
                    infile >> rez;
                    visi_rezultatai.push_back(rez);

                    for (int i = 0; i < visi_rezultatai.size(); i++)
                    {
                        if (!isNumber(visi_rezultatai[i]))
                        {
                            cout << "Klaida: faile rezultatu vietose yra raides! \n";
                        }
                        else
                        {
                            tikrinimas.push_back(stoi(visi_rezultatai[i]));
                        }

                        visi_rezultatai.clear();
                        vector<string>().swap(visi_rezultatai);
                    }
                }

                studentai.push_back(studentas{ vardas, pavarde, tikrinimas });

                tikrinimas.clear();
                vector<int>().swap(tikrinimas);
            }

            vector<double> vidurkiai;
            vector<double> medianos;


            for (int i = 0; i < studentai.size(); i++)
            {

                cout << "Skaiciuojama mediana ir vidurkis \n";

                vidurkiai.push_back(gal_rez(studentai[i].pazymiai.back(), studentai[i].pazymiai));
                medianos.push_back(gal_mediana(studentai[i].pazymiai.back(), studentai[i].pazymiai));
            }

            vector<rusiavimas> stud_rus;

            for (int i = 0; i < studentai.size(); i++)
            {
                stud_rus.push_back(rusiavimas{ studentai[i].vardai, studentai[i].pavardes, vidurkiai[i], medianos[i] });
            }

            vidurkiai.clear();
            medianos.clear();
            studentai.clear();
            vector<double>().swap(vidurkiai);
            vector<double>().swap(medianos);
            vector<studentas>().swap(studentai);

            string var;
            cout << "Rusiuoti pagal pavardes ar vardus ? (V/P)";
            cin >> var;

            if (var == "V")
            {
                sort(stud_rus.begin(), stud_rus.end(), palygintiVardus);
            }
            else if (var == "P")
            {
                sort(stud_rus.begin(), stud_rus.end(), palygintiPavardes);
            }

            myfile.open("kursiokai.txt");

            if (myfile.fail())
            {
                perror(nullptr);
                return 1;
            }
            else
            {
                for (int i = 0; i < info.size(); i++)
                {
                    myfile << "Vardas" << setw(25) << "Pavarde" << setw(25) << "Vidurkis" << setw(25) << "Mediana" << "\n";
                }

                for (int i = 0; i < stud_rus.size(); i++)
                {
                    myfile << stud_rus[i].vardai << setw(25) << stud_rus[i].pavardes << setw(25) << stud_rus[i].vidurkiai << setw(25) << stud_rus[i].medianos << "\n";
                }
            }
            myfile.close();
            stud_rus.clear();
            vector<rusiavimas>().swap(stud_rus);
        }
    }
    else if (atsakymas == "N")
    {
        cout << "Iveskite studentu skaiciu: \n";
        cin >> sk;

        if (sk > 0)
        {
            for (int i = 0; i < sk; i++) {

                cout << "Iveskite studento varda: \n";
                cin >> vardas;
                if (isdigit(vardas[i]))
                {
                    cout << "Klaida! Vardas negali buti skaicius\n";
                }
                else {
                    vardai.push_back(vardas);

                    cout << "Iveskite studento pavarde: \n";
                    cin >> pavarde;
                    if (isdigit(pavarde[i]))
                    {
                        cout << "Klaida! Pavarde negali buti skaicius \n";
                    }
                    else
                    {
                        pavardes.push_back(pavarde);

                        cout << "Ar balus sugeneruoti automatiskai? (T/N) \n";
                        string ats;
                        cin >> ats;

                        if (ats == "T") {

                            while (true) {

                                int max = 10;
                                srand(time(0));
                                tmp = rand() % max;
                                nd.push_back(tmp);

                                cout << "Sugeneruotas balas:  " << tmp << "\n";


                                cout << "Ar jau ivesti visi rezulatatai (T/N)? \n";
                                string ats2;
                                cin >> ats2;

                                if (ats2 == "T") {
                                    break;
                                }
                            }
                        }
                        else if (ats == "N") {

                            while (true) {
                                cout << "Iveskite namu darbu rezultatus \n";
                                cin >> tmp;
                                if (tmp > 0 && tmp <= 10)
                                {
                                    nd.push_back(tmp);
                                    cout << "Ar jau ivesti visi rezulatatai (T/N)? \n";
                                    string ats2;
                                    cin >> ats2;

                                    if (ats2 == "T") {
                                        break;
                                    }
                                }
                                else {
                                    cout << "Klaida! Pazimys turi buti 10-baleje sistemoje.\n";
                                }
                            }
                        }
                        else
                        {
                            cout << "Klaida! reikia pasirinkti T arba N";
                        }

                        cout << "Ar egzamino bala sugeneruoti automatiskai? (T/N) \n";
                        string ats2;
                        cin >> ats2;

                        if (ats2 == "T")
                        {
                            int max = 10;
                            srand(time(0));
                            egzaminas = rand() % max;
                            cout << "Egzamino balas  " << egzaminas << "\n";
                        }
                        else if (ats == "N")
                        {
                            cout << "Iveskite egzamino rezultata: \n";
                            cin >> egzaminas;
                            if (egzaminas < 0 || egzaminas > 11)
                            {
                                cout << "Klaida! Egzamino rezultatas turi buti 10-baleje sistemoje.\n";
                            }
                        }
                        else
                        {
                            cout << "Klaida! reikia pasirinkti T arba N";
                        }

                        galutinis1.push_back(gal_rez(egzaminas, nd));

                        galutiniai.push_back(vid(egzaminas, nd));

                        galutiniai2.push_back(gal_mediana(egzaminas, nd));

                        nd.clear();

                    }

                }
            }
        }
        else {
            cout << "Studentu skaicius turi buti teigiamas skaicius \n";
        }

        spausdinimas(vardai, pavardes, galutinis1, galutiniai, galutiniai2);

    }
}

void spausdinimas(vector<string> vardai, vector<string> pavardes, vector<double>galutinis1, vector<double> galutiniai, vector<double> galutiniai2)
{
    cout << setw(10) << "Vardas" << setw(25) << "Pavarde" << setw(25) << "Galutinis" << setw(25) << "Vidurkis" << setw(25) << "Mediana" << endl;
    cout << "---------------------------------------------------------------------------------------------------------\n";
    for (int i = 0; i < vardai.size(); i++) {

        cout << setw(5) << vardai[i] << setw(25) << pavardes[i] << setw(25) << galutinis1[i] << setw(25) << galutiniai[i] << setw(25) << galutiniai2[i] << endl;

    }
}

