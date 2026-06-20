
# UECS1104 Remote Work Readiness and Productivity Tracking System

A C++ console-based application developed for **UECS1104 Programming and Problem Solving**. The system helps organizations evaluate employees' remote work readiness and track daily productivity through work activity logging and report generation using text-file-based storage.

## Features

### Remote Work Readiness Module

* Home office safety and readiness assessment
* 22-point remote work safety checklist
* Employee and workspace information recording
* Automatic readiness evaluation and summary generation
* Safety report generation from stored records

### Productivity Tracking Module

* Daily work activity logging
* Activity scheduling with start and end times
* Productivity metrics tracking
* Focus level and distraction level assessment
* Productive vs non-productive task analysis
* Activity evaluation and feedback collection
* Productivity report generation

### Data Management

* Persistent storage using text files
* Automatic entry numbering system
* Report generation from saved records
* Input validation for user entries
* Time format validation (HH:MM)

## Technologies Used

* C++
* File Handling (ifstream / ofstream)
* Dynamic Memory Allocation
* Arrays and Functions
* Input Validation
* Console-Based User Interface

## Files Used

```text
SafetyChecklist.txt    - Stores remote work readiness records
WorkLog.txt            - Stores productivity tracking records
EntryNumber.txt        - Stores checklist entry numbers
WorkNumber.txt         - Stores productivity log entry numbers
```

## Program Structure

```text
Main Menu
│
├── Remote Work Readiness
│   ├── Safety Checklist
│   └── Generate Safety Report
│
└── Productivity Tracking System
    ├── Log Work Activities
    └── Generate Productivity Report
```

## Sample Functionality

### Remote Work Readiness

1. Enter employee information.
2. Complete the 22-question safety checklist.
3. Generate a workspace suitability assessment.
4. Save results to a text file.
5. Generate and view readiness reports.

### Productivity Tracking

1. Enter employee details.
2. Log daily activities.
3. Record activity duration.
4. Track focus and distraction levels.
5. Evaluate productivity.
6. Generate productivity reports.

## Learning Outcomes

This project demonstrates:

* Structured programming in C++
* File handling and data persistence
* Function decomposition and modular design
* Input validation techniques
* Dynamic memory allocation
* Problem-solving and system design
* Report generation using file-based databases

## Course Information

**Course:** UECS1104 Programming and Problem Solving

**Trimester:** June 2024

**Assignment:** Remote Work Readiness and Productivity Tracking System

## Contributors

Group 5

* [Ang Yong Xen](https://github.com/yongxennzz)
* [Kyle Yamato Christian](https://github.com/kyleyamatoc-bot)
* [Tan Jun Yin](https://github.com/Jun-Yin67)
* Lim Jun Sheng

## Disclaimer

This project was developed for academic purposes as part of a university assignment at Universiti Tunku Abdul Rahman (UTAR).
