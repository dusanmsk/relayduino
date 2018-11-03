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

    def relayInterval = 30

    def broadcastAddress = Inet4Address.getByName("255.255.255.255")
    def localAddress = Inet4Address.getByName("192.168.10.21")
    DatagramSocket sendSocket = new DatagramSocket(12345, localAddress)

    def main() {

        Thread pingThread = new Thread(new Runnable() {
            @Override
            void run() {
                while (true) {
                    send("ping;")
                    Thread.sleep(5000)
                }
            }
        })

        pingThread.start()

        while (true) {
            for (int i = 1; i <= 16; i++) {
                sendPort(i, 1)
                Thread.sleep(relayInterval)
                sendPort(i, 0)
                Thread.sleep(relayInterval)
                sendPort(i, 1)
                Thread.sleep(relayInterval)
                sendPort(i, 0)
                Thread.sleep(relayInterval)
                sendPort(i, 1)
                Thread.sleep(relayInterval*2)
                sendPort(i, 0)
                Thread.sleep(relayInterval*2)
            }
        }
    }

    def sendPort(port, value) {
        send("om0 b0 r${port} ${value};")
    }

    def send(String msg) {
        println msg
        DatagramPacket dp = new DatagramPacket(msg.bytes, msg.size(), broadcastAddress, 6666);
        sendSocket.send(dp)
    }
}

def m = new OutputMain()
m.main()
