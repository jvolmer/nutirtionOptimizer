#ifndef SOLVER_H
#define SOLVER_H
#include <glpk.h>
#include <vector>
#include <string>
#include <utility>

class Bound
{
public:
    virtual ~Bound() {};
    virtual int getType() const = 0;
    virtual double getLower() const = 0;
    virtual double getUpper() const = 0;
    
};

class GnuLinearBound : public Bound
{
private:
    int m_type;
    double m_lower;
    double m_upper;

public:
    GnuLinearBound(int type, double lower, double upper);
    int getType() const {return m_type;}
    double getLower() const {return m_lower;}
    double getUpper() const {return m_upper;}
    static GnuLinearBound getBound(double lower, double upper);
};


class Solver
{
public:
    virtual ~Solver() {};
    virtual const std::vector<double>& getResultVariables() const = 0;
    virtual double getResultValue() const = 0;

    virtual void setProblemCoefficient(std::vector<double> coefficients) = 0;
    virtual void setConstraintCoefficients(std::vector<std::vector<double>> coefficientVectors) = 0;
    virtual void setStructuralBound(std::vector<double> minBounds, std::vector<double> maxBounds) = 0;
    virtual void setAuxiliaryBound(std::vector<double> minBounds, std::vector<double> maxBounds) = 0;


    virtual void prepare() = 0;
    virtual void solve() = 0;

};

class GnuLinearSolver : public Solver
{    
private:
    glp_prob* m_problemObject;
    int m_problemType;
    std::vector<double> m_problemCoefficient;
    std::vector<std::vector<double>> m_constraintCoefficient;
    std::vector<GnuLinearBound> m_auxiliaryBound;
    std::vector<GnuLinearBound> m_structuralBound;
    std::vector<double> m_resultVariable;
    double m_resultValue;

public:
    GnuLinearSolver(int problemType, std::vector<double> problemCoefficient = {}, std::vector<std::vector<double>> constraintCoefficient = {}, std::vector<GnuLinearBound> auxiliaryBound = {}, std::vector<GnuLinearBound> structuralBound = {});
    ~GnuLinearSolver();

    const std::vector<double>& getResultVariables() const {return m_resultVariable;}
    double getResultValue() const {return m_resultValue;}

    void setProblemCoefficient(std::vector<double> coefficients){ m_problemCoefficient = std::move(coefficients); }
    void setConstraintCoefficients(std::vector<std::vector<double>> coefficientVectors){ m_constraintCoefficient = std::move(coefficientVectors); }
    void setStructuralBound(std::vector<double> minBounds, std::vector<double> maxBounds);
    void setAuxiliaryBound(std::vector<double> minBounds, std::vector<double> maxBounds);
    
    void prepareStructuralVariables();
    void prepareAuxiliaryVariables();
    void prepare();
    
    void solve();

};

class MockSolver : public Solver
{
private:
    std::vector<double> m_results;
    
public:
    MockSolver() {};
    ~MockSolver() {};

    const std::vector<double>& getResultVariables() const {return m_results;}
    double getResultValue() const {return 0;}
    
    void setProblemCoefficient(std::vector<double> coefficients){}
    void setConstraintCoefficients(std::vector<std::vector<double>> coefficientVectors){};
    void setStructuralBound(std::vector<double> minBounds, std::vector<double> maxBounds){}
    void setAuxiliaryBound(std::vector<double> minBounds, std::vector<double> maxBounds){ m_results = std::move(minBounds); };
    
    void prepare(){};
    void solve(){};
};

#endif
