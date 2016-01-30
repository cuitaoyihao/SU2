/*!
 * \file driver_structure.hpp
 * \brief Headers of the main subroutines for driving single or multi-zone problems.
 *        The subroutines and functions are in the <i>driver_structure.cpp</i> file.
 * \author T. Economon, H. Kline, R. Sanchez
 * \version 4.1.0 "Cardinal"
 *
 * SU2 Lead Developers: Dr. Francisco Palacios (Francisco.D.Palacios@boeing.com).
 *                      Dr. Thomas D. Economon (economon@stanford.edu).
 *
 * SU2 Developers: Prof. Juan J. Alonso's group at Stanford University.
 *                 Prof. Piero Colonna's group at Delft University of Technology.
 *                 Prof. Nicolas R. Gauger's group at Kaiserslautern University of Technology.
 *                 Prof. Alberto Guardone's group at Polytechnic University of Milan.
 *                 Prof. Rafael Palacios' group at Imperial College London.
 *
 * Copyright (C) 2012-2015 SU2, the open-source CFD code.
 *
 * SU2 is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * SU2 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with SU2. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "../../Common/include/mpi_structure.hpp"
#include "iteration_structure.hpp"
#include "solver_structure.hpp"
#include "integration_structure.hpp"
#include "output_structure.hpp"
#include "numerics_structure.hpp"
#include "../../Common/include/geometry_structure.hpp"
#include "../../Common/include/grid_movement_structure.hpp"
#include "../../Common/include/config_structure.hpp"

using namespace std;

/*! 
 * \class CDriver
 * \brief Parent class for driving an iteration of a single or multi-zone problem.
 * \author T. Economon
 * \version 4.1.0 "Cardinal"
 */
class CDriver {
protected:
  unsigned short nZone;	/*!< \brief Total number of zones in the problem. */

public:
	
	/*! 
	 * \brief Constructor of the class.
	 * \param[in] iteration_container - Container vector with all the iteration methods.
   * \param[in] solver_container - Container vector with all the solutions.
   * \param[in] geometry_container - Geometrical definition of the problem.
   * \param[in] integration_container - Container vector with all the integration methods.
   * \param[in] numerics_container - Description of the numerical method (the way in which the equations are solved).
   * \param[in] config - Definition of the particular problem.
   * \param[in] val_nZone - Total number of zones.
	 */
  CDriver(CIteration **iteration_container,
          CSolver ****solver_container,
          CGeometry ***geometry_container,
          CIntegration ***integration_container,
          CNumerics *****numerics_container,
          CConfig **config,
          unsigned short val_nZone);
	
	/*!
	 * \brief Destructor of the class.
	 */
	virtual ~CDriver(void);

	/*!
	 * \brief A virtual member.
	 * \param[in] iteration_container - Container vector with all the iteration methods.
   * \param[in] output - Pointer to the COutput class.
   * \param[in] integration_container - Container vector with all the integration methods.
   * \param[in] geometry_container - Geometrical definition of the problem.
   * \param[in] solver_container - Container vector with all the solutions.
   * \param[in] numerics_container - Description of the numerical method (the way in which the equations are solved).
   * \param[in] config_container - Definition of the particular problem.
   * \param[in] surface_movement - Surface movement classes of the problem.
   * \param[in] grid_movement - Volume grid movement classes of the problem.
   * \param[in] FFDBox - FFD FFDBoxes of the problem.
	 */
  
  virtual void Run(CIteration **iteration_container,
                   COutput *output,
                   CIntegration ***integration_container,
                   CGeometry ***geometry_container,
                   CSolver ****solver_container,
                   CNumerics *****numerics_container,
                   CConfig **config_container,
                   CSurfaceMovement **surface_movement,
                   CVolumetricMovement **grid_movement,
                   CFreeFormDefBox*** FFDBox){};
  /*!
   * \brief Definition of the physics iteration class or within a single zone.
   * \param[in] iteration_container - Pointer to the iteration container to be instantiated.
   * \param[in] config - Definition of the particular problem.
   * \param[in] iZone - Index of the zone.
   */
  void Iteration_Preprocessing(CIteration **iteration_container, CConfig **config, unsigned short iZone);

