
def broadcastAddress = Inet4Address.getByName("255.255.255.255")
def localAddress = Inet4Address.getByName("192.168.10.21")
DatagramSocket sendSocket = new DatagramSocket(12345, localAddress)
sendSocket.setBroadcast(true)

1.upto(10000000) {
    DatagramPacket dp = new DatagramPacket("ping;\0".getBytes(), 6, broadcastAddress, 6666);
    sendSocket.send(dp)
    Thread.sleep(1000)
    println("sent")
}



