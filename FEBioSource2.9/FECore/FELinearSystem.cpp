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
#include "FELinearSystem.h"

//-----------------------------------------------------------------------------
FELinearSystem::FELinearSystem(FEGlobalMatrix& K, vector<double>& F, vector<double>& u) : m_K(K), m_F(F), m_u(u)
{
}

//-----------------------------------------------------------------------------
//! assemble global stiffness matrix
void FELinearSystem::AssembleLHS(vector<int>& elm, matrix& ke)
{
	if (elm.empty()) return;

	// assemble into the global stiffness
	m_K.Assemble(ke, elm);

	// check the prescribed contributions
	SparseMatrix& K = m_K;
	int N = ke.rows();
	int neq = m_K.Rows();

	// loop over columns
	for (int j = 0; j<N; ++j)
	{
		int J = -elm[j] - 2;
		if ((J >= 0) && (J<neq))
		{
			// dof j is a prescribed degree of freedom

			// loop over rows
			for (int i = 0; i<N; ++i)
			{
				int I = elm[i];
				if (I >= 0)
				{
					// dof i is not a prescribed degree of freedom
					m_F[I] -= ke[i][j] * m_u[J];
				}
			}

			// set the diagonal element of K to 1
			K.set(J, J, 1);

			// set the rhs vector to the prescribed value
			// that way the solution vector will contain the prescribed value
			m_F[J] = m_u[J];
		}
	}
}

//-----------------------------------------------------------------------------
void FELinearSystem::AssembleRHS(vector<int>& lm, matrix& ke, vector<double>& U)
{
	int ne = (int)lm.size();
	for (int j = 0; j<ne; ++j)
	{
		if (lm[j] >= 0)
		{
			double q = 0;
			for (int k = 0; k<ne; ++k)
			{
				if (lm[k] >= 0) q += ke[j][k] * U[lm[k]];
				else if (-lm[k] - 2 >= 0) q += ke[j][k] * U[-lm[k] - 2];
			}
			m_F[lm[j]] += q;
		}
	}
}

//-----------------------------------------------------------------------------
void FELinearSystem::AssembleRHS(vector<int>& lm, vector<double>& fe)
{
	const int n = (int)lm.size();
	for (int i = 0; i<n; ++i)
	{
		int nid = lm[i];
		if (nid >= 0) 
		{
			m_F[nid] += fe[i];
		}
	}
}