  /*!
   * \brief Definition and allocation of all solution classes.
   * \param[in] solver_container - Container vector with all the solutions.
   * \param[in] geometry - Geometrical definition of the problem.
   * \param[in] config - Definition of the particular problem.
   */
  void Solver_Preprocessing(CSolver ***solver_container, CGeometry **geometry, CConfig *config);

  /*!
   * \brief Definition and allocation of all integration classes.
   * \param[in] integration_container - Container vector with all the integration methods.
   * \param[in] geometry - Geometrical definition of the problem.
   * \param[in] config - Definition of the particular problem.
   */
  void Integration_Preprocessing(CIntegration **integration_container, CGeometry **geometry, CConfig *config);

  /*!
   * \brief Definition and allocation of all solver classes.
   * \param[in] numerics_container - Description of the numerical method (the way in which the equations are solved).
   * \param[in] solver_container - Container vector with all the solutions.
   * \param[in] geometry - Geometrical definition of the problem.
   * \param[in] config - Definition of the particular problem.
   */
  void Numerics_Preprocessing(CNumerics ****numerics_container, CSolver ***solver_container, CGeometry **geometry, CConfig *config);

};
/*!
 * \class CSingleZoneDriver
 * \brief Class for driving an iteration of the physics within a single zone.
 * \author T. Economon
 * \version 4.1.0 "Cardinal"
 */
class CSingleZoneDriver : public CDriver {
public:
	
	/*! 
	 * \brief Constructor of the class.
	 * \param[in] iteration_container - Container vector with all the iteration methods.
	 * \param[in] solver_container - Container vector with all the solutions.
	 * \param[in] geometry_container - Geometrical definition of the problem.
	 * \param[in] integration_container - Container vector with all the integration methods.
	 * \param[in] numerics_container - Description of the numerical method (the way in which the equations are solved).
	 * \param[in] config - Definition of the particular problem.
	 * \param[in] val_nZone - Total number of zones.
	 */
  CSingleZoneDriver(CIteration **iteration_container,
                    CSolver ****solver_container,
                    CGeometry ***geometry_container,
                    CIntegration ***integration_container,
                    CNumerics *****numerics_container,
                    CConfig **config,
                    unsigned short val_nZone);
	
	/*!
	 * \brief Destructor of the class.
	 */
	~CSingleZoneDriver(void);
	
	/*! 
	 * \brief Run a single iteration of the physics within a single zone.
	 * \param[in] iteration_container - Container vector with all the iteration methods.
   * \param[in] output - Pointer to the COutput class.
   * \param[in] integration_container - Container vector with all the integration methods.
   * \param[in] geometry_container - Geometrical definition of the problem.
   * \param[in] solver_container - Container vector with all the solutions.
   * \param[in] numerics_container - Description of the numerical method (the way in which the equations are solved).
   * \param[in] config_container - Definition of the particular problem.
   * \param[in] surface_movement - Surface movement classes of the problem.
   * \param[in] grid_movement - Volume grid movement classes of the problem.
   * \param[in] FFDBox - FFD FFDBoxes of the problem.
	 */
  
  void Run(CIteration **iteration_container,
           COutput *output,
           CIntegration ***integration_container,
           CGeometry ***geometry_container,
           CSolver ****solver_container,
           CNumerics *****numerics_container,
           CConfig **config_container,
           CSurfaceMovement **surface_movement,
           CVolumetricMovement **grid_movement,
           CFreeFormDefBox*** FFDBox);


};


/*!
 * \class CMultiZoneDriver
 * \brief Class for driving an iteration of the physics within multiple zones.
 * \author T. Economon
 * \version 4.1.0 "Cardinal"
 */
class CMultiZoneDriver : public CDriver {
public:
  
  /*!
   * \brief Constructor of the class.
   * \param[in] iteration_container - Container vector with all the iteration methods.
   * \param[in] solver_container - Container vector with all the solutions.
   * \param[in] geometry_container - Geometrical definition of the problem.
   * \param[in] integration_container - Container vector with all the integration methods.
   * \param[in] numerics_container - Description of the numerical method (the way in which the equations are solved).
   * \param[in] config - Definition of the particular problem.
   * \param[in] val_nZone - Total number of zones.
   */
  CMultiZoneDriver(CIteration **iteration_container,
                   CSolver ****solver_container,
                   CGeometry ***geometry_container,
                   CIntegration ***integration_container,
                   CNumerics *****numerics_container,
                   CConfig **config,
                   unsigned short val_nZone);
  
