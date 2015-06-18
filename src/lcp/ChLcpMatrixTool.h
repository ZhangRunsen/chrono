//
// PROJECT CHRONO - http://projectchrono.org
//
// Copyright (c) 2010-2011 Alessandro Tasora
// Copyright (c) 2013 Project Chrono
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file at the top level of the distribution
// and at http://projectchrono.org/license-chrono.txt.
//

#ifndef CHLCPMATRIXTOOL_H
#define CHLCPMATRIXTOOL_H

#include "core/ChSpmatrix.h"

namespace chrono{

	typedef void (ChSparseMatrixBase::* ChSparseMatrixSetElementPtr)(int, int, double); // type for SetElement
	typedef void (ChSparseMatrixBase::* ChSparseMatrixPasteMatrixPtr)(ChMatrix<>*, int, int); // type for PasteMatrix
	typedef void (ChSparseMatrixBase::* ChSparseMatrixPasteMatrixFloatPtr)(ChMatrix<float>*, int, int); // type for PasteMatrixFloat and transposed versionk
	typedef void (ChSparseMatrixBase::* ChSparseMatrixPasteClippedMatrixPtr)(ChMatrix<>*, int, int, int, int, int, int ); // type for PasteClippedMatrix and PasteSumClippedMatrix
	typedef void (ChSparseMatrixBase::* ChSparseMatrixResetPtr)(int, int); // type for Reset

	class ChApi ChLcpMatrixTool{
		//
		// POINTERs TO MATRIX MEMBER FUNCTIONS
		//
	public: // it should be protected and made friend of LcpVariables, LcpConstraint, LcpKblock?, LcpSystemDescriptor?
		static int prova; // dummy variable used in testing

		static int n; // overall matrix dimension
		static int m; // stiffness/mass matrix dimension
		static ChSparseMatrixBase* output_matrix;
		static struct MatrixFunctions {
			static ChSparseMatrixSetElementPtr			SetElementPtr;
			static ChSparseMatrixPasteMatrixPtr			PasteMatrixPtr;
			static ChSparseMatrixPasteMatrixPtr			PasteTranspMatrixPtr;
			static ChSparseMatrixPasteMatrixFloatPtr	PasteMatrixFloatPtr; // is this function replaceable?
			static ChSparseMatrixPasteMatrixFloatPtr	PasteTranspMatrixFloatPtr;
			static ChSparseMatrixPasteClippedMatrixPtr	PasteClippedMatrixPtr;
			static ChSparseMatrixPasteClippedMatrixPtr	PasteSumClippedMatrixPtr;
			static ChSparseMatrixResetPtr				ResetPtr;
		}; // addresses of various methods of the (derived) matrix

		template <class SparseMatrixType>
		void SetMatrixTools(SparseMatrixType* dest_matrix){
			output_matrix = (ChSparseMatrixBase*)dest_matrix; // explicit just to be clear
			MatrixFunctions::SetElementPtr				= (ChSparseMatrixSetElementPtr)			&SparseMatrixType::SetElement;
			MatrixFunctions::PasteMatrixPtr				= (ChSparseMatrixPasteMatrixPtr)		&SparseMatrixType::PasteMatrix;
			MatrixFunctions::TranspPasteMatrixPtr		= (ChSparseMatrixPasteMatrixPtr)		&SparseMatrixType::TranspPasteMatrix;
			MatrixFunctions::PasteMatrixFloatPtr		= (ChSparseMatrixPasteMatrixFloatPtr)	&SparseMatrixType::PasteMatrixFloat;
			MatrixFunctions::PasteTranspMatrixFloatPtr	= (ChSparseMatrixPasteMatrixFloatPtr)	&SparseMatrixType::PasteTranspMatrixFloat;
			MatrixFunctions::PasteClippedMatrixPtr		= (ChSparseMatrixPasteClippedMatrixPtr)	&SparseMatrixType::PasteClippedMatrix;
			MatrixFunctions::PasteSumClippedMatrixPtr	= (ChSparseMatrixPasteClippedMatrixPtr)	&SparseMatrixType::PasteSumClippedMatrix;
			MatrixFunctions::ResetPtr					= (ChSparseMatrixResetPtr)&SparseMatrixType::Reset;
		}
	}; // END class ChLcpMatrixTool



} // END namespace chrono

#endif