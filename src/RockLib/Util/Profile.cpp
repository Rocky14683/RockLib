//
// Created by Rocky Chen on 2023/10/21.
//

#include "RockLib/Util/Profile.hpp"
#include <cmath>
#include <array>
#include <optional>

namespace RockLib {

    namespace math {

        auto findQuadRealRoots(double a, double b, double c) {
            struct Result {
                std::optional<double> rr1;
                std::optional<double> rr2;
                unsigned int numOfRoots = 0;
            };
            // (-b +- sqrt(b^2 - 4ac)) / 2a
            double delta = std::pow(b, 2) - 4.0 * a * c;
            if (delta > 0) {
                return Result{(-b + std::sqrt(delta)) / (2.0 * a), (-b - std::sqrt(delta)) / (2.0 * a), 2};
            } else if (delta == 0) {
                return Result{-b / (2.0 * a), std::nullopt, 1};
            } else return Result{};
        }

        auto findCubicRealRoots(double a, double b, double c, double d) {
            struct Result {
                std::optional<double> rr1;
                std::optional<double> rr2;
                std::optional<double> rr3;
                unsigned int numOfRoots = 0;
            };
            Result result;

            if (a == 0) {
                auto quadRoot = math::findQuadRealRoots(b, c, d);
                return Result{quadRoot.rr1, quadRoot.rr2, std::nullopt, quadRoot.numOfRoots};
            }

            if (d == 0) {
                auto quadRoot = math::findQuadRealRoots(a, b, c);
                return Result{quadRoot.rr1, quadRoot.rr2, std::nullopt, quadRoot.numOfRoots};
            }

            b /= a;
            c /= a;
            d /= a;

            double q = (3 * c - std::pow(b, 2)) / 9.0;
            double r = (b * (9.0 * c - 2.0 * std::pow(b, 2)) - (27.0 * d)) /
                       54.0; //-(27.0*d) + b*(9.0*c - 2.0*(b*b)) / 54
            double discriminant = std::pow(r, 2) + std::pow(q, 3);

            double term1 = b / 3.0;

            if (discriminant > 0) { // 1 real root
                double s = r + sqrt(discriminant);
                s = (s < 0) ? -cbrt(-s) : cbrt(s);

                double t = r - sqrt(discriminant);
                t = (t < 0) ? -cbrt(-t) : cbrt(t);

                result.rr1 = -term1 + s + t;
                result.numOfRoots = 1;

                return result;

                result.numOfRoots = 1;
            } else if (discriminant == 0) { //2 real roots
                double r13 = (r < 0) ? -cbrt(-r) : cbrt(r);
                result.rr1 = -term1 + 2.0 * r13;
                result.rr2 = -r13 - term1;
                result.numOfRoots = 2;

                return result;
            } else if (discriminant < 0) {
                q = -q;
                double dum1 = std::acos(r / std::sqrt(std::pow(q, 3)));
                double r13 = 2.0 * std::sqrt(q);

                result.rr1 = r13 * std::cos(dum1 / 3.0) - term1;
                result.rr2 = r13 * std::cos((dum1 + 2.0 * M_PI) / 3.0) - term1;
                result.rr3 = r13 * std::cos((dum1 + 4.0 * M_PI) / 3.0) - term1;
                result.numOfRoots = 3;
                return result;
            }

            return result;
        }

        double findMinPositiveTwoRoots(double r1, double r2) {
            if (r1 > 0 && r2 > 0) {
                return std::min(r1, r2);
            } else if (r1 > 0 && r2 < 0) {
                return r1;
            } else if (r1 < 0 && r2 > 0) {
                return r2;
            } else throw std::logic_error("No positive roots");
        }

        double findMinPositiveThreeRoots(double r1, double r2, double r3) {
            if (r1 > 0 && r2 > 0 && r3 > 0) {
                return std::min(std::min(r1, r2), r3);
            } else if (r1 > 0 && r3 > 0) {
                return std::min(r1, r3);
            } else if (r1 > 0 && r2 > 0) {
                return std::min(r1, r2);
            } else if (r2 > 0 && r3 > 0) {
                return std::min(r2, r3);
            } else if (r1 > 0) {
                return r1;
            } else if (r2 > 0) {
                return r2;
            } else if (r3 > 0) {
                return r3;
            } else throw std::logic_error("No positive roots");
        }
    };

