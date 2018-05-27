// @(#)root/tmva $Id$
// Author: Manos Stergiadis

/**********************************************************************************
 * Project: TMVA - a Root-integrated toolkit for multivariate data analysis       *
 * Package: TMVA                                                                  *
 * Class  :                                                                       *
 * Web    : http://tmva.sourceforge.net                                           *
 *                                                                                *
 * Description:                                                                   *
 *      Testing Flatten function for every architecture using templates           *
 *                                                                                *
 * Authors (alphabetical):                                                        *
 *      Manos Stergiadis      <em.stergiadis@gmail.com - CERN, Switzerland        *
 *                                                                                *
 * Copyright (c) 2005-2015:                                                       *
 *      CERN, Switzerland                                                         *
 *      U. of Victoria, Canada                                                    *
 *      MPI-K Heidelberg, Germany                                                 *
 *      U. of Bonn, Germany                                                       *
 *                                                                                *
 * Redistribution and use in source and binary forms, with or without             *
 * modification, are permitted according to the terms listed in LICENSE           *
 * (http://tmva.sourceforge.net/LICENSE)                                          *
 **********************************************************************************/


#ifndef ROOT_TESTFLATTEN_H
#define ROOT_TESTFLATTEN_H

#include <iostream>
#include "TestConvNet.h"

using namespace TMVA::DNN;
using namespace TMVA::DNN::CNN;


/*************************************************************************
 * Test 1:
 * depth = 3, width = 5, height = 5
 *************************************************************************/
template<typename Architecture_t>
void testFlatten()
{
    using Matrix_t = typename Architecture_t::Matrix_t;

    double input[][5][5] = {{{158, 157, 22, 166, 179},
                                {68, 179, 233, 110, 163},
                                {168, 216, 76, 8, 102},
                                {159, 163, 25, 78, 119},
                                {116, 50, 206, 102, 247},
                               },

                               {{187, 166, 121, 112, 136},
                                {237, 30, 180, 7, 248},
                                {52, 172, 146, 130, 92},
                                {124, 244, 214, 175, 9},
                                {80, 232, 139, 224, 237}},

                               {{53, 147, 103, 53, 110},
                                {112, 222, 19, 156, 232},
                                {81, 19, 188, 224, 220},
                                {255, 190, 76, 219, 95},
                                {245, 4, 217, 22, 22}}};

    double expected[][25] = {{158, 157, 22,  166, 179, 68, 179, 233, 110, 163, 168, 216, 76,
                                   8, 102, 159, 163, 25,  78, 119, 116, 50,  206, 102, 247},

                                {187, 166, 121, 112, 136, 237, 30, 180, 7,   248, 52,  172, 146,
                                 130, 92,  124, 244, 214, 175, 9,  80,  232, 139, 224, 237},

                                { 53,  147, 103, 53,  110, 112, 222, 19,  156, 232, 81, 19, 188,
                                 224, 220, 255, 190, 76,  219, 95,  245, 4,   217, 22, 22}};

    size_t size = 3;
    size_t nRows = 5;
    size_t nCols = 5;

    std::vector<Matrix_t> A;
    for (size_t i = 0; i < size; i++) {
        Matrix_t temp(nRows, nCols);
        for (size_t j = 0; j < nRows; j++) {
            for (size_t k = 0; k < nCols; k++) {
                temp(j, k) = input[i][j][k];
            }
        }
        A.push_back(temp);
    }

    Matrix_t B(size, nRows * nCols);
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < nRows * nCols; j++) {
            B(i, j) = expected[i][j];
        }
    }

    bool status = testFlatten<Architecture_t>(A, B, size, nRows, nCols);

    if (status)
        std::cout << "Test passed!" << std::endl;
    else
        std::cout << "Test not passed!" << std::endl;
}

/*************************************************************************
 * Test 1:
 * depth = 3, width = 5, height = 5
 *************************************************************************/
template<typename Architecture_t>
void testDeflatten()
{
    using Matrix_t = typename Architecture_t::Matrix_t;

    double input[][25] = {{158, 157, 22,  166, 179, 68, 179, 233, 110, 163, 168, 216, 76,
                           8, 102, 159, 163, 25,  78, 119, 116, 50,  206, 102, 247},

                           {187, 166, 121, 112, 136, 237, 30, 180, 7,   248, 52,  172, 146,
                            130, 92,  124, 244, 214, 175, 9,  80,  232, 139, 224, 237},

                           { 53,  147, 103, 53,  110, 112, 222, 19,  156, 232, 81, 19, 188,
                            224, 220, 255, 190, 76,  219, 95,  245, 4,   217, 22, 22}};

    double expected[][5][5] = {{{158, 157, 22, 166, 179},
                                {68, 179, 233, 110, 163},
                                {168, 216, 76, 8, 102},
                                {159, 163, 25, 78, 119},
                                {116, 50, 206, 102, 247},
                               },

                               {{187, 166, 121, 112, 136},
                                {237, 30, 180, 7, 248},
                                {52, 172, 146, 130, 92},
                                {124, 244, 214, 175, 9},
                                {80, 232, 139, 224, 237}},

                               {{53, 147, 103, 53, 110},
                                {112, 222, 19, 156, 232},
                                {81, 19, 188, 224, 220},
                                {255, 190, 76, 219, 95},
                                {245, 4, 217, 22, 22}}};

    size_t size = 3;
    size_t nRows = 5;
    size_t nCols = 5;

    Matrix_t A(size, nRows * nCols);
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < nRows * nCols; j++) {
            A(i, j) = input[i][j];
        }
    }

    std::vector<Matrix_t> B;
    for (size_t i = 0; i < size; i++) {
        Matrix_t temp(nRows, nCols);
        for (size_t j = 0; j < nRows; j++) {
            for (size_t k = 0; k < nCols; k++) {
                temp(j, k) = expected[i][j][k];
            }
        }
        B.push_back(temp);
    }

    bool status = testDeflatten<Architecture_t>(A, B, size, nRows, nCols);

    if (status)
        std::cout << "Test passed!" << std::endl;
    else
        std::cout << "Test not passed!" << std::endl;
}

#endif //ROOT_TESTFLATTEN_H