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
#include "version.h"
#include "FECore/log.h"
#include "febio.h"
#include <stdio.h>

int febio::Hello()
{
	felog.printf("===========================================================================\n");
	felog.printf("    ______ ______ ____   _       \n");
	felog.printf("   / ____// ____// __ ) (_)____  \n");
	felog.printf("  / /_   / __/  / __  |/ // __ \ \n");
	felog.printf(" / __/  / /___ / /_/ // // /_/ / \n");
	felog.printf("/_/    /_____//_____//_/ \____/  \n");
	felog.printf("    __  ___ ______ __    _____   \n");
	felog.printf("   /  |/  // ____// /   / ___/   \n");
	felog.printf("  / /|_/ // /    / /    \__ \    \n");
	felog.printf(" / /  / // /___ / /___ ___/ /    \n");
	felog.printf("/_/  /_/ \____//_____//____/     \n");
	felog.printf("      F I N I T E   E L E M E N T S   F O R   B I O M E C H A N I C S     \n");
	felog.printf("      MCLS Modified                                                       \n");
	felog.printf("                                                                          \n");
	felog.printf("                 --- v e r s i o n - %d . %d . %d", VERSION, SUBVERSION, SUBSUBVERSION);
	if (SVNREVISION) felog.printf(" . %d ---                 \n", SVNREVISION);
	else felog.printf(" ---                 \n");
	felog.printf("                                                                           \n");
	felog.printf("                                                                           \n");
	felog.printf("  http://febio.org                                                         \n");
	felog.printf("  FEBio is a registered trademark.                                         \n");
	felog.printf("  copyright (c) 2006-2019 - All rights reserved                            \n");
	felog.printf("                                                                           \n");
	felog.printf("===========================================================================\n");
	felog.printf("\n\n");

	return 0;
}
