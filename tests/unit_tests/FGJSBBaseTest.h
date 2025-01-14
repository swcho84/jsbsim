#include <string>
#include <limits>
#include <cxxtest/TestSuite.h>
#include <FGJSBBase.h>

class FGJSBBaseTest : public CxxTest::TestSuite, public JSBSim::FGJSBBase
{
public:
  void testCASConversion() {
    double p = 2116.228;
    TS_ASSERT_EQUALS(VcalibratedFromMach(-0.1, p), 0.0);
    TS_ASSERT_EQUALS(VcalibratedFromMach(0, p), 0.0);
    TS_ASSERT_DELTA(VcalibratedFromMach(0.5, p), 558.2243, 1E-4);
    TS_ASSERT_DELTA(VcalibratedFromMach(1.0, p), 1116.4486, 1E-4);
    TS_ASSERT_DELTA(VcalibratedFromMach(1.5, p), 1674.6728, 1E-4);
    TS_ASSERT_EQUALS(MachFromVcalibrated(0.0, p), 0.0);
    TS_ASSERT_DELTA(MachFromVcalibrated(558.2243, p), 0.5, 1E-4);
    TS_ASSERT_DELTA(MachFromVcalibrated(1116.4486, p), 1.0, 1E-4);
    TS_ASSERT_DELTA(MachFromVcalibrated(1674.6728, p), 1.5, 1E-4);
  }

  void testNumericRoutines() {
    double dx = 1.0;
    float  fx = 1.0;
    double dy = dx + std::numeric_limits<double>::epsilon();
    float  fy = fx + std::numeric_limits<float>::epsilon();
    TS_ASSERT(EqualToRoundoff(dx, dy));
    TS_ASSERT(EqualToRoundoff(dx, fy));
    TS_ASSERT(EqualToRoundoff(fx, fy));
    TS_ASSERT(EqualToRoundoff(fx, dy));
    TS_ASSERT_EQUALS(sign(1.235), 1.0);
    TS_ASSERT_EQUALS(sign(0.0), 1.0);
    TS_ASSERT_EQUALS(sign(-1E-5), -1.0);
    TS_ASSERT_EQUALS(Constrain(0.0,-1E-5,1.0), 0.0);
    TS_ASSERT_EQUALS(Constrain(0.0,  0.5,1.0), 0.5);
    TS_ASSERT_EQUALS(Constrain(0.0, 10.0,1.0), 1.0);
    Filter f0;
    Filter f(1.0, 1E-5);
    double x = f.execute(3.0);
    // Called twice for 100% coverage
    // Need to test that the numbers follow a Gaussian law ?
    double ran0 = GaussianRandomNumber();
    double ran1 = GaussianRandomNumber();
  }

  void testTemperatureConversion() {
    TS_ASSERT(EqualToRoundoff(KelvinToFahrenheit(0.0), -459.4));
    TS_ASSERT(EqualToRoundoff(KelvinToFahrenheit(288.15), 59.27));
    TS_ASSERT(EqualToRoundoff(CelsiusToRankine(0.0), 491.67));
    TS_ASSERT(EqualToRoundoff(CelsiusToRankine(15.0), 518.67));
    TS_ASSERT(EqualToRoundoff(RankineToCelsius(491.67), 0.0));
    TS_ASSERT_DELTA(RankineToCelsius(518.67), 15.0, 1E-8);
    TS_ASSERT(EqualToRoundoff(KelvinToRankine(0.0), 0.0));
    TS_ASSERT(EqualToRoundoff(KelvinToRankine(288.15), 518.67));
    TS_ASSERT(EqualToRoundoff(RankineToKelvin(0.0), 0.0));
    TS_ASSERT_DELTA(RankineToKelvin(518.67), 288.15, 1E-8);
    TS_ASSERT(EqualToRoundoff(CelsiusToFahrenheit(0.0), 32.0));
    TS_ASSERT(EqualToRoundoff(CelsiusToFahrenheit(15.0), 59.0));
    TS_ASSERT(EqualToRoundoff(FahrenheitToCelsius(32.0), 0.0));
    TS_ASSERT_DELTA(FahrenheitToCelsius(59.0), 15.0, 1E-8);
    TS_ASSERT(EqualToRoundoff(KelvinToCelsius(0.0), -273.15));
    TS_ASSERT(EqualToRoundoff(KelvinToCelsius(288.15), 15.0));
    TS_ASSERT(EqualToRoundoff(CelsiusToKelvin(-273.15), 0.0));
    TS_ASSERT(EqualToRoundoff(CelsiusToKelvin(15.0), 288.15));
  }

  void testMisc() {
    std::string version = GetVersion();
    disableHighLighting();
  }
};
