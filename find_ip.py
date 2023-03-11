import subprocess
#cmd = 'arp -a | findstr "00:0e:c6:5b:65:ab"'

ip_0 = '00:0e:c6:73:c7:31'
ip_1 = '00:0e:c6:5b:65:ab'

#returned_output = subprocess.check_output((cmd),shell=True,stderr=subprocess.STDOUT)
#print(returned_output)
#parse=str(returned_output).split(' ',1)
#ip=parse[1].split(' ')
#print(ip[1])

network_ip = "172.21.16"
for host_ip in range(1,255):
    #print(["ping ",network_ip + "." + str(host_ip)],shell=True,stderr=subprocess.STDOUT)
    subprocess.run(["ping -c 2 " + network_ip + "." + str(host_ip)], shell=True, stderr=subprocess.STDOUT)

