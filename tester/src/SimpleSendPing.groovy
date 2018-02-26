
def broadcastAddress = Inet4Address.getByName("255.255.255.255")
def localAddress = Inet4Address.getByName("192.168.2.108")
DatagramSocket sendSocket = new DatagramSocket(12345, localAddress)
sendSocket.setBroadcast(true)

1.upto(10) {
    DatagramPacket dp = new DatagramPacket("abcd\0".getBytes(), 5, broadcastAddress, 6666);
    sendSocket.send(dp)
    Thread.sleep(1000)
    println("sent")
}



