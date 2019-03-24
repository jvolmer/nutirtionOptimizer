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
    int getType() const {return m_type;}
    double getLower() const {return m_lower;}
    double getUpper() const {return m_upper;}
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

    const std::vector<double>& getResultVariables() const {return m_resultVariable;}
    double getResultValue() const {return m_resultValue;}

    void addProblemCoefficient(double coefficient){m_problemCoefficient.push_back(coefficient);}
    void addConstraintCoefficients(const std::vector<double>& coefficients){m_constraintCoefficient.push_back(coefficients);}
    void addAuxiliaryBound(const GnuLinearBound& bound){m_auxiliaryBound.push_back(bound);}
    void addStructuralBound(const GnuLinearBound& bound){m_structuralBound.push_back(bound);}

    void prepare();
    void solve();

};

#endif
