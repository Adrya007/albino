#include "computus.h"

#include <boost/python.hpp>
using namespace boost::python;

BOOST_PYTHON_MODULE(calc)
{
    boost::python::def("computeCatholic", Computus::computeCatholic);
    boost::python::def("computeOrtodox",Computus::computeOrtodox);
    
    boost::python::def("checkYear", Computus::checkYear);
    boost::python::def("doGauss", Computus::doGauss);
    boost::python::def("julianToGregorian", Computus::julianToGregorian);
    
}

