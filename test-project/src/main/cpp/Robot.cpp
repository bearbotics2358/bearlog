// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <frc2/command/CommandScheduler.h>
#include <units/velocity.h>

constexpr units::meter_t kMaxHeight = 100_m;
constexpr units::meter_t kMinHeight = 0_m;

Robot::Robot() {
  BearLog::SetOptions(BearLogOptions(BearLogOptions::NTPublish::Yes,
                                     BearLogOptions::LogWithNTPrefix::Yes,
                                     BearLogOptions::LogExtras::Yes));
  std::srand(std::time(nullptr));

  BearLog::SetPdh(std::make_shared<frc::PowerDistribution>());
}

void Robot::RobotPeriodic() {
  frc2::CommandScheduler::GetInstance().Run();

  // Basic position value
  BearLog::Log("Debug/MotorPosition", m_motor.GetPosition().GetValueAsDouble());

  // Unit aware logging
  BearLog::Log("Debug/MotorPosition", m_motor.GetPosition().GetValue());

  BearLog::Log("Random/Random", std::rand());

  if (m_testIncrease) {
    m_height += 0.1_m;

    if (m_height > kMaxHeight) {
      m_testIncrease = false;
    }
  } else {
    m_height -= 0.1_m;

    if (m_height < kMinHeight) {
      m_testIncrease = true;
    }
  }

  // Unit aware logging
  BearLog::Log("Units/Height", m_height);
  BearLog::Log("Units/Height", units::inch_t(m_height));
  BearLog::Log("Units/Height", units::centimeter_t(m_height));

  BearLog::Log("Units/Angle", 42_deg);
  BearLog::Log("Units/Velocity", 42_mps);
}

void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::DisabledExit() {}

void Robot::AutonomousInit() {
  m_autonomousCommand = m_container.GetAutonomousCommand();

  if (m_autonomousCommand) {
    frc2::CommandScheduler::GetInstance().Schedule(m_autonomousCommand.value());
  }
}

void Robot::AutonomousPeriodic() {}

void Robot::AutonomousExit() {}

void Robot::TeleopInit() {
  if (m_autonomousCommand) {
    m_autonomousCommand->Cancel();
  }
}

void Robot::TeleopPeriodic() {}

void Robot::TeleopExit() {}

void Robot::TestInit() {
  frc2::CommandScheduler::GetInstance().CancelAll();
}

void Robot::TestPeriodic() {}

void Robot::TestExit() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
