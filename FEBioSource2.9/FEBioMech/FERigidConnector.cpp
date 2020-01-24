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
#include "FERigidConnector.h"
#include "FECore/FERigidSystem.h"
#include "FECore/FERigidBody.h"
#include "FECore/FEModel.h"
#include <FECore/FEMaterial.h>
#include <FECore/log.h>

//-----------------------------------------------------------------------------
BEGIN_PARAMETER_LIST(FERigidConnector, FENLConstraint);
	ADD_PARAMETER(m_nRBa, FE_PARAM_INT   , "body_a"        );
	ADD_PARAMETER(m_nRBb, FE_PARAM_INT   , "body_b"        );
END_PARAMETER_LIST();

int FERigidConnector::m_ncount = 0;

//-----------------------------------------------------------------------------
FERigidConnector::FERigidConnector(FEModel* pfem) : FENLConstraint(pfem) 
{
    m_F = m_M = vec3d(0, 0, 0);
	m_rbA = m_rbB = 0;
};

//-----------------------------------------------------------------------------
FERigidConnector::~FERigidConnector() {}

//-----------------------------------------------------------------------------
bool FERigidConnector::Init()
{
	// do base class first
	if (FENLConstraint::Init() == false) return false;

	// When the rigid spring is read in, the ID's correspond to the rigid materials.
	// Now we want to make the ID's refer to the rigid body ID's
	FEModel& fem = *GetFEModel();
	FEMaterial* pm = fem.GetMaterial(m_nRBa - 1);
	if (pm->IsRigid() == false)
	{
		felog.printbox("FATAL ERROR", "Rigid connector %d (spring) does not connect two rigid bodies\n", m_nID + 1);
		return false;
	}
	m_nRBa = pm->GetRigidBodyID();

	pm = fem.GetMaterial(m_nRBb - 1);
	if (pm->IsRigid() == false)
	{
		felog.printbox("FATAL ERROR", "Rigid connector %d (spring) does not connect two rigid bodies\n", m_nID);
		return false;
	}
	m_nRBb = pm->GetRigidBodyID();

	// get the actual rigid bodies
	FERigidSystem& rs = *fem.GetRigidSystem();
	m_rbA = rs.Object(m_nRBa);
	m_rbB = rs.Object(m_nRBb);

	return true;
}

//-----------------------------------------------------------------------------
void FERigidConnector::BuildMatrixProfile(FEGlobalMatrix& M)
{
    vector<int> lm(12);
                    
    int* lm1 = m_rbA->m_LM;
    int* lm2 = m_rbB->m_LM;
                    
    for (int j=0; j<6; ++j) lm[j  ] = lm1[j];
    for (int j=0; j<6; ++j) lm[j+6] = lm2[j];
    M.build_add(lm);
}

//-----------------------------------------------------------------------------
void FERigidConnector::Serialize(DumpStream& ar)
{
	FENLConstraint::Serialize(ar);
	if (ar.IsSaving())
	{
        ar << m_nID;
        ar << m_nRBa << m_nRBb;
        ar << m_F << m_M;
	}
	else
	{
        ar >> m_nID;
        ar >> m_nRBa >> m_nRBb;
        ar >> m_F >> m_M;

		// get the actual rigid bodies
		FERigidSystem& rs = *GetFEModel()->GetRigidSystem();
		m_rbA = rs.Object(m_nRBa);
		m_rbB = rs.Object(m_nRBb);
	}
}
