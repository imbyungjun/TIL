#네트워크



##1. 기본개념
\- Network edge  
&nbsp;&nbsp;&nbsp;&nbsp;End systems(hosts)  
&nbsp;&nbsp;&nbsp;&nbsp;Client / Server model  
&nbsp;&nbsp;&nbsp;&nbsp;Peer-to-peer model  
\- Network core  
&nbsp;&nbsp;&nbsp;&nbsp;라우터들간의 연결망

###1) Circuit switching    고정bps
\- Circuit을 통해서 정보전달  
\- 두개의 end system이 상호 약속하에 직접 연결되는것.  
\- set up 과정이 필요하고 traffic과 관계없이 일정한 서비스 제공가능  
\- Frequency division (FDM)  
\- Time division (TDM)  

###2) Packet switching    동적bps
\- Data stream을 Packets로 나누어 정보전달  
\- 각각의 packets는 bandwidth 전체를 사용. (Resources 공유)  
       
#####Circuit switching vs Packet switching
\- Packet switching이 resource 공유, 간단함, 사전연결 x라서 좋음.  
\- Congestion 발생가능 (delay, loss 발생가능)    
    =>    보완을 위해선 Reliable transfer, Congestion control 필요    

#####Throughput
Sender / Receiver 간에 bits가 전달되는데 걸린 시간 비율 (bits / time)  
전체 throughput은 가장 작은 throughput인 Bottlenect에 맞추어진다.


##2. Network OSI 7 Layers
\- Application layer  
\- Presentation layer
\- Session layer
\- Transport layer
\- Network layer
\- Link layer
\- Physical layer

###2.1 Application Layer
1) Client - Server  

	Server : always on host
            고정 IP
            Server farms for scaling
    Client : 서버와 소통
            간헐적 연결
            동적 IP
            Client간에는 직접 통신하지 않음


2) P2P (Peer to Peer)

    no always on server
    임의의 end system들간 직접 통신
    Peer들의 간헐적 연결과 동적IP
    Highly scalable but difficult to manage

3) Hybrid  
    
    Client - Server와 P2P의 혼용
    ex) Skype

##2.2 Transport Layer  
sender side : app message를 segments로 나누어 network layer에 전달  
receiver side : segments를 다시 message로 조립하여 appl layer에 전달  

각각의 Datagram(Network layer 정보단위)은 source IP, destination IP를 갖음.  
각각의 Segmentation( )은 source / destination port #를 갖는다.  
IP address + Port #으로 목표 socket에 접근.   

1) UDP  
    Connectionless    (delay x)  
    No connection state  
    No congestion control  
    Destination = Dest IP addr + Dest Port #    

* UDP segment format

| Src Port # | Dest Port # |
|:---------:|:-----------:|
| Length     | Checksum  |
|| Application Data (message)|



1) TCP  
	Connection oriented    
	Destination = Src IP + Src Port # + Dest IP + Dest Port #    
 
* TCP segment format

|       
##2.3 Network Layer

##2.4 Link Layer

##2.5 Physical Layer














