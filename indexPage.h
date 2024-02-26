#ifndef indexPage_H
#define indexPage_H

extern String mainPage;

void indexCreator (){
        mainPage = String("<!DOCTYPE html>\n") +
                "<html>\n" +
                "<head>\n" +
                "  <title>Control Panel</title>\n" +
                "</head>\n" +
                "<body>\n" +
                "  <h1>Control Panel</h1>\n" +
                "  <!-- Brightness slider -->\n" +
                "  <label for=\"brightness\">Brightness:</label>\n" +
                "  <input type=\"range\" id=\"brightness\" name=\"brightness\" min=\"0\" max=\"100\" value=${ledBright} oninput=\"updateBrightness(this.value)\">\n" +
                "  <br><br>\n" +
                "  <!-- Delay slider -->\n" +
                "  <label for=\"delay\">Delay:</label>\n" +
                "  <input type=\"range\" id=\"delay\" name=\"delay\" min=\"0\" max=\"100\" value=${ledDelay} oninput=\"updateDelay(this.value)\">\n" +
                "  <br><br>\n" +
                "  <!-- Finished toggle -->\n" +
                "  <label for=\"finished\">Finished:</label>\n" +
                "  ${finished}\n" +
                "  <br><br>\n" +
                "  <!-- Форма для ввода цветов -->\n" +
                "  <form id=\"colorForm\" onsubmit=\"sendColor(); return false;\">\n" +
                "    <!-- Red color input -->\n" +
                "    <label for=\"red\">Red:</label>\n" +
                "    <input type=\"number\" id=\"red\" name=\"red\" min=\"0\" max=\"255\" value=${int_R} >\n" +
                "    <br><br>\n" +
                "    <!-- Green color input -->\n" +
                "    <label for=\"green\">Green:</label>\n" +
                "    <input type=\"number\" id=\"green\" name=\"green\" min=\"0\" max=\"255\" value=${int_G} >\n" +
                "    <br><br>\n" +
                "    <!-- Blue color input -->\n" +
                "    <label for=\"blue\">Blue:</label>\n" +
                "    <input type=\"number\" id=\"blue\" name=\"blue\" min=\"0\" max=\"255\" value=${int_B} >\n" +
                "    <br><br>\n" +
                "    <!-- Submit button -->\n" +
                "    <input type=\"submit\" value=\"Submit\">\n" +
                "  </form>\n" +
                "  <!-- Lightning type selection -->\n" +
                "  <label for=\"lightning-type\">Lightning Type:</label>\n" +
                "  <select id=\"lightning-type\" name=\"lightning-type\" onchange=\"updateLightningType(this.value)\">\n" +
                "    <option value=\"static\">None</option>\n" +
                "    <option value=\"static\">Static</option>\n" +
                "    <option value=\"weelcolour\">Weel Colour</option>\n" +
                "    <option value=\"weelcolourreverse\">Weel Colour Reverse</option>\n" +
                "    <option value=\"random\">Random</option>\n" +
                "    <option value=\"weelcolourpinkblue\">Weel Colour Pink Blue</option>\n" +
                "  </select>\n" +
                "  <br><br>\n" +
                "  <script>\n" +
                "    function updateBrightness(value) {\n" +
                "      // Send brightness value to Arduino\n" +
                "      fetch(\"/update?brightness=\" + value);\n" +
                "    }\n" +
                "    function updateDelay(value) {\n" +
                "      // Send delay value to Arduino\n" +
                "      fetch(\"/update?delay=\" + value);\n" +
                "    }\n" +
                "    function updateFinish(checked) {\n" +
                "      // Send cancel value to Arduino\n" +
                "      fetch(\"/update?finished=\" + (checked ? \"1\" : \"0\"))\n" +
                "      setTimeout(function() {\n" +
                "        location.reload();\n" +
                "      }, 200);\n" +
                "    }\n" +
                "    function sendColor() {\n" +
                "      // Получаем значения компонентов цвета\n" +
                "      var redValue = document.getElementById(\"red\").value;\n" +
                "      var greenValue = document.getElementById(\"green\").value;\n" +
                "      var blueValue = document.getElementById(\"blue\").value;\n" +
                "      fetch(\"/update?colour&red=\" + redValue + \"&green=\" + greenValue + \"&blue=\" + blueValue);\n" +
                "    }\n" +
                "    function updateLightningType(value) {\n" +
                "      // Send lightning type value to Arduino\n" +
                "      fetch(\"/update?type=\" + value)\n" +
                "      setTimeout(function() {\n" +
                "        location.reload();\n" +
                "      }, 200);\n" +
                "    }\n" +
                "  </script>\n" +
                "</body>\n" +
                "</html>\n";
}

#endif