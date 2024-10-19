# Excess Demand Method EDM
This repository contains the implementation and research of the Excess Demand Method (EDM) for solving the Transportation Problem (TP), a classic issue in operations research. The goal is to minimize the total transportation cost of delivering goods from various suppliers to multiple consumers.


## Introduction
The Transportation Problem (TP) focuses on minimizing the cost of transporting commodities from multiple suppliers to consumers. This project implements a new approach called the Excess Demand Method (EDM), which has been shown to provide a better Initial Basic Feasible Solution (IBFS) compared to Supply Selection Method (SSM), Bilqis Chastine Erma method (BCE), Total Opportunity Cost Matrix - Minimal Total (TOCM-MT), Vogel's Approximation Method (VAM), and Juman and Hoque's Method (JHM). 

## Features
* **Efficient Calculation**: Provides an efficient way to compute the Initial Basic Feasible Solution (IBFS) for transportation problems.
* **Comparison with Other Methods**: Includes comparisons with 6 other methods: VAM,JHM,TOCM-MT,BCE and SSM.
* **32 Test Cases**: Tested on 32 numerical problems, demonstrating improved performance in transportation cost minimization.

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

- C++ compiler (e.g., DEV C, GCC, MSVC)
- Optional: [Tora System 7th Edition](https://www.torascience.com/) for result validation

### **Clone the Repository**

```bash
git clone https://github.com/your-username/transportation-problem-EDM.git
cd transportation-problem-EDM
```

![alt text](https://github.com/rihanfarih/Excess-Demand-Method-EDM-/blob/main/step1.png)
### **combine the dataset and program into one same folder**
![alt text](https://github.com/rihanfarih/Excess-Demand-Method-EDM-/blob/main/step2.png)
### **Open the EDM Program**
![alt text](https://github.com/rihanfarih/Excess-Demand-Method-EDM-/blob/main/step3.png)
### **Change the input file and run it**
![alt text](https://github.com/rihanfarih/Excess-Demand-Method-EDM-/blob/main/step%204.png)

![alt text](https://github.com/rihanfarih/Excess-Demand-Method-EDM-/blob/main/step5.png)



## **Methods Implemented**

- **Vogel's Approximation Method (VAM)**
- **Juman Hoque Method (JHM)**
- **Total Opportunity-Cost Method Modified (TOCM-MT)**
- **Bilqis Chastine Erma (BCE)**
- **Supply Selection Method (SSM)**
- **Excess Demand Method (EDM)** (New)

## **Comparison with Other Methods**

The project compares **EDM** with other traditional methods across 32 numerical cases. **EDM** consistently outperforms other methods in producing minimal total costs.

| Method      | Total Optimal      | Accuracy (%) |
|-------------|--------------------|-------------------------|
| **VAM**     | 19                | 59,38                      |
| **JHM**     | 22                 | 68,75                      |
| **TOCM-MT**     | 18                 | 56,25                      |
| **BCE**    | 21                 | 65,63                      |
| **SSM** | 22                 | 68,75                      |
| **EDM**     | **27**             | **84,38**                  |

## **Results**

The **Excess Demand Method (EDM)** led to better total transportation costs in **27 out of 32** numerical problems when compared to the other seven methods. This demonstrates **EDM’s** efficiency in achieving optimal solutions.

