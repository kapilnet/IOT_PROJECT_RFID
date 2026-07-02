const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
const char* aws_endpoint = "YOUR_AWS_IOT_ENDPOINT-ats.iot.us-east-1.amazonaws.com";
const int aws_port = 8883; 
const char* mqtt_topic = "attendance/scan";
const char* device_id = "ESP32_Scanner_01";

const char* amazonRootCA = R"EOF(
-----BEGIN CERTIFICATE-----
... Paste Root CA ...
-----END CERTIFICATE-----
)EOF";

const char* deviceCert = R"EOF(
-----BEGIN CERTIFICATE-----
... Paste Device Cert ...
-----END CERTIFICATE-----
)EOF";

const char* deviceKey = R"EOF(
-----BEGIN RSA PRIVATE KEY-----
... Paste Private Key ...
-----END RSA PRIVATE KEY-----
)EOF";
