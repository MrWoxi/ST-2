// Copyright 2025 UNN-CS
#include <stdexcept>
#include "circle.h"
#include "tasks.h"

double getEarthRopeGap(double earthRadiusKm, double addedRopeMeters) {
  if (earthRadiusKm <= 0.0)
    throw std::invalid_argument("Earth radius must be positive");
  if (addedRopeMeters <= 0.0)
    throw std::invalid_argument("Added rope length must be positive");

  const double earthRadiusM = earthRadiusKm * 1000.0;
  Circle earth(earthRadiusM);
  earth.setFerence(earth.getFerence() + addedRopeMeters);
  return earth.getRadius() - earthRadiusM;
}

PoolCosts calculatePoolCosts(double poolRadius,
                             double trackWidth,
                             double concretePricePerSqM,
                             double fencePricePerM) {
  if (poolRadius <= 0.0)
    throw std::invalid_argument("Pool radius must be positive");
  if (trackWidth <= 0.0)
    throw std::invalid_argument("Track width must be positive");
  if (concretePricePerSqM < 0.0)
    throw std::invalid_argument("Concrete price cannot be negative");
  if (fencePricePerM < 0.0)
    throw std::invalid_argument("Fence price cannot be negative");

  Circle pool(poolRadius);
  Circle outer(poolRadius + trackWidth);

  double walkwayArea   = outer.getArea() - pool.getArea();
  double concreteCost  = walkwayArea * concretePricePerSqM;
  double fenceCost     = outer.getFerence() * fencePricePerM;

  return {concreteCost, fenceCost, concreteCost + fenceCost};
}
