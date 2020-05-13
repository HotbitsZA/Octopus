#include <iostream>
#include <algorithm>
#include <utility>
//#include <string>
//#include "naive_bayes.h"
#include "preprocessing.h"
//#include "mlr.h"
#include "defines.h"
#include <iomanip>
#include <random>
#include <map>
#include "LaLigaFix.h"
#include "SeriaAFix.h"
#include "EPLFix.h"
#include "BundesLigaFix.h"
#include "Models.h"
//#include "logistic_regression.h"
//using namespace std;
//#include <ctime>

std::unique_ptr<AllowedRanges> ComputeRanges(uint8_t lig)
{
    std::unique_ptr<AllowedRanges> arReturn;
    Fixtures fixtures;
    std::vector<uint_l> results;
    std::vector<double> biases;
    std::string model;
    std::unique_ptr<Predictions> predictions;

    switch(lig)
    {
    case SPAIN:
        fixtures = LaLigaFix;
        results  = LaLigaRes;
        biases   = LaLigaBias1;
        model    = LALIGA_MODEL;
        break;
    case ITALY:
        fixtures = SeriaAFix;
        results  = SeriaARes;
        biases   = SeriaABias1;
        model    = SERIAA_MODEL;
        break;
    case ENGLAND:
        fixtures = EPLFix;
        results  = EPLRes;
        biases   = EPLBias1;
        model    = EPL_MODEL;
        break;
    case GERMANY:
        fixtures = BundesLigaFix;
        results  = BundesLigaRes;
        biases   = BundesLigaBias1;
        model    = BUNDESLIGA_MODEL;
        break;
    default:
        return arReturn;
    }

    gnbModel gnbM(model);
    predictions = gnbM.Predict(&fixtures, biases[HOME], biases[DRAW], biases[AWAY]);
    arReturn = std::make_unique<AllowedRanges>();
    arReturn->home.clear();
    arReturn->draw.clear();
    arReturn->away.clear();
    //loop 3 times for h,d,a
    for(uint8_t hda = HOME; hda <= AWAY; hda++)
    {
        //loop 10 times for 10 to 100 %
        double _low, _high = 0.4;
        for(uint8_t percent = TEN; percent <= HUNDRED; percent++)
        {
            int bala;
            double avarage = 0.0;
            std::vector<double> cOdds;
            _high += 10;
            _low = _high - 10 + 0.1;
            if(_high == 10.4)
                _low = -1;

            bala = 0;
            avarage = 0.0;
            cOdds.clear();
            for(size_t result = 0; result < results.size(); result++)
            {
                switch(hda)
                {
                case HOME:
                    if((results[result] == 1) && ((*predictions)[result][HOME] > _low ) && ((*predictions)[result][HOME] <= _high))
                    {
                        bala++;
                        avarage += fixtures[result][2];
                        cOdds.push_back(fixtures[result][2]);
                    }
                    break;
                case DRAW:
                    if((results[result] == 2) && ((*predictions)[result][DRAW] > _low) && ((*predictions)[result][DRAW] <= _high))
                    {
                        bala++;
                        avarage += fixtures[result][3];
                        cOdds.push_back(fixtures[result][3]);
                    }
                    break;
                case AWAY:
                    if((results[result] == 3) && ((*predictions)[result][AWAY] > _low) && ((*predictions)[result][AWAY] <= _high))
                    {
                        bala++;
                        avarage += fixtures[result][4];
                        cOdds.push_back(fixtures[result][4]);
                    }
                    break;
                default:
                    break;
                }
            }
            //We have the results, calculate averages, etc
            std::pair<double, double> ar;
            if(avarage > 0.0)
            {
                double _min = *(std::min_element(cOdds.begin(), cOdds.end()));
                double _max = *(std::max_element(cOdds.begin(), cOdds.end()));
                double ave = avarage / bala;
                double devp = ((_max - ave) + (ave - _min)) / 2;
                ar = std::make_pair(ave, ave+devp);
                //ar = std::make_pair(ave-devp, ave+devp);
            }
            else
            {
                ar = std::make_pair(0.0, 0.0);
            }

            switch(hda)
            {
            case HOME:
                arReturn->home.push_back(ar);
                break;
            case DRAW:
                arReturn->draw.push_back(ar);
                break;
            case AWAY:
                arReturn->away.push_back(ar);
                break;
            }
        }
    }

    return arReturn;
}

