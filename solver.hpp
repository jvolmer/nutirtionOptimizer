#ifndef SOLVER_H
#define SOLVER_H
#include <vector>
#include <string>
#include <glpk.h>

class GnuLinearBound{

private:
    int m_type;
    double m_lower;
    double m_upper;

public:
    GnuLinearBound(int type, double lower, double upper);
    int getType();
    double getLower();
    double getUpper();
};

class GnuLinearSolver{
    
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
    GnuLinearSolver(int problemType);
    ~GnuLinearSolver();
    void addProblemCoefficient(double coefficient);
    void addConstraintCoefficients(const std::vector<double>& coefficients);
    void addAuxiliaryBound(const GnuLinearBound& bound);
    void addStructuralBound(const GnuLinearBound& bound);
    const std::vector<double>& getResultVariables();
    double getResultValue();

    void prepare();
    void solve();

};

#endif
