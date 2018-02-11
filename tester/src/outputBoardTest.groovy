/*

cyklicky pozapina a cyklicky rozopina vystupy
m0 b0 i1 1
...
m0 b0 i16 1
ping
m0 b0 i1 0
...
m0 b0 i16 0
ping
*/

class Main {
    DatagramSocket socket = new DatagramSocket(6666, InetAddress.getByName("0.0.0.0"))
    def broadcastAddress = Inet4Address.getByName("255.255.255.255")
    def main() {
        socket.setBroadcast(true)
        while (true) {
            for (int i = 1; i <= 16; i++) {
                sendPort(i, 1)
                Thread.sleep(1000)
            }
            send("ping")
            for (int i = 1; i <= 16; i++) {
                sendPort(i, 0)
                Thread.sleep(1000)
            }
            send("ping")
        }
    }

    def sendPort(port, value) {
        send("m0 b0 i${port} ${value}")
    }

    def send(String msg) {
        DatagramPacket dp = new DatagramPacket(msg.bytes, msg.size(), broadcastAddress, 6666);
        socket.send(dp)
        println msg
    }
}

def m = new InputMain()
m.main()