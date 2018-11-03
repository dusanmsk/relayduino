import java.util.regex.Matcher
import java.util.regex.Pattern

// read packets sent by input boards and show statistics on stdout

class InputMain {

    /*
        masterId = int
        boardId = int
        values = [16]

     */
    def data = []

    def broadcastAddress = Inet4Address.getByName("192.168.10.55")//("255.255.255.255")
    def localAddress = Inet4Address.getByName("192.168.10.109")
    DatagramSocket sendSocket = new DatagramSocket(12345, localAddress)
    DatagramSocket recvSocket = new DatagramSocket(5555, InetAddress.getByName("0.0.0.0"))

    def send(String msg) {
        println msg
        DatagramPacket dp = new DatagramPacket(msg.bytes, msg.size(), broadcastAddress, 6666);
        sendSocket.send(dp)
    }


    def bufSize = 32768
    byte[] recvBuf = new byte[bufSize]
    DatagramPacket packet = new DatagramPacket(recvBuf, bufSize)

    Thread pingThread = new Thread(new Runnable() {
        @Override
        void run() {
            while (true) {
                send("ping")
                Thread.sleep(5000)
            }
        }
    })


    def main() {
        Pattern p = Pattern.compile("im(\\d+) b(\\d+) i(\\d+) (\\d+)")

        // run ping on background
        sendSocket.setBroadcast(true)
        pingThread.start()
        println "ping started"

        while (true) {
            recvSocket.receive(packet)
            String s = new String(recvBuf, 0, packet.length)
            if (s.contains("pong")) continue;
            // im0 b0 i12 1
            Matcher m = p.matcher(s)
            if (m.matches()) {
                def masterId = m.group(1).toInteger()
                def boardId = m.group(2).toInteger()
                def inputId = m.group(3).toInteger()
                def value = m.group(4).toInteger()
                def rec = data.find { i -> i.masterId == masterId && i.boardId == boardId }
                if (rec == null) {
                    rec = [masterId: masterId, boardId: boardId, values: [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0]]
                    data << rec
                }
                if (value == 1) {
                    def cnt = rec.values[inputId]
                    rec.values[inputId] = cnt + 1
                }

                printData()
            }


        }
    }

    def printData() {
        for (int masterId = 0; masterId < 9; masterId++) {
            for (int boardId = 0; boardId < 8; boardId++) {
                def rec = data.find { i -> i.masterId == masterId && i.boardId == boardId }
                if (rec != null) {
                    print "${masterId}  ${boardId}  "
                    for (int inputId = 1; inputId <= 16; inputId++) {
                        def value = rec.values[inputId]
                        if ( value == 0) { value = "-"}
                        print "${value} "
                    }
                    println ""
                }
            }
        }
        println "--------------------------\n"
    }
}

def m = new InputMain()
m.main()