    auto Profile::getMinPosAndReachedAccelToReachMaxVelocity(double v0, double vMax, double aMax, double jMax) {
        struct Result {
            double minPosToMaxVelocity;
            double reachedAccelToMaxVelocity;
        };

        std::array<double, 8> a{.0};
        std::array<double, 8> v{v0};
        std::array<double, 8> p{.0};
        double ar = std::sqrt(jMax - (vMax - v[0]));
        double t = ar / jMax;

        for (unsigned int interval = 1; interval <= 7; interval++) {
            double j;
            switch (interval) {
                case 1:
                case 3:
                case 5:
                case 7:
                    j = (interval == 1 || interval == 7) ? jMax : -jMax;
                    a[interval] = a[interval - 1] + j * t;
                    v[interval] = v[interval - 1] + a[interval - 1] * t + j * std::pow(t, 2) / 2.0;
                    p[interval] = p[interval - 1] + v[interval - 1] * t + a[interval - 1] * std::pow(t, 2) / 2.0 +
                                  j * std::pow(t, 3) / 6.0;
                    break;
                case 2:
                case 6:
                case 4:
                    a[interval] = a[interval - 1];
                    v[interval] = v[interval - 1];
                    p[interval] = interval == 4 ? (p[3] + a[3] * std::pow(t, 2) / 2.0) : p[interval - 1];
                    break;
                default:
                    throw std::runtime_error("Invalid interval");
            }

        }
        return Result{p[7], ar};
    }

    double Profile::getReachedAccelWhenNoConstAccelStage(double p, double v, double vMax, double aMax, double jMax) {
        double a = 2.0,
                b = 0.0,
                c = 4.0 * v * jMax,
                d = -std::pow(jMax, 2) * p;
        auto roots = math::findCubicRealRoots(a, b, c, d);
        switch (roots.numOfRoots) {
            case 1:
                return roots.rr1.value();
                break;
            case 2:
                return math::findMinPositiveTwoRoots(roots.rr1.value(), roots.rr2.value());
                break;
            case 3:
                return math::findMinPositiveThreeRoots(roots.rr1.value(), roots.rr2.value(), roots.rr3.value());
        }
        return 0;
    }

    auto Profile::getMinPosAndConstAccelTimeToMaxAV(double v0, double vMax, double aMax, double jMax) {
        struct Result {
            double minPosToMaxAV;
            double constAccelTimeToMaxAV;
        };

        double t = aMax / jMax;
        double ta = (vMax - v0 - (std::pow(aMax, 2) / jMax)) / aMax;
        std::array<double, 8> a{.0};
        std::array<double, 8> v{v0};
        std::array<double, 8> p{.0};

        for (unsigned int interval = 1; interval <= 7; interval++) {
            double j;
            switch (interval) {
                case 1:
                case 3:
                case 5:
                case 7:
                    j = (interval == 1 || interval == 7) ? jMax : -jMax;
                    a[interval] = a[interval - 1] + j * t;
                    v[interval] = v[interval - 1] + a[interval - 1] * t + j * std::pow(t, 2) / 2.0;
                    p[interval] = p[interval - 1] + v[interval - 1] * t + a[interval - 1] * std::pow(t, 2) / 2.0 +
                                  j * std::pow(t, 3) / 6.0;
                    break;
                case 2:
                case 6:
                case 4:
                    a[interval] = a[interval - 1];
                    v[interval] = v[interval - 1];
                    p[interval] = interval == 4 ? (p[3] + a[3] * std::pow(t, 2) / 2.0) : p[interval - 1];
                    break;
                default:
                    throw std::runtime_error("Invalid interval");
            }
        }
        return Result{p[7], ta};
    }

