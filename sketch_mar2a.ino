#include <AFMotor.h>
#include <Servo.h>

// Define Motors
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

// Define Servo Motor
Servo servo_motor;

// Define Ultrasonic Sensor Pins
const int trigPin = 13;  
const int echoPin = 3;   

// Define Water Sensor Pin
const int waterSensorPin = A0;  // Analog pin

// Define obstacle detection distance
const int obstacleDistance = 20;  

bool waterDetected = false;  // Track if water has been detected

void setup() {
    Serial.begin(9600);
    Serial.println("Waiting for water detection...");

    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(waterSensorPin, INPUT);

    servo_motor.attach(9);
    servo_motor.write(90);  // Center position

    stopMotors();  // Keep motors stopped initially
}

void loop() {
    int waterLevel = analogRead(waterSensorPin);

    // Wait for water detection before starting the robot
    if (!waterDetected) {
        Serial.print("Water Level: ");
        Serial.println(waterLevel);

        if (waterLevel > 500) {  // Adjust threshold if needed
            Serial.println("Water detected! Robot starting...");
            waterDetected = true;
            moveForward();  // Start moving
            delay(500);
        } else {
            stopMotors();  // Ensure the robot remains halted
            delay(1000);  // Check again after some time
            return;
        }
    }

    // If water has been detected, proceed with normal obstacle avoidance
    int distance = getFilteredDistance();  
    
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.print(" cm, Water Level: ");
    Serial.println(waterLevel);

    if (distance > obstacleDistance) {
        moveForward();
    } else {
        stopMotors();
        Serial.println("Obstacle detected! Scanning...");

        delay(500);  

        int leftDistance = lookLeft();
        delay(500);
        int rightDistance = lookRight();
        delay(500);

        Serial.print("Left: "); Serial.print(leftDistance); Serial.print(" cm, ");
        Serial.print("Right: "); Serial.print(rightDistance); Serial.println(" cm");

        if (leftDistance > rightDistance) {
            Serial.println("Turning Left...");
            turnLeft();
        } else if (rightDistance > leftDistance) {
            Serial.println("Turning Right...");
            turnRight();
        } else {
            Serial.println("Both directions blocked, moving backward...");
            moveBackward();  // Move backward if both directions are blocked
            turnLeft();  // Turn left after moving backward
        }

        delay(500);
        moveForward();  // Continue moving forward after turning
    }
}

// Function to Measure and Filter Distance
int getFilteredDistance() {
    int samples = 5;
    int total = 0;
    int validCount = 0;
    
    for (int i = 0; i < samples; i++) {
        int distance = getDistance();
        if (distance > 2 && distance < 400) {
            total += distance;
            validCount++;
        }
        delay(10);
    }
    
    if (validCount == 0) return 100;
    return total / validCount;
}

// Function to Measure Distance
int getDistance() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    long duration = pulseIn(echoPin, HIGH, 25000);
    if (duration == 0) {
        Serial.println("Ultrasonic sensor timeout!");
        return 100;
    }

    int distance = duration * 0.034 / 2;
    return constrain(distance, 2, 400);
}

// Function to Stop Motors
void stopMotors() {
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    motor3.run(RELEASE);
    motor4.run(RELEASE);
}

// Function to Move Forward
void moveForward() {
    setMotorSpeed(200);
    motor1.run(FORWARD);
    motor2.setSpeed(240);  // Increased front right motor power
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);
}

// Function to Move Backward
void moveBackward() {
    setMotorSpeed(200);
    motor1.run(BACKWARD);
    motor2.setSpeed(240);  // More power for front right
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);
    delay(700);  // Move backward for some time
}

// Function to Turn Left
void turnLeft() {
    setMotorSpeed(200);
    motor1.run(BACKWARD);
    motor2.setSpeed(255);  // More power for front right motor
    motor2.run(FORWARD);
    motor3.run(BACKWARD);
    motor4.run(FORWARD);
    delay(1500);  // Increased turning time for better turn
}

// Function to Turn Right
void turnRight() {
    setMotorSpeed(200);
    motor1.run(FORWARD);
    motor2.setSpeed(255);  // More power for front right motor
    motor2.run(BACKWARD);
    motor3.run(FORWARD);
    motor4.run(BACKWARD);
    delay(1500);  // Increased turning time for better turn
}

// Function to Set Motor Speed
void setMotorSpeed(int speed) {
    motor1.setSpeed(speed);
    motor2.setSpeed(speed);
    motor3.setSpeed(speed);
    motor4.setSpeed(speed);
}

// Function to Look Left
int lookLeft() {
    servo_motor.write(150);  
    delay(700);  
    int distance = getFilteredDistance();
    servo_motor.write(90);  
    delay(500);  
    return distance;
}

// Function to Look Right
int lookRight() {
    servo_motor.write(30);  
    delay(700);  
    int distance = getFilteredDistance();
    servo_motor.write(90);  
    delay(500);  
    return distance;
}