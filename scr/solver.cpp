#include "bound.hpp"
#include "solver.hpp"
#include <limits>
#include <glpk.h>
#include <vector>
#include <string>
#include <utility>
#include <cmath>
#include <json/json.h>
#include <iostream>


GnuLinearSolver::GnuLinearSolver(int problemType, std::vector<double> problemCoefficient, std::vector<std::vector<double>> constraintCoefficient, std::vector<GnuLinearBound> auxiliaryBound, std::vector<GnuLinearBound> structuralBound):
    m_problemObject {glp_create_prob()},
    m_problemType {problemType},
    m_problemCoefficient {std::move(problemCoefficient)},
    m_constraintCoefficient {std::move(constraintCoefficient)},
    m_auxiliaryBound {std::move(auxiliaryBound)},
    m_structuralBound {std::move(structuralBound)}
{
    // set optimzation direction flag
    glp_set_obj_dir(m_problemObject, m_problemType);

    // disable terminal output
    glp_term_out(GLP_OFF);

}

GnuLinearSolver::~GnuLinearSolver()
{
    glp_delete_prob(m_problemObject);
}

void GnuLinearSolver::setStructuralBound(std::vector<double> minBounds, std::vector<double> maxBounds)
{
    for (unsigned i=0; i<minBounds.size(); i++)
        m_structuralBound.push_back(GnuLinearBound(minBounds[i], maxBounds[i]));
}

void GnuLinearSolver::setAuxiliaryBound(std::vector<double> minBounds, std::vector<double> maxBounds)
{
    for (unsigned i=0; i<minBounds.size(); i++)
        m_auxiliaryBound.push_back(GnuLinearBound(minBounds[i], maxBounds[i]));
}

            
void GnuLinearSolver::prepare()
{
    prepareStructuralVariables();
    prepareAuxiliaryVariables();
}

void GnuLinearSolver::prepareStructuralVariables()
{
    glp_add_cols(m_problemObject, m_structuralBound.size());
    
    for (unsigned i=0; i<m_structuralBound.size(); i++)
    {    
        glp_set_col_bnds(m_problemObject, i+1, m_structuralBound[i].getType(), m_structuralBound[i].getLower(), m_structuralBound[i].getUpper());
        glp_set_obj_coef(m_problemObject, i+1, m_problemCoefficient[i]);
    }
}
    
void GnuLinearSolver::prepareAuxiliaryVariables()
{
    glp_add_rows(m_problemObject, m_auxiliaryBound.size());

    for (unsigned i=0; i<m_auxiliaryBound.size(); i++)
    {
        glp_set_row_bnds(m_problemObject, i+1, m_auxiliaryBound[i].getType(), m_auxiliaryBound[i].getLower(), m_auxiliaryBound[i].getUpper());
    }
    
    unsigned iGes = 0;
    int ia[1+1000], ja[1+1000];
    double ar[1+1000];
    for (unsigned iAux=0; iAux<m_auxiliaryBound.size(); iAux++)
    {
        for (unsigned iStruc=0; iStruc<m_structuralBound.size(); iStruc++)
        {
            ia[iGes+1] = iAux+1, ja[iGes+1] = iStruc+1, ar[iGes+1] = m_constraintCoefficient[iAux][iStruc];
            iGes++;
        }
    }
    glp_load_matrix(m_problemObject, iGes, ia, ja, ar);
}

void GnuLinearSolver::solve()
{
    glp_simplex(m_problemObject, NULL);
    m_resultValue = glp_get_obj_val(m_problemObject);
    for (unsigned i=0; i<m_structuralBound.size(); i++)
        m_resultVariable.push_back(glp_get_col_prim(m_problemObject, i+1));
}

Json::Value GnuLinearSolver::toJson() const
{
    Json::Value out;

    Json::Value problemCoefficient;
    for (unsigned int i=0; i<m_problemCoefficient.size(); i++)
        problemCoefficient["variable" + std::to_string(i)] = m_problemCoefficient[i];
    out["problemCoefficient"] = problemCoefficient;

    Json::Value constraintCoefficients;
    for (unsigned int i=0; i<m_constraintCoefficient.size(); i++)
    {
        Json::Value coefficient;
        for (unsigned int j=0; j<m_constraintCoefficient[i].size(); j++)
            coefficient["variable" + std::to_string(j)] = m_constraintCoefficient[i][j];
        constraintCoefficients["auxiliaryVariable" + std::to_string(i)] = coefficient;
    }
    out["constraintCoefficients"] = constraintCoefficients;

    Json::Value auxiliaryBound;
    for (unsigned int i=0; i<m_auxiliaryBound.size(); i++)
    {
        auxiliaryBound["auxiliaryVariable" + std::to_string(i)] = m_auxiliaryBound[i].toJson();
    }
    out["auxiliaryBounds"] = auxiliaryBound;

    Json::Value structuralBound;
    for (unsigned int i=0; i<m_structuralBound.size(); i++)
    {
        structuralBound["structuralVariable" + std::to_string(i)] = m_structuralBound[i].toJson();
    }
    out["structuralBounds"] = structuralBound;

    Json::Value result;
    for (unsigned int i=0; i<m_resultVariable.size(); i++)
        result["variable" + std::to_string(i)] = m_resultVariable[i];
    out["result"] = result;
    
    out["resultMinimum"] = m_resultValue;

    return out;
}
