// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <optional>

#include <ctre/phoenix6/TalonFX.hpp>
#include <frc/PowerDistribution.h>
#include <frc/TimedRobot.h>
#include <frc2/command/CommandPtr.h>

#include "RobotContainer.h"
#include "bearlog/bearlog.h"


class Robot : public frc::TimedRobot {
 public:
  Robot();
  void RobotPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;
  void DisabledExit() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void AutonomousExit() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TeleopExit() override;
  void TestInit() override;
  void TestPeriodic() override;
  void TestExit() override;

 private:

  const int kMotorId = 5;

  std::optional<frc2::CommandPtr> m_autonomousCommand;

  RobotContainer m_container;
  ctre::phoenix6::hardware::TalonFX m_motor{kMotorId};

  units::meter_t m_height = 0_m;
  bool m_testIncrease = true;
};
