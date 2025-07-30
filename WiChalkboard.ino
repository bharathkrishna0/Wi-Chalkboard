#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "WiChalk";
const char* password = "chalkboard";

WebServer server(80);

// Max 10 messages stored
#define MAX_MESSAGES 10
String messages[MAX_MESSAGES];
int messageCount = 0;

// HTML page (served inline)
String getHTMLPage() {
  String html = "<!DOCTYPE html><html><head><title>Wi-Chalkboard</title>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  html += "<style>body{font-family:sans-serif;padding:20px;}textarea{width:100%;height:80px;}ul{list-style:none;padding:0;}li{margin:10px 0;background:#eee;padding:10px;border-radius:5px;}</style></head><body>";
  html += "<h2>🧠 Wi-Chalkboard</h2>";
  html += "<form action='/submit' method='POST'>";
  html += "<textarea name='message' placeholder='Write your message...'></textarea><br><br>";
  html += "<input type='submit' value='Post Message'>";
  html += "</form><hr><h3>📝 Recent Messages:</h3><ul>";

  for (int i = messageCount - 1; i >= 0; i--) {
    html += "<li>" + messages[i] + "</li>";
  }

  html += "</ul></body></html>";
  return html;
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
  server.send(303);
}

void setup() {
  Serial.begin(115200);
  Serial.println("Starting Wi-Chalkboard...");

  WiFi.softAP(ssid, password);
  Serial.println("AP started. Connect to:");
  Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot);
  server.on("/submit", HTTP_POST, handleSubmit);
  server.begin();
  Serial.println("Web server started");
}

void loop() {
  server.handleClient();
}
