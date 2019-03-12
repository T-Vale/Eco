void html_interface()
{
  // listen for incoming clients
  read_value();

  time_t tempo = now();

  int annos = year(tempo);
  int mensis = month(tempo);
  int diems = day(tempo);
  int horas = hour(tempo);
  int minutes = minute(tempo);
  int seconds = second(tempo);

  EthernetClient client = server.available();
  if (client)
  {
    //Serial.println("HTML Communication Started");
    boolean currentLineIsBlank = true;

    String receivedLine = "";
    String receivedPost = "";
    boolean thereIsAPost = false;

    boolean statusxml = false;
    boolean timeSet = false;
    boolean sensorAssign = false;
    boolean dataGraph = false;
    boolean defineAlarms = false;
    boolean rawData = false;
    boolean plotGraph = false;

    while (client.connected())
    {
      if (client.available())
      {
        char c = client.read();
        if (receivedLine.length() < LINELENGTH)
        {
          receivedLine = receivedLine + c;
        }

        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply

        if (c == '\n' && currentLineIsBlank)
        {
          while (client.available())
          {
            char d = client.read();
            if (receivedPost.length() < LINELENGTH)
            {
              receivedPost = receivedPost + d;
            }
            else
            {
              client.flush();
            }
          }
          if ((receivedPost.length() > 0) && thereIsAPost)
          {
            receivedPost += "&";
            boolean thepostisfine = false;

            htmlRequest_timeSetting(receivedPost, netEndChar);
            htmlRequest_delaySetting(receivedPost, netEndChar);
            htmlRequest_adcPost(receivedPost, netEndChar);
            htmlRequest_defineAlarms(receivedPost, netEndChar);
          }
          thereIsAPost = false;

          if(!statusxml)
          {
            // send a standard http response header
            client.println(F("HTTP/1.1 200 OK"));
            client.println(F("Content-Type: text/html"));
            client.println(F("Connection: close"));  // the connection will be closed after completion of the response
            client.println();
            client.println(F("<!DOCTYPE HTML>"));
            client.println(F("<html>"));
            client.println(F("<style>"));
  
            client.println(F("\t#rcorners {"));
            client.println(F("\t\tborder-radius: 15px 50px;"));
            client.println(F ("\t\tbackground: #000080;"));
            client.println(F("\t\tpadding: 25px 50px;"));
            client.println(F("\t\twidth: 65px;"));
            client.println(F("\t\theight: 25px;"));
            client.println(F("\t\tfont-family: verdana;"));
            client.println(F("\t\tfont-size: 35px;"));
            client.println(F("\t\ttext-shadow: 1% 1% #f2f2f2;"));
            client.println(F("\t\tcolor: white;"));
            client.println(F("\t}"));
  
            client.println(F("\t#titles {"));
            client.println(F("\t\tpadding: 0px 10px;"));
            client.println(F("\t\tfont-family: verdana;"));
            client.println(F("\t\tfont-size: 17px;"));
            client.println(F("\t\ttext-shadow: 1% 1% #f2f2f2;"));
            client.println(F("\t\tcolor: black;"));
            client.println(F("\t}"));
  
            client.println(F("\t#buttons {"));
            //client.println(F("\t\tpadding: 0px 50px;"));
            client.println(F("\t\twidth: 300px;"));
            client.println(F("\t\tfont-family: verdana;"));
            client.println(F("\t\tfont-size: 17px;"));
            client.println(F("\t\tdisplay: inline;"));
            client.println(F("\t}"));
  
            client.println(F("\t#fillin {"));
            client.println(F("\t\tpadding: 0px 10px;"));
            client.println(F("\t\tfont-family: verdana;"));
            client.println(F("\t\tfont-size: 10px;"));
            client.println(F("\t}"));
  
            client.println(F("\t#textbox {"));
            client.println(F("\t\tfont-family: verdana;"));
            client.println(F("\t\tfont-size: 10px;"));
            client.println(F("\t\twidth: 40px;"));
            client.println(F("\t\tdisplay: inline;"));
            client.println(F("\t}"));
  
            client.println(F("\t#hovertable {"));
            client.println(F("\t\tpadding: 0px 10px;"));
            client.println(F("\t\tborder-collapse: collapse;"));
            client.println(F("\t\twidth: 600px;"));
            client.println(F("\t\tfont-family: verdana;"));
            client.println(F("\t\tfont-size: 10px;"));
            client.println(F("\t}"));
  
            client.println(F("\t#hovertr:hover{background-color:#f5f5f5}"));
  
            client.println(F("\t#invisibletable {"));
            client.println(F("\t\tpadding: 0px 10px;"));
            client.println(F("\t\tborder-collapse: collapse;"));
            client.println(F("\t\twidth: 300px;"));
            client.println(F("\t\tfont-family: verdana;"));
            client.println(F("\t\tfont-size: 10px;"));
            client.println(F("\t}"));
  
            client.println(F("\tth, td {"));
            client.println(F("\t\tpadding: 8px 10px;"));
            client.println(F("\t\ttext-align: left;"));
            client.println(F("\t\tborder-bottom: 1px solid #ddd;"));
            client.println(F("\t}"));
  
            client.println(F("\ta {"));
            //client.println(F("\t\tpadding: 0px 50px;"));
            client.println(F("\t\ttext-decoration:none;"));
            //client.println(F("\t\tfont-family: verdana;"));
            //client.println(F("\t\tfont-size: 17px;"));
            client.println(F("\t\tdisplay: inline;"));
            client.println(F("\t}"));
  
            client.println(F("\tp {"));
            client.println(F("\t\tpadding: 0px 10px;"));
            client.println(F("\t\tfont-family: verdana;"));
            client.println(F("\t\tfont-size: 10px;"));
            client.println(F("\t\tcolor: black;"));
            client.println(F("\t}"));
  
            client.println(F("\tcode {"));
            client.println(F("\t\tpadding: 0px 10px;"));
            client.println(F("\t\tfont-size: 14px;"));
            client.println(F("\t\tcolor: black;"));
            client.println(F("\t}"));
  
            client.println(F("</style>"));
            client.print(F("<a href=\"http://"));
            client.print(ipAddress_[0]);
            client.print(F("."));
            client.print(ipAddress_[1]);
            client.print(F("."));
            client.print(ipAddress_[2]);
            client.print(F("."));
            client.print(ipAddress_[3]);
            client.println(F("\">"));
            client.println(F("<h3 id=\"rcorners\">"));
            client.println(F("\tEco"));
            client.println(F("</h3>"));
            client.println(F("</a>"));
            
            
            if (timeSet)
            {
              client.println(F("<h2 id=\"titles\">"));
              client.println(F("\tTime Settings"));
              client.println(F("</h2>"));
              client.println(F("<body>"));
              client.print(F("<form action=\"http://"));
              client.print(ipAddress_[0]);
              client.print(F("."));
              client.print(ipAddress_[1]);
              client.print(F("."));
              client.print(ipAddress_[2]);
              client.print(F("."));
              client.print(ipAddress_[3]);
              client.println(F("\" method=\"POST\" id=\"fillin\">"));
              client.println(F("\t<table id=\"invisibletable\">"));
              client.println(F("\t\t<tr>"));
              client.println(F("\t\t\t<td>Year</td>"));
              client.print(F("\t\t\t<td><input id=\"textbox\" type=\"number\" name=\"year\" value=\""));
              client.print(annos);
              client.println(F("\" min=\"1900\" max=\"5000\"></td>"));
              client.println(F("\t\t\t<td>Month</td>"));
              client.print(F("\t\t\t<td><input id=\"textbox\" type=\"number\" name=\"month\" value=\""));
              client.print(mensis);
              client.println(F("\" min=\"1\" max=\"12\"></td>"));
              client.println(F("\t\t\t<td>Day</td>"));
              client.print(F("\t\t\t<td><input id=\"textbox\" type=\"number\" name=\"day\" value=\""));
              client.print(diems);
              client.println(F("\" min=\"1\" max=\"31\"></td>"));
              client.println(F("\t\t</tr>"));
              client.println(F("\t\t<tr>"));
              client.println(F("\t\t\t<td>Hour</td>"));
              client.print(F("\t\t\t<td><input id=\"textbox\" type=\"number\" name=\"hour\" value=\""));
              client.print(horas);
              client.println(F("\" min=\"0\" max=\"23\"></td>"));
              client.println(F("\t\t\t<td>Minute</td>"));
              client.print(F("\t\t\t<td><input id=\"textbox\" type=\"number\" name=\"minute\" value=\""));
              client.print(minutes);
              client.println(F("\" min=\"0\" max=\"59\"></td>"));
              client.println(F("\t\t\t<td>Second</td>"));
              client.print(F("\t\t\t<td><input id=\"textbox\" type=\"number\" name=\"second\" value=\""));
              client.print(seconds);
              client.println(F("\" min=\"0\" max=\"59\"></td>"));
              client.println(F("\t\t</tr>"));
              client.println(F("\t</table>"));
              client.println(F("\t<br>"));
              client.println("\t<input type=\"submit\" value=\"Set time\" id=\"buttons\">");
              client.println("</form>");
              client.println(F("\t<br>"));
              client.print(F("<form action=\"http://"));
              client.print(ipAddress_[0]);
              client.print(F("."));
              client.print(ipAddress_[1]);
              client.print(F("."));
              client.print(ipAddress_[2]);
              client.print(F("."));
              client.print(ipAddress_[3]);
              client.println(F("\" method=\"POST\" id=\"fillin\">"));
              client.println(F("\t<table id=\"invisibletable\">"));
              client.println(F("\t\t<tr>"));
              client.println(F("\t\t\t<td>Time between readings (s)</td>"));
              client.print(F("\t\t\t<td><input id=\"textbox\" type=\"number\" name=\"delay\" value=\""));
              client.print(delayTime);
              client.println(F("\" min=\"60\" max=\"30000\"></td>"));
              client.println(F("\t\t</tr>"));
              client.println(F("\t</table>"));
              client.println(F("\t<br>"));
              client.println("\t<input type=\"submit\" value=\"Set delay\" id=\"buttons\">");
              client.println("</form>");
            }
            else if (sensorAssign)
            {
              client.println(F("<h2 id=\"titles\">"));
              client.println(F("\tSensor Setting"));
              client.println(F("</h2>"));
              client.println(F("<body>"));
              client.print(F("<form action=\"http://"));
              client.print(ipAddress_[0]);
              client.print(F("."));
              client.print(ipAddress_[1]);
              client.print(F("."));
              client.print(ipAddress_[2]);
              client.print(F("."));
              client.print(ipAddress_[3]);
              client.println(F("\" method=\"POST\" id=\"fillin\">"));
              client.println(F("\t<table id=\"invisibletable\">"));
              client.println(F("\t\t<tr>"));
              client.println(F("\t\t\t<th>ADC</th>"));
              client.println(F("\t\t\t<th>Assigned Sensor</th>"));
              client.println(F("\t\t</tr>"));
              for (int adc = 0; adc < MAXIMUMNUMBEROFADCS; adc++)
              {
                client.println(F("\t\t<tr>"));
                client.print(F("\t\t\t<td>"));
                client.print(adc);
                client.println(F("</td>"));
                client.println(F("\t\t\t<td>"));
                client.print(F("\t\t\t\t<select name=\"adc"));
                client.print(adc);
                client.println(F("\">"));
                for (int sensor = -1; sensor < sensorNumber; sensor++)
                {
                  client.print(F("\t\t\t\t<option "));
                  if (adcSensor_[adc] == sensor)
                  {
                    client.print(F("selected "));
                  }
                  client.print(F("value=\""));
                  client.print(sensor);
                  client.print(F("\">"));
                  if (sensor != -1)
                  {
                    client.print(sensorName_[sensor]);
                  }
                  else
                  {
                    client.print("n/a");
                  }
                  client.println(F("</option>"));
                }
                client.println(F("\t\t\t\t</select>"));
                client.println(F("\t\t\t</td>"));
                client.println(F("\t\t</tr>"));
              }
              client.println(F("\t</table>"));
              client.println(F("\t<br>"));
              client.println("\t<input type=\"submit\" value=\"Assign Sensors\" id=\"buttons\">");
              client.println("</form>");
            }
            else if (defineAlarms)
            {
              client.println(F("<h2 id=\"titles\">"));
              client.println(F("\tAlarm Settings"));
              client.println(F("</h2>"));
              client.println(F("<body>"));
              client.print(F("<form action=\"http://"));
              client.print(ipAddress_[0]);
              client.print(F("."));
              client.print(ipAddress_[1]);
              client.print(F("."));
              client.print(ipAddress_[2]);
              client.print(F("."));
              client.print(ipAddress_[3]);
              client.println(F("\" method=\"POST\" id=\"fillin\">"));
              client.println(F("\t<table id=\"invisibletable\">"));
              client.println(F("\t\t<tr>"));
              client.println(F("\t\t\t<th>ADC</th>"));
              client.println(F("\t\t\t<th>Status</th>"));
              client.println(F("\t\t\t<th>Minimum</th>"));
              client.println(F("\t\t\t<th>Maximum</th>"));
              client.println(F("\t\t\t<th>Hysteresis</th>"));
              client.println(F("\t\t</tr>"));
              for (int adc = 0; adc < MAXIMUMNUMBEROFADCS; adc++)
              {
                client.println(F("\t\t<tr>"));
                client.print(F("\t\t\t<td>"));
                client.print(adc);
                client.println(F("</td>"));
                client.println(F("\t\t\t<td>"));
                client.print(F("\t\t\t\t<select name=\"alarm"));
                client.print(adc);
                client.println(F("\">"));
                client.print(F("\t\t\t\t<option "));
                if (alarmStatus_[adc])
                {
                  client.print(F("selected "));
                }
                client.print(F("value=\"1\">"));
                client.print(F("On"));
                client.println(F("</option>"));
                client.print(F("\t\t\t\t<option "));
                if (!alarmStatus_[adc])
                {
                  client.print(F("selected "));
                }
                client.print(F("value=\"0\">"));
                client.print(F("Off"));
                client.println(F("</option>"));
                client.println(F("\t\t\t\t</select>"));
                client.println(F("\t\t\t</td>"));
                client.print(F("\t\t\t<td><input id=\"textbox\" type=\"number\" step=\"0.1\" name=\"alarmmin"));
                client.print(adc);
                client.print(F("\" value=\""));
                client.print(alarmMin_[adc]);
                client.println(F("\"</td>"));
                client.print(F("\t\t\t<td><input id=\"textbox\" type=\"number\" step=\"0.1\" name=\"alarmmax"));
                client.print(adc);
                client.print(F("\" value=\""));
                client.print(alarmMax_[adc]);
                client.println(F("\"</td>"));
                client.print(F("\t\t\t<td><input id=\"textbox\" type=\"number\" step=\"0.1\" name=\"alarmhys"));
                client.print(adc);
                client.print(F("\" value=\""));
                client.print(alarmHys_[adc]);
                client.println(F("\"</td>"));
                client.println(F("\t\t</tr>"));
              }
              client.println(F("\t</table>"));
              client.println(F("\t<br>"));
              client.println("\t<input type=\"submit\" value=\"Submit Values\" id=\"buttons\">");
              client.println("</form>");
            }
            else if (dataGraph)
            {
              client.println(F("<h2 id=\"titles\">"));
              client.println(F("\tData & Graphics"));
              client.println(F("</h2>"));
              client.println(F("<body>"));
  
              client.print(F("<form action=\"http://"));
              client.print(ipAddress_[0]);
              client.print(F("."));
              client.print(ipAddress_[1]);
              client.print(F("."));
              client.print(ipAddress_[2]);
              client.print(F("."));
              client.print(ipAddress_[3]);
              client.print("/plotgraph");
              client.println(F("\" method=\"GET\" id=\"fillin\">"));
              client.println(F("\t<table id=\"invisibletable\">"));
              client.println(F("\t\t<tr>"));
              client.print(F("\t\t\t<td>"));
              client.print("ADC");
              client.println(F("</td>"));
              client.println(F("\t\t\t<td>"));
              client.print(F("\t\t\t\t<select name=\"dadc\">"));
              for (int adc = 0; adc < MAXIMUMNUMBEROFADCS; adc++)
              {
                if (adcSensor_[adc] >= 0 && adcSensor_[adc] < MAXIMUMNUMBEROFSENSORS)
                {
                  client.print(F("\t\t\t\t<option "));
                  client.print(F("value=\""));
                  client.print(adc);
                  client.print(F("\">"));
                  client.print(adc);
                  client.println(F("</option>"));
                }
              }
              client.println(F("\t\t\t\t</select>"));
              client.println(F("\t\t\t</td>"));
              client.print(F("\t\t\t<td>"));
              client.print("Data Type");
              client.println(F("</td>"));
              client.println(F("\t\t\t<td>"));
              client.print(F("\t\t\t\t<select name=\"dtype\">"));
              client.print(F("\t\t\t\t<option value=\"0\">"));
              client.print(F("Graphic Plot"));
              client.println(F("</option>"));
              client.print(F("\t\t\t\t<option value=\"1\">"));
              client.print(F("Data Text"));
              client.println(F("</option>"));
              client.println(F("\t\t\t\t</select>"));
              client.println(F("\t\t\t</td>"));
              client.println(F("\t\t</tr>"));
              client.println(F("\t\t<tr>"));
              client.println(F("\t\t\t<td>Year</td>"));
              client.print(F("\t\t\t<td><input id=\"textbox\" type=\"number\" name=\"dyear\" value=\""));
              client.print(annos);
              client.println(F("\" min=\"1900\" max=\"5000\"></td>"));
              client.println(F("\t\t\t<td>Month</td>"));
              client.print(F("\t\t\t<td><input id=\"textbox\" type=\"number\" name=\"dmonth\" value=\""));
              client.print(mensis);
              client.println(F("\" min=\"1\" max=\"12\"></td>"));
              client.println(F("\t\t\t<td>Day</td>"));
              client.print(F("\t\t\t<td><input id=\"textbox\" type=\"number\" name=\"dday\" value=\""));
              client.print(diems);
              client.println(F("\" min=\"1\" max=\"31\"></td>"));
              client.println(F("\t\t</tr>"));
              client.println(F("\t</table>"));
              client.println(F("\t<br>"));
              client.println("\t<input type=\"submit\" value=\"Get Data\" id=\"buttons\">");
              client.println("</form>");
            }
            else if (plotGraph) //mudar nome para dataGraph
            {
              client.println(F("<h2 id=\"titles\">"));
              client.print(F("\tData - ADC "));
              client.println(dataGraphArray_[3]);
              client.println(F("<br>"));
              client.println(sensorName_[adcSensor_[dataGraphArray_[3]]]);
              client.println(" ");
              client.println(sensorType_[adcSensor_[dataGraphArray_[3]]]);
              client.println(" ");
              client.println(sensorUnit_[adcSensor_[dataGraphArray_[3]]]);
              client.println(F("<br>"));
              client.print(dataGraphArray_[0]);
              client.print("-");
              client.print(dataGraphArray_[1]);
              client.print("-");
              client.println(dataGraphArray_[2]);
              client.println(F("</h2>"));
              client.println(F("<body>"));
  
              String fileLoc = "/DATA/" + String(dataGraphArray_[0]) + "/" + String(dataGraphArray_[1]) + "/" + String(dataGraphArray_[2]) + ".TXT";
              File dataFile = SD.open(fileLoc);
              char ch;
              String line = "";
              String buff = "";
              String buff2 = "";
              long timeseconds = 0;
  
              if (dataFile)
              {
                if (dataGraphArray_[4] == 0)
                {
                  client.println(F("<canvas id=\"graphic\" width=\"500\" height=\"250\" style=\"display: inline;\">"));
                  client.println(F("Your browser does not support the HTML5 canvas tag.</canvas>"));
                  client.println(F("<p><b>Minimum value measured:</b></p>"));
                  client.println(F("<p id=\"mini\" style=\"display: inline;\"></p>"));
                  client.println(F("<p><b>Maximum value measured:</b></p>"));
                  client.println(F("<p id=\"maxi\" style=\"display: inline;\"></p>"));
  
                  client.println(F("<script>"));
                  client.println(F("\tvar w = document.getElementById(\"graphic\").offsetWidth;"));
  
                  client.println(F("\tvar d = document.getElementById(\"graphic\");"));
                  client.println(F("\tvar dL = d.getContext(\"2d\");"));
  
                  client.println(F("\tvar imagex = document.getElementById(\"graphic\").offsetWidth;"));
                  client.println(F("\tvar imagey = document.getElementById(\"graphic\").offsetHeight;"));
                  client.println(F("\tvar leftmargin = imagex * 0.1;"));
                  client.println(F("\tvar rightmargin = imagex * 0.04;"));
                  client.println(F("\tvar topmargin = imagey * 0.1;"));
                  client.println(F("\tvar bottommargin = imagey * 0.1;"));
                  client.println(F("\tvar gxmin = leftmargin;"));
                  client.println(F("\tvar gymin = topmargin;"));
                  client.println(F("\tvar gxmax = document.getElementById(\"graphic\").offsetWidth - rightmargin;"));
                  client.println(F("\tvar gymax = document.getElementById(\"graphic\").offsetHeight - bottommargin;"));
                  client.println(F("\tvar gxlength = gxmax - gxmin;"));
                  client.println(F("\tvar gylength = gymax - gymin;"));
  
                  client.println(F("\tvar traceLen = 4;"));
  
                  client.println(F("\tvar tmin = 0 * 3600;"));
                  client.println(F("\tvar tmax = 24 * 3600;"));
  
                  //client.println(F("\tvar tmed = tmax - tmin;"));
  
                  client.print(F("\tvar vmin = "));
                  client.print(sensorGraphMin_[adcSensor_[dataGraphArray_[3]]]);
                  client.println(F(";")); // AQUI
                  client.print(F("\tvar vmax = "));
                  client.print(sensorGraphMax_[adcSensor_[dataGraphArray_[3]]]);
                  client.println(F(";")); // AQUI
  
  
                  client.println(F("\tvar t = [];")); // AQUI
                  client.println(F("\tvar v = [];")); // AQUI
  
  
                  while (dataFile.available())
                  {
                    ch = dataFile.read();
                    line += ch;
  
                    if (ch == '\n')
                    {
                      client.print(F("\tt.push("));
                      parse_parameterReader(line, " ", buff, ":");
                      buff2 = buff + ":";
                      timeseconds = buff.toInt() * 3600;
                      parse_parameterReader(line, buff2, buff, ":");
                      buff2 += buff + ":";
                      timeseconds += buff.toInt() * 60;
                      parse_parameterReader(line, buff2, buff, "\t");
                      timeseconds += buff.toInt();
                      client.print(timeseconds);
                      buff2 = "";
                      timeseconds = 0;
                      client.println(F(");")); // AQUI
                      client.print(F("\tv.push("));
                      parse_adcValueFinder(line, buff, dataGraphArray_[3]);
                      client.print(buff.toInt() * sensorEqM_[adcSensor_[dataGraphArray_[3]]] + sensorEqB_[adcSensor_[dataGraphArray_[3]]]);
                      line = "";
                      client.println(F(");")); // AQUI
                    }
                  }
                  dataFile.close();
  
  
                  client.println(F("\tif(Math.min.apply(null, v) < vmin)"));
                  client.println(F("\t{"));
                  client.println(F("\t\tvmin = Math.min.apply(null, v);"));
                  client.println(F("\t}"));
  
                  client.println(F("\tif(Math.max.apply(null, v) > vmax)"));
                  client.println(F("\t{"));
                  client.println(F("\t\tvmax = Math.max.apply(null, v);"));
                  client.println(F("\t}"));
  
                  client.println(F("\tdocument.getElementById('maxi').innerHTML = Math.max.apply(null, v);"));
                  client.println(F("\tdocument.getElementById('mini').innerHTML = Math.min.apply(null, v);"));
  
                  client.println(F("\tdL.strokeStyle = \"#000080\";"));
                  client.println(F("\tdL.moveTo((((t[0] - tmin) * gxlength) / (tmax - tmin)) + gxmin, (gylength - (((v[0] - vmin) * gylength) / (vmax - vmin))) + gymin);"));
  
                  client.println(F("\tfor(i = 1; i < t.length; i++)"));
                  client.println(F("\t{"));
                  client.println(F("\t\tdL.lineTo((((t[i] - tmin) * gxlength) / (tmax - tmin)) + gxmin, (gylength - (((v[i] - vmin) * gylength) / (vmax - vmin))) + gymin);"));
                  client.println(F("\t}"));
  
                  client.println(F("\tdL.stroke();"));
                  client.println(F("\tdL.beginPath();"));
                  client.println(F("\tdL.strokeStyle = '#000000';"));
                  client.println(F("\tdL.moveTo(gxmin,gymin);")); //draws the axis
                  client.println(F("\tdL.lineTo(gxmin,gymax);"));
                  client.println(F("\tdL.lineTo(gxmax,gymax);"));
  
                  client.println(F("\tdL.font = \"10px Verdana\";"));
                  client.println(F("\tvar ytraces = 4;"));
  
                  client.println(F("\tvar text;"));
  
                  client.println(F("\tfor(i = 0; i <= ytraces; i++)"));
                  client.println(F("\t{"));
                  client.println(F("\t\ttext = vmax - i * (vmax - vmin)/ytraces;"));
                  client.println(F("\t\ttext = text.toFixed(2);"));
                  client.println(F("\t\tdL.fillText(text, gxmin - 10 * traceLen, i * gylength/ytraces + gymin);"));
                  client.println(F("\tdL.moveTo(gxmin - traceLen, i * gylength/ytraces + gymin);"));
                  client.println(F("\tdL.lineTo(gxmin + traceLen, i * gylength/ytraces + gymin);"));
                  client.println(F("\t}"));
  
                  client.println(F("\tdL.moveTo(gxmin - traceLen, gymax);"));
                  client.println(F("\tdL.lineTo(gxmin + traceLen, gymax);"));
  
                  client.println(F("\tvar xtraces = 24;"));
                  client.println(F("\tfor(i = 0; i <= xtraces; i++)"));
                  client.println(F("\t{"));
                  client.println(F("\t\ttext = (i * (tmax/3600 - tmin/3600)/xtraces);"));
                  client.println(F("\t\ttext = text.toFixed(0);"));
                  client.println(F("\t\tdL.fillText(text, i * gxlength/xtraces + gxmin, gymax + 3 * traceLen);"));
                  client.println(F("\t\tdL.moveTo(i * gxlength/xtraces + gxmin, gymax - traceLen);"));
                  client.println(F("\t\tdL.lineTo(i * gxlength/xtraces + gxmin, gymax + traceLen);"));
                  client.println(F("\t}"));
  
                  client.println(F("\tdL.stroke();"));
                  client.println(F("</script>"));
  
  
                }
                else if (dataGraphArray_[4] == 1)
                {
                  while (dataFile.available())
                  {
                    ch = dataFile.read();
                    line += ch;
  
                    if (ch == '\n')
                    {
                      client.print("<code>");
                      parse_parameterReader(line, " ", buff, ":");
                      client.print(buff);
                      client.print(":");
                      parse_parameterReader(line, ":", buff, ":");
                      buff2 = ":" + buff + ":";
                      client.print(buff);
                      client.print(":");
                      parse_parameterReader(line, buff2, buff, "\t");
                      client.print(buff);
                      buff2 = "";
                      client.print("  Value: ");
                      parse_adcValueFinder(line, buff, dataGraphArray_[3]);
                      client.print(buff.toInt() * sensorEqM_[adcSensor_[dataGraphArray_[3]]] + sensorEqB_[adcSensor_[dataGraphArray_[3]]]);
                      line = "";
                      client.println("</code><br>");
                    }
                  }
                  dataFile.close();
                }
              }
  
              // if the file isn't open, pop up an error:
              else
              {
                client.print("<p>Error opening: ");
                client.print(fileLoc);
                client.println("</p>");
              }
            }
            else if (rawData)
            {
            }
            else
            {
              client.println(F("<h2 id=\"titles\">"));
              client.println(F("\tAssigned Sensors"));
              client.println(F("</h2>"));
              client.println(F("<body>"));
              client.println(F("<table id=\"hovertable\">"));
              client.println(F("\t<tr>"));
              client.println(F("\t\t<th>ADC</th>"));
              client.println(F("\t\t<th>Name</th>"));
              client.println(F("\t\t<th>Type</th>"));
              client.println(F("\t\t<th>Units</th>"));
              client.println(F("\t\t<th>Value</th>"));
              client.println(F("\t\t<th>Min</th>"));
              client.println(F("\t\t<th>Max</th>"));
              client.println(F("\t\t<th>Hys</th>"));
              client.println(F("\t\t<th>Alarm</th>"));
              client.println(F("\t\t<th>Alarm Status</th>"));
              client.println(F("\t</tr>"));
  
              for (int adc = 0; adc < MAXIMUMNUMBEROFADCS; adc++)
              {
                client.println(F("\t<tr id=\"hovertr\">"));
                client.print(F("\t\t<td>"));
                client.print(adc);
                client.println(F("</td>"));
                if (adcSensor_[adc] >= 0 && adcSensor_[adc] <= MAXIMUMNUMBEROFSENSORS)
                {
                  client.print(F("\t\t<td>"));
                  client.print(sensorName_[adcSensor_[adc]]);
                  client.println(F("</td>"));
                  client.print(F("\t\t<td>"));
                  client.print(sensorType_[adcSensor_[adc]]);
                  client.println(F("</td>"));
                  client.print(F("\t\t<td>"));
                  client.print(sensorUnit_[adcSensor_[adc]]);
                  client.println(F("</td>"));
                  client.print(F("\t\t<td>"));
                  client.print(adcValue_[adc] * sensorEqM_[adcSensor_[adc]] + sensorEqB_[adcSensor_[adc]]);
                  client.println(F("</td>"));
                  client.print(F("\t\t<td>"));
                  client.print(alarmMin_[adc]);
                  client.println(F("</td>"));
                  client.print(F("\t\t<td>"));
                  client.print(alarmMax_[adc]);
                  client.println(F("</td>"));
                  client.print(F("\t\t<td>"));
                  client.print(alarmHys_[adc]);
                  client.println(F("</td>"));
                  client.print(F("\t\t<td>"));
                  if(alarmStatus_[adc])
                  {
                    client.print(F("Defined"));
                  }
                  else
                  {
                    client.print(F("Not defined"));
                  }
                  client.println(F("</td>"));
                  client.print(F("\t\t<td>"));
                  if(alarmOn_[adc])
                  {
                    client.print(F("Active"));
                  }
                  else
                  {
                    client.print(F("Not active"));
                  }
                  client.println(F("</td>"));
                  client.println(F("\t</tr>"));
                }
                else
                {
                  client.print(F("\t\t<td>"));
                  client.print(F("Not Assigned"));
                  client.println(F("</td>"));
                  client.print(F("\t\t<td>"));
                  client.print(F("-"));
                  client.println(F("</td>"));
                  client.print(F("\t\t<td>"));
                  client.print(F("-"));
                  client.println(F("</td>"));
                  client.print(F("\t\t<td>"));
                  client.print(F("-"));
                  client.println(F("</td>"));
                  client.print(F("\t\t<td>"));
                  client.print(F("-"));
                  client.println(F("</td>"));
                  client.print(F("\t\t<td>"));
                  client.print(F("-"));
                  client.println(F("</td>"));
                  client.print(F("\t\t<td>"));
                  client.print(F("-"));
                  client.println(F("</td>"));
                  client.print(F("\t\t<td>"));
                  client.print(F("-"));
                  client.println(F("</td>"));
                  client.print(F("\t\t<td>"));
                  client.print(F("-"));
                  client.println(F("</td>"));
                  client.println(F("\t</tr>"));
                }
              }
              client.println(F("</table>"));
              client.println(F("<br>"));
  
              client.print(F("<p><b>Time: </b>"));
              client.print(annos);
              client.print(F("-"));
              client.print(mensis);
              client.print(F("-"));
              client.print(diems);
              client.print(F(" "));
              client.print(horas);
              client.print(F(":"));
              client.print(minutes);
              client.print(F(":"));
              client.print(seconds);
              client.println(F("</p>"));
  
              client.print(F("<p><b>Time between readings: </b>"));
              client.print(delayTime);
              client.print(F(" s"));
              client.println(F("</p>"));
  
              client.println(F("<br>"));
              client.print(F("<a href=\"http://"));
              client.print(ipAddress_[0]);
              client.print(F("."));
              client.print(ipAddress_[1]);
              client.print(F("."));
              client.print(ipAddress_[2]);
              client.print(F("."));
              client.print(ipAddress_[3]);
              client.println(F("/settime\"><input type=\"submit\" value=\"Time Settings\" id=\"buttons\"></a>"));
  
              client.print(F("<a href=\"http://"));
              client.print(ipAddress_[0]);
              client.print(F("."));
              client.print(ipAddress_[1]);
              client.print(F("."));
              client.print(ipAddress_[2]);
              client.print(F("."));
              client.print(ipAddress_[3]);
              client.println(F("/assignsensor\"><input type=\"submit\" value=\"Assign Sensors\" id=\"buttons\"></a>"));
  
              client.println(F("<br>"));
              client.print(F("<a href=\"http://"));
              client.print(ipAddress_[0]);
              client.print(F("."));
              client.print(ipAddress_[1]);
              client.print(F("."));
              client.print(ipAddress_[2]);
              client.print(F("."));
              client.print(ipAddress_[3]);
              client.println(F("/datagraph\"><input type=\"submit\" value=\"Data & Graphics\" id=\"buttons\"></a>"));

              client.print(F("<a href=\"http://"));
              client.print(ipAddress_[0]);
              client.print(F("."));
              client.print(ipAddress_[1]);
              client.print(F("."));
              client.print(ipAddress_[2]);
              client.print(F("."));
              client.print(ipAddress_[3]);
              client.println(F("/definealarms\"><input type=\"submit\" value=\"Define Alarms\" id=\"buttons\"></a>"));
  
              /*client.print(F("<a href=\"http://"));
              client.print(ipAddress_[0]);
              client.print(F("."));
              client.print(ipAddress_[1]);
              client.print(F("."));
              client.print(ipAddress_[2]);
              client.print(F("."));
              client.print(ipAddress_[3]);
              client.println(F("/rawdata\"><input type=\"submit\" value=\"Raw Data\" id=\"buttons\"></a>"));*/
            }
            client.println(F("</body>"));
            client.println("</html>");
          }
          else
          {
            client.println(F("HTTP/1.1 200 OK"));
            client.println(F("Content-Type: text/xml"));
            client.println(F("Connection: close"));  // the connection will be closed after completion of the response
            client.println();
            client.println(F("<?xml version=\"1.0\" encoding=\"windows-1252\"?>"));
            client.println(F("<Equipment>"));
            client.print(F("<Device>"));
            client.print(myNameIs);
            client.println(F("</Device>"));
            client.print(F("<ID>"));
            client.print(macAddress_[0], HEX);
            client.print(":");
            client.print(macAddress_[1], HEX);
            client.print(":");
            client.print(macAddress_[2], HEX);
            client.print(":");
            client.print(macAddress_[3], HEX);
            client.print(":");
            client.print(macAddress_[4], HEX);
            client.print(":");
            client.print(macAddress_[5], HEX);
            client.println(F("</ID>"));
            client.print(F("<FW>"));
            client.print(myFWIs);
            client.println(F("</FW>"));
            for(int adcnum = 0; adcnum < MAXIMUMNUMBEROFADCS; adcnum++)
            {
              client.print(F("<ADC"));
              client.print(adcnum);
              client.println(F(">"));
              if(adcSensor_[adcnum] != -1)
              {
                client.print(F("<Value>"));
                client.print(adcValue_[adcnum] * sensorEqM_[adcSensor_[adcnum]] + sensorEqB_[adcSensor_[adcnum]]);
                client.println(F("</Value>"));
                client.print(F("<Unit>"));
                client.print(sensorUnit_[adcSensor_[adcnum]]);
                client.println(F("</Unit>"));
                client.print(F("<Type>"));
                client.print(sensorType_[adcSensor_[adcnum]]);
                client.println(F("</Type>"));
                client.print(F("<Name>"));
                client.print(sensorName_[adcSensor_[adcnum]]);
                client.println(F("</Name>"));
              }
              else
              {
                client.print(F("<Value>-1</Value>"));
                client.print(F("<Unit>na</Unit>"));
                client.print(F("<Type>na</Type>"));
                client.print(F("<Name>na</Name>"));
              }
              client.print(F("</ADC"));
              client.print(adcnum);
              client.println(F(">"));
            }          
            client.println(F("</Equipment>"));
          }
          break;
        }

        if (c == '\n')
        {
          // you're starting a new line
          currentLineIsBlank = true;
          String buffLine = "";

          if (parse_parameterReader(receivedLine, "GET /", buffLine, " HTTP"))
          {
            if ((buffLine.length() > 0))
            {
              statusxml = (buffLine == "status.xml");
              timeSet = (buffLine == "settime");
              sensorAssign = (buffLine == "assignsensor");
              dataGraph = (buffLine == "datagraph");
              rawData = (buffLine == "rawdata");
              defineAlarms = (buffLine == "definealarms");
              if(buffLine.indexOf("plotgraph") >= 0)
              {
                plotGraph = htmlRequest_plotGraph(buffLine + netEndChar, netEndChar);
              }
            }

          }
          else if (parse_parameterReader(receivedLine, "POST /", buffLine, " HTTP"))
          {
            thereIsAPost = true;
          }
          receivedLine = "";
        }

        else if (c != '\r')
        {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
  }
}



