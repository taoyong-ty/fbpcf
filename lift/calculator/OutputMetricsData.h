/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include "../common/GroupedLiftMetrics.h"

namespace private_lift {
/*
 * Simple struct representing the metrics in a Lift computation
 */
struct OutputMetricsData {
  int64_t testPopulation;
  int64_t controlPopulation;
  // For conversion_lift, events == conversions
  // For converter_lift, events == buyers
  int64_t testEvents;
  int64_t controlEvents;
  int64_t testValue;
  int64_t controlValue;
  int64_t testSquared;
  int64_t controlSquared;

  OutputMetricsData() = default;

  OutputMetricsData(bool isConversionLift)
      : isConversionLift_{isConversionLift} {}

  bool isConversionLift() const {
    return isConversionLift_;
  }

  friend std::ostream& operator<<(
      std::ostream& os,
      const OutputMetricsData& out) {
    if (out.isConversionLift()) {
      os << "Test Conversions: " << out.testEvents << "\n";
      os << "Control Conversions: " << out.controlEvents << "\n";
    } else {
      os << "Test Buyers: " << out.testEvents << "\n";
      os << "Control Buyers: " << out.controlEvents << "\n";
    }
    os << "Test Value: " << out.testValue << "\n";
    os << "Control Value: " << out.controlValue << "\n";
    os << "Test Squared: " << out.testSquared << "\n";
    os << "Control Squared: " << out.controlSquared << "\n";
    os << "Test Population: " << out.testPopulation << "\n";
    os << "Control Population: " << out.controlPopulation << "\n";
    return os;
  }

  // Helper method that converts the output metrics of a game implementation
  // to a common lift metrics representation. The LiftMetrics introduced in
  // D22969707 serve as the common metrics data structure between game and
  // aggregator
  LiftMetrics toLiftMetrics() const {
    LiftMetrics metrics{};
    metrics.testPopulation = testPopulation;
    metrics.controlPopulation = controlPopulation;
    metrics.testBuyers = testEvents;
    metrics.controlBuyers = controlEvents;
    metrics.testValue = testValue;
    metrics.controlValue = controlValue;
    metrics.testSquared = testSquared;
    metrics.controlSquared = controlSquared;
    return metrics;
  }

 private:
  bool isConversionLift_;
};

} // namespace private_lift
