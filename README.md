# Excess Demand Method EDM
This repository contains the implementation and research of the Excess Demand Method (EDM) for solving the Transportation Problem (TP), a classic issue in operations research. The goal is to minimize the total transportation cost of delivering goods from various suppliers to multiple consumers.


## Introduction
The Transportation Problem (TP) focuses on minimizing the cost of transporting commodities from multiple suppliers to consumers. This project implements a new approach called the Excess Demand Method (EDM), which has been shown to provide a better Initial Basic Feasible Solution (IBFS) compared to traditional methods such as the North-West Corner Method (NWM), Least Cost Method (LCM), and Vogel's Approximation Method (VAM).

## Features
* **Efficient Calculation**: Provides an efficient way to compute the Initial Basic Feasible Solution (IBFS) for transportation problems.
* **Comparison with Other Methods**: Includes comparisons with 7 other methods: NWM, LCM, VAM, TDM1, TOCM-MT, JHM, and BCE.
* **65 Test Cases**: Tested on 65 numerical problems, demonstrating improved performance in transportation cost minimization.

## **Table of Contents**

- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
- [Methods Implemented](#methods-implemented)
- [Comparison with Other Methods](#comparison-with-other-methods)
- [Results](#results)

## **Installation**
To use this project, clone the repository and run the implementation. The project is written in C++, so make sure you have a C++ compiler installed on your machine.
### **Prerequisites**

- C++ compiler (e.g., GCC, MSVC)
- Optional: [Tora System 7th Edition](https://www.torascience.com/) for result validation

### **Clone the Repository**

```bash
git clone https://github.com/your-username/transportation-problem-EDM.git
cd transportation-problem-EDM
```
### **Open the EDM Program**
### **Change the input file and run it**



## **Methods Implemented**

- **North-West Corner Method (NWM)**
- **Least Cost Method (LCM)**
- **Vogel's Approximation Method (VAM)**
- **Total Opportunity-Cost Method Modified (TOCM-MT)**
- **Juman-Hoque Method (JHM)**
- **Balanced Cost Efficiency (BCE)**
- **Excess Demand Method (EDM)** (New)

## **Comparison with Other Methods**

The project compares **EDM** with other traditional methods across 65 numerical cases. **EDM** consistently outperforms other methods in producing minimal total costs.

| Method      | Total Optimal      | Accuracy (%) |
|-------------|--------------------|-------------------------|
| **NWM**     | 4                 | 6,15                      |
| **LCM**     | 9                 | 13,85                      |
| **VAM**     | 29                 | 44,62                      |
| **TDM1**    | 22                 | 33,85                      |
| **TOCM-MT** | 33                 | 50,77                      |
| **JHM**     | 43                 | 66,15                      |
| **BCE**     | 45                 | 69,23                      |
| **EDM**     | **52**             | **80**                  |

## **Results**

The **Excess Demand Method (EDM)** led to better total transportation costs in **52 out of 65** numerical problems when compared to the other seven methods. This demonstrates **EDM’s** efficiency in achieving optimal solutions.

