#include <WiFi.h>
#include <ESP_Mail_Client.h>

// WiFi credentials
#define WIFI_SSID "WIFINAME"
#define WIFI_PASSWORD "PASSWORD"

// SMTP server credentials
#define SMTP_SERVER "smtp.gmail.com"
#define SMTP_PORT 465

// Email credentials
#define SENDER_EMAIL "testingesp177@gmail.com"
#define SENDER_PASSWORD "thkc stzd vyfh mnnx"
#define RECIPIENT_EMAIL "jarabalasaiteja@gmail.com"  // Corrected email
#define RECIPIENT_NAME "SAI TEJA"

// Create a session and message object
SMTPSession smtp;
ESP_Mail_Session session;
SMTP_Message message;

void connectToWiFi() {
  Serial.print("Connecting to WiFi");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(200);
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void configureSMTP() {
  session.server.host_name = SMTP_SERVER;
  session.server.port = SMTP_PORT;
  session.login.email = SENDER_EMAIL;
  session.login.password = SENDER_PASSWORD;

  smtp.debug(1);  // Enable debug information
}

void setupEmail() {
  message.sender.name = "ESP32 Alert";
  message.sender.email = SENDER_EMAIL;
  message.subject = "ESP32 Email Alert";
  message.addRecipient(RECIPIENT_NAME, RECIPIENT_EMAIL);

  // HTML email content
  String htmlMsg = "<div style=\"color:#000000;\"><h1>Alert from ESP32!</h1><p>Your custom message here.</p></div>";
  message.html.content = htmlMsg.c_str();
  message.html.charSet = "utf-8";
  message.html.transfer_encoding = Content_Transfer_Encoding::enc_7bit;
}

bool sendEmail() {
  if (!smtp.connect(&session)) {
    Serial.println("Failed to connect to SMTP server.");
    return false;
  }

  if (!MailClient.sendMail(&smtp, &message)) {
    Serial.print("Error sending Email: ");
    Serial.println(smtp.errorReason());
    return false;
  }
  
  Serial.println("Email sent successfully!");
  return true;
}

void setup() {
  Serial.begin(115200);
  connectToWiFi();
  configureSMTP();
  setupEmail();
  sendEmail();
}

void loop() {
  // In a real application, you might have your main code logic here.
  // For the purpose of this example, the loop is empty.
}