uint8_t PrintResult(double H, double D, double A, bool inPercentage=false)
{
    uint8_t uiReturn = 3;

    if(inPercentage)
        std::cout << "H=" << H*100 << "%,\tD=" << D*100 << "%,\tA=" << A*100 << "%,\t";
    else
        std::cout << "H=" << H << ",\tD=" << D << ",\tA=" << A << ",\t";

    if(H > D && H > A){
        std::cout << "1";
        uiReturn = HOME;
    }
    else if (D > H && D > A){
        std::cout << "2";
        uiReturn = DRAW;
    }
    else if(A > H && A > D){
        std::cout << "3";
        uiReturn = AWAY;
    }
    else
        std::cout << "?";

    return uiReturn;
}

uint8_t PrintToString(double H, double D, double A, std::string& outString)
{
    uint8_t uiReturn = 3;

    outString += ("H=" + std::to_string(H) + ",\tD=" + std::to_string(D) + ",\tA=" + std::to_string(A) + ",\t");

    if(H > D && H > A){
        outString += "1";
        uiReturn = HOME;
    }
    else if (D > H && D > A){
        outString += "2";
        uiReturn = DRAW;
    }
    else if(A > H && A > D){
        outString += "3";
        uiReturn = AWAY;
    }
    else
        outString += "?";

    return uiReturn;
}

bool compare(std::pair<uint_l, float> mp1, std::pair<uint_l, float> mp2)
{
    return mp1.second < mp2.second;
}
//#include <cstdlib>
double get_random(std::default_random_engine &e)
{
    //static std::default_random_engine e;
    static std::uniform_real_distribution<> dis(0,2);
    return dis(e);
}

/*void printData(double *pData)
{
    for(size_t i = 0; i < 31; i++)
        std::cout << pData[i] << ", ";
    std::cout << "\n";
}*/

