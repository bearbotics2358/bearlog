#pragma once

#include <frc/RobotController.h>

#include "bearlog/internal/data_log_writer.h"
#include "bearlog/internal/network_tables_writer.h"

class BearLogOptions {
public:
  enum class NTPublish {No, Yes};
  enum class LogWithNTPrefix {No, Yes};

  /**
   * Use enum classes as parameters instead of bools:
   * - Better type safety
   * - Allow options to be expanded more easily in the future
   * - Be more clear about which option is being set
   */
  BearLogOptions(NTPublish ntPublish = NTPublish::Yes,
                 LogWithNTPrefix withNTPrefix = LogWithNTPrefix::Yes):
      m_NtPublish(ntPublish),
      m_LogWithNTPrefix(withNTPrefix) {}

  bool ShouldPublishToNetworkTables() {
    return m_NtPublish == NTPublish::Yes;
  }

  bool ShouldLogToFileWithNTPrefix() {
    return m_LogWithNTPrefix == LogWithNTPrefix::Yes;
  }

private:
  NTPublish m_NtPublish;
  LogWithNTPrefix m_LogWithNTPrefix;
};

class BearLog {
  const std::string kLogTable = "/Robot";

public:
  // Delete the copy constructor. BearLog should not be cloneable.
  BearLog(const BearLog&) = delete;

  // Preventing assigning a BearLog object
  BearLog& operator=(const BearLog&) = delete;

  static void SetOptions(BearLogOptions options) {
    GetInstance().m_Options = options;

    GetInstance().m_DataLogger.SetShouldUseNTTablePrefix(options.ShouldLogToFileWithNTPrefix());
  };

  static void SetEnabled(bool newEnabled) {
    GetInstance().m_IsEnabled = newEnabled;
  }

  static bool IsEnabled() {
    return GetInstance().m_IsEnabled;
  }

  static void Log(std::string key, bool value) {
    if (!IsEnabled()) {
      return;
    }

    uint64_t now = frc::RobotController::GetFPGATime();

    GetInstance().m_DataLogger.Log(now, key, value);
    if (GetInstance().m_Options.ShouldPublishToNetworkTables()) {
      GetInstance().m_NTLogger.Log(now, key, value);
    }
  }

  static void Log(std::string key, std::span<const double> value) {
    if (!IsEnabled()) {
      return;
    }

    uint64_t now = frc::RobotController::GetFPGATime();

    GetInstance().m_DataLogger.Log(now, key, value);
    if (GetInstance().m_Options.ShouldPublishToNetworkTables()) {
      GetInstance().m_NTLogger.Log(now, key, value);
    }
  }

  static void Log(std::string key, double value) {
    if (!IsEnabled()) {
      return;
    }

    uint64_t now = frc::RobotController::GetFPGATime();

    GetInstance().m_DataLogger.Log(now, key, value);
    if (GetInstance().m_Options.ShouldPublishToNetworkTables()) {
      GetInstance().m_NTLogger.Log(now, key, value);
    }
  }

  static void Log(std::string key, int value) {
    if (!IsEnabled()) {
      return;
    }

    uint64_t now = frc::RobotController::GetFPGATime();

    GetInstance().m_DataLogger.Log(now, key, value);
    if (GetInstance().m_Options.ShouldPublishToNetworkTables()) {
      GetInstance().m_NTLogger.Log(now, key, value);
    }
  }

  static void Log(std::string key, std::span<const std::string> value) {
    if (!IsEnabled()) {
      return;
    }

    uint64_t now = frc::RobotController::GetFPGATime();

    GetInstance().m_DataLogger.Log(now, key, value);
    if (GetInstance().m_Options.ShouldPublishToNetworkTables()) {
      GetInstance().m_NTLogger.Log(now, key, value);
    }
  }

  static void Log(std::string key, const std::string& value) {
    if (!IsEnabled()) {
      return;
    }

    uint64_t now = frc::RobotController::GetFPGATime();

    GetInstance().m_DataLogger.Log(now, key, value);
    if (GetInstance().m_Options.ShouldPublishToNetworkTables()) {
      GetInstance().m_NTLogger.Log(now, key, value);
    }
  }

  template<typename Units>
  static void Log(std::string key, Units value) {
    if (!IsEnabled()) {
      return;
    }

    // @todo Add a better compiler error message when the Units class doesn't support the necessary functions

    uint64_t now = frc::RobotController::GetFPGATime();

    std::string key_with_units = key + "(" + value.abbreviation() + ")";

    GetInstance().m_DataLogger.Log(now, key_with_units, value.value());
    if (GetInstance().m_Options.ShouldPublishToNetworkTables()) {
      GetInstance().m_NTLogger.Log(now, key_with_units, value.value());
    }
  }

private:
  // Make the constructor private to disallow direct instantiation of BearLog
  BearLog(): m_DataLogger(kLogTable), m_NTLogger(kLogTable) {
    m_IsEnabled = true;
  }

  static BearLog& GetInstance() {
    static BearLog instance;
    return instance;
  }

  bool m_IsEnabled;
  DataLogWriter m_DataLogger;
  NetworkTablesWriter m_NTLogger;
  BearLogOptions m_Options;
};