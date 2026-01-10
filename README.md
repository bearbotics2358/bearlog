# BearLog

BearLog is a logging framework for FRC team [Bearbotics 2358](https://www.bearbotics.com). It was heavily inspired by the [DogLog](https://doglog.dev) framework with the goal of making a similarly featured library available to C++ teams.

## Philosophy

Simplicity. Being able to quickly publish a value from any subsystem without extra boilerplate code is very important to us. During a debugging session while trying to track down problems, we want to be able to easily throw a value into a log file or NetworkTables from anywhere with a single line of code.

## Installation

We are still working on getting this library configured so that it is more easily maintained and distributable. For now, the best way to get BearLog into your FRC C++ project is to copy the whole [`bearlog`](https://github.com/bearbotics2358/bearlog/tree/main/test-project/src/main/include/bearlog) folder from the `include` folder in the test-project. Paste all the files into your own `include` folder and you're ready to go.

## Usage

### Quick Start
In the file you want logging available, add this `#include` line:
```cpp
#include "bearlog/bearlog.h"
```

Then to log a value, one line of code is all you need. Just replace the key and value with the corresponding values you want to log.
```cpp
BearLog::Log("Elevator/Height", m_elevatorHeight);
```

### Configuration
BearLog supports some configuration options. By default, it will always log to `.wpilog` files using WPILib's internal [DataLogManager](https://docs.wpilib.org/en/stable/docs/software/telemetry/datalog.html).

* Publish to NetworkTables
* Choose to include or exclude the `NT` prefix in logging to DataLogManager for easier viewing in [AdvantageScope](https://docs.advantagescope.org/)

```cpp
BearLog::SetOptions(BearLogOptions(BearLogOptions::NTPublish::Yes, BearLogOptions::LogWithNTPrefix::Yes));
```

## Acknowledgments

BearLog was inspired by the highly configurable and extremely simple interface of [DogLog](https://doglog.dev). So thank you to [Team 581](https://github.com/team581) and all the DogLog contributors!
