# ESP32C4--ArduinoIDE--UDP
两个esp32c4之间互相传递数据。传递方式是udp。  

### 实现功能：  
转动我的esp32上的电位器，能控制别人esp32上的灯。彼此可以互相控制，因为数据通过udp传递。

### 视频  
https://youtu.be/K930K2eVGZE  

### 两个人烧到板子里面的代码有什么不同  
IP互换，别的不变
板子一：  
![image](https://github.com/wenxiwei00/ESP32C4--ArduinoIDE--UDP/assets/114196821/067a7f00-29dd-4cec-932a-c483d30f866b)  
板子二：  
![image](https://github.com/wenxiwei00/ESP32C4--ArduinoIDE--UDP/assets/114196821/69722d5b-5d2f-4fbc-a2c4-68a1cdcc7f5c)  

### 参考资料  
代码里面会发现udp传数据的时候是通过string在传输，可参考ASCII码  
![image](https://github.com/wenxiwei00/ESP32C4--ArduinoIDE--UDP/assets/114196821/3edb87c2-31c1-43c3-bef7-3b1dba293d46)  

