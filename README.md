

# Faulty Node Detection in IoT Systems using Machine Learning

An end-to-end IoT and machine learning system designed to detect faulty sensor nodes using real-time temperature data.

This project was developed as part of an academic thesis and covers the complete pipeline from **hardware design and data collection** to **cloud integration and ML-based fault detection**.

---

## Project Overview

In IoT environments, faulty sensor nodes can generate inaccurate data, leading to unreliable system behavior and poor decision-making.

This project addresses the problem by:
- Collecting real-time temperature data from sensors
- Transmitting data to the cloud (ThingSpeak)
- Training a machine learning model to detect faulty nodes
- Classifying sensor behavior as **normal** or **faulty**

---

## Key Highlights

- Designed and implemented the **hardware circuit independently**
- Collected a **self-generated, real-world dataset**
- Built a **machine learning model from scratch**
- Integrated **IoT devices with cloud and ML pipeline**
- Developed a complete **end-to-end fault detection system**

---

## System Architecture



Temperature Sensor → Arduino / ESP → ThingSpeak Cloud → ML Model → Fault Detection



---

## 📡 Hardware Implementation

- Temperature sensor (custom-built circuit)
- Arduino / ESP microcontroller
- WiFi module for cloud communication

All components were manually assembled and tested to generate real sensor data.

---

## 📊 Dataset

- Fully **self-collected dataset**
- Based on real sensor readings
- Includes:
  - Normal operating conditions
  - Faulty node behavior

This ensures realistic data distribution and improves model reliability.

---

## 🧠 Machine Learning Model

- Framework: TensorFlow / Keras
- Model: Artificial Neural Network (ANN)

### Workflow:
- Data preprocessing (scaling, encoding)
- Train-test split
- Model training and evaluation

### Output:
- `0 → Normal`
- `1 → Faulty`

---

## 📁 Project Structure

```

faulty-node-detection/
│
├── fault-detector.ipynb       # ML model training & prediction
├── datasets/                  # Self-collected sensor data
├── arduinoCode/
│   └── arduinoCode.ino        # Sensor data acquisition
├── espCode/
│   └── espCode.ino            # Cloud communication (ThingSpeak)

````

---

## 🚀 Getting Started

### 1. Clone the Repository

```bash
git clone https://github.com/your-username/faulty-node-detection.git
cd faulty-node-detection
````

---

### 2. Install Dependencies

```bash
pip install numpy pandas tensorflow scikit-learn keras
```

---

### 3. Configure ThingSpeak

Update your credentials in the notebook:

```python
READ_API_KEY = "your_api_key"
CHANNEL_ID = "your_channel_id"
```

---

### 4. Run the Model

Open and execute:

```
fault-detector.ipynb
```

---

### 5. Upload Microcontroller Code

* Upload `arduinoCode.ino` to Arduino
* Upload `espCode.ino` to ESP module

---

## 🔍 Features

* Real-time IoT data collection
* Fault detection using machine learning
* Cloud-based data integration (ThingSpeak)
* Self-generated dataset for realistic modeling
* End-to-end system implementation

---

## 🛠️ Technologies Used

* Python (NumPy, Pandas, Scikit-learn)
* TensorFlow / Keras
* Arduino / ESP
* ThingSpeak API

---

## 📈 Future Improvements

* Real-time inference API
* Model deployment as a microservice
* Support for multiple sensor types
* Advanced anomaly detection techniques
* Integration with streaming systems (MQTT/Kafka)

---

## 📄 License

This project is licensed under the MIT License.
