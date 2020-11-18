import http.server
import socketserver
import socket

# very poor python script

PORT = 8080
Handler = http.server.SimpleHTTPRequestHandler
ip = socket.gethostbyname(socket.gethostname())

with socketserver.TCPServer((ip, PORT), Handler) as httpd:
    print("link : http://%s:%s" % (ip, PORT))
    httpd.serve_forever()