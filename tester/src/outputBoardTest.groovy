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

class OutputMain {

    def broadcastAddress = Inet4Address.getByName("255.255.255.255")
    def localAddress = Inet4Address.getByName("192.168.2.108")
    DatagramSocket sendSocket = new DatagramSocket(12345, localAddress)

    def main() {

        Thread pingThread = new Thread(new Runnable() {
            @Override
            void run() {
                while (true) {
                    send("ping")
                    Thread.sleep(5000)
                }
            }
        })

        pingThread.start()

        while (true) {
            for (int i = 1; i <= 16; i++) {
                sendPort(i, 1)
                Thread.sleep(500)
                sendPort(i, 0)
                Thread.sleep(500)
                sendPort(i, 1)
                Thread.sleep(500)
                sendPort(i, 0)
                Thread.sleep(500)
                sendPort(i, 1)
                Thread.sleep(1000)
                sendPort(i, 0)
                Thread.sleep(1000)
            }
        }
    }

    def sendPort(port, value) {
        send("om4 b7 r${port} ${value}")
    }

    def send(String msg) {
        println msg
        DatagramPacket dp = new DatagramPacket(msg.bytes, msg.size(), broadcastAddress, 6666);
        sendSocket.send(dp)
    }
}

def m = new OutputMain()
m.main()