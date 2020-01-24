/*This file is part of the FEBio source code and is licensed under the MIT license
listed below.

See Copyright-FEBio.txt for details.

Copyright (c) 2019 University of Utah, The Trustees of Columbia University in 
the City of New York, and others.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/


#include "stdafx.h"
#include "FECarreauFluid.h"
#include "FEFluid.h"

// define the material parameters
BEGIN_PARAMETER_LIST(FECarreauFluid, FEViscousFluid)
ADD_PARAMETER2(m_mu0, FE_PARAM_DOUBLE, FE_RANGE_GREATER_OR_EQUAL(0.0), "mu0");
ADD_PARAMETER2(m_mui, FE_PARAM_DOUBLE, FE_RANGE_GREATER_OR_EQUAL(0.0), "mui");
ADD_PARAMETER2(m_lam, FE_PARAM_DOUBLE, FE_RANGE_GREATER_OR_EQUAL(0.0), "lambda");
ADD_PARAMETER2(m_n  , FE_PARAM_DOUBLE, FE_RANGE_GREATER_OR_EQUAL(0.0), "n");
END_PARAMETER_LIST();

//-----------------------------------------------------------------------------
//! Constructor.
FECarreauFluid::FECarreauFluid(FEModel* pfem) : FEViscousFluid(pfem)
{
    m_mu0 = 0;
    m_mui = 0;
    m_lam = 0;
    m_n = 1;
}

//-----------------------------------------------------------------------------
//! viscous stress
mat3ds FECarreauFluid::Stress(FEMaterialPoint& pt)
{
    FEFluidMaterialPoint& vt = *pt.ExtractData<FEFluidMaterialPoint>();
    mat3ds D = vt.RateOfDeformation();
    double mu = ShearViscosity(pt);
    
    mat3ds s = D*(2*mu);
    
    return s;
}

//-----------------------------------------------------------------------------
//! tangent of stress with respect to strain J
mat3ds FECarreauFluid::Tangent_Strain(FEMaterialPoint& mp)
{
    return mat3ds(0,0,0,0,0,0);
}

//-----------------------------------------------------------------------------
//! tangent of stress with respect to rate of deformation tensor D
tens4ds FECarreauFluid::Tangent_RateOfDeformation(FEMaterialPoint& pt)
{
    FEFluidMaterialPoint& vt = *pt.ExtractData<FEFluidMaterialPoint>();
    mat3ds D = vt.RateOfDeformation();
    double gdot = sqrt(2*(D*D).tr());
    double lamg2 = m_lam*m_lam*gdot*gdot;
    
    double mu = m_mui + (m_mu0 - m_mui)*pow(1+lamg2, (m_n-1)*0.5);
    double dmu = 2*(m_mu0 - m_mui)*(m_n-1)*m_lam*m_lam*pow(1+lamg2, (m_n-3)*0.5);
    mat3dd I(1.0);
    tens4ds c = dyad1s(D)*(2*dmu) + dyad4s(I)*(2*mu);
    return c;
}

//-----------------------------------------------------------------------------
//! dynamic viscosity
double FECarreauFluid::ShearViscosity(FEMaterialPoint& pt)
{
    FEFluidMaterialPoint& vt = *pt.ExtractData<FEFluidMaterialPoint>();
    mat3ds D = vt.RateOfDeformation();
    double gdot = sqrt(2*(D*D).tr());
    double mu = m_mui + (m_mu0 - m_mui)*pow(1+m_lam*m_lam*gdot*gdot, (m_n-1)*0.5);
    return mu;
}

//-----------------------------------------------------------------------------
//! bulk viscosity
double FECarreauFluid::BulkViscosity(FEMaterialPoint& pt)
{
    return 2*ShearViscosity(pt)/3.;
}
