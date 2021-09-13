byte noAuthCount = 0;

void getAuthorization()
{
  if (noAuthCount > 4)
  {
    Serial.println();
    Serial.print("Locked");

    server.send(423, "application/json", "{\"response\":\"Locked\"}");
    delay(30000);
    //return;
  }

  if (!server.authenticate(www_username, www_password))
  {
    noAuthCount++;
    if (noAuthCount == 254)
      noAuthCount = 5;

    Serial.println();
    Serial.print("NoAuthCount: " + String(noAuthCount));

    return server.requestAuthentication();
    //server.send(401, "application/json", "{\"response\":\"Unauthorized\"}");
    //return;
  }
  noAuthCount = 0;
  Serial.println();
  Serial.print("NoAuthCount: " + String(noAuthCount));
}

void handleStatus()
{
  if (server.method() != HTTP_POST)
    server.send(405, "application/json", "{\"status\":\"method not allowed\"}");

  getAuthorization();
  // if (!server.authenticate(www_username, www_password))
  //   server.send(401, "application/json", "{\"response\":\"Unauthorized\"}");

  server.send(200, "application/json", "{\"status\":\"armed\"}");
}

// void LoadEndpoints()
// {
//   server.on("/", []()
//             {
//               if (!server.authenticate(www_username, www_password))
//               {
//                 return server.requestAuthentication();
//               }
//               server.send(200, "application/json", "{\"response\":\"ok\"}");
//             });

//   server.begin();

//   Serial.println();
//   Serial.print("Open http://");
//   Serial.print(WiFi.localIP());
//   Serial.println("/ in your browser to see it working");
// }
