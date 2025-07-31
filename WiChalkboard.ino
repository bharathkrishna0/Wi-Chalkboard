#include <WiFi.h>
#include <WebServer.h>
#include "web_page.h"

const char* ssid = "WiChalk";
const char* password = "chalkboard";

WebServer server(80);

// Max 10 messages stored
#define MAX_MESSAGES 10
String messages[MAX_MESSAGES];
int messageCount = 0;

// Generate dynamic HTML page
String getHTMLPage() {
  String msgList = "";
  for (int i = messageCount - 1; i >= 0; i--) {
    msgList += "<li>" + messages[i] + "</li>";
  }

  String page = MAIN_page;
  page.replace("%MESSAGES%", msgList);
  return page;
}

// Root handler
void handleRoot() {
  server.send(200, "text/html", getHTMLPage());
}

// Message submission handler
void handleSubmit() {
  if (server.hasArg("message")) {
    String msg = server.arg("message");
    msg.trim();
    if (msg.length() > 0) {
      if (messageCount < MAX_MESSAGES) {
        messages[messageCount++] = msg;
      } else {
        // Shift messages to make room
        for (int i = 1; i < MAX_MESSAGES; i++) {
          messages[i - 1] = messages[i];
        }
        messages[MAX_MESSAGES - 1] = msg;
      }
    }
  }
  server.sendHeader("Location", "/", true);
  server.send(303); // Redirect to home
}

void setup() {
  Serial.begin(115200);
  Serial.println("Starting Wi-Chalkboard...");

  WiFi.softAP(ssid, password);
  Serial.print("Access Point started. Connect to: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot);
  server.on("/submit", HTTP_POST, handleSubmit);
  server.begin();
  Serial.println("Web server started");
}

void loop() {
  server.handleClient();
}
