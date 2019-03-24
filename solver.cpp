#include "solver.hpp"

GnuLinearBound::GnuLinearBound(int type, double lower, double upper):
    m_type {type},
    m_lower {lower},
    m_upper {upper}
{
}

int GnuLinearBound::getType()
{
    return m_type;
}

double GnuLinearBound::getLower()
{
    return m_lower;
}

double GnuLinearBound::getUpper()
{
    return m_upper;
}

GnuLinearSolver::GnuLinearSolver(std::string& name, int problemType):
    m_problemObject {glp_create_prob()},
    m_name{name},
    m_problemType {problemType}
{
    glp_set_prob_name(m_problemObject, m_name.c_str());
    glp_set_obj_dir(m_problemObject, m_problemType);
}

GnuLinearSolver::~GnuLinearSolver()
{
    glp_delete_prob(m_problemObject);
}

void GnuLinearSolver::addProblemCoefficient(double coefficient)
{
    m_problemCoefficient.push_back(coefficient);
}

void GnuLinearSolver::addConstraintCoefficients(const std::vector<double>& coefficients)
{
    m_constraintCoefficient.push_back(coefficients);
}

void GnuLinearSolver::addAuxiliaryBound(const GnuLinearBound& bound)
{
    m_auxiliaryBound.push_back(bound);
}

void GnuLinearSolver::addStructuralBound(const GnuLinearBound& bound)
{
    m_structuralBound.push_back(bound);
}

const std::vector<double>& GnuLinearSolver::getResultVariables()
{
    return m_resultVariable;
}

double GnuLinearSolver::getResultProblemValue()
{
    return m_resultProblemValue;
}

void GnuLinearSolver::prepare()
{
    glp_add_rows(m_problemObject, m_auxiliaryBound.size());
    glp_add_cols(m_problemObject, m_structuralBound.size());

    for (unsigned i=0; i<m_auxiliaryBound.size(); i++)
    {
        char variableName[50];
        sprintf(variableName, "AuxiliaryVariable%d", i+1);
        glp_set_row_name(m_problemObject, i+1, variableName);
        glp_set_row_bnds(m_problemObject, i+1, m_auxiliaryBound[i].getType(), m_auxiliaryBound[i].getLower(), m_auxiliaryBound[i].getUpper());
    }
    
    for (unsigned i=0; i<m_structuralBound.size(); i++)
    {    
        char variableName[50];
        sprintf(variableName, "StructuralVariable%d", i+1);
        glp_set_col_name(m_problemObject, i+1, variableName);
        glp_set_col_bnds(m_problemObject, i+1, m_structuralBound[i].getType(), m_structuralBound[i].getLower(), m_structuralBound[i].getUpper());
        glp_set_obj_coef(m_problemObject, i+1, m_problemCoefficient[i]);
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
    m_resultProblemValue = glp_get_obj_val(m_problemObject);
    for (unsigned i=0; i<m_structuralBound.size(); i++)
        m_resultVariable.push_back(glp_get_col_prim(m_problemObject, i+1));
}
