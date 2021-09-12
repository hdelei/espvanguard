void LoadEndpoints() {
  server.on("/", []() {
    if (!server.authenticate(www_username, www_password)) {
      return server.requestAuthentication();
    }
    server.send(200, "application/json", "{\"response\":\"ok\"}");
  });

  server.begin();
  
  Serial.println();
  Serial.print("Open http://");
  Serial.print(WiFi.localIP());
  Serial.println("/ in your browser to see it working");
}