int main()
{
    bool train = false;
    /**********************************************/
    std::cout << "------Octopus------" << std::endl;
    std::cout << "-------------------" << std::endl;
    std::cout << std::fixed << std::setprecision(3);
    std::default_random_engine e;
    e.seed(std::time(nullptr));
    /**********************************************/
    std::string lbName("Ingnition");
    std::transform(lbName.begin(), lbName.end(), lbName.begin(), ::toupper);
    std::cout << lbName << "\n";
    return 0;

    if(train)
    {
        std::string FnamePT;
        std::vector<unsigned long int> YLabels, lrYLabels;
        std::vector<std::vector<double>> XPT;
        bool skip = false;
        //double teams = 20;

        for(int lig = SPAIN; lig <= GERMANY; lig++)
        {
            switch(lig)
            {
            case SPAIN:
                FnamePT = LALIGA_MODEL;
                YLabels = LaLigaRes;
                XPT = LaLigaFix;
                skip = false;
                break;
            case ITALY:
                FnamePT = SERIAA_MODEL;
                YLabels = SeriaARes;
                XPT = SeriaAFix;
                skip = true;
                break;
            case ENGLAND:
                FnamePT = EPL_MODEL;
                YLabels = EPLRes;
                XPT = EPLFix;
                skip = false;
                break;
            case GERMANY:
                FnamePT = BUNDESLIGA_MODEL;
                YLabels = BundesLigaRes;
                XPT = BundesLigaFix;
                skip = false;
                //teams = 18;
                break;
            default:
                std::cout << "No league found!!!!! \n";
                exit(EXIT_FAILURE);
                break;
            }
            if(skip)
                continue;

            ///Remove after testing
            //scale down Team name and position
            /*for(auto& fix : XPT)
            {
                fix[0] /= teams; fix[6] /= teams;
                fix[1] /= teams; fix[5] /= teams;

            }*/
            ///********************
            gaussian_naive_bayes OctopusLearner3(XPT, YLabels, DEBUG);
            OctopusLearner3.fit();
            OctopusLearner3.save_model(FnamePT);

            /*for(size_t i = 0; i < YLabels.size(); i++)
            {
                if(YLabels[i] == 1)
                    lrYLabels.push_back(1);
                else
                    lrYLabels.push_back(0);
            }
            logistic_regression lr(XPT, lrYLabels, DEBUG);
            lr.fit();
            lr.save_model("LR_" + FnamePT);*/
        }
    }
    else
    {
        //int lig = SPAIN;
        //int lig = ITALY;
        int lig = ENGLAND;
        //int lig = GERMANY;
        std::vector<std::string> output;
        std::time_t _timer = (std::time(nullptr) + 120);    //5 minutes

        Fixtures odds;      //All past fixtures of that lig or current to be predicted
        Fixtures odds2;     //Populate with probabilities, for further training
        Fixtures mlrOdds;   //For training mlr model, should be all past fixtures of that lig
        std::vector<uint_l> results;     //All past results for that lig, will be used for training mlr model also
        std::vector<uint_l> predictions; //gaussian_naive_bayes predictions for training
        std::vector<double> predictions2;           //mlr predictions, maybe for training
        std::map<uint_l, double> probabilities;
        std::string model, Modelmlr, model2;
        bool UseBias = true;    //Must always be true
        double HM, DM, AM;
        bool tune = true;
        std::vector<double> bias;
        //double teams = 20;

        //Maybe remove the below after test
        std::map<unsigned long int, unsigned long int> right{{1,0}, {2,0}, {3,0}}, wrong{{1,0}, {2,0}, {3,0}}, totals{{1,0},{2,0},{3,0}};

        switch(lig)
        {
        case SPAIN:
            model = LALIGA_MODEL;
            model2 = LALIGA_MODEL3;
            Modelmlr = LALIGA_MODEL2;
            results = LaLigaRes;
            odds = tune ? LaLigaFix : LaLigaNewFix;
            mlrOdds = LaLigaFix;
            bias = LaLigaBias1;
            HM = LaLigaBias1[HOME]; DM = LaLigaBias1[DRAW]; AM = LaLigaBias1[AWAY];
            break;
        case ITALY:
            model = SERIAA_MODEL;
            model2 = SERIAA_MODEL3;
            Modelmlr = SERIAA_MODEL2;
            results = SeriaARes;
            odds = tune ? SeriaAFix : SeriaANewFix;
            mlrOdds = SeriaAFix;
            bias = SeriaABias1;
            HM = SeriaABias1[HOME]; DM = SeriaABias1[DRAW]; AM = SeriaABias1[AWAY];
            break;
        case ENGLAND:
            model = EPL_MODEL;
            model2 = EPL_MODEL3;
            Modelmlr = EPL_MODEL2;
            results = EPLRes;
            odds = tune ? EPLFix : EPLNewFix;
            mlrOdds = EPLFix;
            bias = EPLBias1;
            HM = EPLBias1[HOME]; DM = EPLBias1[DRAW]; AM = EPLBias1[AWAY];
            break;
        case GERMANY:
            model = BUNDESLIGA_MODEL;
            model2 = BUNDESLIGA_MODEL3;
            Modelmlr = BUNDESLIGA_MODEL2;
            results = BundesLigaRes;
            odds = tune ? BundesLigaFix : BundesLigaNewFix;
            mlrOdds = BundesLigaFix;
            bias = BundesLigaBias1;
            HM = BundesLigaBias1[HOME]; DM = BundesLigaBias1[DRAW]; AM = BundesLigaBias1[AWAY];
            //teams = 18;
            break;
        }
        ///Remove after testing
        //scale down Team name and position
        /*for(auto& fix : odds)
        {
            fix[0] /= teams; fix[6] /= teams;
            fix[1] /= teams; fix[5] /= teams;

        }
        for(auto& fix : mlrOdds)
        {
            fix[0] /= teams; fix[6] /= teams;
            fix[1] /= teams; fix[5] /= teams;

        }*/
        ///********************

        ///Put back after testing
        mlrModel Octopus1("LR_" + model);
        //gnbModel Octopus2(model2);
        TrainingData ModelData;
        if(!tune)
        {
            ModelData.gnbName       = model;
            ModelData.Bias          = bias;
            ModelData.fixtures      = mlrOdds;
            ModelData.gnbResults    = results;
            Octopus1.Train(&ModelData);
            //Octopus2.Train(&ModelData);
            std::cout << "\n";
            output.resize(odds.size());
        }

        ///******************************************************************
        gaussian_naive_bayes Octopus(NODEBUG);
        Octopus.load_model(model);
        std::unique_ptr<AllowedRanges> ar = ComputeRanges(lig);

        unsigned int HCH, HWH, ACH, AWH, DCH, DWH;
        unsigned int correct, highest = results.size() / 2;

        /*std::random_device rd;
        std::default_random_engine re(rd());
        std::uniform_real_distribution<> dis(0, 2);*/
        //std::uniform_real_distribution<> dis(2, 100);
        //uint32_t u32_Loop = 0;
        HCH = ACH = DCH = 0;
        HWH = DWH = AWH = 10000;
        for(auto val : results)
            totals[val]++;  //Totals of 1, 2, and 3 from results

        //std::vector<std::string> output();
        do
        {
            if(tune)
            {
                if( std::time(nullptr) > _timer)
                {
                    std::cout << "==============================================================================================\n";
                    e.seed(std::time(nullptr));
                    _timer = (std::time(nullptr) + 120);    //5 minutes
                }
                AM = get_random(e);//dis(re);
                DM = get_random(e);//dis(re);
                HM = get_random(e);//dis(re);
                correct = 0;
            }


            for(size_t fixture = 0; fixture < odds.size(); fixture++)
            {
                double H, D, A;
                double dTotal = 0.0;
                probabilities = Octopus.predict(odds[fixture]);

                if(UseBias)
                {
                    double biasH, biasD, biasA;
                    biasH = HM;
                    biasA = AM;
                    biasD = DM;

                    dTotal = (probabilities[1]*biasH) + (probabilities[2]*biasD) + (probabilities[3]*biasA);
                    H = ((probabilities[1]*biasH) / dTotal)*100;
                    D = ((probabilities[2]*biasD) / dTotal)*100;
                    A = ((probabilities[3]*biasA) / dTotal)*100;
                }
                else
                {
                    dTotal = (probabilities[1]) + (probabilities[2]) + (probabilities[3]);
                    H = (probabilities[1] / dTotal)*100;
                    D = (probabilities[2] / dTotal)*100;
                    A = (probabilities[3] / dTotal)*100;
                }

                ///Put back after testing
                if(tune)
                {
                    if(H > D && H > A){
                        predictions.push_back(1);
                    }
                    else if (D > H && D > A){
                        predictions.push_back(2);
                    }
                    else if(A > H && A > D){
                        predictions.push_back(3);
                    }
                    else{
                        predictions.push_back(0);
                    }
                }
                else
                {
                    double proba = 0;
                    double dOdds = 0.0;
                    uint8_t u8Result;
                    double _low, _high = 0.4;

                    //u8Result = PrintResult(H, D, A);
                    output[fixture] = (std::to_string(fixture+1)+" : ");
                    u8Result = PrintToString(H, D, A, output[fixture]);
                    switch(u8Result)
                    {
                    case HOME:
                        proba = H;
                        dOdds = odds[fixture][2];
                        break;
                    case DRAW:
                        proba = D;
                        dOdds = odds[fixture][3];
                        break;
                    case AWAY:
                        proba = A;
                        dOdds = odds[fixture][4];
                        break;
                    default:
                        break;
                    }

                    for(size_t perc = TEN; perc <= HUNDRED; perc++)
                    {
                        _high += 10;
                        _low = _high - 10 + 0.1;
                        if(_high == 10.4)
                            _low = 0.0;

                        if((proba >= _low) && (proba <= _high))
                        {
                            switch(u8Result)
                            {
                            case HOME:
                                if((dOdds >= std::get<0>(ar->home[perc])) && (dOdds <= std::get<1>(ar->home[perc])))
                                    output[fixture] += ",H"; //else output[fixture] += ",";
                                    //std::cout << ",H"; else std::cout << ",";
                                break;
                            case DRAW:
                                if((dOdds >= std::get<0>(ar->draw[perc])) && (dOdds <= std::get<1>(ar->draw[perc])))
                                    output[fixture] += ",D"; //else output[fixture] += ",";
                                    //std::cout << ",D"; else std::cout << ",";
                                break;
                            case AWAY:
                                if((dOdds >= std::get<0>(ar->away[perc])) && (dOdds <= std::get<1>(ar->away[perc])))
                                    output[fixture] += ",A"; //else output[fixture] += ",";
                                    //std::cout << ",A"; else std::cout << ",";
                                break;
                            default:
                                output[fixture] += ",?";
                                break;
                            }
                            break;  //From perc for loop
                        }
                    }
                    //std::cout << "\n";
                    odds2.push_back({H/100, D/100, A/100, odds[fixture][0], odds[fixture][1], odds[fixture][2], odds[fixture][3], odds[fixture][4],
                                              odds[fixture][5], odds[fixture][6]});
                    //odds2.push_back({H, D, A});
                }
                ///******************************************************************
            }

            if(!tune)
            {
                //std::cout << "ENDENDENDENDENDENDENDENDENDENDENDENDENDENDENDENDENDENDENDEND\n";

                ///Let's do a second prediction based on predicted percentages
                /*std::unique_ptr<Predictions> pred2 = Octopus2.Predict(&odds2);
                for(size_t y = 0; y < pred2->size(); y++)
                {
                    PrintResult((*pred2)[y][HOME], (*pred2)[y][DRAW], (*pred2)[y][AWAY]);
                    std::cout << "\n";
                    //std::cout << (*pred2)[y][3] << ": H=" << (*pred2)[y][0] << ",\tD=" << (*pred2)[y][1] << ",\tA=" << (*pred2)[y][2] << ",\t";
                    //std::cout << (*pred2)[y][3] << ": H=" << odds2[y][0] << ",\tD=" << odds2[y][1] << ",\tA=" << odds2[y][2] << ",\t";
                    //std::cout << "\n";
                    //(*pred2)[y][HOME];
                }*/
                ///***********************************************************
                //Do it 3 time for H, D, and A
                for(uint_l cnt1 = 1; cnt1 <= 3; cnt1++)
                {
                    std::unique_ptr<Predictions> pred2 = Octopus1.Predict(&odds2, cnt1);
                    for(size_t cnt2 = 0; cnt2 < pred2->size(); cnt2++)
                    {
                        /*std::cout << static_cast<int>((*pred2)[cnt2][2]) << ": " << (*pred2)[cnt2][0] << "\t" << (*pred2)[cnt2][1] << "\t";
                        if((*pred2)[cnt2][0] > (*pred2)[cnt2][1])
                            std::cout << "3\n";
                        else
                            std::cout << "0\n";*/
                        if((*pred2)[cnt2][0] > (*pred2)[cnt2][1])
                            output[cnt2] += ("," + std::to_string(cnt1));
                    }
                }
                for(auto& str : output)
                    std::cout << str << "\n";

                break;  //From do loop
            }

            //Don't temper with below for now
            /******************************************************************************************************************/
            wrong[1] = wrong[2] = wrong[3] = 0;
            right[1] = right[2] = right[3] = 0;
            for(unsigned int i = 0; i < predictions.size(); i++)
            {
                if(predictions[i] == results[i])
                {
                    correct++;
                    right[results[i]]++;
                }
                else
                {
                    if((predictions[i] < 4) && (predictions[i] > 0))
                        wrong[results[i]]++;
                    else
                    {
                        wrong[1]++; wrong[2]++; wrong[3]++;
                    }
                }
            }
            predictions.clear();
            //percentage = (double)(correct / predictions.size()) * 100.00;
            if(correct > highest)
            {
                HCH = ACH = DCH = 0;
                HWH = DWH = AWH = 10000;
            }
            //if((correct >= highest) && ((right[1] >= HCH && wrong[1] < HWH) || (right[2] >= DCH && wrong[2] < DWH) || (right[3] >= ACH && wrong[3] < AWH)))
            if((correct > highest))// && ((right[1] > HCH || wrong[1] < HWH) || (right[2] > DCH || wrong[2] < DWH) || (right[3] > ACH || wrong[3] < AWH)))
            {
                std::cout << std::fixed << std::setprecision(4);
                //Don't print double chances
                //if(results.size() == (right[1]+right[2]+right[3]+wrong[1]+wrong[2]+wrong[3]))
                {
                    double perc = (static_cast<double>(correct) / results.size()) * 100;
                    std::cout << correct << "/" << results.size() << "\t" << HM << ", " << DM << ", " << AM <<"\t= "<< round(perc) <<"%\t";
                    std::cout << "1 = "/*<< right[1] << "/" << wrong[1]*/ << "(" << round((static_cast<double>(right[1])/totals[1])*100) << "%)"
                              << "\t2 = " /*<< right[2] << "/" << wrong[2]*/ << "(" << round((static_cast<double>(right[2])/totals[2])*100) << "%)"
                              << "\t3 = " /*<< right[3] << "/" << wrong[3]*/ << "(" << round((static_cast<double>(right[3])/totals[3])*100) << "%)" << "\n";
                }

                highest = correct > highest ? correct : highest;

                HCH = (right[1] > HCH) ? right[1] : HCH;
                HWH = (wrong[1] < HWH) ? wrong[1] : HWH;

                DCH = (right[2] > DCH)?right[2]:DCH;
                DWH = (wrong[2] < DWH)?wrong[2]:DWH;

                ACH = (right[3] > ACH)?right[3]:ACH;
                AWH = (wrong[3] < AWH)?wrong[3]:AWH;
            }
            //Don't temper end
            /******************************************************************************************************************/
            /*if(u32_Loop < 10)
            {
                DM *= (1 + (u32_Loop / 10));
                HM /= (1 + (u32_Loop / 10));
                goto START;
            }*/

        }while(correct < results.size());//(correct < 53);
        std::cout << "\n";
    }

    return 0;
}
