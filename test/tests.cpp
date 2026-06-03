// Copyright 2025 UNN-CS Team

#include <gtest/gtest.h>
#include <cmath>
#include <stdexcept>
#include "circle.h"
#include "tasks.h"

const double EPS = 1e-6;
const double PI = 3.14159265358979;

TEST(Circle, constructor) {
  Circle c(5.0);
  EXPECT_NEAR(c.getRadius(), 5.0, EPS);
  EXPECT_NEAR(c.getFerence(), 2.0 * PI * 5.0, EPS);
  EXPECT_NEAR(c.getArea(), PI * 25.0, EPS);
}

TEST(Circle, constructorThrows) {
  EXPECT_THROW(Circle(0.0), std::invalid_argument);
  EXPECT_THROW(Circle(-1.0), std::invalid_argument);
}

TEST(Circle, setRadius) {
  Circle c(1.0);
  c.setRadius(4.0);
  EXPECT_NEAR(c.getRadius(), 4.0, EPS);
  EXPECT_NEAR(c.getFerence(), 2.0 * PI * 4.0, EPS);
  EXPECT_THROW(c.setRadius(0.0), std::invalid_argument);
}

TEST(Circle, setFerence) {
  Circle c(1.0);
  c.setFerence(2.0 * PI * 7.0);
  EXPECT_NEAR(c.getRadius(), 7.0, EPS);
  EXPECT_THROW(c.setFerence(-10.0), std::invalid_argument);
}

TEST(Circle, setArea) {
  Circle c(1.0);
  c.setArea(PI * 9.0);
  EXPECT_NEAR(c.getRadius(), 3.0, EPS);
  EXPECT_THROW(c.setArea(0.0), std::invalid_argument);
}

TEST(EarthRope, gapIsConstant) {
  double gap1 = getEarthRopeGap(6378.1, 1.0);
  double gap2 = getEarthRopeGap(1000.0, 1.0);
  EXPECT_NEAR(gap1, gap2, EPS);
}

TEST(EarthRope, formula) {
  EXPECT_NEAR(getEarthRopeGap(6378.1, 1.0), 1.0 / (2.0 * PI), EPS);
  EXPECT_NEAR(getEarthRopeGap(6378.1, 2.0), 2.0 / (2.0 * PI), EPS);
}

TEST(EarthRope, throws) {
  EXPECT_THROW(getEarthRopeGap(0.0, 1.0), std::invalid_argument);
  EXPECT_THROW(getEarthRopeGap(6378.1, -1.0), std::invalid_argument);
}

TEST(Pool, defaults) {
  PoolCosts p = calculatePoolCosts();
  EXPECT_NEAR(p.totalCost, p.concreteCost + p.fenceCost, EPS);
}

TEST(Pool, custom) {
  PoolCosts p = calculatePoolCosts(2.0, 1.0, 500.0, 1000.0);
  double ec = (PI * 9.0 - PI * 4.0) * 500.0;
  double ef = 2.0 * PI * 3.0 * 1000.0;
  EXPECT_NEAR(p.concreteCost, ec, EPS);
  EXPECT_NEAR(p.fenceCost, ef, EPS);
}

TEST(Pool, throws) {
  EXPECT_THROW(calculatePoolCosts(0.0, 1.0, 1000.0, 2000.0),
    std::invalid_argument);
  EXPECT_THROW(calculatePoolCosts(3.0, -1.0, 1000.0, 2000.0),
    std::invalid_argument);
  EXPECT_THROW(calculatePoolCosts(3.0, 1.0, -100.0, 2000.0),
    std::invalid_argument);
}
