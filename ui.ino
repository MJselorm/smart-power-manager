#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "your wifi name";
const char* password = "your wifi password";

WiFiServer server(80);


void site_setup() {
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.begin();
}


void handleWebsite() {
  WiFiClient client = server.available();

  if (!client) return;

  Serial.println("New Client");

  while (client.connected()) {
    if (client.available()) {

      String request = client.readStringUntil('\r');
      Serial.println(request);

      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html; charset=UTF-8");
      client.println("Connection: close");
      client.println();

      // Determine status and colors based on battery
      String statusColor, statusText, backgroundColor;
      
      if (batteryPercent >= 70) {
        statusColor = "#10b981";  // Green
        statusText = "Healthy";
        backgroundColor = "rgba(16, 185, 129, 0.1)";
      } else if (batteryPercent >= 40) {
        statusColor = "#f59e0b";  // Amber
        statusText = "Medium";
        backgroundColor = "rgba(245, 158, 11, 0.1)";
      } else if (batteryPercent > 10) {
        statusColor = "#ef4444";  // Red
        statusText = "Critical";
        backgroundColor = "rgba(239, 68, 68, 0.1)";
      } else {
        statusColor = "#7f1d1d";  // Dark red
        statusText = "Critically Low";
        backgroundColor = "rgba(127, 29, 29, 0.2)";
      }

      client.println("<!DOCTYPE html>");
      client.println("<html lang='en'>");
      client.println("<head>");
      client.println("<meta charset='UTF-8'>");
      client.println("<meta name='viewport' content='width=device-width, initial-scale=1.0'>");
      client.println("<meta http-equiv='refresh' content='5'>");
      client.println("<title>Smart Device Monitor</title>");
      client.println("<style>");
      client.println("* { margin: 0; padding: 0; box-sizing: border-box; }");
      client.println("body {");
      client.println("  font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', sans-serif;");
      client.println("  background: linear-gradient(135deg, #0f172a 0%, #1e293b 100%);");
      client.println("  min-height: 100vh;");
      client.println("  display: flex;");
      client.println("  align-items: center;");
      client.println("  justify-content: center;");
      client.println("  padding: 20px;");
      client.println("  color: #1f2937;");
      client.println("}");
      client.println(".container {");
      client.println("  background: white;");
      client.println("  border-radius: 20px;");
      client.println("  box-shadow: 0 20px 60px rgba(0, 0, 0, 0.3);");
      client.println("  padding: 40px 30px;");
      client.println("  max-width: 500px;");
      client.println("  width: 100%;");
      client.println("  animation: slideIn 0.5s ease-out;");
      client.println("}");
      client.println("@keyframes slideIn {");
      client.println("  from { opacity: 0; transform: translateY(20px); }");
      client.println("  to { opacity: 1; transform: translateY(0); }");
      client.println("}");
      client.println(".header {");
      client.println("  text-align: center;");
      client.println("  margin-bottom: 40px;");
      client.println("}");
      client.println("h1 {");
      client.println("  font-size: 28px;");
      client.println("  font-weight: 700;");
      client.println("  color: #111827;");
      client.println("  margin-bottom: 8px;");
      client.println("}");
      client.println(".subtitle {");
      client.println("  font-size: 14px;");
      client.println("  color: #6b7280;");
      client.println("  letter-spacing: 0.5px;");
      client.println("}");
      client.println(".battery-section {");
      client.println("  background: " + backgroundColor + ";");
      client.println("  border-left: 4px solid " + statusColor + ";");
      client.println("  border-radius: 12px;");
      client.println("  padding: 25px;");
      client.println("  margin-bottom: 30px;");
      client.println("  transition: all 0.3s ease;");
      client.println("}");
      client.println(".battery-percentage {");
      client.println("  display: flex;");
      client.println("  align-items: baseline;");
      client.println("  justify-content: center;");
      client.println("  margin-bottom: 20px;");
      client.println("}");
      client.println(".percentage-value {");
      client.println("  font-size: 56px;");
      client.println("  font-weight: 700;");
      client.println("  color: " + statusColor + ";");
      client.println("}");
      client.println(".percentage-symbol {");
      client.println("  font-size: 24px;");
      client.println("  color: " + statusColor + ";");
      client.println("  margin-left: 8px;");
      client.println("}");
      client.println(".battery-bar {");
      client.println("  width: 100%;");
      client.println("  height: 12px;");
      client.println("  background: #e5e7eb;");
      client.println("  border-radius: 10px;");
      client.println("  overflow: hidden;");
      client.println("  margin-bottom: 15px;");
      client.println("}");
      client.println(".battery-fill {");
      client.println("  height: 100%;");
      client.println("  background: " + statusColor + ";");
      client.println("  border-radius: 10px;");
      client.println("  transition: width 0.5s ease;");
      client.println("  width: " + String(batteryPercent) + "%;");
      client.println("}");
      client.println(".status-text {");
      client.println("  text-align: center;");
      client.println("  font-size: 14px;");
      client.println("  font-weight: 600;");
      client.println("  color: " + statusColor + ";");
      client.println("  text-transform: uppercase;");
      client.println("  letter-spacing: 1px;");
      client.println("}");
      client.println(".device-states {");
      client.println("  background: #f9fafb;");
      client.println("  border-radius: 12px;");
      client.println("  padding: 20px;");
      client.println("  margin-bottom: 25px;");
      client.println("}");
      client.println(".state-title {");
      client.println("  font-size: 12px;");
      client.println("  font-weight: 700;");
      client.println("  color: #6b7280;");
      client.println("  text-transform: uppercase;");
      client.println("  letter-spacing: 0.5px;");
      client.println("  margin-bottom: 12px;");
      client.println("}");
      client.println(".device-list {");
      client.println("  list-style: none;");
      client.println("}");
      client.println(".device-item {");
      client.println("  display: flex;");
      client.println("  align-items: center;");
      client.println("  padding: 10px 0;");
      client.println("  font-size: 14px;");
      client.println("  color: #374151;");
      client.println("  border-bottom: 1px solid #e5e7eb;");
      client.println("}");
      client.println(".device-item:last-child {");
      client.println("  border-bottom: none;");
      client.println("}");
      client.println(".device-icon {");
      client.println("  width: 24px;");
      client.println("  height: 24px;");
      client.println("  margin-right: 12px;");
      client.println("  background: " + statusColor + ";");
      client.println("  border-radius: 6px;");
      client.println("  display: flex;");
      client.println("  align-items: center;");
      client.println("  justify-content: center;");
      client.println("  color: white;");
      client.println("  font-size: 12px;");
      client.println("  font-weight: bold;");
      client.println("}");
      client.println(".refresh-info {");
      client.println("  text-align: center;");
      client.println("  font-size: 12px;");
      client.println("  color: #9ca3af;");
      client.println("  margin-top: 20px;");
      client.println("  padding-top: 20px;");
      client.println("  border-top: 1px solid #e5e7eb;");
      client.println("}");
      client.println("</style>");
      client.println("</head>");

      client.println("<body>");
      client.println("<div class='container'>");
      
      // Header
      client.println("<div class='header'>");
      client.println("<h1>⚡ Device Monitor</h1>");
      client.println("<div class='subtitle'>Smart Battery Status</div>");
      client.println("</div>");

      // Battery Section
      client.println("<div class='battery-section'>");
      client.println("<div class='battery-percentage'>");
      client.print("<div class='percentage-value'>");
      client.print(batteryPercent);
      client.println("</div>");
      client.println("<div class='percentage-symbol'>%</div>");
      client.println("</div>");
      client.println("<div class='battery-bar'>");
      client.println("<div class='battery-fill'></div>");
      client.println("</div>");
      client.print("<div class='status-text'>");
      client.print(statusText);
      client.println(" Battery</div>");
      client.println("</div>");

      // Device States
      client.println("<div class='device-states'>");
      client.println("<div class='state-title'>Active Devices</div>");
      client.println("<ul class='device-list'>");

      if (batteryPercent >= 70) {
        client.println("<li class='device-item'>");
        client.println("<div class='device-icon'>✓</div>");
        client.println("All Devices Active");
        client.println("</li>");
      } else if (batteryPercent >= 40) {
        client.println("<li class='device-item'>");
        client.println("<div class='device-icon'>⚠</div>");
        client.println("Buzzer");
        client.println("</li>");
        client.println("<li class='device-item'>");
        client.println("<div class='device-icon'>⚠</div>");
        client.println("Lamp");
        client.println("</li>");
      } else if (batteryPercent > 10) {
        client.println("<li class='device-item'>");
        client.println("<div class='device-icon'>!</div>");
        client.println("Lamp Only");
        client.println("</li>");
      } else {
        client.println("<li class='device-item'>");
        client.println("<div class='device-icon'>✕</div>");
        client.println("All Devices Off");
        client.println("</li>");
      }

      client.println("</ul>");
      client.println("</div>");

      // Refresh Info
      client.println("<div class='refresh-info'>");
      client.println("🔄 Auto-refreshing every 5 seconds");
      client.println("</div>");

      client.println("</div>");
      client.println("</body>");
      client.println("</html>");

      break;
    }
  }

  client.stop();
  Serial.println("Client Disconnected");
}
