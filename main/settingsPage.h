#ifndef settingsPage_H
#define settingsPage_H

extern String settingsPage;

void settingsPageCreator (){ 
        settingsPage = String("<!DOCTYPE html>\n") +
                "<html>\n" +
                "<head>\n" +
                        "<title>WiFi Settings</title>\n" +
                "</head>\n" +
                "<body>\n" +
                "<h1>WiFi Settings</h1>" +
                "<form id=\"New Credentials\" onsubmit=\"settingsUpdate(); return false;\">\n" +
                "    <!-- SSID cred input -->\n" +
                "    <label for=\"ssid\">SSID:</label>\n" +
                "    <input type=\"text\" id=\"ssid\" name=\"ssid\" value=\"ssid\" >\n" +
                "    <br><br>\n" +
                "    <!-- Pass cred input -->\n" +
                "    <label for=\"pass\">Password:</label>\n" +
                "    <input type=\"text\" id=\"pass\" name=\"pass\" value=\"password\" >\n" +
                "    <br><br>\n" +
                "    <!-- Submit button -->\n" +
                "    <input type=\"submit\" value=\"Submit\">\n" +
                "</form>\n" +
                "  <script>\n" +
                "    function settingsUpdate() {\n" +
                "      // Получаем значения компонентов цвета\n" +
                "      var ssidValue = btoa(document.getElementById(\"ssid\").value);\n" +
                "      var passValue = btoa(document.getElementById(\"pass\").value);\n" +
                "      fetch(\"/settingsupdate?ssid=\" + ssidValue + \"&pass=\" + passValue);\n" +
                "    }\n" +
                "  </script>\n" +
                "</body>\n" +
                "</html>\n";
}

#endif
