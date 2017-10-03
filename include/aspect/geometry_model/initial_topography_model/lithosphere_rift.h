/*
  Copyright (C) 2016 by the authors of the ASPECT code.

  This file is part of ASPECT.

  ASPECT is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2, or (at your option)
  any later version.

  ASPECT is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with ASPECT; see the file LICENSE.  If not see
  <http://www.gnu.org/licenses/>.
*/


#ifndef _aspect_geometry_model__initial_topography_lithosphere_rift_h
#define _aspect_geometry_model__initial_topography_lithosphere_rift_h

#include <aspect/geometry_model/initial_topography_model/interface.h>


namespace aspect
{
  namespace InitialTopographyModel
  {
    using namespace dealii;

    /**
     * A class that describes an initial topography for the geometry model,
     * by defining a set of polylines on the surface from the prm file. It
     * sets the elevation in each Polyline to a constant value.
     */
    template <int dim>
    class LithosphereRift : public Interface<dim>,
    public SimulatorAccess<dim>
    {
      public:
        /**
         * Initialization function. This function is called once at the
         * beginning of the program. Checks preconditions.
         */
        void
        initialize ();

        /**
         * Return the value of the topography for a point.
         */
        virtual
        double value (const Point<dim-1> &p) const;


        /**
         * Declare the parameters this class takes through input files.
         */
        static
        void
        declare_parameters (ParameterHandler &prm);

        /**
         * Read the parameters this class declares from the parameter file.
         */
        virtual
        void
        parse_parameters (ParameterHandler &prm);

      private:
        /**
         * The standard deviation of the Gaussian amplitude of the lithospheric thicknesses
         * with distance from the rift axis.
         */
        double sigma;

        /**
         * The maximum amplitude of the Gaussian distribution of the lithospheric thicknesses
         * with distance from the rift axis. It should have a value between -1 and 1, where positive
         * numbers represent a reduction in thickness and negative numbers an increase.
         */
        double A;

        /**
         * The maximum amplitude of the Gaussian distribution of the topography around the rift.
         */
        double topo_rift_amplitude;

        /**
         * The reference lithospheric column used in computing the topography based on isostasy
         * and the thickness of this column.
         */
        double ref_rgh;
        double compensation_depth;


        /**
         * The maximum amplitude of the topography of the polygon area.
         */
        double topo_polygon_amplitude;

        /**
         * Vector for field densities.
         */
        std::vector<double> densities;

        /**
         * Vector for the reference field thicknesses away from the rift.
         */
        std::vector<double> thicknesses;

        /**
         * Vector for the rift  thicknesses at the center.
         */
        std::vector<double> rift_thicknesses;

        /**
         * Vector for the polygon thicknesses at the center.
         */
        std::vector<double> polygon_thicknesses;

    };
  }
}


#endif