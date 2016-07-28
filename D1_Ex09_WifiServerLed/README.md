Server listens to Port 80 and answers to  
(1) request /?led=on or /?led=0ff: switch blue LED (D4=GPIO2) on or off  
(2) all other requests: error message  

The website and all server functions a placed in header file D1_Ex09_WifiServerLed.h

Hardware: WeMos D1 mini

DON´T FORGET TO CHANGE *ssid AND *password (file  myWifiData.h or direct in D1_Ex07_HelloWebsite.h)