  /*!
   * \brief Destructor of the class.
   */
  ~CMultiZoneDriver(void);
  
  /*!
   * \brief Run a single iteration of the physics within multiple zones.
   * \param[in] iteration_container - Container vector with all the iteration methods.
   * \param[in] output - Pointer to the COutput class.
   * \param[in] integration_container - Container vector with all the integration methods.
   * \param[in] geometry_container - Geometrical definition of the problem.
   * \param[in] solver_container - Container vector with all the solutions.
   * \param[in] numerics_container - Description of the numerical method (the way in which the equations are solved).
   * \param[in] config_container - Definition of the particular problem.
   * \param[in] surface_movement - Surface movement classes of the problem.
   * \param[in] grid_movement - Volume grid movement classes of the problem.
   * \param[in] FFDBox - FFD FFDBoxes of the problem.
   */
  
  void Run(CIteration **iteration_container,
           COutput *output,
           CIntegration ***integration_container,
           CGeometry ***geometry_container,
           CSolver ****solver_container,
           CNumerics *****numerics_container,
           CConfig **config_container,
           CSurfaceMovement **surface_movement,
           CVolumetricMovement **grid_movement,
           CFreeFormDefBox*** FFDBox);

};


/*!
 * \class CSpectralDriver
 * \brief Class for driving an iteration of a spectral method problem using multiple zones.
 * \author T. Economon
 * \version 4.1.0 "Cardinal"
 */
class CSpectralDriver : public CDriver {
public:
  
  /*!
   * \brief Constructor of the class.
   * \param[in] iteration_container - Container vector with all the iteration methods.
   * \param[in] solver_container - Container vector with all the solutions.
   * \param[in] geometry_container - Geometrical definition of the problem.
   * \param[in] integration_container - Container vector with all the integration methods.
   * \param[in] numerics_container - Description of the numerical method (the way in which the equations are solved).
   * \param[in] config - Definition of the particular problem.
   * \param[in] val_nZone - Total number of zones.
   */
  CSpectralDriver(CIteration **iteration_container,
                   CSolver ****solver_container,
                   CGeometry ***geometry_container,
                   CIntegration ***integration_container,
                   CNumerics *****numerics_container,
                   CConfig **config,
                   unsigned short val_nZone);
  
  /*!
   * \brief Destructor of the class.
   */
  ~CSpectralDriver(void);
  
  /*!
   * \brief Run a single iteration of a spectral method problem.
   * \param[in] iteration_container - Container vector with all the iteration methods.
   * \param[in] output - Pointer to the COutput class.
   * \param[in] integration_container - Container vector with all the integration methods.
   * \param[in] geometry_container - Geometrical definition of the problem.
   * \param[in] solver_container - Container vector with all the solutions.
   * \param[in] numerics_container - Description of the numerical method (the way in which the equations are solved).
   * \param[in] config_container - Definition of the particular problem.
   * \param[in] surface_movement - Surface movement classes of the problem.
   * \param[in] grid_movement - Volume grid movement classes of the problem.
   * \param[in] FFDBox - FFD FFDBoxes of the problem.
   */
  
  void Run(CIteration **iteration_container,
           COutput *output,
           CIntegration ***integration_container,
           CGeometry ***geometry_container,
           CSolver ****solver_container,
           CNumerics *****numerics_container,
           CConfig **config_container,
           CSurfaceMovement **surface_movement,
           CVolumetricMovement **grid_movement,
           CFreeFormDefBox*** FFDBox);
  
  /*!
   * \brief Computation and storage of the time spectral source terms.
   * \author T. Economon, K. Naik
   * \param[in] geometry - Geometrical definition of the problem.
   * \param[in] solver_container - Container vector with all the solutions.
   * \param[in] config - Definition of the particular problem.
   * \param[in] nZone - Total number of zones (periodic instances).
   * \param[in] iZone - Current zone number.
   */
  void SetSpectralMethod(CGeometry ***geometry_container, CSolver ****solver_container,
                       CConfig **config_container, unsigned short nZone, unsigned short iZone);
  
