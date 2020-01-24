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


#pragma once
#include "FEBiphasic.h"

//-----------------------------------------------------------------------------
// This class implements a poroelastic material that has a strain-dependent
// permeability which is orthotropic in the reference state, but exhibits
// further strain-induced anisotropy, according to the constitutive relation
// of Ateshian and Weiss (JBME 2010)

class FEPermRefTransIso :	public FEHydraulicPermeability
	{
	public:
		//! constructor
		FEPermRefTransIso(FEModel* pfem);
		
		//! permeability
		mat3ds Permeability(FEMaterialPoint& pt) override;
		
		//! Tangent of permeability
		tens4ds Tangent_Permeability_Strain(FEMaterialPoint& mp) override;
		
	public:
		double	m_perm0;		//!< permeability for I term
		double	m_perm1T;		//!< transverse permeability for b term
		double	m_perm1A;		//!< axial permeability for b term
		double	m_perm2T;		//!< transverse permeability for b^2 term
		double	m_perm2A;		//!< axial permeability for b^2 term
		double	m_M0;			//!< nonlinear exponential coefficient for I term
		double	m_MT;			//!< nonlinear exponential coefficient for transverse direction
		double	m_MA;			//!< nonlinear exponential coefficient for axial direction
		double	m_alpha0;		//!< nonlinear power exponent for I term
		double	m_alphaT;		//!< nonlinear power exponent for transverse direction
		double	m_alphaA;		//!< nonlinear power exponent for axial direction
		
		// declare parameter list
		DECLARE_PARAMETER_LIST();
	};
