#include <iostream>
#include <string>
#include "naive_bayes.h"
#include "preprocessing.h"
#include "defines.h"
#include <iomanip>
#include <random>
#include "LaLigaFix.h"
#include "SeriaAFix.h"
#include "EPLFix.h"
#include "BundesLigaFix.h"
//using namespace std;

int main()
{
    bool train = true;
    std::cout << "---Octopus---" << std::endl;
    std::cout << "-------------" << std::endl;
/*
    //std::vector<std::string> PSLTeams{"CHIEFS","PLKCITY","WITS","SUNDOWNS","HPARK","SSU","ARROWS","PIRATES","CELTIC","CPTC","BAROKA","LEOPARDS","MARITZBURG","STELLENBOSCH","CHIPPA","AMAZULU"};
    //CHIEFS - 4PLKCITY - 11WITS - 15SUNDOWNS - 14HPARK - 7SSU - 12ARROWS - 1PIRATES - 10CELTIC - 3CPTC - 6BAROKA - 2LEOPARDS - 8MARITZBURG - 9STELLENBOSCH - 13CHIPPA - 5AMAZULU - 0

    //std::vector<std::string> GERTeams{"BAYERNM","LEIPZIG","FREIBURG","SCHALKE","MONCHENGLADBACH","LEVERKUSEN","WOLFS","DORTMUND","FRANKFURT",
                                      //"HERTHABERLIN","WERDER","HOFFENHEIM","AUGSBURG","DUSSELDORF","UNIONBERLIN","MAINZ","FCKOLN","PADERBORN"};
    //BAYERNM - 1LEIPZIG - 9FREIBURG - 6SCHALKE - 14MONCHENGLADBACH - 12LEVERKUSEN - 10WOLFS - 17DORTMUND - 2FRANKFURT - 5HERTHABERLIN - 7WERDER - 16HOFFENHEIM - 8
    //AUGSBURG - 0DUSSELDORF - 3UNIONBERLIN - 15MAINZ - 11FCKOLN - 4PADERBORN - 13

    //std::vector<std::string> ENGTeams{"LIVERPOOL","MANCITY","LEICESTER","ARSENAL","WHUTD","TOTTENHAM","CHELSEA","BOURNEMOUTH","CPALACE","MANUTD",
                                      //"BURNELY","SHEFFIELD","WOLVES","SOUTHAMPTON","EVERTON","BHA","NORWICH","AVILLA","NEWCASTLE","WATFORD"};
    //LIVERPOOL - 9MANCITY - 10LEICESTER - 8ARSENAL - 0WHUTD - 18TOTTENHAM - 16CHELSEA - 5BOURNEMOUTH - 3CPALACE - 6MANUTD - 11
    //BURNELY - 4SHEFFIELD - 14WOLVES - 19SOUTHAMPTON - 15EVERTON - 7BHA - 2NORWICH - 13AVILLA - 1NEWCASTLE - 12WATFORD - 17

    //std::vector<std::string> SPATeams{"RMADRID","GRANADA","AMADRID","BARCELONA","RSOCIEDAD","SEVILLA","ABILBAO","VILLAREAL","VALENCIA","RVALLADOLID",
                                      //"EIBAR","LEVANTE","OSASUNA","ALAVES","RBETIS","GETAFE","CELTA","ESPANYOL","MALLORCA","LEGANES"};
    //RMADRID - 14GRANADA - 8AMADRID - 2BARCELONA - 3RSOCIEDAD - 15SEVILLA - 17ABILBAO - 0VILLAREAL - 19VALENCIA - 18RVALLADOLID - 16
    //EIBAR - 5LEVANTE - 10OSASUNA - 12ALAVES - 1RBETIS - 13GETAFE - 7CELTA - 4ESPANYOL - 6MALLORCA - 11LEGANES - 9

    //std::vector<std::string> ITATeams{"INTER","JUVENTUS","ATALANTA","NAPOLI","ROMA","LAZIO","CAGLIARI","PARMA","TORINO","FIORENTINA",
                                      //"BOLOGNA","UDINESE","SASSUOLO","VERONA","BRESCIA","ACMILAN","LECCE","GENOA","SPAL","SAMPDORIA"};
    //INTER - 7JUVENTUS - 8ATALANTA - 1NAPOLI - 11ROMA - 13LAZIO - 9CAGLIARI - 4PARMA - 12TORINO - 17FIORENTINA - 5
    //BOLOGNA - 2UDINESE - 18SASSUOLO - 15VERONA - 19BRESCIA - 3ACMILAN - 0LECCE - 10GENOA - 6SPAL - 16SAMPDORIA - 14

    LabelEncoder<std::string> encoder(ITATeams);
    std::vector<unsigned long int> numerical_data = encoder.fit_transorm();
    for(int i = 0; i < ITATeams.size(); i++)
    {
        std::cout << ITATeams[i] << " - " << numerical_data[i] << "\n";
    }

    return 0;
*/

/*
    std::string FnamePT;
    std::vector<unsigned long int> YLabels;
    std::vector<std::vector<double>> XPT;
    XPT = {
            {ROMA,4,1.30,2.82,1.90,6,ATALANTA},{FIORENTINA,20,0.70,2.99,3.66,19,SAMPDORIA},{GENOA,14,1.40,2.51,1.94,7,BOLOGNA},{INTER,2,1.03,2.52,2.79,5,LAZIO},{PARMA,16,1.74,2.45,1.59,8,SASSUOLO},{NAPOLI,3,0.19,6.85,13.34,9,CAGLIARI},{SPAL,17,1.05,2.53,2.69,18,LECCE},{TORINO,10,1.48,2.23,2.06,12,ACMILAN},
{JUVENTUS,2,0.30,4.57,9.86,19,SPAL},{SAMPDORIA,20,3.93,2.96,0.68,1,INTER},{SASSUOLO,10,2.28,2.70,1.15,3,ATALANTA},{NAPOLI,6,0.21,6.51,11.63,14,BRESCIA},{LAZIO,9,0.48,3.81,4.99,15,GENOA},{LECCE,12,3.96,3.48,0.62,7,ROMA},{UDINESE,18,1.90,2.29,1.55,8,BOLOGNA},{CAGLIARI,4,1.20,2.28,2.55,16,VERONA},{ACMILAN,13,1.23,2.25,2.50,17,FIORENTINA},{PARMA,11,2.12,2.35,1.37,5,TORINO},
{SPAL,19,1.34,2.35,2.17,8,PARMA},{VERONA,14,1.58,2.32,1.85,20,SAMPDORIA},{GENOA,18,1.87,2.27,1.59,16,ACMILAN},{FIORENTINA,10,0.56,3.07,4.81,12,UDINESE},{ROMA,5,0.42,4.04,5.75,7,CAGLIARI},{ATALANTA,3,0.28,5.01,9.49,17,LECCE},{BOLOGNA,11,2.17,2.64,1.22,6,LAZIO},{TORINO,9,2.84,2.77,0.92,4,NAPOLI},{INTER,1,1.68,2.18,1.82,2,JUVENTUS},
{LAZIO,6,1.31,2.76,1.92,3,ATALANTA},{NAPOLI,4,0.21,5.45,13.25,10,VERONA},{JUVENTUS,1,0.36,3.98,9.35,11,BOLOGNA},{SASSUOLO,15,3.84,2.78,0.73,2,INTER},{CAGLIARI,7,1.15,2.36,2.58,17,SPAL},{SAMPDORIA,20,2.24,2.64,1.18,5,ROMA},{UDINESE,14,1.88,2.18,1.63,9,TORINO},{PARMA,12,1.44,2.28,2.06,19,GENOA},{ACMILAN,13,0.46,3.58,5.77,18,LECCE},{BRESCIA,16,2.85,2.59,0.96,8,FIORENTINA},
{VERONA,14,1.56,2.29,1.88,17,SASSUOLO},{LECCE,16,7.70,4.08,0.37,1,JUVENTUS},{INTER,2,0.25,4.88,11.58,8,PARMA},{GENOA,19,0.90,2.75,2.86,15,BRESCIA},{BOLOGNA,13,0.88,2.73,2.96,20,SAMPDORIA},{ATALANTA,3,0.44,3.72,5.99,10,UDINESE},{TORINO,11,0.76,2.68,3.68,5,CAGLIARI},{SPAL,18,6.01,3.66,0.48,4,NAPOLI},{ROMA,6,1.22,2.54,2.27,12,ACMILAN},{FIORENTINA,9,1.50,2.51,1.82,7,LAZIO},
{PARMA,5,1.22,2.24,2.56,15,VERONA},{BRESCIA,18,4.88,3.25,0.57,2,INTER},{NAPOLI,4,1.05,2.79,2.45,3,ATALANTA},{CAGLIARI,7,1.75,2.36,1.63,10,BOLOGNA},{JUVENTUS,1,0.29,4.22,10.76,17,GENOA},{LAZIO,6,0.57,3.25,4.67,11,TORINO},{SAMPDORIA,20,0.82,2.70,3.31,16,LECCE},{SASSUOLO,14,1.88,2.49,1.45,9,FIORENTINA},{UDINESE,12,2.97,2.58,0.94,5,ROMA},{ACMILAN,13,0.47,3.39,5.92,19,SPAL},
{ROMA,4,1.71,2.59,1.54,6,NAPOLI},{BOLOGNA,11,2.57,2.54,1.09,2,INTER},{TORINO,13,5.82,3.03,0.55,1,JUVENTUS},{ATALANTA,3,0.30,4.78,9.22,7,CAGLIARI},{GENOA,17,0.91,2.50,3.08,14,UDINESE},{VERONA,12,1.15,2.28,2.68,18,BRESCIA},{LECCE,16,1.79,2.38,1.59,15,SASSUOLO},{FIORENTINA,8,0.50,3.46,5.26,9,PARMA},{ACMILAN,10,2.09,2.40,1.36,5,LAZIO},{SPAL,19,1.67,2.24,1.79,20,SAMPDORIA}
          };
    YLabels = {3,1,2,1,1,3,3,1,1,3,3,1,1,3,1,2,3,1,1,1,3,1,2,1,2,2,3,2,1,1,3,1,2,1,1,2,2,3,2,2,1,1,1,2,2,1,3,3,3,2,1,1,1,2,3,3,1,1,3,3,3,3,1,2,2,3,3};
    FnamePT = "SerieAPT.json";

    //Other data
    //"EPLTeams.json"
    //"EPLpos.json"
    //"BundesligaTeams.json"
    //"Bundesligapos.json"
    //"SerieATeams.json"
    //"SerieApos.json"
    //std::map<unsigned long int, double> probabilities = SerieApos.predict({11, 2.15, 2.35, 1.35, 5});

    gaussian_naive_bayes OctopusLearner3(XPT, YLabels, DEBUG);
    OctopusLearner3.fit();
    OctopusLearner3.save_model(FnamePT);

    return 0;
*/
    if(train)
    {

    }
    else
    {
        std::vector<unsigned long int> results{3,1,2,1,1,3,3,1, 1,3,3,1,1,3,1,2,3,1, 1,1,3,1,2,1,2,2,3, 2,1,1,3,1,2,1,1,2,2, 3,2,2,1,1,1,2,2,1,3, 3,3,2,1,1,1,2,3,3,1, 1,3,3,3,3,1,2,2,3,3};
        std::vector<unsigned long int> predictions;
        std::random_device rd;
        std::default_random_engine re(rd());
        std::uniform_real_distribution<> dis(0.00001, 2);

        std::vector<std::vector<double>> odds {
                                                {ROMA,4,1.30,2.82,1.90,6,ATALANTA},{FIORENTINA,20,0.70,2.99,3.66,19,SAMPDORIA},{GENOA,14,1.40,2.51,1.94,7,BOLOGNA},{INTER,2,1.03,2.52,2.79,5,LAZIO},{PARMA,16,1.74,2.45,1.59,8,SASSUOLO},{NAPOLI,3,0.19,6.85,13.34,9,CAGLIARI},{SPAL,17,1.05,2.53,2.69,18,LECCE},{TORINO,10,1.48,2.23,2.06,12,ACMILAN},
        {JUVENTUS,2,0.30,4.57,9.86,19,SPAL},{SAMPDORIA,20,3.93,2.96,0.68,1,INTER},{SASSUOLO,10,2.28,2.70,1.15,3,ATALANTA},{NAPOLI,6,0.21,6.51,11.63,14,BRESCIA},{LAZIO,9,0.48,3.81,4.99,15,GENOA},{LECCE,12,3.96,3.48,0.62,7,ROMA},{UDINESE,18,1.90,2.29,1.55,8,BOLOGNA},{CAGLIARI,4,1.20,2.28,2.55,16,VERONA},{ACMILAN,13,1.23,2.25,2.50,17,FIORENTINA},{PARMA,11,2.12,2.35,1.37,5,TORINO},
        {SPAL,19,1.34,2.35,2.17,8,PARMA},{VERONA,14,1.58,2.32,1.85,20,SAMPDORIA},{GENOA,18,1.87,2.27,1.59,16,ACMILAN},{FIORENTINA,10,0.56,3.07,4.81,12,UDINESE},{ROMA,5,0.42,4.04,5.75,7,CAGLIARI},{ATALANTA,3,0.28,5.01,9.49,17,LECCE},{BOLOGNA,11,2.17,2.64,1.22,6,LAZIO},{TORINO,9,2.84,2.77,0.92,4,NAPOLI},{INTER,1,1.68,2.18,1.82,2,JUVENTUS},
        {LAZIO,6,1.31,2.76,1.92,3,ATALANTA},{NAPOLI,4,0.21,5.45,13.25,10,VERONA},{JUVENTUS,1,0.36,3.98,9.35,11,BOLOGNA},{SASSUOLO,15,3.84,2.78,0.73,2,INTER},{CAGLIARI,7,1.15,2.36,2.58,17,SPAL},{SAMPDORIA,20,2.24,2.64,1.18,5,ROMA},{UDINESE,14,1.88,2.18,1.63,9,TORINO},{PARMA,12,1.44,2.28,2.06,19,GENOA},{ACMILAN,13,0.46,3.58,5.77,18,LECCE},{BRESCIA,16,2.85,2.59,0.96,8,FIORENTINA},
        {VERONA,14,1.56,2.29,1.88,17,SASSUOLO},{LECCE,16,7.70,4.08,0.37,1,JUVENTUS},{INTER,2,0.25,4.88,11.58,8,PARMA},{GENOA,19,0.90,2.75,2.86,15,BRESCIA},{BOLOGNA,13,0.88,2.73,2.96,20,SAMPDORIA},{ATALANTA,3,0.44,3.72,5.99,10,UDINESE},{TORINO,11,0.76,2.68,3.68,5,CAGLIARI},{SPAL,18,6.01,3.66,0.48,4,NAPOLI},{ROMA,6,1.22,2.54,2.27,12,ACMILAN},{FIORENTINA,9,1.50,2.51,1.82,7,LAZIO},
        {PARMA,5,1.22,2.24,2.56,15,VERONA},{BRESCIA,18,4.88,3.25,0.57,2,INTER},{NAPOLI,4,1.05,2.79,2.45,3,ATALANTA},{CAGLIARI,7,1.75,2.36,1.63,10,BOLOGNA},{JUVENTUS,1,0.29,4.22,10.76,17,GENOA},{LAZIO,6,0.57,3.25,4.67,11,TORINO},{SAMPDORIA,20,0.82,2.70,3.31,16,LECCE},{SASSUOLO,14,1.88,2.49,1.45,9,FIORENTINA},{UDINESE,12,2.97,2.58,0.94,5,ROMA},{ACMILAN,13,0.47,3.39,5.92,19,SPAL},
        {ROMA,4,1.71,2.59,1.54,6,NAPOLI},{BOLOGNA,11,2.57,2.54,1.09,2,INTER},{TORINO,13,5.82,3.03,0.55,1,JUVENTUS},{ATALANTA,3,0.30,4.78,9.22,7,CAGLIARI},{GENOA,17,0.91,2.50,3.08,14,UDINESE},{VERONA,12,1.15,2.28,2.68,18,BRESCIA},{LECCE,16,1.79,2.38,1.59,15,SASSUOLO},{FIORENTINA,8,0.50,3.46,5.26,9,PARMA},{ACMILAN,10,2.09,2.40,1.36,5,LAZIO},{SPAL,19,1.67,2.24,1.79,20,SAMPDORIA}
                                              };

        gaussian_naive_bayes Octopus(NODEBUG);
        Octopus.load_model("SerieAPT.json");
        bool UseBias = true;
        //int counter = 0;
        double HM, DM, AM;
        double percentage = 0;
        int correct;
        //do
        {
            correct = 0;
            HM = dis(re);
            DM = dis(re);
            AM = dis(re);

            for(auto fix : odds)
            {
                int H, D, A;

                double dTotal = 0.0;
                std::map<unsigned long int, double> probabilities = Octopus.predict(fix);
                if(UseBias)
                {
                    double biasH, biasD, biasA; //For testing

                    HM = 0.43839; DM = 1.85658; AM = 1.24872;
                    //HM = 0.443746; DM = 1.9111; AM = 1.27712;
                    //HM = 0.375114; DM = 1.61691; AM = 1.08458;

                    biasH = (20/fix[1])*HM;
                    biasA = (20/fix[5])*AM;
                    biasD = 20/((fix[1]+fix[5]) / 2)*DM;

                    dTotal = (probabilities[1]*biasH) + (probabilities[2]*biasD) + (probabilities[3]*biasA);
                    H = round(((probabilities[1]*biasH) / dTotal) * 100);
                    D = round(((probabilities[2]*biasD) / dTotal) * 100);
                    A = round(((probabilities[3]*biasA) / dTotal) * 100);
                }
                else
                {
                    dTotal = (probabilities[1]) + (probabilities[2]) + (probabilities[3]);
                    H = round((probabilities[1] / dTotal) * 100);
                    D = round((probabilities[2] / dTotal) * 100);
                    A = round((probabilities[3] / dTotal) * 100);
                }
                //if(counter == 13)
                    //std::cout << "H: "<< H << "%\tD: " << D << "%\tA: " << A << "%\t= ";
                if(H > D && H > A)
                    std::cout << "1,";
                    //predictions.push_back(1);
                else if (D > H && D > A)
                    std::cout << "2,";
                    //predictions.push_back(2);
                else if(A > H && A > D)
                    std::cout << "3,";
                    //predictions.push_back(3);
                else if(H == D && H != A)   //else if(H == D && H != A)
                    std::cout << "12,";
                    //predictions.push_back(12);
                else if(H == A && H != D)   //else if(H == A && H != D)
                    std::cout << "13,";
                    //predictions.push_back(13);
                else if (D == A && D != H)  //else if (D == A && D != H)
                    std::cout << "23,";
                    //predictions.push_back(23);
                else
                    std::cout << "0,";
                    //predictions.push_back(0);
                //counter++;
            }
            /*
            for(int i = 0; i < predictions.size(); i++)
            {
                if(predictions[i] == results[i])
                    correct++;
                else if((predictions[i] == 12) && ((results[i] == 1) || (results[i] == 2)))
                    correct++;
                else if((predictions[i] == 13) && ((results[i] == 1) || (results[i] == 3)))
                    correct++;
                else if((predictions[i] == 23) && ((results[i] == 2) || (results[i] == 3)))
                    correct++;
            }
            predictions.clear();
            //percentage = (double)(correct / predictions.size()) * 100.00;
            if(correct >= 43)
            {
                std::cout << correct << " = HM = " << HM << "; DM = " << DM << "; AM = " << AM <<";\n";
                if(correct > 43)
                    break;
            }
            */
        }//while(correct < 50);
        //std::cout << "HM = " << HM << "; DM = " << DM << "; AM = " << AM <<";\n";
        std::cout << "\n";
    }
    return 0;
}
