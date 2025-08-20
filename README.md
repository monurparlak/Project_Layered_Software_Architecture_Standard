# Layered Software Architecture Standard

This repository defines a **layered software architecture** that spans from
**MCU-based embedded systems** to **Linux user-space applications**.  
It provides a unified project structure, coding guidelines, API contracts,
protocol definitions, testing strategy, CI/CD pipelines, and documentation standards.

---

## 🎯 Objectives
- Establish a **single repository** for both embedded firmware and Linux applications
- Enforce **clear separation of concerns** using layered architecture
- Provide **standardized coding, testing, and CI/CD practices**
- Define **protocols and ICDs** for MCU ↔ Linux communication
- Support **scalable and maintainable** product development

---

## 📂 Repository Layout

```text
repo/
├─ embedded/         # MCU side
│  ├─ hal/           # Vendor HAL/LL wrappers
│  ├─ bsp/           # Board support (pins, clocks, variants)
│  ├─ drivers/       # Hardware drivers (LED, UART, SPI, I2C, sensors)
│  ├─ services/      # Business logic (debounce, state machines, logger)
│  ├─ middleware/    # Protocols, framing, security
│  ├─ osal/          # OS abstraction (FreeRTOS/POSIX)
│  ├─ app/           # Application layer (CLI, scenarios, state handlers)
│  ├─ config/        # Build-time configuration (Kconfig, YAML, INI)
│  └─ tests/         # Unit tests (Unity/CMock) + HIL tests
│
├─ linux/            # Linux side
│  ├─ src/           # Daemon/CLI implementation
│  ├─ include/       # Public headers
│  ├─ services/      # Business logic and adapters
│  ├─ transport/     # gRPC, REST, MQTT, Serial, USB
│  ├─ storage/       # SQLite, file logging, configuration
│  ├─ systemd/       # .service/.socket files
│  ├─ packaging/     # DEB/RPM, containers, OTA packaging
│  └─ tests/         # Unit & integration tests (GTest, PyTest)
│
├─ interfaces/       # Interface Control Documents (ICD)
│  ├─ *.proto        # Protobuf definitions
│  ├─ *.json         # JSON schema
│  └─ README.md      # Interface versioning rules
│
├─ docs/             # Project documentation
│  ├─ architecture.md # Layered architecture description
│  ├─ icd.md          # MCU ⇄ Linux protocol documentation
│  ├─ build.md        # Build instructions
│  └─ contributing.md # Contribution guide
│
├─ scripts/          # Developer tools
│  ├─ format.sh      # Code formatting
│  ├─ lint.sh        # Static analysis
│  ├─ ci-build.sh    # CI helper scripts
│  └─ test-run.sh    # Automated test runner
│
└─ CMakeLists.txt    # Top-level build system entry point
```
---

## ⚙️ Architecture Layers

1. **HAL/LL** – Hardware abstraction (register-level or vendor HAL)  
2. **BSP** – Board support (pin mapping, clock setup, variants)  
3. **Drivers** – Device drivers (sensors, buttons, communication)  
4. **Services** – Business logic modules (debouncing, state handling, logging)  
5. **Middleware/Protocol** – Framing, encoding, security, OTA  
6. **OSAL** – RTOS/POSIX abstraction (mutexes, tasks, timers)  
7. **Application** – User scenarios, CLI commands, state machines  
8. **Linux App** – User-space daemons, REST/gRPC endpoints, data storage  

**Rule:** Upper layers depend on lower layers, never the opposite. Interfaces are exposed through headers and `ops` tables (dependency injection).

---

## ✅ Features
- MISRA-C / Barr-C compliant coding guidelines for MCU code  
- C++ Core Guidelines for Linux components  
- Unified build system (CMake) for MCU and Linux targets  
- Protocols defined with Protobuf/CBOR + strict versioning rules  
- Testing strategy:
  - **MCU:** Unity + CMock, Hardware-in-the-loop (HIL)  
  - **Linux:** GTest + PyTest, golden vector tests for protocols  
- CI/CD pipeline (format → build → test → package → artifacts)  
- Secure updates (signed firmware & Linux packages)  
- Systemd integration for Linux daemons  

---

## 🚀 Quick Start

```bash
# Clone the repository
git clone https://github.com/monurparlak/Project_Layered_Software_Architecture_Standard.git
cd repo

# Build embedded firmware
cmake -B build-embedded embedded
make -C build-embedded

# Build Linux application
cmake -B build-linux linux
make -C build-linux