  /*!
   * \brief Computation of the Time-Spectral operator matrix.
   * \author K. Naik
   * \param[in] D - su2double pointer to the operator matrix.
   * \param[in] nZone - Total number of zones (periodic instances).
   */
  void ComputeTimeSpectral_Operator(su2double **D, su2double period, unsigned short nZone);
    
    /*!
     * \brief Dense matrix matrix Product A*B - A(nRows_prod*nRows_prod), B(nRows_prod*nCols_prod)
     * \param[in] nRows_prod - nRows of product matrix, nCols_prod - nCols of product matrix
     */
    void MatrixMatrixProduct(unsigned short nRows_prod, unsigned short nCols_prod, su2double *matrix_a, su2double *matrix_b, su2double *product);
    
    /*!
     * \brief Inverse of dense square matrix using Gauss-Jordan elimination
     * \author Sravya NImmagadda
     * \param[in] nVar_mat - size of square matrix (nRows/nCols)
     * *block and *invblock - pointers to matrix and its inverse
     */
    void InverseBlock(unsigned short nVar_mat, su2double *block, su2double *invBlock);
    
    /*!
     * \brief Computation of the Harmonic-Balance operator matrix.
     * \author Sravya Nimmagadda
     * \param[in] D - double pointer to the operator matrix.
     * \param[in] omega_HB - single pointer to array of frequency values to be modelled.
     * \param[in] nHarmonics - Total number of harmonics (Number of Frequency values).
     * \param[in] nZone - Total number of zones (periodic instances).
     */
    void ComputeHarmonicBalance_Operator(su2double **D, su2double *omega_HB, su2double period, unsigned short nZone);
    
    /*!
     * \brief Computation and storage of the time-spectral mesh velocities.
     * \author K. Naik, T. Economon
     * \param[in] geometry - Geometrical definition of the problem.
     * \param[in] config - Definition of the particular problem.
     * \param[in] nZone - Total number of zones (periodic instances).
     */
    void SetTimeSpectral_Velocities(CGeometry ***geometry_container,
                                      CConfig **config_container, unsigned short nZone);

};


/*!
 * \class CFSIDriver
 * \brief Class for driving a BGS iteration for a fluid-structure interaction problem in multiple zones.
 * \author R. Sanchez.
 * \version 4.1.0 "Cardinal"
 */
class CFSIDriver : public CDriver {
public:

	/*!
	 * \brief Constructor of the class.
	 * \param[in] iteration_container - Container vector with all the iteration methods.
   * \param[in] solver_container - Container vector with all the solutions.
   * \param[in] geometry_container - Geometrical definition of the problem.
   * \param[in] integration_container - Container vector with all the integration methods.
   * \param[in] numerics_container - Description of the numerical method (the way in which the equations are solved).
   * \param[in] config - Definition of the particular problem.
   * \param[in] val_nZone - Total number of zones.
	 */
  CFSIDriver(CIteration **iteration_container,
             CSolver ****solver_container,
             CGeometry ***geometry_container,
             CIntegration ***integration_container,
             CNumerics *****numerics_container,
             CConfig **config,
             unsigned short val_nZone);

	/*!
	 * \brief Destructor of the class.
	 */
	~CFSIDriver(void);

	/*!
	 * \brief Run a Block Gauss-Seidel iteration of the FSI problem.
	 * \param[in] iteration_container - Container vector with all the iteration methods.
   * \param[in] output - Pointer to the COutput class.
   * \param[in] integration_container - Container vector with all the integration methods.
   * \param[in] geometry_container - Geometrical definition of the problem.
   * \param[in] solver_container - Container vector with all the solutions.
   * \param[in] numerics_container - Description of the numerical method (the way in which the equations are solved).
   * \param[in] config_container - Definition of the particular problem.
   * \param[in] surface_movement - Surface movement classes of the problem.
   * \param[in] grid_movement - Volume grid movement classes of the problem.
   * \param[in] FFDBox - FFD FFDBoxes of the problem.
	 */
  
  void Run(CIteration **iteration_container,
           COutput *output,
           CIntegration ***integration_container,
           CGeometry ***geometry_container,
           CSolver ****solver_container,
           CNumerics *****numerics_container,
           CConfig **config_container,
           CSurfaceMovement **surface_movement,
           CVolumetricMovement **grid_movement,
           CFreeFormDefBox*** FFDBox);

};

