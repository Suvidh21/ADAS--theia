ADAS – THEIA 🚗

Version: 1.2

Overview

THEIA is an experimental Advanced Driver Assistance System (ADAS) project focused on obstacle avoidance and intelligent vehicle behavior.
The project is designed in a modular manner, starting from an Arduino-based autonomous car, with future expansion toward computer vision–based ADAS using YOLOv8.

The current repository contains the embedded control logic (Arduino) for the vehicle.
Computer vision models and datasets are intentionally kept external to maintain a clean and professional repository.

Objective of the Project

The primary goals of THEIA are:

To design a low-cost ADAS prototype

To understand real-time decision making in autonomous vehicles

To implement obstacle detection and avoidance

To build a scalable system that can later integrate:

Camera-based perception

AI-based object detection

Real-time video processing

This project serves both academic learning and practical ADAS experimentation.

Current Scope (Version 1.2)
What is implemented now

Arduino-based autonomous vehicle logic

Obstacle detection using sensors

Motor control for:

Forward movement

Turning

Emergency stop

Basic decision logic based on sensor distance

Tested on a physical prototype vehicle

What is NOT included in this repository

YOLO models

Datasets

Trained weights

Computer vision pipelines

These are provided via external links (see below).

System Architecture (Conceptual)

Sensors
Distance / proximity sensors continuously monitor obstacles.

Arduino Controller

Reads sensor data

Applies decision logic

Controls motors accordingly

Motor Driver
Executes movement commands from Arduino.

Future Expansion Layer

Camera input

YOLOv8 inference

ADAS decision fusion

Repository Structure
ADAS--theia/
│
├── Theia CAR/
│   └── sketch_mar2a/
│       ├── sketch_mar2a.ino
│       ├── motor test.txt
│       └── working code for theia.txt
│
└── README.md

Hardware Requirements

Arduino (Uno / Nano / compatible)

Motor driver module (L298N or similar)

DC motors with wheels

Obstacle detection sensor (Ultrasonic / proximity)

Power supply / battery

Chassis

Software Requirements
For Arduino Module

Arduino IDE

Required Arduino libraries (installed via Arduino Library Manager):

Servo

Adafruit Touch / Sensor libraries (as per hardware used)

Note: Arduino libraries are not uploaded to this repository as per best practices.

Computer Vision & YOLO Integration (Future Work)

THEIA is designed to evolve into a vision-based ADAS system.

Planned Vision Features

Pedestrian detection

Vehicle detection

Traffic sign recognition

Lane detection

Collision warning

Object Detection Model

YOLOv8 (Ultralytics)

YOLOv8 Repository:
https://github.com/ultralytics/ultralytics

Dataset Links (External)

The datasets are not stored in this repository to keep it lightweight.

Recommended datasets:

ADAS Dataset (Roboflow):
https://universe.roboflow.com/

COCO Dataset (for object detection):
https://cocodataset.org/

Users can train or fine-tune YOLOv8 models using these datasets.

---

## Planned Implementation Flow (Vision-Based ADAS)

In the current experimental phase, THEIA follows a **hybrid processing approach** where perception is handled on an external computing device while vehicle actuation remains embedded.

In this version, a **camera is mounted on the Arduino-based car** to capture real-time video of the surrounding environment. The live video feed is transmitted to a **laptop**, where all computer vision processing is performed.

On the laptop, a **YOLOv8 object detection model** is executed. The model is trained using **ADAS-related datasets** to identify key road entities such as:

* Pedestrians
* Traffic signs
* Traffic lights
* Road signs
* Other vehicles

The detection results produced by YOLOv8 are then interpreted to understand the driving scenario. Based on this interpretation, **control decisions** (such as stop, slow down, or change direction) are generated and communicated back to the vehicle controller.

The **Arduino / ESP32** acts purely as an execution unit in this setup, receiving high-level commands and performing motor control accordingly. This architecture is intentionally chosen because **Arduino-class microcontrollers do not have sufficient computational capability** to perform real-time deep learning inference.

For future onboard processing, more powerful embedded platforms such as **NVIDIA Jetson Nano** or similar edge AI devices are planned. These platforms will allow the YOLOv8 model to run **directly on the vehicle**, enabling a fully self-contained vision-based ADAS system without reliance on an external laptop.


ADAS Theory (Brief)

Advanced Driver Assistance Systems (ADAS) are intelligent automotive systems designed to enhance vehicle safety, driving comfort, and situational awareness by assisting the driver or the vehicle in making timely decisions.
























