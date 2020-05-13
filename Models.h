#ifndef __MODELS_H__
#define __MODELS_H__

#include <string>
#include <vector>
#include <memory>
#include "naive_bayes.h"
#include "mlr.h"
#include "logistic_regression.h"

typedef unsigned long int uint_l;
typedef std::vector<std::vector<double>> Fixtures;
typedef Fixtures Predictions;
typedef gaussian_naive_bayes gnb;
typedef LinearRegression mlr;
typedef logistic_regression lr;

struct TrainingData
{
    std::string gnbName;
    std::vector<double> Bias;
    Fixtures fixtures;
    std::vector<uint_l> gnbResults;
};


class Model
{
private:
    /* data */
public:
    Model(std::string name): ModelName(name) {}
    ~Model(){}
    virtual bool Train(TrainingData *pData) = 0;
    virtual std::unique_ptr<Predictions> Predict(Fixtures* pOdds) = 0;
    //virtual std::unique_ptr<Predictions> Predict(Fixtures* pOdds, double bH, double bD, double bA);
protected:
    std::string ModelName;
    bool DataOk(TrainingData *data)
    {
        return ( (data->gnbName.length() > 1)   &&
                 (data->Bias.size() == 3)       &&
                 (data->fixtures.size() > 0)    &&
                 (data->gnbResults.size() > 0)  &&
                 (data->fixtures.size() == data->gnbResults.size()));
    }
};

//Multiple Linear Regression (MLR) model
class mlrModel : public Model
{
private:
    /* data */
public:
    mlrModel(std::string name): Model(name) {}
    ~mlrModel(){}
    bool Train(TrainingData *pData) override;
    std::unique_ptr<Predictions> Predict(Fixtures* pOdds) override;
    std::unique_ptr<Predictions> Predict(Fixtures* pOdds, uint_l venue);    //For predicting posibility of H, D, or A
};

//Multiple Linear Regression (MLR) model
class gnbModel : public Model
{
private:
    /* data */
public:
    gnbModel(std::string name): Model(name) {}
    ~gnbModel(){}
    bool Train(TrainingData *pData) override;
    std::unique_ptr<Predictions> Predict(Fixtures* pOdds) override;
    std::unique_ptr<Predictions> Predict(Fixtures* pOdds, double bH, double bD, double bA);
};

#endif
