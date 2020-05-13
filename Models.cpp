#include "Models.h"
#include <map>
#include <iostream>

bool mlrModel::Train(TrainingData *pData)
{
    //Lets confirm all is well first
    if(!DataOk(pData))
        return false;

    double total, H, D, A;
    std::map<uint_l, double> probabilities;
    Fixtures mlrOdds;
    //std::vector<double> mlrResults;
    std::vector<uint_l> lrResults;

    gnb gnb1(NODEBUG);
    gnb1.load_model(pData->gnbName);
    for (size_t i = 0; i < pData->fixtures.size(); i++)
    {
        probabilities = gnb1.predict(pData->fixtures[i]);
        total = (probabilities[1]*pData->Bias[0]) + (probabilities[2]*pData->Bias[1]) + (probabilities[3]*pData->Bias[2]);
        H = ((probabilities[1]*pData->Bias[0]) / total)*100;
        D = ((probabilities[2]*pData->Bias[1]) / total)*100;
        A = ((probabilities[3]*pData->Bias[2]) / total)*100;

        mlrOdds.push_back({H/100, D/100, A/100, pData->fixtures[i][0], pData->fixtures[i][1], pData->fixtures[i][2], pData->fixtures[i][3],
                                    pData->fixtures[i][4], pData->fixtures[i][5], pData->fixtures[i][6]});
        //mlrOdds.push_back({H, D, A});
    }

    //Lets do this 3 time for H, D, and A
    std::string tmpName;
    std::string::size_type n = ModelName.find(".json");
    for(uint_l venue = 1; venue <= 3; venue++)
    {
        tmpName = ModelName;
        lrResults.clear();
        for (size_t i = 0; i < pData->gnbResults.size(); i++)
        {
            //mlrResults.push_back(static_cast<double>(pData->gnbResults[i]));
            if(pData->gnbResults[i] == (venue)) lrResults.push_back(1); else lrResults.push_back(0);
        }

        lr mlr1(mlrOdds, lrResults, DEBUG);
        mlr1.fit();
        mlr1.save_model(tmpName.insert(n, std::to_string(venue)));
    }
    return true;
}

std::unique_ptr<Predictions> mlrModel::Predict(Fixtures* pOdds)
{
    //Predictions is a vector of {H, !H, COUNT}
    std::unique_ptr<Predictions> predictions = std::make_unique<Predictions>();
    lr _mlr(ModelName);
    std::cout << "LR Model: (" << ModelName << ") PREDICTION\n";
    for (size_t i = 0; i < pOdds->size(); i++)
    {
        //double prediction = _mlr.predict((*pOdds)[i]);
        std::map<uint_l, double> prediction = _mlr.predict((*pOdds)[i]);
        predictions->push_back({static_cast<double>(prediction[1]), static_cast<double>(prediction[0]), static_cast<double>(i+1)});
        //std::cout << i+1  << ": " << predictions << " = " << (*predictions)[i][0] << "\n";
    }
    return predictions;
}

//For predicting posibility of H, D, or A
std::unique_ptr<Predictions> mlrModel::Predict(Fixtures* pOdds, uint_l venue)
{
    //Predictions is a vector of {H/D/A, !(H/D/A), COUNT}
    std::string tmpName = ModelName;
    std::string::size_type n = ModelName.find(".json");

    std::unique_ptr<Predictions> predictions = std::make_unique<Predictions>();
    lr _mlr(tmpName.insert(n, std::to_string(venue)));
    std::cout << "LR Model: (" << tmpName << ") PREDICTION\n";
    for (size_t i = 0; i < pOdds->size(); i++)
    {
        //double prediction = _mlr.predict((*pOdds)[i]);
        std::map<uint_l, double> prediction = _mlr.predict((*pOdds)[i]);
        predictions->push_back({static_cast<double>(prediction[1]), static_cast<double>(prediction[0]), static_cast<double>(i+1)});
        //std::cout << i+1  << ": " << predictions << " = " << (*predictions)[i][0] << "\n";
    }
    return predictions;
}

//Remeber not tunning here, only training based on tuned results
bool gnbModel::Train(TrainingData *pData)
{
    if(!DataOk(pData))
        return false;

    double total, H, D, A;
    std::map<uint_l, double> probabilities;
    Fixtures gnbOdds;

    gnb gnb1(NODEBUG);
    gnb1.load_model(pData->gnbName);
    for (size_t i = 0; i < pData->fixtures.size(); i++)
    {
        probabilities = gnb1.predict(pData->fixtures[i]);
        total = (probabilities[1]*pData->Bias[0]) + (probabilities[2]*pData->Bias[1]) + (probabilities[3]*pData->Bias[2]);
        H = ((probabilities[1]*pData->Bias[0]) / total);//*100;
        D = ((probabilities[2]*pData->Bias[1]) / total);//*100;
        A = ((probabilities[3]*pData->Bias[2]) / total);//*100;

        gnbOdds.push_back({H, D, A, pData->fixtures[i][2], pData->fixtures[i][3], pData->fixtures[i][4]});
    }

    gnb _gnb(gnbOdds, pData->gnbResults, DEBUG);
    _gnb.fit();
    _gnb.save_model(ModelName);
    return true;
}

std::unique_ptr<Predictions> gnbModel::Predict(Fixtures* pOdds, double bH, double bD, double bA)
{
    //Predictions is a vector of {H, D, A}
    double total, H, D, A;
    std::map<uint_l, double> probabilities;
    std::unique_ptr<Predictions> predictions = std::make_unique<Predictions>();
    gnb _gnb(NODEBUG);
    _gnb.load_model(ModelName);
    for (size_t i = 0; i < pOdds->size(); i++)
    {
        probabilities = _gnb.predict((*pOdds)[i]);
        total = (probabilities[1]*bH) + (probabilities[2]*bD) + (probabilities[3]*bA);
        H = ((probabilities[1]*bH) / total)*100;
        D = ((probabilities[2]*bD) / total)*100;
        A = ((probabilities[3]*bA) / total)*100;
        predictions->push_back({H, D, A});
    }
    return predictions;
}

std::unique_ptr<Predictions> gnbModel::Predict(Fixtures* pOdds)
{
    //Predictions is a vector of {H, D, A}
    //double total, H, D, A;
    std::map<uint_l, double> probabilities;
    std::unique_ptr<Predictions> predictions = std::make_unique<Predictions>();
    gnb _gnb(NODEBUG);
    _gnb.load_model(ModelName); //LaligaPT2.json
    //std::cout << "GNB Model: " << ModelName << "\n";
    for (size_t i = 0; i < pOdds->size(); i++)
    {
        probabilities = _gnb.predict((*pOdds)[i]);
        predictions->push_back({probabilities[1], probabilities[2], probabilities[3]});
        //std::cout << "H=" << probabilities[1] << ",\tD=" << probabilities[2] << ",\tA=" << probabilities[3] << "\n";
    }
    return predictions;
}
