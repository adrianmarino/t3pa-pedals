import sys
import glob
import serial

class SerialPort:
    def __init__(self, port):
        self.serial_port = serial.Serial(port, 9600, timeout=2)

    def send(self, value):
        value = value.replace('\n', '')
        value = value.replace('\r', '')
        value = value.encode('utf-8')
        self.serial_port.write(value)

    def receive(self):
        result = ''
        value = self.serial_port.readline()
        while(len(value) >0):
            result += value.decode('ascii')
            value = self.serial_port.readline()
        return result
    
    def close(self):
        self.serial_port.close()
    
    @staticmethod
    def avaiable():
        """ Lists serial port names
    
            :raises EnvironmentError:
                On unsupported or unknown platforms
            :returns:
                A list of the serial ports available on the system
        """
        if sys.platform.startswith('win'):
            ports = ['COM%s' % (i + 1) for i in range(256)]
        elif sys.platform.startswith('linux') or sys.platform.startswith('cygwin'):
            # this excludes your current terminal "/dev/tty"
            ports = glob.glob('/dev/tty*')
        elif sys.platform.startswith('darwin'):
            ports = glob.glob('/dev/tty.*')
        else:
            raise EnvironmentError('Unsupported platform')
    
        result = []
        for port in ports:
            try:
                s = serial.Serial(port)
                s.close()
                result.append(port)
            except (OSError, serial.SerialException):
                pass
        return result