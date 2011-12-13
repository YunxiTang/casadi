/*
 *    This file is part of CasADi.
 *
 *    CasADi -- A symbolic framework for dynamic optimization.
 *    Copyright (C) 2010 by Joel Andersson, Moritz Diehl, K.U.Leuven. All rights reserved.
 *
 *    CasADi is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License as published by the Free Software Foundation; either
 *    version 3 of the License, or (at your option) any later version.
 *
 *    CasADi is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with CasADi; if not, write to the Free Software
 *    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#ifndef PIECEWISE_SIMULATOR_INTERNAL_HPP
#define PIECEWISE_SIMULATOR_INTERNAL_HPP

#include "piecewise_simulator.hpp"
#include "simulator.hpp"
#include "fx_internal.hpp"

namespace CasADi{

/** \brief PiecewiseSimulator data storage classs
  \author Joel Andersson 
  \date 2010
*/
class PiecewiseSimulatorInternal : public FXInternal{
public:
  
  /** \brief  Constructor */
  PiecewiseSimulatorInternal(const FX& dae, const FX& output_fcn, const std::vector<double>& gridc);
  
  /** \brief  Destructor */
  virtual ~PiecewiseSimulatorInternal();
  
  /** \brief  Clone */
  virtual PiecewiseSimulatorInternal* clone() const{ return new PiecewiseSimulatorInternal(deepcopy(dae_),deepcopy(output_fcn_),gridc_);}

  /** \brief  initialize */
  virtual void init();

  /** \brief  Integrate */
  virtual void evaluate(int nfdir, int nadir);
  
  /// Get the parameters that change on a coarse time scale, sampled on the fine timescale
 	Matrix<double> getVFine() const; 

  Integrator integrator_;
  FX dae_;
  Simulator simulator_;
  
  FX output_fcn_;
  
  /** \brief The hart of this class, a casadi of simulator calls */
  FX all_output_;
  
  /** grid */
  std::vector<double> grid_;
  
  /** Coarse grid */
  std::vector<double> gridc_;
  
  /** The local non-dimensional time grid */
  std::vector<double> gridlocal_;
  
  /** \brief Number of static parameters */
  int np_;
  
  /** \brief Number of variable parameters */
  int nv_;
  
  /** \brief Number of coarse time steps */
  int ns_;
  
  /** \brief Number of fine-grained time steps */
  int nf_;
  
};
  
} // namespace CasADi

#endif // PIECEWISE_SIMULATOR_INTERNAL_HPP
