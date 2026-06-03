// Copyright 2025 UNN-CS
#ifndef INCLUDE_TASKS_H_
#define INCLUDE_TASKS_H_

struct PoolCosts {
  double concreteCost;
  double fenceCost;
  double totalCost;
};

double getEarthRopeGap(double earthRadiusKm = 6378.1,
                       double addedRopeMeters = 1.0);

PoolCosts calculatePoolCosts(double poolRadius = 3.0,
                             double trackWidth = 1.0,
                             double concretePricePerSqM = 1000.0,
                             double fencePricePerM = 2000.0);

#endif  // INCLUDE_TASKS_H_
