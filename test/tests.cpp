// Copyright 2025 UNN-CS Team

#include <gtest/gtest.h>
#include <cmath>
#include <stdexcept>
#include "circle.h"
#include "tasks.h"

const double EPS = 1e-6;
const double PI = 3.14159265358979;

TEST(Circle, constructorSetsRadius) {
  Circle c(5.0);
  EXPECT_NEAR(c.getRadius(), 5.0, EPS);
}
TEST(Circle, constructorSetsFerence) {
  Circle c(5.0);
  EXPECT_NEAR(c.getFerence(), 2.0 * PI * 5.0, EPS);
}
TEST(Circle, constructorSetsArea) {
  Circle c(5.0);
  EXPECT_NEAR(c.getArea(), PI * 25.0, EPS);
}
TEST(Circle, constructorThrowsZero) {
  EXPECT_THROW(Circle(0.0), std::invalid_argument);
}
TEST(Circle, constructorThrowsNegative) {
  EXPECT_THROW(Circle(-3.0), std::invalid_argument);
}
TEST(Circle, setRadiusUpdatesAll) {
  Circle c(1.0);
  c.setRadius(4.0);
  EXPECT_NEAR(c.getRadius(), 4.0, EPS);
  EXPECT_NEAR(c.getFerence(), 2.0 * PI * 4.0, EPS);
  EXPECT_NEAR(c.getArea(), PI * 16.0, EPS);
}
TEST(Circle, setRadiusThrowsZero) {
  Circle c(1.0);
  EXPECT_THROW(c.setRadius(0.0), std::invalid_argument);
}
TEST(Circle, setRadiusThrowsNegative) {
  Circle c(1.0);
  EXPECT_THROW(c.setRadius(-1.0), std::invalid_argument);
}
TEST(Circle, setFerenceUpdatesAll) {
  Circle c(1.0);
  c.setFerence(2.0 * PI * 7.0);
  EXPECT_NEAR(c.getRadius(), 7.0, EPS);
  EXPECT_NEAR(c.getArea(), PI * 49.0, EPS);
}
TEST(Circle, setFerenceThrows) {
  Circle c(1.0);
  EXPECT_THROW(c.setFerence(0.0), std::invalid_argument);
  EXPECT_THROW(c.setFerence(-5.0), std::invalid_argument);
}
TEST(Circle, setAreaUpdatesAll) {
  Circle c(1.0);
  c.setArea(PI * 9.0);
  EXPECT_NEAR(c.getRadius(), 3.0, EPS);
  EXPECT_NEAR(c.getFerence(), 2.0 * PI * 3.0, EPS);
}
TEST(Circle, setAreaThrows) {
  Circle c(1.0);
  EXPECT_THROW(c.setArea(0.0), std::invalid_argument);
  EXPECT_THROW(c.setArea(-1.0), std::invalid_argument);
}
TEST(Circle, chainedUpdates) {
  Circle c(2.0);
  c.setArea(PI * 4.0);
  c.setFerence(2.0 * PI * 6.0);
  EXPECT_NEAR(c.getRadius(), 6.0, EPS);
}

TEST(EarthRope, gapIsConstant) {
  double g1 = getEarthRopeGap(6378.1, 1.0);
  double g2 = getEarthRopeGap(1000.0, 1.0);
  EXPECT_NEAR(g1, g2, EPS);
}
TEST(EarthRope, oneMeterFormula) {
  EXPECT_NEAR(getEarthRopeGap(6378.1, 1.0), 1.0 / (2.0 * PI), EPS);
}
TEST(EarthRope, twoMeterFormula) {
  EXPECT_NEAR(getEarthRopeGap(6378.1, 2.0), 2.0 / (2.0 * PI), EPS);
}
TEST(EarthRope, defaultArgs) {
  EXPECT_NEAR(getEarthRopeGap(), 1.0 / (2.0 * PI), EPS);
}
TEST(EarthRope, throwsZeroRadius) {
  EXPECT_THROW(getEarthRopeGap(0.0, 1.0), std::invalid_argument);
}
TEST(EarthRope, throwsNegativeRope) {
  EXPECT_THROW(getEarthRopeGap(6378.1, -1.0), std::invalid_argument);
}

TEST(Pool, totalEqualsParts) {
  PoolCosts p = calculatePoolCosts();
  EXPECT_NEAR(p.totalCost, p.concreteCost + p.fenceCost, EPS);
}
TEST(Pool, concreteCost) {
  PoolCosts p = calculatePoolCosts(3.0, 1.0, 1000.0, 2000.0);
  double area = PI * 16.0 - PI * 9.0;
  EXPECT_NEAR(p.concreteCost, area * 1000.0, EPS);
}
TEST(Pool, fenceCost) {
  PoolCosts p = calculatePoolCosts(3.0, 1.0, 1000.0, 2000.0);
  EXPECT_NEAR(p.fenceCost, 2.0 * PI * 4.0 * 2000.0, EPS);
}
TEST(Pool, customValues) {
  PoolCosts p = calculatePoolCosts(2.0, 1.0, 500.0, 1000.0);
  EXPECT_NEAR(p.concreteCost, (PI * 9.0 - PI * 4.0) * 500.0, EPS);
  EXPECT_NEAR(p.fenceCost, 2.0 * PI * 3.0 * 1000.0, EPS);
}
TEST(Pool, throwsZeroRadius) {
  EXPECT_THROW(
    calculatePoolCosts(0.0, 1.0, 1000.0, 2000.0),
    std::invalid_argument);
}
TEST(Pool, throwsNegativeTrack) {
  EXPECT_THROW(
    calculatePoolCosts(3.0, -1.0, 1000.0, 2000.0),
    std::invalid_argument);
}
TEST(Pool, throwsNegativeConcrete) {
  EXPECT_THROW(
    calculatePoolCosts(3.0, 1.0, -100.0, 2000.0),
    std::invalid_argument);
}
