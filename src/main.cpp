#include <ESP8266WiFi.h>
#include <espnow.h>

#define CAM_ID 0 // Change this to the ID of the camera you are using

// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
    int preview;
    int live;
} struct_message;

// Create a struct_message called myData
struct_message myData;

// Callback function that will be executed when data is received
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Preview: ");
  Serial.println(myData.preview);
  Serial.print("Live: ");
  Serial.println(myData.live);
  Serial.println();

  if (myData.live == CAM_ID) {
    digitalWrite(LED_BUILTIN, LOW);
  } else {
    digitalWrite(LED_BUILTIN, HIGH);
  }
}
 
void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.print("ESP8266 Board MAC Address:  ");
  Serial.println(WiFi.macAddress());

  pinMode(LED_BUILTIN, OUTPUT); // LED als Output definieren

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  
}
