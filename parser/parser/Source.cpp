
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>

struct Vote {
    Vote(char US_p, char Ch_p, char Custom_p, std::string Name) {
        US = US_p;
        Ch = Ch_p;
        Custom = Custom_p;
        ResolutionName = Name;
    }
public:
    char US;
    char Ch;
    char Custom;
    std::string ResolutionName;
};

std::vector <Vote> Read(std::string custom, bool& error) {
    std::vector <Vote> VoteMasiv;
    std::ifstream file("out.txt");
    if (file) {
        char skip;
        char US;
        char Ch;
        char Custom;
        std::string line;
        std::string name;
        bool flag = false;
        while (!file.eof()) {
            file >> skip;
            file >> skip;
            std::getline(file, line, '/');
            name = line;
            std::getline(file, line, '"');
            size_t pos = line.find("CHINA");
            Ch = line[pos - 2];
            pos = line.find("UNITED STATES");
            US = line[pos - 2];
            pos = line.find(custom);
            if (pos > 100000000000) { flag = true; }
            else {
                Custom = line[pos - 2];
                Vote NewVote = Vote(US, Ch, Custom, name);
                VoteMasiv.push_back(NewVote);
            }
            if (flag) { std::getline(file, line, '$'); file >> skip; std::cout << "Ошибка чтения" << std::endl; error = true; }
        }
    }
    else error = true;
    return VoteMasiv;
}

int main()
{
    bool loading = false;
    int menu = 0;
    setlocale(LC_ALL, "Russian");


    while (menu != 3) {
        std::cout << "\n1.Парсинг \n2.Анализ страны \n3.Выход \n";
        std::cin >> menu;
        std::wcout << "\n";
        if (menu == 1) {
            system("main.exe");
        }
        if (menu == 2) {
            std::cout << "Введите название страны: \n";
            std::string country;
            std::cin >> country;
            bool errorcheck = false;
            std::vector <Vote> VoteMasiv = Read(country, errorcheck);
            if (country == "AFGHANISTAN" or errorcheck) { std::cout << "Невозможно прочитать"; return 0; }
            double USScore = 0;
            double ChScore = 0;
            for (int i = 0; i < VoteMasiv.size(); i++) {
                if ((VoteMasiv[i].US == 'Y') and (VoteMasiv[i].Ch == 'N'))
                {
                    if (VoteMasiv[i].Custom == 'Y') USScore++;
                    if (VoteMasiv[i].Custom == 'N') ChScore++;
                }
                if ((VoteMasiv[i].US == 'N') and (VoteMasiv[i].Ch == 'Y'))
                {
                    if (VoteMasiv[i].Custom == 'N') USScore++;
                    if (VoteMasiv[i].Custom == 'Y') ChScore++;
                }
                if ((VoteMasiv[i].US == 'Y') and (VoteMasiv[i].Ch == 'Y'))
                {
                    if (VoteMasiv[i].Custom == 'N') { USScore--; ChScore--; }
                    if (VoteMasiv[i].Custom == 'Y') { USScore++; ChScore++; }
                    if (VoteMasiv[i].Custom == 'A') { USScore = USScore - 0.5; ChScore = ChScore - 0.5; }
                }
                if ((VoteMasiv[i].US == 'N') and (VoteMasiv[i].Ch == 'N'))
                {
                    if (VoteMasiv[i].Custom == 'N') { USScore++; ChScore++; }
                    if (VoteMasiv[i].Custom == 'Y') { USScore--; ChScore--; }
                    if (VoteMasiv[i].Custom == 'A') { USScore = USScore - 0.5; ChScore = ChScore - 0.5; }
                }
                if ((VoteMasiv[i].US == 'A') and (VoteMasiv[i].Ch == 'Y'))
                {
                    if (VoteMasiv[i].Custom == 'N') { ChScore--; }
                    if (VoteMasiv[i].Custom == 'Y') { ChScore++; }
                    if (VoteMasiv[i].Custom == 'A') { USScore++; }
                }
                if ((VoteMasiv[i].US == 'A') and (VoteMasiv[i].Ch == 'N'))
                {
                    if (VoteMasiv[i].Custom == 'N') { ChScore++; }
                    if (VoteMasiv[i].Custom == 'Y') { ChScore--; }
                    if (VoteMasiv[i].Custom == 'A') { USScore++; }
                }
                if ((VoteMasiv[i].US == 'N') and (VoteMasiv[i].Ch == 'A'))
                {
                    if (VoteMasiv[i].Custom == 'N') { USScore++; }
                    if (VoteMasiv[i].Custom == 'Y') { USScore--; }
                    if (VoteMasiv[i].Custom == 'A') { ChScore++; }
                }
                if ((VoteMasiv[i].US == 'Y') and (VoteMasiv[i].Ch == 'A'))
                {
                    if (VoteMasiv[i].Custom == 'N') { USScore--; }
                    if (VoteMasiv[i].Custom == 'Y') { USScore++; }
                    if (VoteMasiv[i].Custom == 'A') { ChScore++; }
                }
                if ((VoteMasiv[i].US == 'Y') and (VoteMasiv[i].Ch == ' '))
                {
                    if (VoteMasiv[i].Custom == 'N') { USScore--; }
                    if (VoteMasiv[i].Custom == 'A') { USScore = USScore - 0.5; }
                    if (VoteMasiv[i].Custom == 'Y') { USScore++; }
                }
                if ((VoteMasiv[i].US == 'N') and (VoteMasiv[i].Ch == ' '))
                {
                    if (VoteMasiv[i].Custom == 'N') { USScore++; }
                    if (VoteMasiv[i].Custom == 'A') { USScore = USScore - 0.5; }
                    if (VoteMasiv[i].Custom == 'Y') { USScore--; }
                }
                if ((VoteMasiv[i].US == ' ') and (VoteMasiv[i].Ch == 'Y'))
                {
                    if (VoteMasiv[i].Custom == 'N') { ChScore++; }
                    if (VoteMasiv[i].Custom == 'A') { ChScore = ChScore - 0.5; }
                    if (VoteMasiv[i].Custom == 'Y') { ChScore--; }
                }
                if ((VoteMasiv[i].US == ' ') and (VoteMasiv[i].Ch == 'N'))
                {
                    if (VoteMasiv[i].Custom == 'N') { ChScore--; }
                    if (VoteMasiv[i].Custom == 'A') { ChScore = ChScore - 0.5; }
                    if (VoteMasiv[i].Custom == 'Y') { ChScore++; }
                }
            }
            std::string Output = " |-----|-----|";
            std::string OutputLow = "US    Mid   China";
            std::cout << "Близость к США =" << USScore << std::endl;
            std::cout << "Близость к Китаю =" << ChScore << std::endl;
            Output.find("ANGOLA");
            double Score = USScore - ChScore;
            if (Score > 0) {
                Score = std::round(Score / 10);
                Output[1 + (6 - Score)] = 'V';
            }
            else if (Score < 0) {
                Score = std::round(Score / 10);
                Score = Score * (-1);
                Output[7 + Score] = 'V';
            }
            else if (Score == 0) {
                Output[7] = 'V';
            }

            std::cout << Output << std::endl;
            std::cout << OutputLow << std::endl;
        }
    }
}