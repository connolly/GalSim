/* -*- c++ -*-
 * Copyright (c) 2012-2014 by the GalSim developers team on GitHub
 * https://github.com/GalSim-developers
 *
 * This file is part of GalSim: The modular galaxy image simulation toolkit.
 * https://github.com/GalSim-developers/GalSim
 *
 * GalSim is free software: redistribution and use in source and binary forms,
 * with or without modification, are permitted provided that the following
 * conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions, and the disclaimer given in the accompanying LICENSE
 *    file.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions, and the disclaimer given in the documentation
 *    and/or other materials provided with the distribution.
 */
#ifndef __INTEL_COMPILER
#if defined(__GNUC__) && __GNUC__ >= 4 && (__GNUC__ >= 5 || __GNUC_MINOR__ >= 8)
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#endif
#endif

#define BOOST_NO_CXX11_SMART_PTR
#include "boost/python.hpp"
#include "boost/python/stl_iterator.hpp"

#include "SBConvolve.h"

namespace bp = boost::python;

namespace galsim {

    struct PySBConvolve 
    {

        // This will be wrapped as a Python constructor; it accepts an arbitrary Python iterable.
        static SBConvolve* construct(const bp::object& iterable, bool real_space,
                                     boost::shared_ptr<GSParams> gsparams) 
        {
            bp::stl_input_iterator<SBProfile> begin(iterable), end;
            std::list<SBProfile> plist(begin, end);
            return new SBConvolve(plist, real_space, gsparams);
        }

        static void wrap() 
        {
            bp::class_< SBConvolve, bp::bases<SBProfile> >("SBConvolve", bp::no_init)
                // bp tries the overloads in reverse order, so we wrap the most general one first
                // to ensure we try it last
                .def("__init__", bp::make_constructor(
                        &construct, bp::default_call_policies(), 
                        (bp::arg("slist"), bp::arg("real_space")=false,
                         bp::arg("gsparams")=bp::object()))
                )
                .def(bp::init<const SBConvolve&>())
                ;
        }

    };

    struct PySBAutoConvolve 
    {
        static void wrap() {
            bp::class_< SBAutoConvolve, bp::bases<SBProfile> >("SBAutoConvolve", bp::no_init)
                .def(bp::init<const SBProfile&, bool, boost::shared_ptr<GSParams> >(
                        (bp::arg("adaptee"), bp::arg("real_space")=false,
                         bp::arg("gsparams")=bp::object())))
                .def(bp::init<const SBAutoConvolve&>())
                ;
        }

    };

    struct PySBAutoCorrelate 
    {
        static void wrap() {
            bp::class_< SBAutoCorrelate, bp::bases<SBProfile> >("SBAutoCorrelate", bp::no_init)
                .def(bp::init<const SBProfile&, bool, boost::shared_ptr<GSParams> >(
                        (bp::arg("adaptee"), bp::arg("real_space")=false,
                         bp::arg("gsparams")=bp::object())))
                .def(bp::init<const SBAutoCorrelate&>())
                ;
        }

    };

    void pyExportSBConvolve() 
    {
        PySBConvolve::wrap();
        PySBAutoConvolve::wrap();
        PySBAutoCorrelate::wrap();
    }

} // namespace galsim