    double Profile::getMinPosToMaxAccel(double v0, double vMax, double aMax, double jMax) {
        double t = aMax / jMax;

        std::array<double, 8> a{.0};
        std::array<double, 8> v{v0};
        std::array<double, 8> p{.0};

        for (unsigned int interval = 1; interval <= 7; interval++) {
            double j;
            switch (interval) {
                case 1:
                case 3:
                case 5:
                case 7:
                    j = (interval == 1 || interval == 7) ? jMax : -jMax;
                    a[interval] = a[interval - 1] + j * t;
                    v[interval] = v[interval - 1] + a[interval - 1] * t + j * std::pow(t, 2) / 2.0;
                    p[interval] = p[interval - 1] + v[interval - 1] * t + a[interval - 1] * std::pow(t, 2) / 2.0 +
                                  j * std::pow(t, 3) / 6.0;
                    break;
                case 2:
                case 6:
                case 4:
                    a[interval] = a[interval - 1];
                    v[interval] = v[interval - 1];
                    p[interval] = interval == 4 ? (p[3] + a[3] * std::pow(t, 2) / 2.0) : p[interval - 1];
                    break;
                default:
                    throw std::runtime_error("Invalid interval");
            }
        }
        return p[7];
    }

    double Profile::getConstAccelTime(double p, double v0, double vMax, double aMax, double jMax) {
        //(2*am^3 + 3*am^2*jm*ta + am*jm^2*ta^2 + 4*v0*am*jm + 2*v0*jm^2*ta + p0*jm^2)/jm^2
        double a = 0.0,
                b = aMax * std::pow(jMax, 2),
                c = 3.0 * std::pow(aMax, 2) * jMax + 2.0 * v0 * std::pow(jMax, 2),
                d = 2.0 * std::pow(aMax, 3) + 4.0 * v0 * aMax * jMax - std::pow(jMax, 2) * p;
        auto roots = math::findCubicRealRoots(a, b, c, d);
        switch (roots.numOfRoots) {
            case 1:
                return roots.rr1.value();
            case 2:
                return math::findMinPositiveTwoRoots(roots.rr1.value(), roots.rr2.value());
            case 3:
                return math::findMinPositiveThreeRoots(roots.rr1.value(), roots.rr2.value(), roots.rr3.value());
        }
        return 0;
    }

    auto Profile::getMinPosReachedAccelAndJerkToReachVF(double v0, double vf, double vMax, double aMax, double jMax) {
        struct Result {
            double minPosToReachVF = .0;
            double accelToReachVF = .0;
            double taToReachVF = .0;
            double tjToReachVF = .0;
        };

        Result result;
        double aReached = std::sqrt(jMax - std::abs(vf - v0));
        double tj = aReached / jMax;
        double t = tj;
        double ta = 0.0;

        std::array<double, 4> a{.0};
        std::array<double, 4> v{v0};
        std::array<double, 4> p{.0};

        if (vf == v0) {
            return result;
        } else {
            jMax = std::copysign(jMax, vf - v0);
        }

        a[1] = a[2] = jMax * t + a[0];
        v[1] = v[2] = jMax * std::pow(jMax, 2) / 2.0 + a[0] * t + v[0];
        p[1] = p[2] = jMax * std::pow(jMax, 3) / 6.0 + a[0] * std::pow(t, 2) / 2.0 + v[0] * t + p[0];
        p[3] = -jMax * std::pow(jMax, 3) / 6.0 + a[2] * std::pow(t, 2) / 2.0 + v[2] * t + p[2];


        if (std::abs(a[2]) <= std::abs(aMax)) {
            result.minPosToReachVF = p[3];
            result.accelToReachVF = a[2];
        } else {
            tj = std::abs(aMax / jMax);
            ta = (std::abs(vf - v0) - std::abs(std::pow(aMax, 2) / jMax)) / aMax;

            a[1] = a[2] = jMax * t + a[0];
            v[1] = jMax * std::pow(jMax, 2) / 2.0 + a[0] * t + v[0];
            v[2] = a[1] * ta + v[1];
            p[1] = jMax * std::pow(jMax, 3) / 6.0 + a[0] * std::pow(t, 2) / 2.0 + v[0] * t + p[0];
            p[2] = a[1] * std::pow(ta, 2) / 2.0 + v[1] * ta + p[1];
            p[3] = -jMax * std::pow(jMax, 3) / 6.0 + a[2] * std::pow(t, 2) / 2.0 + v[2] * t + p[2];
        }
        result.taToReachVF = ta;
        result.tjToReachVF = tj;

        return result;
    }

