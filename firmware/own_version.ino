// Este software foi modificado a partir do original criado por https://github.com/dakk
// Modificações feitas por https://github.com/apenas-will em março de 2025
// Licenciado sob a Licença Apache 2.0

#include <math.h>

const int NUM_QUBITS = 7;
const int NUM_STATES = 1 << NUM_QUBITS; // 2^NUM_QUBITS
const int LED_PINS[NUM_QUBITS] = {11, 10, 9, 8, 7, 6, 5}; // Digital pins for qubits LEDs
const int SUPERPOSITION_LED = 4;
const int BUTTON_COMPUTE_PIN = 12;

int lastButtonState = LOW;
bool circuitSelected = false;
int selectedCircuit = -1;

// Complex number struct
struct Complex {
  float real;
  float imag;
  
  Complex(float r = 0, float i = 0) : real(r), imag(i) {}
  
  Complex operator*(const Complex& other) const {
    return Complex(real * other.real - imag * other.imag,
                   real * other.imag + imag * other.real);
  }
  
  Complex& operator+=(const Complex& other) {
    real += other.real;
    imag += other.imag;
    return *this;
  }
  
  Complex operator-(const Complex& other) const {
    return Complex(real - other.real, imag - other.imag);
  }
  
  Complex operator+(const Complex& other) const {
    return Complex(real + other.real, imag + other.imag);
  }
};

// Quantum state vector
Complex stateVector[NUM_STATES];



void setup() {
  Serial.begin(9600); 
  Serial.println("Arduino Quantum Computer");
  randomSeed(analogRead(0));
  
  for (int i = 0; i < NUM_QUBITS; i++) {
    pinMode(LED_PINS[i], OUTPUT);
  }
  
  pinMode(BUTTON_COMPUTE_PIN, INPUT_PULLUP);

  // Selection of quantum circuit
  Serial.println("Select a quantum circuit:");
  Serial.println("1 - Custom Circuit");
  Serial.println("2 - GHZ State");
  Serial.println("3 - Bernstein-Vazirani");

  while (!circuitSelected) {
    if (Serial.available()) {
      char choice = Serial.read();
      if (choice == '1') {
        selectedCircuit = 1;
        circuitSelected = true;
      } else if (choice == '2') {
        selectedCircuit = 2;
        circuitSelected = true;
      } else if (choice == '3') {
        selectedCircuit = 3;
        circuitSelected = true;
      }
    }
  }
}

void swap(Complex& a, Complex& b) {
  Complex temp = a;
  a = b;
  b = temp;
}


// Initialize the state vector to |00000>
void initializeState() {
  for (int i = 0; i < NUM_STATES; i++) {
    stateVector[i] = Complex();
  }
  stateVector[0] = Complex(1, 0);
}


// Apply CNOT gate with control and target qubits
void CX(int control, int target) {
  for (int i = 0; i < NUM_STATES; i++) {
    if ((i & (1 << control)) && !(i & (1 << target))) {
      swap(stateVector[i], stateVector[i ^ (1 << target)]);
    }
  }
}


// Apply Hadamard gate to a specific qubit
void H(int qubit) {
  const float SQRT_2 = 1.0 / sqrt(2);
  for (int i = 0; i < NUM_STATES; i++) {
    if (i & (1 << qubit)) {
      Complex temp = stateVector[i];
      stateVector[i] = stateVector[i ^ (1 << qubit)] * SQRT_2 - temp * SQRT_2;
      stateVector[i ^ (1 << qubit)] = temp * SQRT_2 + stateVector[i ^ (1 << qubit)] * SQRT_2;
    }
  }
}

void X(int qubit) {
  for (int i = 0; i < NUM_STATES; i++) {
    if (i & (1 << qubit)) {
      swap(stateVector[i], stateVector[i ^ (1 << qubit)]);
    }
  }
}


void Y(int qubit) {
  const Complex I(0, 1);
  for (int i = 0; i < NUM_STATES; i++) {
    if (i & (1 << qubit)) {
      Complex temp = stateVector[i];
      stateVector[i] = stateVector[i ^ (1 << qubit)] * I;
      stateVector[i ^ (1 << qubit)] = temp * Complex(0, -1);
    }
  }
}


void Z(int qubit) {
  for (int i = 0; i < NUM_STATES; i++) {
    if (i & (1 << qubit)) {
      stateVector[i] = stateVector[i] * Complex(-1, 0);
    }
  }
}


// Measure the quantum state and collapse it
void measure() {
  float probabilities[NUM_STATES];
  float cumulativeProb = 0;
  
  for (int i = 0; i < NUM_STATES; i++) {
    probabilities[i] = stateVector[i].real * stateVector[i].real + 
                       stateVector[i].imag * stateVector[i].imag;
    cumulativeProb += probabilities[i];
  }
  
  float randomValue = random(1000) / 1000.0 * cumulativeProb;
  int measured_state = 0;
  
  for (int i = 0; i < NUM_STATES; i++) {
    if (randomValue <= probabilities[i]) {
      measured_state = i;
      break;
    }
    randomValue -= probabilities[i];
  }
  
  // Collapse the state vector
  for (int i = 0; i < NUM_STATES; i++) {
    stateVector[i] = Complex();
  }
  stateVector[measured_state] = Complex(1, 0);
  
  // Output result to LEDs
  for (int i = 0; i < NUM_QUBITS; i++) {    
    digitalWrite(LED_PINS[i], (measured_state & (1 << i)) ? HIGH : LOW);
    Serial.print((measured_state & (1 << i))?1:0);
  }
  Serial.print("\n");
}

// Implementation of the GHZ state
void GHZ(){
  initializeState();
  H(0);
  for (int i = 0; i < NUM_QUBITS - 1; i++) {
    CX(i, i+1);
  }
  measure();
}

// Implementation of an oracle for Bernstein-Vazirani algorithm
void oracle(String s) {
  int n = s.length();
  for (int i = 0; i < n; ++i) {
    if (s[n - 1 - i] == '1') {
      CX(i, n - 1);
    }
  }
}

// Implementation of the Bernstein-Vazirani algorithm
void BernsteinVazirani(String s){
  initializeState();
  X(NUM_QUBITS - 1);
  for(int i = 0; i < NUM_QUBITS; i++){
    H(i);
  }
  oracle(s);
  for(int i = 0; i < NUM_QUBITS; i++){
    H(i);
  }
  measure();
}

void computeCustomCircuit() {
  // Write a circuit here!
  initializeState();
  H(0);
  for (int i = 0; i < NUM_QUBITS - 1; i++) {
    CX(i, i+1);
  }
  measure();
}
  
void compute() {  
  initializeState();
  if (selectedCircuit == 1) {
    computeCustomCircuit();
  } else if (selectedCircuit == 2) {
    GHZ();
  } else if (selectedCircuit == 3) {
    BernsteinVazirani("1010101");
  }
}
  
void loop() {
  int reading = digitalRead(BUTTON_COMPUTE_PIN);
  if (reading == LOW && lastButtonState == HIGH) {
    lastButtonState = LOW;
    compute();  
  } 
  lastButtonState = reading;
  digitalWrite(SUPERPOSITION_LED, (reading == HIGH) ? HIGH : LOW);
}

