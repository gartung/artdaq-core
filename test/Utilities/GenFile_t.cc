#include "artdaq-core/Utilities/ExceptionHandler.hh"
#include "artdaq-core/Utilities/configureMessageFacility.hh"

#define BOOST_TEST_MODULE GenFile_t
#include <fhiclcpp/make_ParameterSet.h>
#include <boost/filesystem.hpp>
#include "cetlib/quiet_unit_test.hpp"
#include "cetlib_except/exception.h"

#define TRACE_NAME "GenFile_t"
#include "tracemf.h"

BOOST_AUTO_TEST_SUITE(GenFile_test)

BOOST_AUTO_TEST_CASE(genFileFileNameFlags)
{
	setenv("ARTDAQ_LOG_ROOT", "/tmp", 1);
	auto pstr = artdaq::generateMessageFacilityConfiguration("configureMessageFacility_t", true, true, "-%N-%H-%T-%U-%%-%?N-%?L-");

	fhicl::ParameterSet pset;
#ifdef SIMPLER_PSET_MAKE
	BOOST_REQUIRE_NO_THROW(pset = fhicl::ParameterSet::make(pstr));
#else
	BOOST_REQUIRE_NO_THROW(fhicl::make_ParameterSet(pstr, pset));
#endif
	mf::StartMessageFacility(pset, "configureMessageFacility_t");

	mf::LogInfo("Test") << "Test Message";
	TLOG(TLVL_INFO) << "Test TRACE";

	boost::filesystem::remove_all("/tmp/configureMessageFacility_t");
}

BOOST_AUTO_TEST_SUITE_END()