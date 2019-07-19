#include "solver.hpp"
#include <glpk.h>
#include <vector>
#include <string>
#include <utility>

GnuLinearBound::GnuLinearBound(int type, double lower, double upper):
    m_type {type},
    m_lower {lower},
    m_upper {upper}
{
}

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
        addStructuralBound({GLP_DB, minBounds[i], maxBounds[i]});        
}

void GnuLinearSolver::setAuxiliaryBound(std::vector<double> minBounds, std::vector<double> maxBounds)
{
    for (unsigned i=0; i<minBounds.size(); i++)
        addAuxiliaryBound({GLP_LO, minBounds[i], 0.});        
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