    auto Profile::equalV0VFCasePlanning(double posDiff, double v, double vMax, double aMax, double jMax) {
        struct Result {
            double tAtMaxJerk = .0;
            double tAtMaxAccel = .0;
            double tAtMaxVelocity = .0;
            double reachedVel = .0;
            double reachedAccel = .0;
        };
        Result result;

        auto [MinPosToMV, ReachedAccelToMV] = Profile::getMinPosAndReachedAccelToReachMaxVelocity(v, vMax, aMax,
                                                                                                  jMax);
        if (ReachedAccelToMV <= aMax) {
            result.reachedVel = vMax;
            result.reachedAccel = ReachedAccelToMV;
            result.tAtMaxJerk = ReachedAccelToMV / jMax;

            if (posDiff > MinPosToMV) {
                result.tAtMaxVelocity = (posDiff - MinPosToMV) / vMax;
            } else {
                double accel = Profile::getReachedAccelWhenNoConstAccelStage(posDiff, v, vMax, aMax, jMax);
                result.tAtMaxJerk = accel / jMax;
            }
        } else if (ReachedAccelToMV > aMax) {
            auto [MinPosToMAV, _] = Profile::getMinPosAndConstAccelTimeToMaxAV(v, vMax, aMax, jMax);
            result.reachedVel = vMax;
            result.reachedAccel = aMax;
            result.tAtMaxJerk = aMax / jMax;
            result.tAtMaxVelocity = .0;

            if (posDiff >= MinPosToMAV) {
                result.tAtMaxVelocity = (posDiff - MinPosToMAV) / vMax;
            } else {
                double MinPosToMaxA = Profile::getMinPosToMaxAccel(v, vMax, aMax, jMax);

                if (posDiff >= MinPosToMaxA) {
                    result.reachedAccel = Profile::getConstAccelTime(posDiff, v, vMax, aMax, jMax);
                } else {
                    double accel = Profile::getReachedAccelWhenNoConstAccelStage(posDiff, v, vMax, aMax, jMax);
                    result.tAtMaxJerk = accel / jMax;
                    result.tAtMaxAccel = .0;
                    result.tAtMaxVelocity = .0;
                }
            }
        }

        return result;
    }

    auto Profile::trajectorySegmentPlanning(double p0, double pf, double v0, double vf, double vMax, double aMax,
                                            double jMax) {
        struct Result {
            double tAtMaxJerk = .0;
            double tAtMaxAccel = .0;
            double tAtMaxVelocity = .0;
            double reachedVel = .0;
            double reachedAccel = .0;
        };

        auto RequirementToReachVF = Profile::getMinPosReachedAccelAndJerkToReachVF(v0, vf, vMax, aMax, jMax);
        double absV;

        if (RequirementToReachVF.minPosToReachVF > std::abs(pf - p0)) {
            throw std::logic_error("Can not reach vf with this small amount of distance");
        } else {
            absV = vf > v0 ? vf : v0;

            if (std::abs(pf - p0) != RequirementToReachVF.minPosToReachVF) {
                double posDiff = pf - p0 - std::copysign(RequirementToReachVF.minPosToReachVF, pf - p0);
                auto result = Profile::equalV0VFCasePlanning(std::abs(posDiff), absV, vMax, aMax, jMax);
                return *((Result *) &result);
            } else {
                return Result{RequirementToReachVF.tjToReachVF, RequirementToReachVF.taToReachVF, .0, .0, .0};
            }
        }
    }

} // RockLib