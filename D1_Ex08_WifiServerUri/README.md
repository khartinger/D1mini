Server listens to Port 80 and answers to  
(1) request without uri: HTML-Website showing the clientIP  
(2) request /set like /set?x=3: count & show params x: 3 etc.  
(3) all other requests : error message

The website and all server functions a placed in header file D1_Ex08_WifiServerUri.h

Hardware: WeMos D1 mini

DON´T FORGET TO CHANGE *ssid AND *password (file  myWifiData.h or direct in D1_Ex07_HelloWebsite.h)
