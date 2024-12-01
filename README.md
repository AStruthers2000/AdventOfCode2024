
# Advent of Code 2024 - C++23 Implementation

Welcome to my [**Advent of Code 2024**](https://adventofcode.com/2024) repository! This project showcases my solutions to the daily programming challenges presented in Advent of Code 2024. Each solution is written in **C++23**, adhering to modern object-oriented programming practices and leveraging the latest language features.

## 🚀 Project Overview

The project is structured with modularity and maintainability in mind:

- Each day's solution is implemented as a subclass of a base `Problem` class, allowing for:
  - Easy organization of daily challenges.
  - A polymorphic array of `Problem` instances for streamlined execution.
- Utility modules and submodules provide reusable functionality for:
  - Math utilities.
  - String parsing.
  - Algorithms.
  - Data structures.
- The codebase takes full advantage of **C++23 features** such as:
  - `std::optional` for expressive and safe optional values.
  - Template classes and functions for flexibility and type safety.
  - Modules for clean code organization and dependency management.

This repository not only documents my journey through the Advent of Code challenges but also serves as a playground to deepen my understanding of **modern C++ development methodologies**.

## 🛠️ Tools & Environment

- **Language:** C++23
- **IDE:** JetBrains Rider.
- **Compiler:** MSVC with support for C++23 and modules.

## 🗂️ File Structure

```
Solution/
├── Problems/
│   ├── Problem.h
│   ├── Problem.cpp
│   ├── Day01/
│   │   ├── Day01.h
│   │   ├── Day01.cpp
│   ├── Day02/
│   │   ├── Day01.h
│   │   ├── Day01.cpp
│   └── ... (more days)
├── Utils/
│   ├── Math/
│   │   └── ... (utils implementation)
│   ├── StringParsing/
│   │   └── ... (utils implementation)
│   └── ... (more utils)
└── AdventOfCode2024.cpp
```

## 🧩 How It Works

1. **Problem Structure:** Each problem is a subclass of `Problem`, implementing specific functionality for the corresponding day. This design ensures that:
   - Code for each problem is modular and encapsulated.
   - A single polymorphic array can store and execute all problems dynamically.

2. **Utilities:** Common utilities like string parsing and math functions are placed in dedicated modules, making them reusable and improving code readability.

3. **Modern C++ Practices:**
   - Use of `std::optional` for optional values.
   - Extensive use of templates for generalized solutions.
   - Modular programming with `import` statements for better organization.

## 📋 Usage

### Adding a New Problem
1. Create a new `DayXX` class and `DayXX` folder in the `Solution/Problems` folder.
2. Inherit from the `Problem` base class.
3. Implement the `LoadProblem()`, `SolvePart1()`, and `SolvePart2()` methods for the problem logic.
4. Add the new problem to the array in `AdventOfCode2024.cpp`.

## 🎯 Goals

This project aims to:
- Solve the Advent of Code 2024 challenges in a clean, efficient, and modular way.
- Embrace and explore modern C++23 features and development methodologies.
- Serve as a learning resource and reference for modular programming in C++.

---

Feel free to explore, learn, and share your feedback!
